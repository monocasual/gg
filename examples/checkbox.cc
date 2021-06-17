#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_checkbox.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Checkbox checkbox1;
	gg::Checkbox checkbox2;
	gg::Checkbox checkbox3;

	myWindow()
	: gg::Window("gg checkbox example", 100, 100, 640, 210)
	, checkbox1(false, "Disable checkbox below")
	, checkbox2(false, "Do nothing")
	, checkbox3(false, "Change checkbox above")
	{
		add(checkbox1);
		add(checkbox2);
		add(checkbox3);

		checkbox1.onChange = [this](bool status) {
			checkbox2.setEnabled(!status);
		};

		checkbox3.onChange = [this](bool status) {
			checkbox2.setStatus(status);
		};
	}

	void resized() override
	{
		checkbox1.setBounds(40, 40, getW() - 80, 30);
		checkbox2.setBounds(40, checkbox1.getYH() + 20, getW() - 80, 30);
		checkbox3.setBounds(40, checkbox2.getYH() + 20, getW() - 80, 30);
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
