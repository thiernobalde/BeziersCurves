#include "gui.h"
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>  /* pour keyvals tq GDK_q */

gboolean on_area_button_press(GtkWidget U * w,GdkEvent U *e, gpointer data)
{

	Gui *g=data;
	printf("bingo");
	/*switch(g->info->selected_tool)
	{
		case TOOL_REMOVE_CURVE:		return on_area_button_press_remove_curve	(g,e);
		case TOOL_REMOVE_CONTROL:	return on_area_button_press_remove_control	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_button_press_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_button_press_add_control		(g,e);
		case TOOL_MOVE_CURVE:		return on_area_button_press_move_curve		(g,e);
		case TOOL_ADD_CURVE:		return on_area_button_press_add_curve		(g,e);
		default:			return TRUE;
	}*/ return TRUE;
}

gboolean on_area_motion(GtkWidget U * w,GdkEvent U *e, gpointer data)
{

	Gui *g=data;
	printf("bingo\n");
	/*switch(g->info->selected_tool)
	{
		case TOOL_MOVE_CURVE:		return on_area_motion_move_curve	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_motion_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_motion_add_control		(g,e);
		case TOOL_ADD_CURVE:		return on_area_motion_add_curve		(g,e);
		default:			return TRUE;
	}*/return TRUE;
}



gboolean on_area_button_release(GtkWidget U * w,GdkEvent U *e, gpointer data)
{

	Gui *g=data;
	printf("bingo");
	/*switch(g->info->selected_tool)
	{
		case TOOL_MOVE_CURVE:		return on_area_button_release_move_curve	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_button_release_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_button_release_add_control		(g,e);
		case TOOL_ADD_CURVE:		return on_area_button_release_add_curve		(g,e);
		default:			return TRUE;
	}*/
	return TRUE;
}


/*---- Creation --------------------------------------------------------------*/

void gui_init_area (Gui *g)
{
    Layout *l = &g->layout;

    g->area = gtk_drawing_area_new ();
    /*gtk_box_pack_start (GTK_BOX (l->m), g->area, EXPAND, FILL, 3);*/
	gtk_container_add (GTK_CONTAINER (l->area_frame),g->area);
	
	g_signal_connect(g->area,"clicked",G_CALLBACK(on_area_button_press),g);
   /* GTK_WIDGET_SET_FLAGS  (g->area, GTK_CAN_FOCUS);
    gtk_widget_add_events (g->area, 
        GDK_BUTTON_MOTION_MASK  |
        GDK_BUTTON_PRESS_MASK   |
        GDK_BUTTON_RELEASE_MASK    );

    
    ON_SIGNAL (g->area, "button-press-event",   on_area_button_press,   g);
    ON_SIGNAL (g->area, "button-release-event", on_area_button_release, g);
    ON_SIGNAL (g->area, "motion-notify-event",  on_area_motion,      g);*/
   
}

