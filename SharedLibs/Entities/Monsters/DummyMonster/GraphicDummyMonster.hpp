//
// Created by hippolyteb on 11/29/16.
//

#ifndef R_TYPE_GRAPHICDUMMYMONSTER_HPP
#define R_TYPE_GRAPHICDUMMYMONSTER_HPP

#include <IDrawable.hpp>
#include "DummyMonster.hpp"

class GrahicDummyMonster : public DummyMonster, public IDrawable {

public:
    GrahicDummyMonster(const std::initializer_list<void *> init);

public:
    void Draw(sf::RenderTexture *rect, TextureBag &) override;


    virtual bool DidChangeDraw() override ;

    void Cycle() override;
};

#endif //R_TYPE_GRAPHICDUMMYMONSTER_HPP
