//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include <vec2.hpp>
#include <PartitionSystem/Tween/Tween.hpp>

class PartitionSegment {
private:
    Tween<vec2<int>> _locationVector;

public:
    PartitionSegment() : _locationVector() {}
    PartitionSegment(const Tween<vec2<int>> &locationVector): _locationVector(locationVector) {}

public:
    Tween<vec2<int>> getLocationVector() const {
        return _locationVector;
    }

    bool isPartOf(TimeRef const &timeRef){
        return this->_locationVector.isPartOf(timeRef);
    }

};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
