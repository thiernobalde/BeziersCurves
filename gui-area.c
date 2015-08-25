#include "gui.h"
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>  /* pour keyvals tq GDK_q */

/*-------------------------pressing-de-boutton-----------------------------*/

gboolean on_area_button_press_add_curve	(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	BezSpot s=info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		bez_spot_init_null(&s);
		info_edited_add_curve_first_control(info,p.x,p.y);
		info_edited_set_progress(info,1);
		info_edited_set_align(info,TRUE);
		listeners_notify(&info->listeners, "aspect-changed");
		
		
		return TRUE;
	}
	if(info->edited.progress==2)
	{
		
		if(e->button==1)
		{
			info_edited_add_curve_last_control(info,p.x,p.y);
			
			
			info_edited_set_progress(info,1);
		}
		if(e->button==3)
		{
			s.curve->is_closed=TRUE;
			
			info_edited_set_spot_null	(info);
			info_edited_set_progress(info,FALSE);
		}
		if(e->button==2)
		{
			s.curve->is_closed=FALSE;
			
			info_edited_set_spot_null	(info);
			info_edited_set_progress(info,FALSE);
		
		}
		listeners_notify(&info->listeners, "aspect-changed");
		
		return TRUE;
	}
	
	return 0;
	
}

gboolean on_area_button_press_add_control	(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,&info->edited.spot)==TRUE)
		{
		 	
		 	info_edited_add_control	(info, p);
		 	listeners_notify(&info->listeners, "aspect-changed");
			info_edited_set_progress(info,1);
			return TRUE;
		}
	}
	return 0;
	
}


gboolean on_area_button_press_move_curve	(Gui *g,GdkEventButton  *e)
{
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,&info->edited.spot)==TRUE)
		{
		 	info_edited_set_progress(info,TRUE);
			return TRUE;
		}
	}
	return 0;
}


gboolean on_area_button_press_move_control	(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,&info->edited.spot)==TRUE)
		{
		 	info_edited_set_progress(info,TRUE);		 	
			info_edited_set_align(info,e->button);
			return TRUE;
		}
	}
	 return TRUE;
}
gboolean on_area_button_press_remove_control	(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	
	if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,s)==TRUE)
	{
	 	bez_drawing_remove_control	   (s->drawing, s->curve, s->control, TRUE);
		
		listeners_notify(&info->listeners, "aspect-changed");
		return TRUE;
	}
	return 0;
	
}
gboolean on_area_button_press_remove_curve	(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,&info->edited.spot)==TRUE)
		{
		 	
		 	
		 	bez_drawing_remove_curve	   (s->drawing,s->curve, TRUE);
			listeners_notify(&info->listeners, "aspect-changed");
			return TRUE;
		}

	return 0;
	
}

gboolean on_area_button_press_color_curve		(Gui *g,GdkEventButton  *e)
{
	
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,s)==TRUE)
		{
			info_edited_set_progress(info,TRUE);
			return TRUE;
		}
	}
	return 0;
}	
gboolean on_area_button_press_fill_curve		(Gui *g,GdkEventButton  *e)
{
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,s)==TRUE)
		{
			info_edited_set_progress(info,TRUE);
			return TRUE;
		}
	}
	return 0;
}	
gboolean on_area_button_press_close_curve		(Gui *g,GdkEventButton  *e)
{
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,s)==TRUE)
	{
		s->curve->is_closed=!(s->curve->is_closed);
		listeners_notify(&info->listeners, "aspect-changed");
		info_edited_set_spot_null	(info);
		return TRUE;
	}

	return 0;
}	
gboolean on_area_button_press_duplicate_curve		(Gui *g,GdkEventButton  *e)
{
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==0)
	{
		if(bez_drawing_near_spot(info->drawing,  p,3.5, FALSE,s)==TRUE)
		{
			info_edited_set_progress(info,TRUE);
			
		}
	}
	if(info->edited.progress==1)
	{
		bez_drawing_duplicate_curve	   (s->drawing, s->curve, 30);
		info_edited_set_progress(info,FALSE);
		listeners_notify(&info->listeners, "aspect-changed");
		return TRUE;
	}	
	
	return 0;
}	
/*-------------------------mouvement-de-la-souris-----------------------------*/

gboolean on_area_motion_add_curve	(Gui *g,GdkEventMotion  *e)
{
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==1)
	{
	
		info_edited_move_spot_control(info,p);
		listeners_notify(&info->listeners, "aspect-changed");
	}
	return 0;
}

gboolean on_area_motion_add_control	(Gui *g,GdkEventMotion  *e)
{
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==1)
	{
		
		info_edited_move_spot_control(info,p);
		listeners_notify(&info->listeners, "aspect-changed");
		
		
	}
	return 0;
}
gboolean on_area_motion_move_curve	(Gui *g,GdkEventMotion  *e)
{
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==1)
	{
		
		info_edited_move_spot_curve(info,p);
		listeners_notify(&info->listeners, "aspect-changed");
		return TRUE;
		
	}
	return 0;
}
gboolean on_area_motion_move_control	(Gui *g,GdkEventMotion  *e)
{
	
	Info *info=g->info;
	Point p; 
	p.x=e->x; p.y=e->y;
	if(info->edited.progress==1)
	{
		
		info_edited_move_spot_control(info,p);
		listeners_notify(&info->listeners, "aspect-changed");
		
	}
	return TRUE;
}

/*-------------------------relachement-de-boutton-----------------------------*/

gboolean on_area_button_release_add_curve	(Gui *g,GdkEventButton U *e)
{
	Info *info=g->info;
	if(info->edited.progress==1)
	{	
		
		
		info_edited_set_progress(info,2);
		
	}
	else if(info->edited.progress==2)
	{	
		
		info_edited_set_spot_null	(info);
		info_edited_set_progress(info,0);
		
	}
	listeners_notify(&info->listeners, "aspect-changed");
	return TRUE;
}
gboolean on_area_button_release_add_control	(Gui *g,GdkEventButton U *e)
{
	Info *info=g->info;
	if(info->edited.progress==1)
	{	
		info_edited_set_spot_null	(info);
		info_edited_set_progress(info,0);
		listeners_notify(&info->listeners, "aspect-changed");
	}
	
	return TRUE;
}
gboolean on_area_button_release_move_curve	(Gui *g,GdkEventButton U *e)
{
	Info *info=g->info;
	if(info->edited.progress==1)
	{	
		info_edited_set_spot_null	(info);
		info_edited_set_progress(info,FALSE);
		listeners_notify(&info->listeners, "aspect-changed");
		return TRUE;
	}
	return 0;
}
gboolean on_area_button_release_move_control(Gui *g,GdkEventButton U *e)
{

	Info *info=g->info;
	
		
		info_edited_set_spot_null	(info);
		info->edited.progress=0;
		info_edited_set_align(info,FALSE);
		listeners_notify(&info->listeners, "aspect-changed");
		return TRUE;
	
	return 0;
}
		


/*------------------------------fonctions-callback-selon-l'action------------------------------------*/

gboolean on_area_button_press(GtkWidget U * w,GdkEventButton *e, gpointer data)
{

	Gui *g=data;
	
	switch(g->info->selected_tool)
	{
		case TOOL_REMOVE_CURVE:		return on_area_button_press_remove_curve	(g,e);
		case TOOL_REMOVE_CONTROL:	return on_area_button_press_remove_control	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_button_press_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_button_press_add_control		(g,e);
		case TOOL_MOVE_CURVE:		return on_area_button_press_move_curve		(g,e);
		case TOOL_ADD_CURVE:		return on_area_button_press_add_curve		(g,e);
		case TOOL_COLOR_CURVE:		return on_area_button_press_color_curve		(g,e);
		case TOOL_FILL_CURVE:		return on_area_button_press_fill_curve		(g,e);
		case TOOL_DUPLICATE_CURVE:	return on_area_button_press_duplicate_curve	(g,e);
		case TOOL_CLOSE_CURVE:		return on_area_button_press_close_curve		(g,e);
		default:			return TRUE;
	}return TRUE;
}

gboolean on_area_motion(GtkWidget U * w,GdkEventMotion  *e, gpointer data)
{

	Gui *g=data;
	
	switch(g->info->selected_tool)
	{
		
		case TOOL_MOVE_CURVE:		return on_area_motion_move_curve	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_motion_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_motion_add_control		(g,e);
		case TOOL_ADD_CURVE:		return on_area_motion_add_curve		(g,e);
		default:			return TRUE;
	}return TRUE;
}



gboolean on_area_button_release(GtkWidget U * w,GdkEventButton *e, gpointer data)
{

	Gui *g=data;
	
	switch(g->info->selected_tool)
	{
		case TOOL_MOVE_CURVE:		return on_area_button_release_move_curve	(g,e);
		case TOOL_MOVE_CONTROL:		return on_area_button_release_move_control	(g,e);
		case TOOL_ADD_CONTROL:		return on_area_button_release_add_control		(g,e);
		case TOOL_ADD_CURVE:		return on_area_button_release_add_curve		(g,e);
		default:			return TRUE;
	}
	return TRUE;
}


/*----------------------------------- Creation --------------------------------------------------------------*/
gboolean on_area_expose (GtkWidget *widget, GdkEventExpose U  *e, gpointer  data)
{
    	
	Gui *gui= data;
	Info *info=gui->info;
	BezSpot *s=&info->edited.spot;
	cairo_pattern_t * fond;
  	double red, green, blue, alpha;
	gui->cr= gdk_cairo_create (widget->window);

 	red= 1.0; green= 1.0; blue= 1.0; alpha= 1.00;
 	fond= cairo_pattern_create_rgba (red, green, blue, alpha);
 	cairo_set_source (gui->cr, fond);
 	cairo_paint (gui->cr);

  	bez_drawing_draw_curves_cr	(info->drawing,gui->cr,5, info->show_controls);
	/*bez_drawing_draw_controls_cr(info->drawing,gui->cr,5, FALSE);*/
	
	if(info->edited.progress==1)
	bez_spot_draw_cr	(s, gui->cr, 10);
	
 	cairo_pattern_destroy (fond);


  	cairo_destroy ( gui->cr);  gui->cr= NULL;
  	return TRUE;
}

void on_area_msg_aspect_changed(Listener *l)
{
	
	GtkWidget *area=l->to;
	gdk_window_invalidate_rect(area->window,NULL,FALSE);
}
void gui_init_area (Gui *g)
{
    Layout *l = &g->layout;
   
    g->area= gtk_drawing_area_new ();
    gtk_container_add (GTK_CONTAINER (l->area_frame),g->area);
	listeners_add(&g->info->listeners,g->area,"aspect-changed",on_area_msg_aspect_changed,g);
	
	
   GTK_WIDGET_SET_FLAGS  (g->area, GTK_CAN_FOCUS);
    gtk_widget_add_events (g->area, 
        GDK_BUTTON_MOTION_MASK  |
        GDK_BUTTON_PRESS_MASK   |
	GDK_EXPOSURE_MASK       |
        GDK_BUTTON_RELEASE_MASK    );

    ON_SIGNAL (g->area, 	"expose-event",       on_area_expose,      g);
    ON_SIGNAL (g->area, 	"button-press-event",   on_area_button_press,   g);
    ON_SIGNAL (g->area, 	"button-release-event", on_area_button_release, g);
    ON_SIGNAL (g->area, 	"motion-notify-event",  on_area_motion,      g);
  
   
}

