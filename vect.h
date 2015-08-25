#ifndef VECT__H
#define VECT__H
#include "util.h"
typedef struct Point
{
	double x,y;

}Point;
typedef Point Vector;
void point_init_zero (Point *p);
void point_init_xy (Point *p, double x, double y);
double distance(Point p, Point q);
Vector vector_add (Vector v, Vector w);
Vector vector_sub (Vector v, Vector w);
Vector point_vector (Point p, Point q);
void point_translate (Point *p, Vector v);
void vector_scale (Vector *v, double lambda);
gboolean com_vector(Point *v, Vector u);

gboolean point_is_near (Point p, Point q,double delta);
Point point_bezier (Point a, Point b, Point c, Point d, double t);


#endif
