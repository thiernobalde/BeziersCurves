#ifndef __GUI__
#define __GUI__

#include <gtk/gtk.h>
#include <cairo.h>
#include <glib.h>
#include "info.h"


#define U __attribute__((unused))
#define TOOL_KEY "tool"




typedef struct Menu
{
	GtkWidget *bar,*file_item,*help_item,*file_menu,*help_menu,\
	*load_item,*save_item,*quit_item,*about_item,*use_item;
}Menu;
typedef struct Layout
{
	GtkWidget *main_box,*central_box, *tool_box;
	GtkWidget *menu_frame, *area_frame,*tool_frame, *status_frame;
}Layout;

typedef struct Gui
{
	Info *info;
	 
	GtkWidget *window; 
	cairo_t* cr;
	Layout layout;
	GtkWidget *statusbar;
	Menu menu; 
	GtkWidget *tool[NB_TOOLS];
	GtkWidget *color_button,*check_button;
	GtkWidget *area;
}Gui;

void listeners_add	(Listeners *ls,gpointer to, gchar const message[],
			OnMessage on_message, gpointer data);
void on_tool_msg_tool_changed(Listener *l);
void on_area_msg_aspect_changed(Listener *l);
void gui_init_area      (Gui *g);
void on_status_bar_msg_tool_changed(Listener * listener);

void on_about_project(GtkMenuItem U *item,gpointer  data);
void on_quit_item_activate(GtkMenuItem U *item,gpointer  data);
void on_loadsave_item_activate(GtkMenuItem U *item,gpointer  data);

void gui_init_tool(Gui *g);	
void gui_init_help_menu(Gui *g);
void gui_init_file_menu(Gui *g);	
void gui_init_menu_bar(Gui *g);
void gui_init_statusbar (Gui *g);
void gui_init_central(Gui *g);

	
void gui_init_window(Gui *g);
void gui_init_layout(Gui *g);
void gui_init(Gui *gui,Info *info);

#endif
