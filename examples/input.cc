#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/gg_input.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Input input1;
	gg::Input input2;
	gg::Input input3;
	gg::Input input4;

	myWindow()
	: gg::Window("gg input example", 100, 100, 640, 250)
	, input3("With pre-existing text.")
	, input4("Read-only.")
	{
		add(input1);
		add(input2);
		add(input3);
		add(input4);

		input4.setEditable(false);
	}

	void resized() override
	{
		input1.setBounds(40, 40, getW() - 80, 40);
		input2.setBounds(40, input1.getYH() + 10, getW() - 80, 40);
		input3.setBounds(40, input2.getYH() + 10, getW() - 80, 40);
		input4.setBounds(40, input3.getYH() + 10, getW() - 80, 40);
	}

	void closed() override
	{
		gg::quit();
	}
};

int main()
{
	gg::init();
	gg::addWindow(std::make_unique<myWindow>());
	gg::run();
}
