//
// Created by hippolyteb on 11/25/16.
//

#ifndef R_TYPE_DUMMYMONSTER_HPP
#define R_TYPE_DUMMYMONSTER_HPP


#include "EntityPartition.hpp"
#include <Entity.hpp>
#include <Timer.hpp>
#include <Base.h>
#include <IDrawable.hpp>
#include "PartitionSegmentBuilder.hpp"

class DummyMonster : public Entity, public IDrawable {
private:
    Timer *_timer;
    EntityPartition _partition;

public:
    DummyMonster(Timer *timer);

    void Draw(sf::RenderTexture &rect) override;

    vec2<unsigned int> GetRenderRect() override;

    vec2<unsigned int> GetPosition() override;
};


#endif //R_TYPE_DUMMYMONSTER_HPP
