#include "gg.hh"
#include "gg_window.hh"
#include "gg_group.hh"
#include "gg_button.hh"


void callback1(void *p)
{
	printf("press me! this is the button callback from button %p\n", p);
}

void callback2(void *p)
{
	printf("click me! this is the button callback from button %p\n", p);
}


int main()
{
	gg_init();
	gg_loadFont("pixelmix.ttf", 10);

	ggWindow *w  = new ggWindow("GG test", 0, 0, 640, 480);

	ggButton *btn1 = new ggButton(20, 20, 600, 440, "button");
	btn1->resizable(true, true);
	w->add(btn1);

	//ggButton *btn2 = new ggButton(btn1->xw()+20, 20, 50, 40, "button");
	//w->add(btn2);

	w->show();

	gg_add(w);
	gg_run();

	return 0;
}

