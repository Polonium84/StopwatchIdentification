#include "SWI_DIP_Test.h"

double Length(Vec4i line)
{
	int x1 = line[0];
	int y1 = line[1];
	int x2 = line[2];
	int y2 = line[3];
	return sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2);
}
double Length(Point p1, Point p2)
{
	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;
	return sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2);
}