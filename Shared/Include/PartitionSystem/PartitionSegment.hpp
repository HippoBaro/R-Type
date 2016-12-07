//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include <vec2.hpp>
#include <PartitionSystem/Tween/Tween.hpp>

class PartitionSegment {
private:
    Tween<vec2<float>> _locationVector;
    float _fireRate = 0;
    std::string _projectileType = "";

public:
    PartitionSegment() : _locationVector() {}
    PartitionSegment(const Tween<vec2<float>> &locationVector, float fireRate, std::string const &projectileType): _locationVector(locationVector),
                                                                                                                   _fireRate(fireRate),
                                                                                                                   _projectileType(projectileType){}

public:
    Tween<vec2<float>> getLocationVector() const {
        return _locationVector;
    }

    bool isPartOf(TimeRef const &timeRef) {
        return this->_locationVector.isPartOf(timeRef);
    }

    TimeRef getStart() {
        return this->_locationVector.getStart();
    }

    bool ShouldFireNow(TimeRef const &timeRef) {
        //auto totalSegmentDuration = _locationVector.getEnd().getMilliseconds() - _locationVector.getStart().getMilliseconds();
        //auto

        return timeRef.getMilliseconds().count() % 5 == 0;
    }

    std::string getCurrentProjectile() {
        return _projectileType;
    }
};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
