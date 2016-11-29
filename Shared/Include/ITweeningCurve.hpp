//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_ITWEENINGCURVE_HPP
#define R_TYPE_ITWEENINGCURVE_HPP

#if MSCV
#define _USE_MATH_DEFINES
#endif
#include <math.h>

class ITweeningCurve {
public:
    virtual ~ITweeningCurve() { }

    virtual double Curve(const double &) const = 0;
};

#endif //R_TYPE_ITWEENINGCURVE_HPP
