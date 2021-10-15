#include "hash.h"

double absDist(Point a, Point b)
{
	int xdif = a.absx-b.absx;
	int ydif = a.absy-b.absy;

	return sqrt(xdif*xdif+ydif*ydif);
}

double dist(Point a, Point b)
{
	double xdif = a.x-b.x;
	double ydif = a.y-b.y;

	return sqrt(xdif*xdif+ydif*ydif);
}

void toAbsPoint(Point* p, int CELL_SIZE)
{
	p->absx=(int)floor(p->x * CELL_SIZE);
	p->absy=(int)floor(p->y * CELL_SIZE);
}

int toHashed(Point p, int CELL_SIZE)
{
	return CELL_SIZE * p.absy + p.absx;
}
