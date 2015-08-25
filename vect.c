#include "vect.h"

void point_init_zero (Point *p)
{
	p->x=0;
	p->y=0;
}
void point_init_xy (Point *p, double x, double y)
{
	p->x=x;
	p->y=y;
}
Vector vector_add (Vector v, Vector w)
{
	Vector V;
	V.x=v.x+w.x;
	V.y=v.y+w.y;
	return V;
}

Vector vector_sub (Vector v, Vector w)
{
	Vector V;
	V.x=v.x-w.x;
	V.y=v.y-w.y;
	return V;
}
gboolean com_vector(Point *v, Vector u)
{	
	if(u.x!=v->x)return FALSE;
	if(u.y!=v->y)return FALSE;
	return TRUE;
}
double distance(Point p, Point q)
{
	
	return sqrt(pow(p.x-q.x,2)+pow(p.y-q.y,2));
	
	
}
Vector point_vector (Point p, Point q)
{
	
	return vector_sub (q,p);
	 
}
void point_translate (Point *p, Vector v)
{
	p->x=p->x+v.x;
	p->y=p->y+v.y;
}
void vector_scale (Vector *v, double lambda)
{
	v->x=lambda*v->x;
	v->y=lambda*v->y;
}

gboolean point_is_near (Point p, Point q,double delta)
{
	
	if( distance(p, q)<=delta) return 1;
	return 0;
}

Point point_bezier (Point a, Point b, Point c, Point d, double t)
{
	Point p; double s=1-t;
	double ss=s*s,sss=ss*s,sst3=ss*t*3;
	double tt=t*t,ttt=tt*t,stt3=tt*s*3;
	p.x=sss*a.x+sst3*b.x + stt3* c.x + ttt* d.x;
	p.y=sss*a.y+sst3*b.y + stt3* c.y + ttt* d.y;
	return p;
}
