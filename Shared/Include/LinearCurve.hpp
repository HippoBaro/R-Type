//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_LINEARCURVE_HPP
#define R_TYPE_LINEARCURVE_HPP

#include "ITweeningCurve.hpp"

class LinearCurve : public ITweeningCurve {
    double Curve(double const &d) const override final;
};


#endif //R_TYPE_LINEARCURVE_HPP
