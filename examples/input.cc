#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/gg_input.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Input input1;
	gg::Input input2;

	myWindow()
	: gg::Window("gg input example", 100, 100, 640, 170)
	{
		add(input1);
		add(input2);
	}

	void resized() override
	{
		input1.setBounds(40, 40, getW() - 80, 40);
		input2.setBounds(40, input1.getYH() + 10, getW() - 80, 40);
	}

	void closed() override
	{
		gg::quit();
	}
};

int main()
{
	gg::init();

	std::unique_ptr<myWindow> w = std::make_unique<myWindow>();
	gg::addWindow(w.get());
	gg::run();
}
