#include "bez_curve.h"

BezCurve * bez_curve_new	(void)
{
	gboolean zero_terminated=FALSE,cells_zeroed=TRUE;
	
	BezCurve * c=g_new(BezCurve,1);

	
	c->controls=g_array_new ( zero_terminated, cells_zeroed,sizeof(BezControl*));
	c->is_closed=0, c->is_stroked=1, c->is_filled=0, 
	c->fill_color=0,c->stroke_color=0; 
	
	return c;
}


unsigned	bez_curve_nb_controls		(BezCurve *c)
{
	return c->controls->len;
}

BezControl  *   bez_curve_get_control		(BezCurve *c, unsigned k)
{
	return g_array_index(c->controls, BezControl *, k);
}

void       bez_curve_destroy	(BezCurve * c)
{
	gboolean  free_cells_segment=TRUE;
	unsigned k, n=bez_curve_nb_controls(c);
	
	for(k=0;k<n;k++)
		bez_control_destroy(bez_curve_get_control(c, k));
	g_array_free(c->controls, free_cells_segment);
	g_free(c);

}
unsigned	bez_curve_get_control_index	(BezCurve *c, BezControl * p)
{
	
	unsigned k, n=bez_curve_nb_controls(c);
	
	for(k=0;k<n;k++)
		if(bez_curve_get_control(c, k)==p)
			return k;
	return -1U;
}

void bez_curve_add_control	(BezCurve *c, BezControl * p)
{
	
	g_array_append_val(c->controls,p);
}

void bez_curve_insert_control	(BezCurve *c, BezControl * p, unsigned index)
{
	
	g_array_insert_val(c->controls,index, p);
}

void bez_curve_remove_control	(BezCurve *c, BezControl * p, gboolean destroy)
{

	unsigned k=bez_curve_get_control_index(c,p);
	if(k==-1U) return ;
	if(destroy)bez_control_destroy(p);
	g_array_remove_index(c->controls, k);
}

void bez_curve_translate	(BezCurve *c, Vector v)
{

	BezControl *b;
	unsigned k, n=bez_curve_nb_controls(c);
	for(k=0;k<n;k++)
	{
		b=bez_curve_get_control(c, k);
		bez_control_translate_mid(b,v);
 		
	}
}


void bez_curve_autoadapt_control(BezCurve *c, BezControl * p)
{
	
	Vector v;
	BezControl *q1, *q2;
	unsigned n=bez_curve_nb_controls(c);
	unsigned k=bez_curve_get_control_index	(c,p);
	
	if(k!=-1U)
	{
		q1=bez_curve_get_control(c, (k+n-1)%n);
		q2=bez_curve_get_control(c, (k+1)%n);
		
		v=vector_sub (q2->mid, q1->mid);
		vector_scale (&v,1/6);
		v=vector_add (v,p->mid);
		
		bez_control_translate_fwd(p, v,TRUE);
	}
	

}

void bez_curve_draw_controls_cr	(BezCurve *c, cairo_t *cr, double radius, gboolean mid_only)
{
	
	unsigned k, n=bez_curve_nb_controls(c);
	BezControl *b;
	for(k=0;k<n;k++)
	{
		
		b=bez_curve_get_control(c,k);
		bez_control_draw_cr (b,cr ,(int)radius, mid_only);
	}
	
	
}


void bez_curve_draw_curves_cr	(BezCurve *c, cairo_t *cr)
{
			
	unsigned k, n=bez_curve_nb_controls(c);
	BezControl *b0,*b1,*b2;
	GdkColor * color;
	
	if(n>=1)
	{
		
		b0=bez_curve_get_control(c,0);
		
		if(n>1)b1=bez_curve_get_control(c,1);
		else b1=b0;
		cairo_move_to(cr, b0->mid.x,b0->mid.y);
		
		cairo_curve_to(cr,b0->fwd.x,b0->fwd.y,b1->bwd.x,b1->bwd.y,b1->mid.x,b1->mid.y);
		k=2;
		
		while(k<n)
		{
			b2=bez_curve_get_control(c,k);
			
			cairo_curve_to(cr,b1->fwd.x,b1->fwd.y,b2->bwd.x,b2->bwd.y,b2->mid.x,b2->mid.y);
			b1=b2;
			k++;
		}
		
		if(c->is_closed==TRUE)
		{
			
			cairo_curve_to(cr,b1->fwd.x,b1->fwd.y,b0->bwd.x,b0->bwd.y,b0->mid.x,b0->mid.y);
		}
		if((c->is_filled==TRUE)&&(c->is_closed==TRUE))
		{
			color=static_color_from_rgb (c->stroke_color);
			gdk_cairo_set_source_color (cr, color);
			cairo_stroke_preserve(cr);

			color=static_color_from_rgb (c->fill_color);
			gdk_cairo_set_source_color (cr, color);
			cairo_fill (cr);
		}
		else
		{
			color=static_color_from_rgb (c->stroke_color);
			gdk_cairo_set_source_color (cr, color);
			cairo_stroke(cr);
		}
	}
	
}

BezFileError bez_curve_scan	(BezCurve *c, FILE * f)
{
	int i=1,nb;
	
	BezControl * p=NULL;
	
	char line[LINE_SIZE],trailing;
	char * format= "	CURVE NB_CONTROLS=%d CLOSED=%d STROKE=(%x %d) FILL=(%x %d) %c";
	char * result= fgets (line, LINE_SIZE, f);
	
	
	if(! result) return BEZ_FGETS_ERROR;
	
	if(sscanf ( result, format,&nb, &c->is_closed,
					&c->stroke_color, &c->is_stroked,
					 &c->fill_color,&c->is_filled,&trailing)!= 6) 
	{			
		
		printf("BEZ_CURVE_ERROR \n");
		return BEZ_CURVE_ERROR;
	}
	else
	{
		
		
		
		while(i<=nb)
		{
			p=bez_control_new();
			bez_control_scan(p, f);
			bez_curve_add_control(c,p);
			
			
			
				
			
			i++;
		}
	}
		
	
	  
	return BEZ_OK; 
}
		
void	     bez_curve_print	(BezCurve *c, FILE * f)
{
	unsigned k, n=bez_curve_nb_controls(c);
	BezControl *p;
	
	char * format= "	CURVE NB_CONTROLS=%d CLOSED=%d STROKE=(%x %d) FILL=(%x %d)\n";
	
	fprintf(f, format, n, c->is_closed,
					c->stroke_color, c->is_stroked,
					c->fill_color, c->is_filled);
	
	for(k=0;k<n;k++)
	{
		p=bez_curve_get_control(c,k);
		bez_control_print (p, f);
	}
}
		
