//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_SMOOTHSTEPCURVE_HPP
#define R_TYPE_SMOOTHSTEPCURVE_HPP


#include "ITweeningCurve.hpp"

class SmoothStepCurve : public ITweeningCurve {
public:
    double Curve(const double &d) const override final;
};


#endif //R_TYPE_SMOOTHSTEPCURVE_HPP
