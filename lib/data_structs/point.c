
#include "psyrender.h"

void Point_copy(Point* out, const Point* in) {
    memcpy((void*) out, (void*) in, sizeof(Point));
}

bool Point_is_equal(const Point* p1, const Point* p2, double epsilon) {
    return fabs(p1->x - p2->x) <= epsilon &&
           fabs(p1->y - p2->y) <= epsilon &&
           fabs(p1->z - p2->z) <= epsilon;
}
