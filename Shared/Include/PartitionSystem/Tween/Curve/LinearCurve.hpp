//
// Created by hippolyteb on 11/24/16.
//

#ifndef R_TYPE_LINEARCURVE_HPP
#define R_TYPE_LINEARCURVE_HPP

#include "PartitionSystem/Tween/Curve/ITweeningCurve.hpp"

class LinearCurve : public ITweeningCurve {
    double Curve(double const &d) const override final {
        return d;
    }
};


#endif //R_TYPE_LINEARCURVE_HPP
