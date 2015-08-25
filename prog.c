
#include "gui.h"


int main(int argc,char **argv)
{
	Info info;
	Gui gui;
	gtk_init(&argc,&argv);
	info_init_default(&info);
	gui_init(&gui,&info);
	
	gtk_widget_show_all(gui.window);
	gtk_main();
	return 0;
}
