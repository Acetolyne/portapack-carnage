/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2017 Furrtek
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

#ifndef __UI_SIDETABVIEW_H__
#define __UI_SIDETABVIEW_H__

#include "ui.hpp"
#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_painter.hpp"

namespace ui {
	
#define MAX_TABS 5

class SideTab : public Widget {
public:
	SideTab();

	void paint(Painter& painter) override;
	
	bool on_key(const KeyEvent key) override;
	bool on_touch(const TouchEvent event) override;
	
	void set(uint32_t index, Dim width, std::string text, Color text_color);

private:
	std::string text_ { };
	Color text_color_ { };
	uint32_t index_ { };
};

class SideTabView : public View {
public:
	struct SideTabDef {
		std::string text;
		ui::Color color;
		View* view;
	};
	
	SideTabView(std::initializer_list<SideTabDef> tab_definitions);
	~SideTabView();
	
	void focus() override;
	void on_show() override;
	
	void set_selected(uint32_t index);
	uint32_t selected() {
		return current_tab;
	};

private:
	size_t n_tabs { };
	std::array<SideTab, MAX_TABS> tabs { };
	std::array<View*, MAX_TABS> views { };
	uint32_t current_tab { 0 };
};

} /* namespace ui */

#endif/*__UI_SIDETABVIEW_H__*/
