/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2016 Furrtek
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __UI_MICTX_H__
#define __UI_MICTX_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_receiver.hpp"
#include "transmitter_model.hpp"
#include "tone_key.hpp"
#include "message.hpp"
#include "receiver_model.hpp"

namespace ui {

class MicTXView : public View {
public:
	MicTXView(NavigationView& nav);
	~MicTXView();

	MicTXView(const MicTXView&) = delete;
	MicTXView(MicTXView&&) = delete;
	MicTXView& operator=(const MicTXView&) = delete;
	MicTXView& operator=(MicTXView&&) = delete;
	
	void focus() override;
	
	// PTT: Enable through KeyEvent (only works with presses), disable by polling :(
	bool on_key(const KeyEvent key) {
		if ((key == KeyEvent::Right) && (!va_enabled)) {
			set_tx(true);
			return true;
		} else
			return false;
	};
	
	std::string title() const override { return "Mic TX RX"; };

private:
	static constexpr uint32_t sampling_rate = 1536000U;
	static constexpr uint32_t lcd_frame_duration = (256 * 1000UL) / 60;	// 1 frame @ 60fps in ms .8 fixed point  /60
	
	void update_vumeter();
	void do_timing();
	void set_tx(bool enable);
	void on_tuning_frequency_changed(rf::Frequency f);
	void on_tx_progress(const bool done);
	void configure_baseband();

	void rxaudio(bool is_on);
	void on_headphone_volume_changed(int32_t v);
	
	bool transmitting { false };
	bool va_enabled { false };
	bool rogerbeep_enabled { false };
	bool rx_enabled { false };
	uint32_t tone_key_index { };
	float mic_gain { 1.0 };
	uint32_t audio_level { 0 };
	uint32_t va_level { };
	uint32_t attack_ms { };
	uint32_t decay_ms { };
	uint32_t attack_timer { 0 };
	uint32_t decay_timer { 0 };
	
	Labels labels {
		{ { 3 * 8, 1 * 8 }, "MIC. GAIN:", Color::light_grey() },
		{ { 3 * 8, 3 * 8 }, "FREQUENCY:", Color::light_grey() },
		{ { 3 * 8, 5 * 8 }, "BANDWIDTH:   kHz", Color::light_grey() },
		{ { 7 * 8, 11 * 8 }, "LEVEL:   /255", Color::light_grey() },
		{ { 6 * 8, 13 * 8 }, "ATTACK:   ms", Color::light_grey() },
		{ { 7 * 8, 15 * 8 }, "DECAY:    ms", Color::light_grey() },
		{ { 4 * 8, 18 * 8 }, "TONE KEY:", Color::light_grey() },
		{ { 9 * 8, 30 * 8 }, "VOL:", Color::light_grey() },
		{ { 5 * 8, 32 * 8 }, "SQUELCH:", Color::light_grey() }
	};
	
	VuMeter vumeter {
		{ 0 * 8, 1 * 8, 2 * 8, 33 * 8 },
		12,
		true
	};
	
	OptionsField options_gain {
		{ 13 * 8, 1 * 8 },
		4,
		{
			{ "x0.5", 5 },
			{ "x1.0", 10 },
			{ "x1.5", 15 },
			{ "x2.0", 20 }
		}
	};
	
	FrequencyField field_frequency {
		{ 13 * 8, 3 * 8 },
	};
	NumberField field_bw {
		{ 13 * 8, 5 * 8 },
		3,
		{ 0, 150 },
		1,
		' '
	};
	
	Checkbox check_va {
		{ 3 * 8, (9 * 8) - 4 },
		7,
		"Voice activation",
		false
	};
	
	NumberField field_va_level {
		{ 13 * 8, 11 * 8 },
		3,
		{ 0, 255 },
		2,
		' '
	};
	NumberField field_va_attack {
		{ 13 * 8, 13 * 8 },
		3,
		{ 0, 999 },
		20,
		' '
	};
	NumberField field_va_decay {
		{ 13 * 8, 15 * 8 },
		4,
		{ 0, 9999 },
		100,
		' '
	};
	
	OptionsField options_tone_key {
		{ 10 * 8, 20 * 8 },
		23,
		{ }
	};

	Checkbox check_rogerbeep {
		{ 3 * 8, 23 * 8 },
		10,
		"Roger beep",
		false
	};

	Checkbox check_rxactive {
		{ 3 * 8, (27 * 8) + 4 },
		8,
		"RX audio listening",
		false
	};

	NumberField field_volume {
		{ 13 * 8, 30 * 8 },
		2,
		{ 0, 99 },
		1,
		' ',
	};
	
	NumberField field_squelch {
		{ 13 * 8, 32 * 8 },
		2,
		{ 0, 99 },
		1,
		' ',
	};

	Text text_ptt {
		{ 7 * 8, 35 * 8, 16 * 8, 16 },
		"PTT: RIGHT BUTTON"
	};


	MessageHandlerRegistration message_handler_lcd_sync {
		Message::ID::DisplayFrameSync,
		[this](const Message* const) {
			this->do_timing();
			this->update_vumeter();
		}
	};
	
	MessageHandlerRegistration message_handler_audio_level {
		Message::ID::AudioLevelReport,
		[this](const Message* const p) {
			const auto message = static_cast<const AudioLevelReportMessage*>(p);
			this->audio_level = message->value;
		}
	};
	
	MessageHandlerRegistration message_handler_tx_progress {
		Message::ID::TXProgress,
		[this](const Message* const p) {
			const auto message = *reinterpret_cast<const TXProgressMessage*>(p);
			this->on_tx_progress(message.done);
		}
	};
};

} /* namespace ui */

#endif/*__UI_MICTX_H__*/
