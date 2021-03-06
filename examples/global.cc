#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_box.hh"
#include "widgets/atoms/gg_button.hh"
#include "widgets/atoms/gg_input.hh"
#include "widgets/atoms/gg_slider.hh"
#include "widgets/gg_alert.hh"
#include <memory>

struct Group : public gg::Element
{
	gg::Box    box;
	gg::Button btn;

	Group()
	: box("Inside.")
	, btn("Quit")
	{
		add(box);
		add(btn);

		btn.onClick = [this]() { showAlert(); };
	}

	void showAlert()
	{
		gg::addWindow(std::make_unique<gg::Alert>("Warning", "Quit: are you really sure?"));
	}

	void draw(gg::Renderer& ren) override
	{
		ren.setColor(gg::Color{15, 15, 15});
		ren.fillRect(m_bounds);

		ren.setColor(gg::Color{255, 255, 255});
		ren.drawRect(m_bounds);

		gg::Element::draw(ren);
	}

	void resized() override
	{
		box.setBounds(getX() + 10, getY() + 10, 100 /*getW() - 20*/, 40);
		btn.setBounds(getX() + 10, getH() - 10, getW() - 20, 40);
	}
};

struct myWindow : public gg::Window
{
	gg::Button btn1;
	gg::Button btn2;
	gg::Button btn3;
	gg::Box    box;
	gg::Box    output;
	gg::Slider vslider;
	gg::Slider hslider;
	Group      group;
	gg::Input  input1;
	gg::Input  input2;

	myWindow()
	: gg::Window("gg test", 100, 100, 640, 480)
	, btn1("Quit")
	, btn2("button x")
	, btn3("button y")
	, box("Example box with some cràzy text.")
	, hslider(gg::Slider::Type::HORIZONTAL)
	{
		add(btn1);
		add(btn2);
		add(btn3);
		add(box);
		add(output);
		add(vslider);
		add(hslider);
		add(group);
		add(input1);
		add(input2);

		btn1.onClick     = []() { gg::quit(); };
		vslider.onChange = [this]() { output.setText(std::to_string(vslider.getValue())); };
		hslider.onChange = [this]() { output.setText(std::to_string(hslider.getValue())); };

		vslider.setValue(0.5);
	}

	void resized() override
	{
		btn1.setBounds(40, 40, 100, 40);
		btn2.setBounds(40, btn1.getYH() + 10, 100, 40);
		btn3.setBounds(40, btn2.getYH() + 10, 100, 40);
		vslider.setBounds(btn2.getXW() + 10, btn1.getYH() + 10, 40, 90);
		output.setBounds(vslider.getXW() + 10, btn1.getYH() + 10, 90, 40);
		hslider.setBounds(vslider.getXW() + 10, output.getYH() + 10, 90, 40);
		box.setBounds(40, btn3.getYH() + 10, getW() - 80, 40);
		group.setBounds(output.getXW() + 10, 40, getW() - output.getXW() - 50, 140);
		input1.setBounds(40, box.getYH() + 10, getW() - 80, 40);
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
	gg::addWindow(std::make_unique<myWindow>());
	gg::run();
}
