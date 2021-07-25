#include "core/gg.hh"
#include "core/gg_window.hh"
#include "widgets/atoms/gg_box.hh"
#include "widgets/gg_viewport.hh"
#include <memory>

struct myWindow : public gg::Window
{
	gg::Viewport viewport1;
	gg::Viewport viewport2;
	gg::Viewport viewport3;
	gg::Box      box1;
	gg::Box      box2;
	gg::Box      box3;

	myWindow()
	: gg::Window("gg viewport example", 100, 100, 640, 670)
	, viewport2(gg::Viewport::Direction::HORIZONTAL)
	, viewport3(gg::Viewport::Direction::VERTICAL)
	, box1("This box is inside a viewport.")
	, box2("This box is inside a horizontal viewport.")
	, box3("This box is inside a vertical viewport.")
	{
		add(viewport1);
		add(viewport2);
		add(viewport3);

		viewport1.setContent(box1, 800, 600);
		viewport2.setContent(box2, 800, 180);
		viewport3.setContent(box3, 800, 1200);
	}

	void resized() override
	{
		viewport1.setBounds(40, 40, getW() - 80, 160);
		viewport2.setBounds(40, viewport1.getYH() + 40, getW() - 80, 200);
		viewport3.setBounds(40, viewport2.getYH() + 40, getW() - 80, 160);
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
