//
// Created by hippolyteb on 11/24/16.
//

#include <cmath>
#include "../../Include/EaseInCurve.hpp"

double EaseInCurve::Curve(const double &d) const {
    return 1 - cos(d * (M_PI/2));
}
