//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include <vec2.hpp>
#include <Tween.hpp>

class PartitionSegment {
private:
    Tween<vec2<unsigned int>> _locationVector;

public:
    PartitionSegment();
    PartitionSegment(const Tween<vec2<unsigned int>> &locationVector);

public:
    Tween<vec2<unsigned int>> getLocationVector() const;
    bool isPartOf(TimeRef const &timeRef);


};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
