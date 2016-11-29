//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_SINECURVE_HPP
#define R_TYPE_SINECURVE_HPP


#include "ITweeningCurve.hpp"

class EaseInOutCurve : public ITweeningCurve {
public:
    double Curve(const double &d) const override final {
        return -0.5 * (cos(M_PI*d) - 1);
    }
};


#endif //R_TYPE_SINECURVE_HPP
