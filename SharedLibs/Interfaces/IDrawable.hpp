//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_IDRAWABLE_HPP
#define R_TYPE_IDRAWABLE_HPP

#include <vec2.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <SFML/Graphics.hpp> //SFML is not Weffc++ compliant
#pragma GCC diagnostic pop

#include <TextureBag.hpp>

class IDrawable {
private:
    std::unique_ptr<sf::RenderTexture> _renderTexture = nullptr;

public:
    virtual ~IDrawable() {}

public:
    virtual void Draw(sf::RenderTexture *, TextureBag &) = 0;
    virtual vec2<float> GetRenderRect() = 0;
    virtual vec2<float> GetPosition() = 0;

    sf::RenderTexture *getRenderTexture() {
        return _renderTexture.get();
    };
    sf::RenderTexture *createRenderTexture(unsigned int width, unsigned int height) {
        _renderTexture = std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture());
        _renderTexture->create(width, height);
        return _renderTexture.get();
    };
};

#endif //R_TYPE_IDRAWABLE_HPP
