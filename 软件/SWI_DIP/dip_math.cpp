#include "SWI_DIP.h"
double Length(Line line)
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
double CosineLaw(Line v1, Line v2)
{
	Vec2i a = { v1[2] - v1[0],v1[3] - v1[1] };
	Vec2i b = { v2[2] - v2[0],v2[3] - v2[1] };
	double top = a[0] * b[0] + a[1] * b[1];
	double bottom = Length(v1) * Length(v2);
	return top / bottom;
}
Point Midpoint(Point p1, Point p2)
{
	double x = round((p1.x + p2.x) / 2.0);
	double y = round((p1.y + p2.y) / 2.0);
	return Point(x, y);
}
Point Midpoint(Line line)
{
	Point p1 = Point(line[0], line[1]);
	Point p2 = Point(line[2], line[3]);
	return Midpoint(p1, p2);
}
Point IntersectionPoint(Point p, Point center, int radius)
{
	double ratio = (double)radius / Length(center, p);
	double x = round(center.x + (p.x - center.x) * ratio);
	double y = round(center.y + (p.y - center.y) * ratio);
	return Point(x, y);
}
bool IsMoreThan180(Line v1, Line v2)
{
	Vec2i a = { v1[2] - v1[0],v1[3] - v1[1] };
	Vec2i b = { v2[2] - v2[0],v2[3] - v2[1] };
	return a[0] * b[1] - a[1] * b[0] < 0;
}