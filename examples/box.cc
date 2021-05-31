#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_box.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Box emptyBox;
	gg::Box textBox;

	myWindow()
	: gg::Window("gg box example", 100, 100, 640, 170)
	, textBox("Example box with some cràzy UTF8 text.")
	{
		add(emptyBox);
		add(textBox);
	}

	void resized() override
	{
		emptyBox.setBounds(40, 40, getW() - 80, 40);
		textBox.setBounds(40, emptyBox.getYH() + 10, getW() - 80, 40);
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
