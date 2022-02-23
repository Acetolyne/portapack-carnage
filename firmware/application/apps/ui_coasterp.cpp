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
#include "manchester.hpp"
#include <cstring>
#include <stdio.h>
#include <bitset>
#include "string_format.hpp"
#include <cctype>

int sum = {};

//@todo on options_action change check state and if program then disable scan buttons
//@todo on check scan boxes disable tied select field
//@todo possibly add function to select number for number field if there is a UI for this already besides the freq UI.

using namespace portapack;

namespace ui {

//long int getCRC(const std::string& str)
//{
//   int num = str.length() / 2;
//   int sum = 0;
//   char p[2];
//   for (auto i = 0; i < str.length() / 2; i++)
//   {
//	std::string p = str.substr(i * 2, 2);
//        char cstr[3];
//        strcpy(cstr, p.c_str());
//        sum += hex2int(cstr);
//   }

   // If there are leftover characters, create a shorter item at the end.
//   if (str.length() % 2 != 0)
//   {
//	std::string p = str.substr(2 * num);
//        char cstr[3];
//        strcpy(cstr, p.c_str());
//        sum += hex2int(cstr);
//   }

//   return sum;
//}

void add(char *c) {
	sum += hex2int(c);
}

void CoasterPagerView::focus() {
	sym_data.focus();
}

CoasterPagerView::~CoasterPagerView() {
	transmitter_model.disable();
	baseband::shutdown();
}

void CoasterPagerView::generate_frame() {
//reset sum so we can recalculate crc on each transmit
	sum = 0;
	char data[1024] = "";
	//set preamble and add to sum
	char pre[7] = {"aaaaaa"};
	add(pre);
	strncat(data, pre, 7);
	//set header and add to sum
	char header[5] = {"fc2d"};
	add(header);
	strncat(data, header, 5);
	//get resturant id and add to sum
	std::string s = to_string_hex(field_rest, 2);
	char rest_id[3] = {};
	strcpy(rest_id, s.c_str());
	add(rest_id);
	strncat(data, rest_id, 3);
	//set systemid and add to sum
	char sysid[2] = {"0"};
	add(sysid);
	strncat(data, sysid, 2);
	//get pagerid and add to sum
	std::string p = to_string_hex(field_page, 3);
	char pager_id[4] = {};
	strcpy(pager_id, p.c_str());
	add(pager_id);
	strncat(data, pager_id, 4);
	//set program1 and add to sum
	char prog1[6] = {"00000"};
	add(prog1);
	strncat(data, prog1, 6);
	//set program2 and add to sum
	char prog2[6] = {"00000"};
	add(prog2);
	strncat(data, prog2, 6);
	//get action and add to sum
	std::string t = to_string_hex(alert, 2);
	char alert_id[3] = {};
	strcpy(alert_id, t.c_str());
	add(alert_id);
	strncat(data, alert_id, 3);
	int z = round(sum % 255);
	std::string c = to_string_hex(z, 2);
	char crc[3] = {};
	strcpy(crc, c.c_str());
	strncat(data, crc, 3);
	//std::string jj = to_string_bin(0110011001100110, 16);
	//For future getcrc function
	//int tmp = hex2int(pre);


	///////////////////////////////////////////////////////////
	//std::string y = std::bitset<8>(zz).to_string();
	//char crc[9] = {};
	//strcpy(crc, y.c_str());
	//std::string winb = hex2int(y);
	//convert sum to string for display (temp testing)
	//std::string pi = to_string_dec_int(sum);
	//char fin[1024] = "";
	//strcat(fin,"aaaaaa");
	//strcat(fin,"fc2d");
	text_message.set(data);
	//memset(bin_ptr, 0, 256);
	//unsigned char tmp[541] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0};
	//char tmp[1082] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,1,0,1,1,0};
	//char * tmpb = {"011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110010101100110100110011010011010101010010110011010101010101010101010011010010101010101010101010101010101010101010101010101010110101001101010101010101010101010101010101010101010100101010110010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"};
	////memcpy(shared_memory.bb_data.data, tmpb, 1082);
	//std::string pii = to_string_dec_int(tmpb);
	//text_message.set(pii);
	//uint8_t datab = {"aaaaaafc2d0d00130000000000448e"};
	//unsigned char datab[31] = {"aaaaaafc2d0d00130000000000448e"};
	//unsigned char* test = reinterpret_cast<unsigned char*>(data);
	//manchester_encode(shared_memory.bb_data.data, datab, 1082, 1);
	//char tmp[541];
	//strcat(tmp, "011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100101010101011010101001100101100110101010010110011010101010101010101010100101100110101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010100110011010100110010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	//manchester_encode(bin_ptr + 16, raw_ptr, 112, 0)
        //text_message.set(data);

	//char testb[60] = {"66666666666555aa659aa59aaaaa9a5aaaaaaaaaaaaaaaaaaaa9a9a6a56"};
	// Copy for baseband
	//std::string n = std::bitset<240>(tmp).to_string();
	//memset(shared_memory.bb_data.data, test, 240);
	uint8_t aa = hex2int("aa");
	uint8_t bb = hex2int("aa");
	uint8_t cc = hex2int("aa");
	uint8_t dd = hex2int("fc");
	uint8_t ee = hex2int("2d");
	uint8_t ff = hex2int("0d");
	uint8_t gg = hex2int("00");
	uint8_t hh = hex2int("13");
	uint8_t ii = hex2int("00");
	uint8_t jj = hex2int("00");
	uint8_t kk = hex2int("00");
	uint8_t ll = hex2int("00");
	uint8_t mm = hex2int("00");
	uint8_t nn = hex2int("44");
	uint8_t oo = hex2int("8e");

	memcpy(shared_memory.bb_data.data, &aa, 8);
	memcpy(shared_memory.bb_data.data + 8, &bb, 8);
	memcpy(shared_memory.bb_data.data + 16, &cc, 8);
	memcpy(shared_memory.bb_data.data + 24, &dd, 8);
	memcpy(shared_memory.bb_data.data + 32, &ee, 8);
	memcpy(shared_memory.bb_data.data + 40, &ff, 8);
	memcpy(shared_memory.bb_data.data + 48, &gg, 8);
	memcpy(shared_memory.bb_data.data + 56, &hh, 8);
	memcpy(shared_memory.bb_data.data + 64, &ii, 8);
	memcpy(shared_memory.bb_data.data + 72, &jj, 8);
	memcpy(shared_memory.bb_data.data + 80, &kk, 8);
	memcpy(shared_memory.bb_data.data + 88, &ll, 8);
	memcpy(shared_memory.bb_data.data + 96, &mm, 8);
	memcpy(shared_memory.bb_data.data + 104, &nn, 8);
	memcpy(shared_memory.bb_data.data + 112, &oo, 8);

}

void CoasterPagerView::start_tx() {
	
	
	generate_frame();
	transmitter_model.set_sampling_rate(2000000);
	transmitter_model.set_baseband_bandwidth(2000000);
	transmitter_model.enable();

	baseband::set_fsk_data(240, 2000000 / 9600 , 3190, 100);
	//progressbar.set_value(100);
	



        
}


void CoasterPagerView::on_tx_progress(const uint32_t progress, const bool done) {
	(void)progress;
	
	uint16_t address = 0;
	uint32_t c;
	//transmitter_model.disable();
	//tx_mode = IDLE;
	//tx_view.set_transmitting(false);
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
		&tx_view,
		&options_alert,
		&progressbar
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

	options_alert.on_change = [this](size_t, int value) {
		alert = value;
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
