#ifndef _MATHQ_H_
#define _MATHQ_H_

#include <cmath>

struct Point{
    int x;
    int y;
};

class MathTwoPoint{
public:
    static int CalcDistance(const Point p1, const Point p2);
};

#endif
