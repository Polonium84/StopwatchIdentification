#include "SWI_DIP_Test.h"

double Length(Vec4i line)
{
	int x1 = line[0];
	int y1 = line[1];
	int x2 = line[2];
	int y2 = line[3];
	return hypot((x1 - x2), (y1 - y2));
}
double Length(Point p1, Point p2)
{
	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;
	return hypot((x1 - x2), (y1 - y2));
}
double CosineLaw(Point p1, Point p2, Point p3)
{
	double a = Length(p1, p2);
	double b = Length(p1, p3);
	double c = Length(p2, p3);
	double top = b * b + c * c - a * a;
	double bottom = 2 * b * c;
	return top / bottom;
}
Point Midpoint(Point p1, Point p2)
{
	double x = round((p1.x + p2.x) / 2.0);
	double y = round((p1.y + p2.y) / 2.0);
	return Point(x, y);
}