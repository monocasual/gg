#include <memory>
#include "../src/core/gg.hh"
#include "../src/core/gg_window.hh"
#include "../src/widgets/gg_button.hh"
#include "../src/widgets/gg_box.hh"
#include "../src/widgets/gg_slider.hh"


struct Group : public gg::Element
{
	gg::Box box;

	Group() : box("Inside.")
	{
		add(box);
	}

	void draw(gg::Renderer& ren) override
	{ 		
   		ren.setColor(15, 15, 15);
    	ren.fillRect(m_x, m_y, m_w, m_h);

		ren.setColor(255, 255, 255);
		ren.drawRect(m_x, m_y, m_w, m_h);
		
		gg::Element::draw(ren);
	}

	void resized() override
	{
		box.setBounds(getX() + 10, getY() + 10, 80, 40);
	}
};


struct myWindow : public gg::Window
{
	Group group;

	myWindow()
	: gg::Window("gg test", 100, 100, 640, 480)
	{
		add(group);
	}

	void resized() override
	{
		group.setBounds(40, 40, getW() - 80, 140);
	}
};


int main()
{
	gg::init();

	std::unique_ptr<myWindow> w = std::make_unique<myWindow>();
	gg::add(w.get());
	return gg::run();
}

