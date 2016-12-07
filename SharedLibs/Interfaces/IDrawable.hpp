//
// Created by hippolyteb on 11/28/16.
//

#ifndef R_TYPE_IDRAWABLE_HPP
#define R_TYPE_IDRAWABLE_HPP

#include <vec2.hpp>
#include <SFML/Graphics.hpp>
#include <../../Client/Includes/TextureBag.hpp>

class IDrawable {
private:
    std::unique_ptr<sf::RenderTexture> _renderTexture = nullptr;
    bool isTextureSet = false;

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
