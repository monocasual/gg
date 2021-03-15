#include <memory>
#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/gg_button.hh"
#include "widgets/gg_box.hh"
#include "widgets/gg_slider.hh"
#include "widgets/gg_alert.hh"


struct Group : public gg::Element
{
	gg::Box box;
	gg::Button btn;
	gg::Alert alert;

	Group()
	: box("Inside."),
	  btn("Quit"),
	  alert("Warning", "Quit: are you really sure?")
	{
		add(box);
		add(btn);

		btn.onClick = [this](){ showAlert(); };
	}

	void showAlert()
	{
		gg::addWindow(&alert);
	}

	void draw(gg::Renderer& ren) override
	{ 		
   		ren.setColor(gg::Color{ 15, 15, 15 });
    	ren.fillRect(m_bounds);

		ren.setColor(gg::Color{ 255, 255, 255 });
		ren.drawRect(m_bounds);
		
		gg::Element::draw(ren);
	}

	void resized() override
	{
		box.setBounds(getX() + 10, getY() + 10, 100/*getW() - 20*/, 40);
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

	myWindow()
	: gg::Window("gg test", 100, 100, 640, 480),
	  btn1      ("Quit"),
	  btn2      ("button x"),
	  btn3      ("button y"),
	  box       ("Example box with some cràzy text."),
	  hslider   (gg::Slider::Type::HORIZONTAL)
	{
		add(btn1);
		add(btn2);
		add(btn3);
		add(box);
		add(output);
		add(vslider);
		add(hslider);
		add(group);

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

		group.setBounds(output.getXW() + 10, 40, getW() - output.getXW() - 50, 140);
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

