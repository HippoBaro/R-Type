//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_SMOOTHSTEPCURVE_HPP
#define R_TYPE_SMOOTHSTEPCURVE_HPP


#include "PartitionSystem/Tween/Curve/ITweeningCurve.hpp"

class SmoothStepCurve : public ITweeningCurve {
public:
    double Curve(const double &d) const override final{
        return (d*d *(3 - 2*d));
    }
};


#endif //R_TYPE_SMOOTHSTEPCURVE_HPP
