#ifndef BEZ_DRAWING__H
#define BEZ_DRAWING__H

#include "bez_curve.h"

typedef struct BezDrawing 
{
	GArray *curves;
}BezDrawing ;

typedef struct BezSpot
{
	BezDrawing *drawing; BezCurve *curve;
	BezControl *control; Point * point;
}BezSpot;
BezDrawing   *	bez_drawing_new		(void);
void		bez_drawing_destroy	(BezDrawing   * d);

unsigned     bez_drawing_nb_curves		(BezDrawing   * d);
BezCurve  *  bez_drawing_get_curve		(BezDrawing   * d, unsigned  k);
unsigned     bez_drawing_get_curve_index	(BezDrawing   * d, BezCurve  * c);

void bez_drawing_add_curve	   (BezDrawing   * d, BezCurve  * c);
void bez_drawing_insert_curve	   (BezDrawing   * d, BezCurve  * c, unsigned  index);
void bez_drawing_remove_curve	   (BezDrawing   * d, BezCurve  * c, gboolean destroy);
void bez_drawing_remove_control	   (BezDrawing   * d, BezCurve  * c,BezControl *p, gboolean destroy);
void bez_drawing_duplicate_curve	   (BezDrawing   * d, BezCurve  * c, double dupli);


void bez_drawing_draw_controls_cr	(BezDrawing   * d, cairo_t *cairo,
				double radius, gboolean mid_only);


void bez_drawing_draw_curves_cr	(BezDrawing   * d, cairo_t *cr, double radius, gboolean mid_only);

BezFileError bez_drawing_scan	(BezDrawing   * d, FILE * f);
void bez_drawing_print	(BezDrawing   * d, FILE * f);

BezFileError bez_drawing_load	(BezDrawing   * d, const gchar *filename);
BezFileError bez_drawing_save	(BezDrawing   * d,const gchar *filename);







void bez_spot_init(BezSpot *s, BezDrawing   * d, BezCurve *c, BezControl *p, Point *q);
void bez_spot_init_null(BezSpot *s);

gboolean bez_drawing_near_spot(BezDrawing   * d,  Point q, double delta, gboolean mid_only, BezSpot *s);

void bez_spot_draw	(BezSpot *s,GdkWindow *window, GdkGC *gc, double radius);
void bez_spot_draw_cr	(BezSpot *s, cairo_t *cairo, double radius);

#endif
