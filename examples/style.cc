#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/gg_box.hh"
#include "widgets/gg_button.hh"
#include <memory>

struct CustomStyle : public gg::Style
{
	gg::Color windowBackgroundColor() const override { return gg::Color{90, 90, 90}; }

	gg::Color boxBoundaryColor() const override { return gg::Color{30, 30, 30}; }
	gg::Color boxBackgroundColor() const override { return gg::Color{100, 100, 100}; }

	gg::Color buttonBoundaryColor() const override { return gg::Color{30, 30, 30}; }
	gg::Color buttonBackgroundColorDown() const override { return gg::Color{90, 90, 90}; }
	gg::Color buttonBackgroundColorUp() const override { return gg::Color{90, 90, 90}; }
};

struct myWindow : public gg::Window
{
	gg::Box    box1;
	gg::Box    box2;
	gg::Button button1;
	gg::Button button2;

	myWindow()
	: gg::Window("gg style example", 100, 100, 640, 220)
	, box1("Box one.")
	, box2("Box two.")
	, button1("Default style")
	, button2("Custom style")
	{
		add(box1);
		add(box2);
		add(button1);
		add(button2);

		button1.onClick = []() {
			gg::setStyle(std::make_unique<gg::Style>());
		};
		button2.onClick = []() {
			gg::setStyle(std::make_unique<CustomStyle>());
		};
	}

	void resized() override
	{
		box1.setBounds(40, 40, getW() - 80, 40);
		box2.setBounds(40, box1.getYH() + 10, getW() - 80, 40);
		button1.setBounds(40, box2.getYH() + 10, 120, 40);
		button2.setBounds(button1.getXW() + 10, box2.getYH() + 10, 120, 40);
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
