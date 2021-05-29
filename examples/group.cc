#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/gg_alert.hh"
#include "widgets/gg_box.hh"
#include "widgets/gg_button.hh"
#include "widgets/gg_input.hh"
#include "widgets/gg_slider.hh"
#include <memory>

struct Group : public gg::Element
{
	gg::Box    box1;
	gg::Box    box2;
	gg::Button btn;

	Group()
	: box1("This box is inside a group.")
	, box2("This box is also inside a group. With clipping.")
	, btn("Button")
	{
		add(box1);
		add(box2);
		add(btn);
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
		box1.setBounds(getX() + 10, getY() + 10, getW() - 20, 40);
		box2.setBounds(getX() + 10, box1.getYH() + 10, 400, 40);
		btn.setBounds(getX() + 10, getH() - 10, getW() - 20, 40);
	}
};

struct myWindow : public gg::Window
{
	Group group;

	myWindow()
	: gg::Window("gg group test", 100, 100, 640, 480)
	{
		add(group);
	}

	void resized() override
	{
		group.setBounds(getBounds().reduced(40));
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
