#include "mathq.h"

int MathTwoPoint::CalcDistance(const Point p1, const Point p2) {
    return std::abs(std::sqrt(pow(p2.x - p1.x, 2) +
                     pow(p2.y - p1.y, 2)));
}
