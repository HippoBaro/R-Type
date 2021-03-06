//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_EASEINCURVE_HPP
#define R_TYPE_EASEINCURVE_HPP


#include "ITweeningCurve.hpp"

class EaseInCurve : public ITweeningCurve {
    double Curve(const double &d) const override final{
        return 1 - cos(d * (M_PI/2));
    }
};


#endif //R_TYPE_EASEINCURVE_HPP
