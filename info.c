#include "info.h"


void info_edited_init_null(Info *info)
{
	Edited *e=&info->edited;
	BezSpot *b=&e->spot;
	
	bez_spot_init_null(b);
	e->progress=0;
	e->align=FALSE;
}
void info_init_default	 (Info * info)
{
	
	listeners_init(&info->listeners , info);
	info->selected_tool=TOOL_ADD_CURVE;
	info->drawing=bez_drawing_new();
	info->show_controls=FALSE;
	
	
	info_edited_init_null(info);
	
}


void info_select_tool	 (Info * info, ToolId tool_id )
{
	if(tool_id==info->selected_tool) return;
		
	info->selected_tool=tool_id;
	info_edited_set_progress(info, 0);
	listeners_notify(&info->listeners, "tool-changed");
	
}

void info_edited_set_progress(Info *info, int progress)
{
	
	info->edited.progress=progress;
	
}


void info_edited_move_spot_curve	(Info * info, Point q)
{
	
	BezSpot s=info->edited.spot;
	Vector vt;
	Point p;
	point_init_xy (&vt,  s.point->x, s.point->y);
	p=vector_sub (q, vt);
	
	bez_curve_translate	(info->edited.spot.curve,p);
}

void info_edited_set_spot_null	(Info * info)
{
	bez_spot_init_null(&info->edited.spot);
}
void info_edited_add_control			(Info * info, Point pointer)
{
	BezControl *control=bez_control_new_xy(pointer.x,pointer.y);
	BezCurve *curve=info->edited.spot.curve;
	unsigned i,k=bez_curve_nb_controls(curve);
	
	for(i=0;i<k;i++)
	{
		if(bez_curve_get_control(curve,i)==info->edited.spot.control)
		{
			
			
			if(i==0)bez_curve_insert_control(curve,control,0);
			else bez_curve_insert_control(curve,control,i);
			info->edited.spot.control=control;
			info->edited.spot.point=&control->mid;
			info->edited.spot.curve=curve;
			return;
		}
	}
}

void info_edited_set_align	(Info * info, gboolean align)
{
	info->edited.align=align;
}

void info_edited_move_spot_control(Info *info,Point q)
{
	BezSpot s=info->edited.spot;
	Point p;
	
	
	if(com_vector(s.point,s.control->fwd)==TRUE)
	{
		
		if(info->edited.align==1)bez_control_translate_fwd(s.control,q,TRUE);
		else if(info->edited.align==3)bez_control_translate_fwd(s.control,q,FALSE);
	}
	
	if(com_vector(s.point,s.control->mid)==TRUE)
	{
		
		Vector vt;
	
		point_init_xy (&vt,  s.point->x, s.point->y);
		p=vector_sub (q, vt);
		bez_control_translate_mid(s.control,p);
	}
	
	else if(com_vector(s.point,s.control->bwd)==TRUE)
	{
		
		if(info->edited.align==1)bez_control_translate_bwd(s.control,q,TRUE);
		else if(info->edited.align==3)bez_control_translate_bwd(s.control,q,FALSE);
	}
	
}

void info_edited_add_curve_first_control	(Info * info, double x, double y)
{
	BezSpot *s=&info->edited.spot;
	BezCurve *c=bez_curve_new  	();
	BezControl *p=bez_control_new_xy(x,y);
	
	s->point=&p->fwd;
	s->control=p;
	bez_curve_add_control	(c,  p);
	s->curve=c;
	bez_drawing_add_curve	   (info->drawing,  c);
	
}
	
void info_edited_add_curve_last_control		(Info * info, double x, double y)
{
	BezSpot *s=&info->edited.spot;
	BezControl *p=bez_control_new_xy(x,y);
	
	s->point=&p->fwd;
	s->control=p;
	bez_curve_add_control	(s->curve,  p);
	
}
	





								   	
		
