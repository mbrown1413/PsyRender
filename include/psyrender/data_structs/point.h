#ifndef _PSY_POINT_H
#define _PSY_POINT_H

typedef Vector Point;

void Point_copy(Point* out, const Point* in);
bool Point_is_equal(const Point* p1, const Point* p2, double epsilon);

#endif
