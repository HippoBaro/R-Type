//
// Created by hippolyteb on 11/24/16.
//

#include "../../Include/SmoothStepCurve.hpp"

double SmoothStepCurve::Curve(const double &d) const {
    return (d*d *(3 - 2*d));
}
