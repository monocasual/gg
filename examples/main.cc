#include "../src/core/gg.hh"
#include "../src/core/gg_window.hh"
#include "../src/widgets/gg_button.hh"


struct myWindow : public gg::Window
{
	gg::Button* btn1;
	gg::Button* btn2;
	gg::Button* btn3;

	myWindow() : gg::Window("gg test", 100, 100, 640, 480),
	             btn1      (new gg::Button("Quit")),
	             btn2      (new gg::Button("button x")),
	             btn3      (new gg::Button("button y"))
	{
		add(btn1);
		add(btn2);
		add(btn3);
		btn1->onClick = [](){ gg::quit(); };
	}

	void resized() override
	{
		btn1->setBounds(40, (getH() / 2) - 20, getW() - 80, 40);
		btn2->setBounds(40, btn1->getYH() + 10, 100, 40);
		btn3->setBounds(40, btn2->getYH() + 10, 100, 40);
	}
};


int main()
{
	gg::init();
	gg::add(new myWindow());
	gg::run();

	return 0;
}

