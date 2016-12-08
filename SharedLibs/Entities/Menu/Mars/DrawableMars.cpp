//
// Created by pasteu_e on 07/12/16.
//

#include "DrawableMars.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

DrawableMars::DrawableMars(const std::initializer_list<void *> init) : DrawableMars(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

DrawableMars::DrawableMars(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(45))
                            .Translate(vec2<float>(-2500, 0)))
            .Loop(99)
            .Build();
}

void DrawableMars::Draw(sf::RenderTexture &rect) {
    sf::Texture texture;
    rect.clear(sf::Color::Transparent);
    texture.loadFromFile("sprites/mars.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));
    rect.draw(sprite);
}

vec2<float> DrawableMars::GetRenderRect() {
    return vec2<float>(500 * 0.6, 500 * 0.6);
}

vec2<float> DrawableMars::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableMars)