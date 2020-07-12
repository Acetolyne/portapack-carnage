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

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_font_fixed_8x16.hpp"
#include "ui_navigation.hpp"
#include "ui_tabview.hpp"
#include "transmitter_model.hpp"
#include "message.hpp"

using namespace jammer;

namespace ui {

class SubView : public View {
public:
	SubView(NavigationView& nav);
	
	void focus() override;
	void paint(Painter&) override;
	
	jammer_range_t frequency_range { false, 0, 0 };
	
private:
	void update_start(rf::Frequency f);
	void update_stop(rf::Frequency f);
	void update_center(rf::Frequency f);
	void update_width(uint32_t w);
	
	uint32_t width { };
	rf::Frequency center { };

	static constexpr Style style_info {
		.font = font::fixed_8x16,
		.background = Color::black(),
		.foreground = Color::grey(),
	};
	
	Labels labels {
		{ { 2 * 8, 9 * 8 + 4 }, "Start", Color::light_grey() },
		{ { 23 * 8, 9 * 8 + 4 }, "Stop", Color::light_grey() },
		{ { 12 * 8, 6 * 8 }, "Center", Color::light_grey() },
		{ { 12 * 8 + 4, 14 * 8 }, "Width", Color::light_grey() }
	};
	
	Checkbox check_enabled {
		{ 1 * 8, 4 },
		12,
		"Enable range"
	};
	
	Button button_load_range {
		{ 18 * 8, 4, 12 * 8, 24 },
		"Load range"
	};
	
	Button button_start {
		{ 0 * 8, 6 * 16, 11 * 8, 28 },
		""
	};
	Button button_stop {
		{ 19 * 8, 6 * 16, 11 * 8, 28 },
		""
	};
	Button button_center {
		{ 76, 4 * 16, 11 * 8, 28 },
		""
	};
	Button button_width {
		{ 76, 8 * 16, 11 * 8, 28 },
		""
	};
};

class TestUIView : public View {
public:
	TestUIView(NavigationView& nav);
	~TestUIView();
	
	TestUIView(const TestUIView&) = delete;
	TestUIView(TestUIView&&) = delete;
	TestUIView& operator=(const TestUIView&) = delete;
	TestUIView& operator=(TestUIView&&) = delete;
	
	void focus() override;
	
	std::string title() const override { return "Jammer"; };
	
private:
	NavigationView& nav_;
	
	void start_tx();
	void stop_tx();
	void set_jammer_channel(uint32_t i, uint32_t width, uint64_t center, uint32_t duration);
	void on_retune(const rf::Frequency freq, const uint32_t range);
	
	JammerChannel * jammer_channels = (JammerChannel*)shared_memory.bb_data.data;
	bool jamming { false };
	
	static constexpr Style style_val {
		.font = font::fixed_8x16,
		.background = Color::black(),
		.foreground = Color::green(),
	};
	static constexpr Style style_cancel {
		.font = font::fixed_8x16,
		.background = Color::black(),
		.foreground = Color::red(),
	};
	
	SubView view_range_a { nav_ };
	SubView view_range_b { nav_ };
	SubView view_range_c { nav_ };
	
	std::array<SubView*, 3> range_views { { &view_range_a, &view_range_b, &view_range_c } };
	
	TabView tab_view {
		{ "Range 1", Color::white(), range_views[0] },
		{ "Range 2", Color::white(), range_views[1] },
		{ "Range 3", Color::white(), range_views[2] },
	};
	
	Labels labels {
		{ { 3 * 8, 12 * 16 }, "Type:", Color::light_grey() },
		{ { 2 * 8, 13 * 16 }, "Speed:", Color::light_grey() },
		{ { 5 * 8, 14 * 16 }, "Hop:", Color::light_grey() }
	};
	
	OptionsField options_type {
		{ 9 * 8, 12 * 16 },
		8,
		{
			{ "Rand FSK", 0 },
			{ "FM tone", 1 },
			{ "CW sweep", 2 },
			{ "Rand CW", 3 },
		}
	};
	
	Text text_range_number {
		{ 22 * 8, 12 * 16, 2 * 8, 16 },
		"--"
	};
	Text text_range_total {
		{ 24 * 8, 12 * 16, 3 * 8, 16 },
		"/--"
	};
	
	OptionsField options_speed {
		{ 9 * 8, 13 * 16 },
		6,
		{
			{ "10Hz  ", 10 },
			{ "100Hz ", 100 },
			{ "1kHz  ", 1000 },
			{ "10kHz ", 10000 },
			{ "100kHz", 100000 }
		}
	};
	
	OptionsField options_hop {
		{ 9 * 8, 14 * 16 },
		5,
		{
			{ "10ms ", 1 },
			{ "50ms ", 5 },
			{ "100ms", 10 },
			{ "1s   ", 100 },
			{ "2s   ", 200 },
			{ "5s   ", 500 },
			{ "10s  ", 1000 }
		}
	};
	
	Button button_transmit {
		{ 9 * 8, 16 * 16, 96, 48 },
		"START"
	};
	
	MessageHandlerRegistration message_handler_retune {
		Message::ID::Retune,
		[this](Message* const p) {
			const auto message = static_cast<const RetuneMessage*>(p);
			this->on_retune(message->freq, message->range);
		}
	};
};

} /* namespace ui */
