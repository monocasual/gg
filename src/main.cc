#include "gg.hh"
#include "gg_window.hh"
#include "gg_button.hh"


struct myWindow : public gg::Window
{
	gg::Button* btn1;

	myWindow() : gg::Window("gg test", 0, 0, 640, 480),
	             btn1      (new gg::Button("button"))
	{
		add(btn1);
	}

	void resized() override
	{
		btn1->setBounds(20, (getH() / 2) - 20, getW() - 40, 40);
	}
};


int main()
{
	gg::init();
	gg::loadFont("pixelmix.ttf", 10);
	gg::add(new myWindow());
	gg::run();

	return 0;
}

