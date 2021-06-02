#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_box.hh"
#include "widgets/atoms/gg_scrollbar.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Scrollbar scrollbar1;
	gg::Scrollbar scrollbar2;
	gg::Scrollbar scrollbar3;
	gg::Box       output;

	myWindow()
	: gg::Window("gg scrollbar example", 100, 100, 640, 250)
	, scrollbar1(gg::Scrollbar::Type::HORIZONTAL)
	, scrollbar2(gg::Scrollbar::Type::HORIZONTAL)
	, scrollbar3(gg::Scrollbar::Type::VERTICAL)
	{
		add(scrollbar1);
		add(scrollbar2);
		add(scrollbar3);
		add(output);

		scrollbar1.setHandleSize(140);

		scrollbar2.setRange({0.0f, 2.0f});

		scrollbar1.onChange = [this](float v) {
			output.setText(std::to_string(v));
		};
		scrollbar2.onChange = [this](float v) {
			output.setText(std::to_string(v));
		};
		scrollbar3.onChange = [this](float v) {
			output.setText(std::to_string(v));
		};
	}

	void resized() override
	{
		scrollbar1.setBounds(40, 40, getW() - 130, 30);
		scrollbar2.setBounds(40, scrollbar1.getYH() + 10, getW() - 130, 30);
		scrollbar3.setBounds(scrollbar1.getXW() + 10, 40, 30, getH() - 80);
		output.setBounds(40, scrollbar2.getYH() + 10, 200, 30);
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
