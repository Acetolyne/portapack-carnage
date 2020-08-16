#include "ace.hpp"
#include "portapack.hpp"
#include <cstring>

using namespace portapack;

namespace ui
{
    AceView::AceView(NavigationView &nav)
    {
        add_children({
            //&labels,
            //&options_action,
            //&sym_data,
            //&field_restaurant,
            //&restaurant_scan,
            //&pager_scan,
            //&field_pager,
            //&text_message,
            //&tx_view,
            //&options_alert,
            //&progressbar
            //&widgets
            &testies
	    });
	
    }

    void AceView::update()
    {
        display.fill_rectangle(
		screen_rect(),
		Color::red()
	    );
        add_child(&testies);
        
    }


    void AceWidget::paint(Painter&) {
        display.fill_rectangle(
		screen_rect(),
		Color::blue()
	    );
    }

    void AceWidget::on_show() {
        display.fill_rectangle(
		screen_rect(),
		Color::blue()
	    );
    }

    void AceWidget::set_parent_rect(const Rect new_parent_rect) {
	View::set_parent_rect(new_parent_rect);
	
	const ui::Rect ace_rect { 0, 0, 100, 100 };
    testies.visible();
	testies.set_color(Color::green());
    }
}