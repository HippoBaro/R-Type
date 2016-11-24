//
// Created by hippolyteb on 11/24/16.
//

#include <math.h>
#include <EaseOutCurve.hpp>

double EaseOutCurve::Curve(const double &d) const {
    return sin(d * (M_PI/2));
}
