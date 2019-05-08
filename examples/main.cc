#include "../src/core/gg.hh"
#include "../src/core/gg_window.hh"
#include "../src/widgets/gg_button.hh"


struct myWindow : public gg::Window
{
	gg::Button* btn1;

	myWindow() : gg::Window("gg test", 100, 100, 640, 480),
	             btn1      (new gg::Button("Quit"))
	{
		add(btn1);
		btn1->onUp([]() { gg::quit(); });
	}

	void resized() override
	{
		btn1->setBounds(40, (getH() / 2) - 20, getW() - 80, 40);
	}
};


int main()
{
	gg::init();
	gg::add(new myWindow());
	gg::run();

	return 0;
}

