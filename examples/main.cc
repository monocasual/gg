#include <memory>
#include "../src/core/gg.hh"
#include "../src/core/gg_window.hh"
#include "../src/widgets/gg_button.hh"
#include "../src/widgets/gg_box.hh"
#include "../src/widgets/gg_slider.hh"


struct myWindow : public gg::Window
{
	gg::Button btn1;
	gg::Button btn2;
	gg::Button btn3;
	gg::Box    box;
	gg::Box    output;
	gg::Slider vslider;
	gg::Slider hslider;

	myWindow()
	: gg::Window("gg test", 100, 100, 640, 480),
	  btn1      ("Quit"),
	  btn2      ("button x"),
	  btn3      ("button y"),
	  box       ("Example box with some text."),
	  hslider   (gg::Slider::Type::HORIZONTAL)
	{
		add(btn1);
		add(btn2);
		add(btn3);
		add(box);
		add(output);
		add(vslider);
		add(hslider);

		btn1.onClick    = [](){ gg::quit(); };
		vslider.onChange = [this](){ output.setText(std::to_string(vslider.getValue())); };
		hslider.onChange = [this](){ output.setText(std::to_string(hslider.getValue())); };

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
	}
};


int main()
{
	gg::init();

	std::unique_ptr<myWindow> w = std::make_unique<myWindow>();
	gg::add(w.get());
	return gg::run();
}

