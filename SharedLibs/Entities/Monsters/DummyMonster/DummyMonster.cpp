//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"
#include <EntityPartitionBuilder.hpp>
#include <EaseInOutCurve.hpp>
#include <EaseOutCurve.hpp>

DummyMonster::DummyMonster(Timer *timer) : _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(5))
                            .From(vec2<int>(0, 0))
                            .To(vec2<int>(500, 500))
                            .WithCurving(new EaseInOutCurve()))
            .ContinueWith(PartitionSegmentBuilder()
                                  .From(vec2<int>(500, 500))
                                  .For(std::chrono::seconds(10))
                                  .To(vec2<int>(100, 90))
                                  .WithCurving(new EaseOutCurve()))
            .Loop(2)
            .Build();
}

void DummyMonster::Draw(sf::RenderTexture &rect) {
    sf::Texture texture;
    rect.clear(sf::Color::Transparent);
    texture.loadFromFile("sprites/r-typesheet1.png", sf::IntRect(101, 3, 32, 14));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(5.f, 5.f));
    rect.draw(sprite);
}

vec2<int> DummyMonster::GetRenderRect() {
    return vec2<int>(32 * 5, 14 * 5);
}

vec2<int> DummyMonster::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
    return pos;
}

extern "C" DLLEXPORT DummyMonster *create(const std::initializer_list<void *> init) {
    for (auto i : init)
        return new DummyMonster((Timer *) i);
    return nullptr;
}

extern "C" DLLEXPORT void destroy(DummyMonster *p) {
    delete p;
}