#include "gg.hh"
#include "gg_window.hh"
#include "gg_group.hh"
#include "gg_button.hh"


int main()
{
	gg::init();
	gg::loadFont("pixelmix.ttf", 10);

	gg::Window* w = new gg::Window("gg test", 0, 0, 640, 480);

	gg::Button* btn1 = new gg::Button(20, 20, 120, 40, "button");
	btn1->setResizable(false, true);
	btn1->onDown([]() { puts("down!"); });
	btn1->onUp  ([]() { puts("up!"); });
	w->add(btn1);

	gg::Button* btn2 = new gg::Button(btn1->getXW() + 20, 20, 120, 40, "button");
	w->add(btn2);

	w->show();

	gg::add(w);
	gg::run();

	return 0;
}

