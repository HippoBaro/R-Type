//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include "../../Include/vec2.hpp"
#include "../../Include/Tween.hpp"

class PartitionSegment {
private:
    Tween<vec2d> _locationVector;

public:
    PartitionSegment();
    PartitionSegment(const Tween<vec2d> &locationVector);

public:
    Tween<vec2d> getLocationVector() const;
    bool isPartOf(TimeRef const &timeRef);
};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
