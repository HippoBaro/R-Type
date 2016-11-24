//
// Created by hippolyteb on 11/24/16.
//

#include <math.h>
#include "../../Include/EaseInOutCurve.hpp"

double EaseInOutCurve::Curve(const double &d) const {
    return -0.5 * (cos(M_PI*d) - 1);
}
