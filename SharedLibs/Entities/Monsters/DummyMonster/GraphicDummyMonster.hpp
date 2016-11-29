//
// Created by hippolyteb on 11/29/16.
//

#ifndef R_TYPE_GRAPHICDUMMYMONSTER_HPP
#define R_TYPE_GRAPHICDUMMYMONSTER_HPP

#include "DummyMonster.hpp"

class GrahicDummyMonster : DrawableEntity, public DummyMonster {

public:
    GrahicDummyMonster(Timer *timer);

public:
    void Draw(sf::RenderTexture &rect) override;
    vec2<int> GetRenderRect() override;
    vec2<int> GetPosition() override;
};

#endif //R_TYPE_GRAPHICDUMMYMONSTER_HPP
