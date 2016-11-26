//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_PARTITIONSEGMENTBUILDER_HPP
#define R_TYPE_PARTITIONSEGMENTBUILDER_HPP

#include <memory>
#include "PartitionSegment.hpp"
#include "../../Include/ITweeningCurve.hpp"
#include "../../Include/vec2.hpp"

class PartitionSegmentBuilder {
private:
    ITweeningCurve *_curvingOption = nullptr;

    TimeRef _start = TimeRef();
    TimeRef _end = TimeRef();

    vec2d _startValue = vec2d();
    vec2d _endValue = vec2d();

public:

    PartitionSegmentBuilder &From(vec2d const &);
    PartitionSegmentBuilder &To(vec2d const &);
    PartitionSegmentBuilder &Begins(TimeRef const &);
    PartitionSegmentBuilder &BeginsAfterPrevious();
    PartitionSegmentBuilder &Ends(TimeRef const &);
    template <class Curve> PartitionSegmentBuilder &WithCurving();
    PartitionSegment Build(Timer *);
};


#endif //R_TYPE_PARTITIONSEGMENTBUILDER_HPP
