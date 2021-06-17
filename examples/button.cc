#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_box.hh"
#include "widgets/atoms/gg_button.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Button button1;
	gg::Button button2;
	gg::Button button3;

	myWindow()
	: gg::Window("gg button example", 100, 100, 640, 220)
	, button1("Disable 2")
	, button2("Disable 1")
	, button3("Enable all")
	{
		add(button1);
		add(button2);
		add(button3);

		button1.onClick = [this]() {
			button2.setEnabled(false);
		};
		button2.onClick = [this]() {
			button1.setEnabled(false);
		};
		button3.onClick = [this]() {
			button1.setEnabled(true);
			button2.setEnabled(true);
		};
	}

	void resized() override
	{
		button1.setBounds(40, 40, 120, 140);
		button2.setBounds(button1.getXW() + 10, 40, 120, 140);
		button3.setBounds(button2.getXW() + 10, 40, 120, 140);
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
