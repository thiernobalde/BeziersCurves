#ifndef __BEZ_CONTROL__
#define __BEZ_CONTROL__

#include "util.h"
#include "vect.h"
#include "bez_enum.h"


typedef struct BezControl 
{
	Point bwd,mid,fwd;
}BezControl ;

BezControl *bez_control_new(void);
BezControl *bez_control_new_xy(double mid_x,double mid_y);
BezControl *bez_control_new_duplicate(BezControl *p,double dup_x,double dup_y);
void  bez_control_destroy(BezControl *p);

Point *bez_control_near_point(BezControl *p,Point q,double delta, gboolean mid_only);
void  bez_control_translate_mid(BezControl *p,Vector v);
void  bez_control_translate_fwd(BezControl *p,Vector v,gboolean align);
void  bez_control_translate_bwd(BezControl *p,Vector v,gboolean align);
void  bez_control_draw_cr (BezControl *p,cairo_t *cr,int radius, gboolean mid_only);
BezFileError bez_control_scan(BezControl *p, FILE *f);
void bez_control_print(BezControl *p, FILE * stream);
#endif
