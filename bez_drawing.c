#include "bez_drawing.h"

void bez_drawing_insert_curve	   (BezDrawing   * d, BezCurve  * c, unsigned  index)
{
	
	g_array_insert_val(d->curves,index, c);
	
}
BezDrawing   *	bez_drawing_new		(void)
{
	
	
	gboolean zero_terminated=FALSE,cells_zeroed=TRUE;
	
	BezDrawing * d=g_new(BezDrawing,1);
	
	d->curves=g_array_new ( zero_terminated, cells_zeroed,sizeof(BezCurve*));
	
	return d;
	
}

unsigned     bez_drawing_nb_curves		(BezDrawing   * d)
{
	return d->curves->len;
}

BezCurve  *  bez_drawing_get_curve		(BezDrawing   * d, unsigned  k)
{
	return g_array_index(d->curves, BezCurve *, k);
}
	
	
unsigned     bez_drawing_get_curve_index	(BezDrawing   * d, BezCurve  * c)
{
	unsigned k, n=bez_drawing_nb_curves(d);

	for(k=0;k<n;k++)
		if(bez_drawing_get_curve(d, k)==c)
			return k;
	return -1U;
}

void		bez_drawing_destroy	(BezDrawing   * d)
{
	
	gboolean  free_cells_segment=TRUE;
	unsigned k, n=bez_drawing_nb_curves(d);
	
	for(k=0;k<n;k++)
		bez_curve_destroy(bez_drawing_get_curve(d, k));
	g_array_free(d->curves, free_cells_segment);
	g_free(d);

}


void bez_drawing_add_curve	   (BezDrawing   * d, BezCurve  * c)
{
	g_array_append_val(d->curves,c);
	
}
	

void bez_drawing_remove_curve	   (BezDrawing   * d, BezCurve  * c, gboolean destroy)
{
	unsigned k=bez_drawing_get_curve_index(d,c);
	if(k==-1U) return ;
	if(destroy)bez_curve_destroy(c);
	g_array_remove_index(d->curves, k);
}
void bez_drawing_remove_control   (BezDrawing   * d, BezCurve  * c, BezControl * p, gboolean destroy)
{
	bez_curve_remove_control	(c, p,  destroy);
	if(c->controls->len==0)bez_drawing_remove_curve	   ( d,  c, destroy);
}
void bez_drawing_duplicate_curve	   (BezDrawing   * d, BezCurve  * c, double dupli)
{
	BezControl *b=NULL,*cont=NULL;
	BezCurve * curve=bez_curve_new  	();
	unsigned k, n=bez_curve_nb_controls(c);
	for(k=0;k<n;k++)
	{
		b=bez_curve_get_control(c, k);
		cont=bez_control_new_duplicate(b,dupli,dupli);
		bez_curve_add_control	(curve, cont);
	}
	curve->is_closed=c->is_closed;
	curve->is_filled=c->is_filled;
	curve->fill_color=c->fill_color;
	curve->is_stroked=c->is_stroked;
	curve->stroke_color=c->stroke_color;
	bez_drawing_add_curve	   ( d,curve);
}
				
void bez_drawing_draw_controls_cr(BezDrawing   * d, cairo_t *cairo,double radius, gboolean mid_only)
{
	
	unsigned k, n=bez_drawing_nb_curves(d);
	BezCurve *c;
	for(k=0;k<n;k++)
	{
		
		c=bez_drawing_get_curve(d,k);
		bez_curve_draw_controls_cr(c, cairo, radius, mid_only);
	}
}

void bez_drawing_draw_curves_cr	(BezDrawing   * d, cairo_t *cr, double radius, gboolean mid_only)
{
	unsigned k, n=bez_drawing_nb_curves(d);
	
	BezCurve *c;
	
	for(k=0;k<n;k++)
	{
		
		
		c=bez_drawing_get_curve(d,k);
		bez_curve_draw_curves_cr(c, cr);
		bez_curve_draw_controls_cr	(c, cr, radius, mid_only);

	}
}


BezFileError bez_drawing_scan	(BezDrawing   * d, FILE * f)
{

	
	int nb,i=0;
	BezCurve *c=NULL;
	char line[LINE_SIZE],trailing;
	char * result= fgets (line, LINE_SIZE, f);
	char * format= "DRAWING NB_CURVES %d";
	
	
	if(! result)
	{
		printf("non resultat\n");
		return BEZ_FGETS_ERROR;
	}
	if(sscanf ( result, format,&nb,&trailing) !=1)
	{
		
		printf("erreur sscanf dans bez_draw\n");
		return BEZ_CURVE_ERROR;
	}
	
	else
	{
		
		while(i<nb)
		{	
			c= bez_curve_new	();
			bez_drawing_add_curve	   (d,c);
			bez_curve_scan(c, f);
			i++;
		}
	
	}
	
	  
	return BEZ_OK; 
}

void bez_drawing_print	(BezDrawing   * d, FILE * f)
{
	
	unsigned k, n=bez_drawing_nb_curves(d);
	BezCurve *c;
	char * format="DRAWING NB_CURVES %d\n";
	
	fprintf(f, format, n);
	
	for(k=0;k<n;k++)
	{
		c=bez_drawing_get_curve(d,k);
		bez_curve_print (c, f);
	}
}

BezFileError bez_drawing_load	(BezDrawing   * d, const gchar *filename)
{

	FILE* f;
	BezFileError Er;
	f=fopen(filename,"r");
	if(f==NULL) return BEZ_FOPEN_ERROR;
	
	else 
	{
	 	Er=bez_drawing_scan( d, f);
		fclose(f);
		return Er;
	}
}
BezFileError bez_drawing_save	(BezDrawing   * d,const gchar *filename)
{
	
	int i,lgch=strlen(filename);
	gchar *fichier;
	FILE* f;
	fichier=malloc(lgch*sizeof(gchar));
	for(i=0;i<lgch;i++)
	fichier[i]=filename[i];
	printf("le fichier %s est sauvé ciao\n",fichier);
	
	f=fopen(fichier,"w");
	if(f==NULL) return BEZ_FOPEN_ERROR;
	
	else 
	{
	 	bez_drawing_print( d, f);
		fclose(f);
		
	}
	return BEZ_OK;
}


void bez_spot_init(BezSpot *s, BezDrawing   * d, BezCurve *c, BezControl *p, Point *q)
{
	s->drawing=d; 
	s->curve=c;
	s->control=p;
	s->point=q;
}

void bez_spot_init_null(BezSpot *s)
{
	s->drawing=NULL; 
	s->curve=NULL;
	s->control=NULL;
	s->point=NULL;
	s=NULL;
}

gboolean bez_drawing_near_spot(BezDrawing   * d,  Point q, double delta, gboolean mid_only, BezSpot *s)
{
	
	unsigned k,j, n=bez_drawing_nb_curves(d),n2;
	BezCurve *c=NULL;
	BezControl *p=NULL;
	Point *qt=NULL;
	bez_spot_init_null(s);
	for(k=0;k<n;k++)
	{
		c=bez_drawing_get_curve(d,k);
		n2=bez_curve_nb_controls(c);
		for(j=0;j<n2;j++)
		{
			p=bez_curve_get_control(c,j);
			qt=bez_control_near_point(p,q,delta,mid_only);
			if(qt!=NULL)
			{
				bez_spot_init(s, d, c, p,qt);
				return TRUE;
			}
		
		
		}
		
				
	}
	return FALSE;
}

void bez_spot_draw	(BezSpot *s,GdkWindow *window, GdkGC *gc, double radius)
{
	
	Point *p=s->point;
	gc_set_rgb_fg (gc, 0x000000);
	gdk_draw_arc(window,gc,FALSE,p->x-radius,p->y-radius,p->x+radius,p->y+radius,64,360*64);
}

void bez_spot_draw_cr	(BezSpot *s, cairo_t *cairo, double radius)
{
	Point *p=s->point;
	if(p!=NULL)
	{
	cairo_arc (cairo, p->x,p->y,radius, 0, 2*M_PI);
	cairo_set_source_rgb (cairo, 0, 0, 0);
	cairo_stroke(cairo);
	}
	
}
