//
// Created by hippolyteb on 11/25/16.
//

#include <iostream>
#include <thread>
#include "DummyMonster.hpp"
#include <EntityPartitionBuilder.hpp>

DummyMonster::DummyMonster(Timer *timer) : IDrawable(this), _timer(timer), _partition(timer) {
    _partition = EntityPartitionBuilder(timer).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(_timer->getCurrent())
                            .For(std::chrono::seconds(1))
                            .From(vec2<unsigned int>(0, 0))
                            .To(vec2<unsigned int>(20, 20))
            ).ContinueWith(
                    PartitionSegmentBuilder()
                            .For(std::chrono::seconds(10))
                            .To(vec2<unsigned int>(5, 5))
            ).Loop(2)
    .Build();

/*    for (int i = 0; i < 501; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto const current = _partition.GetCurrentSegment(timer->getCurrent()).getLocationVector().GetTweened();
        std::cout << "Monster pos : [X:" << current.x << "; Y:" << current.y << "] TIME : " << _timer->getCurrent().getMilliseconds().count() << std::endl;
    }*/
}

void DummyMonster::Draw(sf::RenderTexture &rect) {
    sf::Sprite sprite;
    sprite.setColor(sf::Color::Cyan);
    rect.draw(sprite);
}

vec2<unsigned int> DummyMonster::GetRenderRect() {
    return vec2<unsigned int>(50, 50);
}

vec2<unsigned int> DummyMonster::GetPosition() {
    return _partition.GetCurrentSegment(_timer->getCurrent()).getLocationVector().GetTweened();
}

extern "C" DLLEXPORT DummyMonster *create(const std::initializer_list<void *> init) {
    std::cout << "TEST" << std::endl;
    for (auto i : init)
        return new DummyMonster((Timer *)i);
    return nullptr;
}

extern "C" DLLEXPORT void destroy(DummyMonster *p) {
    delete p;
}