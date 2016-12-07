//
// Created by pasteu_e on 27/11/16.
//

#include "RTypeMenuContext.hpp"

void RTypeMenuContext::Draw(sf::RenderTexture &context, TextureBag &) {
    context.create(800, 600);
    context.clear(sf::Color::Black);
    sf::Texture texture;
    texture.loadFromFile("sprites/spacebackground.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(1.5f, 1.5f));
    context.draw(sprite);
    sf::Font font;
    if (font.loadFromFile("sprites/pdark.ttf"))
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::White);

        text.setString("Hello Hippolyte");
        context.draw(text);
        text.setString("Hello Hippolyte");
        context.draw(text);
    }
    context.display();
}