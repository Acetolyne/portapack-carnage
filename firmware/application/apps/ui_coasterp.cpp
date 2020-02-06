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

#include "ui_coasterp.hpp"

#include "baseband_api.hpp"
#include "portapack_persistent_memory.hpp"

#include <cstring>
#include <stdio.h>
#include <bitset>
#include "string_format.hpp"
#include <cctype>

//@todo on options_action change check state and if program then disable scan buttons
//@todo on check scan boxes disable tied select field
//@todo possibly add function to select number for number field if there is a UI for this already besides the freq UI.
//@todo create a function to lowercase hex values.

using namespace portapack;

namespace ui {

std::vector<std::string> Split(const std::string& str)
{
   std::vector<std::string> ret;
   int num = str.length() / 2;
   for (auto i = 0; i < str.length() / 2; i++)
   {
        ret.push_back(str.substr(i * 2, 2));
   }

   // If there are leftover characters, create a shorter item at the end.
   if (str.length() % 2 != 0)
   {
        ret.push_back(str.substr(2 * num));
   }


   return ret;
}

void CoasterPagerView::focus() {
	sym_data.focus();
}

CoasterPagerView::~CoasterPagerView() {
	transmitter_model.disable();
	baseband::shutdown();
}

void CoasterPagerView::generate_frame() {
	uint8_t frame[19];
	uint32_t c;
	
	// Preamble (8 bytes)
	for (c = 0; c < 8; c++)
		frame[c] = 0x55;		// Isn't this 0xAA ?
	
	// Sync word
	frame[8] = 0x2D;
	frame[9] = 0xD4;
	
	// Data length
	frame[10] = 8;
	
	// Data
	for (c = 0; c < 8; c++)
		frame[c + 11] = (sym_data.get_sym(c * 2) << 4) | sym_data.get_sym(c * 2 + 1);

	// Copy for baseband
	memcpy(shared_memory.bb_data.data, frame, 19);
}

void CoasterPagerView::start_tx() {
	generate_frame();
	//int tmp = 200;
        //char hex_string[20];
        //char rest_id = {"200"};
        //std::dec str = std::int("c8");
        text_message.set("");
        const char *e;
        char sink[24] = {"aaaaaafc2d"};
        /////////////auto i = Split(temp);
        char pack[1024] = "";
        std::string rest_id = to_string_hex(field_rest, 2);
        const char *c = rest_id.c_str();
	std::string pager_id = to_string_hex(field_page, 3);
        const char *d = pager_id.c_str();
        //e = action.c_str();
        ////std::string jj = to_string_hex(action, 1);
        ////const char *j = jj.c_str();

        


        strncat(pack, sink, 24);
        strncat(pack, c, 32);
        strcat(pack, "0");
        strncat(pack, d, 8);
	switch (action)
	{
		case 0:
                        strcat(pack, "0000000000");
			break;
		case 1:
                        strncat(pack, "ffffff", 10);
			break;
		default:
			strcat(pack, "0000000000");
	}
        strncat(pack, "07", 2);
        
        //uint16_t baz (std::string("c8"));

        //std::string a  = "aa";
        
        ////std::string n;
        ////int t = strlen(temp);
        ////n = t;
        //for (int j = 0; j < sizeof(i); ++j)
        //{
        text_message.set(pack);
        //IMPORTANT clear the memory after done
        memset(pack, 0, 1024 * sizeof(char));
          //std::string n = std::bitset<2>(i[j]).to_string();
          
        //}
        //text_message.set(n);
	//transmitter_model.set_sampling_rate(2280000);
	//transmitter_model.set_rf_amp(true);
	//transmitter_model.set_baseband_bandwidth(1750000);
	//transmitter_model.enable();

	//baseband::set_fsk_data(19 * 8, 2280000 / 1000, 5000, 32);
        
}


void CoasterPagerView::on_tx_progress(const uint32_t progress, const bool done) {
	(void)progress;
	
	uint16_t address = 0;
	uint32_t c;
	
	if (done) {
		if (tx_mode == SINGLE) {
			transmitter_model.disable();
			tx_mode = IDLE;
			tx_view.set_transmitting(false);
		} else if (tx_mode == SCAN) {
			// Increment address
			
			for (c = 0; c < 4; c++) {
				address <<= 4;
				address |= sym_data.get_sym(12 + c);
			}
			
			address++;
			
			for (c = 0; c < 4; c++) {
				sym_data.set_sym(15 - c, address & 0x0F);
				address >>= 4;
			}
			
			start_tx();
		}
	}
}

CoasterPagerView::CoasterPagerView(NavigationView& nav) {
	const uint8_t data_init[8] = { 0x44, 0x01, 0x3B, 0x30, 0x30, 0x30, 0x34, 0xBC };
	uint32_t c;
	
	baseband::run_image(portapack::spi_flash::image_tag_fsktx);
	
	add_children({
		&labels,
                &options_action,
		&sym_data,
		&field_restaurant,
		&restaurant_scan,
		&pager_scan,
		&field_pager,
		&text_message,
		&tx_view
	});
	

	// Bytes to nibbles
	for (c = 0; c < 16; c++)
		sym_data.set_sym(c, (data_init[c >> 1] >> ((c & 1) ? 0 : 4)) & 0x0F);
	
	restaurant_scan.set_value(false);
        pager_scan.set_value(false);
	
	generate_frame();

	options_action.on_change = [this](size_t, int value) {
		action = value;
	};

        field_restaurant.on_change = [this](int32_t v) {
		field_rest = v;
	};

        field_pager.on_change = [this](int32_t v) {
		field_page = v;
	};

	tx_view.on_edit_frequency = [this, &nav]() {
		auto new_view = nav.push<FrequencyKeypadView>(receiver_model.tuning_frequency());
		new_view->on_changed = [this](rf::Frequency f) {
			receiver_model.set_tuning_frequency(f);
		};
	};
	
	tx_view.on_start = [this]() {
		if (tx_mode == IDLE) {
			if (restaurant_scan.value())
				tx_mode = SCAN;
			else
				tx_mode = SINGLE;
			tx_view.set_transmitting(true);
			start_tx();
		}
	};
	
	tx_view.on_stop = [this]() {
		tx_view.set_transmitting(false);
		tx_mode = IDLE;
	};
}

} /* namespace ui */
