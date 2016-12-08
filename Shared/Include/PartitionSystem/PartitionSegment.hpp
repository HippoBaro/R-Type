//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include <vec2.hpp>
#include <PartitionSystem/Tween/Tween.hpp>
#include <string>

class PartitionSegment {
private:
    Tween<vec2<float>> _locationVector;
    std::string _projectileType = "";
    int _shootNumber = 0;
    long _lastShot = getStart().getMilliseconds().count();
    long _timeBeetweenShot = 0;

public:
    PartitionSegment() : _locationVector() {}
    PartitionSegment(const Tween<vec2<float>> &locationVector, float fireRate, std::string const &projectileType): _locationVector(locationVector),
                                                                                                                   _projectileType(projectileType){

        auto totalDuration = (getEnd().getMilliseconds() - getStart().getMilliseconds()).count();
        _shootNumber = (int) (fireRate * totalDuration / 1000);
        if (_shootNumber > 0)
            _timeBeetweenShot = totalDuration / _shootNumber;
    }

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

    TimeRef getEnd() {
        return this->_locationVector.getEnd();
    }

    bool ShouldFireNow(TimeRef const &timeRef) {
        auto start = getStart();
        auto end = getEnd();
        if (timeRef < start || timeRef > end)
            return false;
        auto lasp = timeRef.getMilliseconds().count() - _lastShot;
        if (_timeBeetweenShot > 0 && lasp > _timeBeetweenShot) {
            _lastShot = timeRef.getMilliseconds().count();
            return true;
        }
        return false;
    }

    std::string getCurrentProjectile() {
        return _projectileType;
    }
};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
