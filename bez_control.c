#include "bez_control.h"



BezControl *bez_control_new(void)
{
	BezControl *p=g_new(BezControl,1);
	p->mid.x=0;
	p->mid.y=0;
	p->bwd=p->mid;
	p->fwd=p->mid;
	return p;
}
BezControl *bez_control_new_xy(double mid_x,double mid_y)
{
	BezControl *p=g_new(BezControl,1);
	p->mid.x=mid_x;
	p->mid.y=mid_y;
	p->bwd=p->mid;
	p->fwd=p->mid;
	return p;
}
BezControl *bez_control_new_duplicate(BezControl *p,double dup_x,double dup_y)
{
	BezControl *cdup=g_new(BezControl,1);
	cdup->mid.x=p->mid.x+dup_x;
	cdup->mid.y=p->mid.y+dup_y;
	cdup->fwd.x=p->fwd.x+dup_x;
	cdup->fwd.y=p->fwd.y+dup_y;
	cdup->bwd.x=p->bwd.x+dup_x;
	cdup->bwd.y=p->bwd.y+dup_y;
	return cdup;
}
void  bez_control_destroy(BezControl *p)
{
	g_free(p);
}

Point*  bez_control_near_point(BezControl *p,Point q,double delta, gboolean mid_only)
{
	
	if(mid_only==TRUE)
	{
		if( point_is_near (p->mid,q,delta)==1)
			return &p->mid;
	}
	else
	{
		if( point_is_near (p->bwd,q,delta)==1)
			return &p->bwd;
		if( point_is_near (p->fwd,q,delta)==1)
			return &p->fwd;
		if( point_is_near (p->mid,q,delta)==1)
			return &p->mid;
	}
	return NULL;
}
void  bez_control_translate_mid(BezControl *p,Vector v)
{
	
	point_translate (&p->mid,v);
	
	point_translate (&p->bwd,v);
	
	point_translate (&p->fwd,v);

}
void  bez_control_translate_fwd(BezControl *p,Vector v,gboolean align)
{
	
	point_init_xy (&p->fwd,v.x, v.y);
	if(align==TRUE)
	{
		
		Vector vt;
		point_init_xy (&vt, p->mid.x,p->mid.y);
		vector_scale (&vt,2);
		p->bwd=vector_sub (vt, p->fwd);
	}
	
	
	
}
void  bez_control_translate_bwd(BezControl *p,Vector v,gboolean align)
{
	point_init_xy (&p->bwd,v.x, v.y);
	if(align==TRUE)
	{
		
		Vector vt;
		point_init_xy (&vt, p->mid.x,p->mid.y);
		vector_scale (&vt,2);
		p->fwd=vector_sub (vt, p->bwd);
	}
	
}

void  bez_control_draw_cr (BezControl *p,cairo_t *cr,int radius, gboolean mid_only)
{
	
	double a,b,am,bm;
	
	am= p->mid.x;
	bm= p->mid.y;
	if(mid_only!=TRUE)
	{
		a= p->fwd.x;
		b= p->fwd.y;
		cairo_arc (cr, a, b, radius, 0, 2*M_PI);
		cairo_set_source_rgb (cr, 0, 0, 1);
		cairo_fill(cr);
		
		cairo_move_to (cr, a, b);
		cairo_line_to (cr, am, bm);
		cairo_stroke (cr);

		a= p->bwd.x;
		b= p->bwd.y;
		cairo_arc (cr, a, b, radius, 0, 2*M_PI);
		cairo_set_source_rgb (cr, 1, 0, 0);
		cairo_fill(cr);
		
		cairo_move_to (cr, a, b);
		cairo_line_to (cr, am, bm);
		cairo_stroke (cr);
	}
	cairo_rectangle (cr, am-(0.5*radius),bm-(0.5*radius),radius,radius);
	cairo_set_source_rgba (cr, /*rgb=*/0.0, 0.0, 1.0, /*alpha=*/ 0.5);
	cairo_fill(cr);
}

void bez_control_print(BezControl *p, FILE * stream)
{
	char *format= "		CONTROL BWD=(%d %d) MID=(%d %d)  FWD=(%d %d)\n";
	
	fprintf(stream, format, 	(int)p->bwd.x,(int)p->bwd.y,
						(int)p->mid.x, (int)p->mid.y,
						(int)p->fwd.x, (int)p->fwd.y);
}
BezFileError bez_control_scan(BezControl *p, FILE *file)
{
	char line[LINE_SIZE],trailing;
	char * format= "		CONTROL BWD=(%lf %lf) MID=(%lf %lf)  FWD=(%lf %lf) %c";
	
	char * result= fgets (line, LINE_SIZE, file);
	
	if(! result) return BEZ_FGETS_ERROR;
	
	if(sscanf ( result, format,	&p->bwd.x, &p->bwd.y,
							&p->mid.x, &p->mid.y,
							&p->fwd.x, &p->fwd.y,&trailing) != 6)
		 return BEZ_CONTROL_ERROR;
	  
	return BEZ_OK;
}
	


