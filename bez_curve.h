#ifndef __BEZ_CURVE__
#define __BEZ_CURVE__

#include "bez_control.h"

typedef struct BezCurve
{
	GArray *controls;
	gint is_stroked,is_filled,is_closed;
	guint fill_color,stroke_color;

}BezCurve;

BezCurve * bez_curve_new  	(void);
void       bez_curve_destroy	(BezCurve * c);

unsigned	bez_curve_nb_controls		(BezCurve *c);
BezControl  *   bez_curve_get_control		(BezCurve *c, unsigned k);
unsigned	bez_curve_get_control_index	(BezCurve *c, BezControl * p);

void bez_curve_add_control	(BezCurve *c, BezControl * p);
void bez_curve_insert_control	(BezCurve *c, BezControl * p, unsigned index);
void bez_curve_remove_control	(BezCurve *c, BezControl * p, gboolean destroy);

void bez_curve_translate	(BezCurve *c, Vector v);
void bez_curve_autoadapt_control(BezCurve *c, BezControl * p);


void bez_curve_draw_controls_cr	(BezCurve *c, cairo_t *cr,
				double radius, gboolean mid_only);

void bez_curve_draw_curves_cr	(BezCurve *c, cairo_t *cr);

BezFileError bez_curve_scan	(BezCurve *c, FILE * f);
void	     bez_curve_print	(BezCurve *c, FILE * f);
#endif
