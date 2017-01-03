//
// Created by aguado_e on 12/22/16.
//

#include "GraphicBackground.hpp"

#ifdef ENTITY_DRW_CTOR
RTYPE_DRAWABLE_ENTITY_REGISTER(GraphicBackground)
#endif

GraphicBackground::GraphicBackground(const std::initializer_list<void *> init) :
        Background(init),
        AAnimatable()
{
    RegisterTrait(Trait::Drawable);
}

void GraphicBackground::Draw(sf::RenderTexture *rect, TextureBag &bag) {
    if (!isTextureSetInit) {
        isTextureSetInit = true;

        std::vector<sf::IntRect> framePos;
        framePos.push_back(sf::IntRect(0, 0, 426, 240));
        framePos.push_back(sf::IntRect(10, 0, 436, 240));
        framePos.push_back(sf::IntRect(20, 0, 446, 240));
        framePos.push_back(sf::IntRect(30, 0, 456, 240));
        framePos.push_back(sf::IntRect(40, 0, 466, 240));
        framePos.push_back(sf::IntRect(50, 0, 476, 240));
        framePos.push_back(sf::IntRect(60, 0, 486, 240));
        framePos.push_back(sf::IntRect(70, 0, 496, 240));
        framePos.push_back(sf::IntRect(80, 0, 506, 240));
        framePos.push_back(sf::IntRect(90, 0, 516, 240));
        framePos.push_back(sf::IntRect(100, 0, 526, 240));
        framePos.push_back(sf::IntRect(110, 0, 536, 240));
        framePos.push_back(sf::IntRect(120, 0, 546, 240));
        framePos.push_back(sf::IntRect(130, 0, 556, 240));
        framePos.push_back(sf::IntRect(140, 0, 566, 240));
        framePos.push_back(sf::IntRect(150, 0, 576, 240));

        framePos.push_back(sf::IntRect(160, 0, 586, 240));
        framePos.push_back(sf::IntRect(170, 0, 596, 240));
        framePos.push_back(sf::IntRect(180, 0, 606, 240));
        framePos.push_back(sf::IntRect(190, 0, 616, 240));
        framePos.push_back(sf::IntRect(200, 0, 626, 240));
        framePos.push_back(sf::IntRect(210, 0, 636, 240));
        framePos.push_back(sf::IntRect(220, 0, 646, 240));
        framePos.push_back(sf::IntRect(230, 0, 656, 240));
        framePos.push_back(sf::IntRect(240, 0, 666, 240));
        framePos.push_back(sf::IntRect(250, 0, 676, 240));
        framePos.push_back(sf::IntRect(260, 0, 686, 240));
        framePos.push_back(sf::IntRect(270, 0, 696, 240));
        framePos.push_back(sf::IntRect(280, 0, 706, 240));
        framePos.push_back(sf::IntRect(290, 0, 716, 240));
        framePos.push_back(sf::IntRect(300, 0, 726, 240));
        framePos.push_back(sf::IntRect(310, 0, 736, 240));


        framePos.push_back(sf::IntRect(320, 0, 746, 240));
        framePos.push_back(sf::IntRect(330, 0, 756, 240));
        framePos.push_back(sf::IntRect(340, 0, 766, 240));
        framePos.push_back(sf::IntRect(350, 0, 776, 240));
        framePos.push_back(sf::IntRect(360, 0, 786, 240));
        framePos.push_back(sf::IntRect(370, 0, 796, 240));
        framePos.push_back(sf::IntRect(380, 0, 806, 240));
        framePos.push_back(sf::IntRect(390, 0, 816, 240));
        framePos.push_back(sf::IntRect(400, 0, 826, 240));
        framePos.push_back(sf::IntRect(410, 0, 836, 240));
        framePos.push_back(sf::IntRect(420, 0, 846, 240));
        framePos.push_back(sf::IntRect(430, 0, 856, 240));
        framePos.push_back(sf::IntRect(440, 0, 866, 240));
        framePos.push_back(sf::IntRect(450, 0, 876, 240));
        framePos.push_back(sf::IntRect(460, 0, 886, 240));
        framePos.push_back(sf::IntRect(470, 0, 896, 240));


        framePos.push_back(sf::IntRect(480, 0, 906, 240));
        framePos.push_back(sf::IntRect(490, 0, 916, 240));
        framePos.push_back(sf::IntRect(500, 0, 926, 240));
        framePos.push_back(sf::IntRect(510, 0, 936, 240));
        framePos.push_back(sf::IntRect(520, 0, 946, 240));
        framePos.push_back(sf::IntRect(530, 0, 956, 240));
        framePos.push_back(sf::IntRect(540, 0, 966, 240));
        framePos.push_back(sf::IntRect(550, 0, 976, 240));
        framePos.push_back(sf::IntRect(560, 0, 986, 240));
        framePos.push_back(sf::IntRect(570, 0, 996, 240));
        framePos.push_back(sf::IntRect(580, 0, 1006, 240));
        framePos.push_back(sf::IntRect(590, 0, 1016, 240));
        framePos.push_back(sf::IntRect(600, 0, 1026, 240));
        framePos.push_back(sf::IntRect(610, 0, 1036, 240));
        framePos.push_back(sf::IntRect(620, 0, 1046, 240));
        framePos.push_back(sf::IntRect(630, 0, 1056, 240));



        setAnimation("medias/images/scrolling.jpg", framePos, bag);
        setLoopDuration(3500);
        setLoopBackAndForth(false);
        setScale(sf::Vector2f(3.0f, 3.0f));
    }
    updateAnimation(rect, bag);
}

void GraphicBackground::Cycle() {
    Background::Cycle();
}
