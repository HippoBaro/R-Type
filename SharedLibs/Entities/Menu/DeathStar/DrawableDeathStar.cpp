//
// Created by pasteu_e on 07/12/16.
//

#include "DrawableDeathStar.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>

DrawableDeathStar::DrawableDeathStar(const std::initializer_list<void *> init) : DrawableDeathStar(GetParamFromInitializerList<Timer*>(init, 0), GetParamFromInitializerList<RType::EventManager*>(init, 1), *GetParamFromInitializerList<TimeRef*>(init, 2), *GetParamFromInitializerList<vec2<float>*>(init, 3)) { }

DrawableDeathStar::DrawableDeathStar(Timer *timer, RType::EventManager *eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : _timer(timer), _eventManager(eventManager) {
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(80))
                            .Translate(vec2<float>(-2500, 0)))
            .Loop(99)
            .Build();
}

void DrawableDeathStar::Draw(sf::RenderTexture &rect) {
    sf::Texture texture;
    rect.clear(sf::Color::Transparent);
    texture.loadFromFile("sprites/deathStar.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect.draw(sprite);
}

vec2<float> DrawableDeathStar::GetRenderRect() {
    return vec2<float>(500 * 0.3, 500 * 0.3);
}

vec2<float> DrawableDeathStar::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableDeathStar)