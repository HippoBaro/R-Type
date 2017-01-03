//
// Created by aguado_e on 12/22/16.
//

#include <Messages/ProjectilePositionChangedMessage.hpp>
#include <Entities/Projectiles/SimpleProjectiles/SimpleProjectile.hpp>
#include "GraphicTentacleBoss.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicTentacleBoss)
#endif

GraphicTentacleBoss::GraphicTentacleBoss(const std::initializer_list<void *> init) :
        TentacleBoss(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
    _eventListener->Subscribe<SimpleProjectile, ProjectilePositionChangedMessage>(
            ProjectilePositionChangedMessage::EventType,
            [&](SimpleProjectile *projectile, ProjectilePositionChangedMessage *message) {
                if (message->TestHitBox(GetPosition(), GetRenderRect(), _id))
                {
                    flicker();
                }
            }
    );
}

void GraphicTentacleBoss::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(256 * 1, 142 * 0, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 0, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 1, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 1, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 2, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 2, 256, 142));
        framePos.push_back(sf::IntRect(256 * 1, 142 * 3, 256, 142));
        framePos.push_back(sf::IntRect(256 * 0, 142 * 3, 256, 142));
        setAnimation("medias/images/r-typesheet34.png", framePos, bag);
        setLoopDuration(1500);
        setScale(sf::Vector2f(4.0f, 4.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicTentacleBoss::Cycle() {
    TentacleBoss::Cycle();
}
