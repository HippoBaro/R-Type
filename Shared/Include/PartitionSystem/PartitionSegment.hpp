//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENT_HPP
#define R_TYPE_PARTITIONSEGMENT_HPP

#include <vec2.hpp>
#include <PartitionSystem/Tween/Tween.hpp>
#include <string>

class PartitionSegment : public RType::ISerializable {
private:
    Tween<vec2<float>> _locationVector;
    std::string _projectileType = "";
    int _shootNumber = 0;
    TimeRef _lastShot = TimeRef();
    long _timeBeetweenShot = 0;

public:
    PartitionSegment() : _locationVector() {

    }
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
        auto lasp = timeRef.getMilliseconds().count() - _lastShot.getMilliseconds().count();
        if (_timeBeetweenShot > 0 && lasp > _timeBeetweenShot) {
            this->_lastShot = TimeRef(timeRef.getMilliseconds());
            return true;
        }
        return false;
    }

    std::string getCurrentProjectile() {
        return _projectileType;
    }

    void Serialize(RType::Packer &packer) override {
        _locationVector.Serialize(packer);
        packer.Pack(_projectileType);
        packer.Pack(_shootNumber);
        _locationVector.Serialize(packer);
        packer.Pack(_timeBeetweenShot);
    }
};


#endif //R_TYPE_PARTITIONSEGMENT_HPP
