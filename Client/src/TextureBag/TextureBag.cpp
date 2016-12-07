//
// Created by hippolyteb on 12/7/16.
//

#include <sstream>
#include "TextureBag.hpp"

sf::Texture *TextureBag::getSprite(std::string const &textureFile, sf::IntRect const &rect) {
    std::stringstream ss;

    ss << textureFile << rect.height << rect.left << rect.top << rect.width;
    auto key = ss.str();
    if (_textures.count(key))
        return &_textures[key];
    return nullptr;
}

sf::Texture *TextureBag::AddSprite(std::string const &textureFile, sf::IntRect const &rect, sf::Texture const &texture) {
    std::stringstream ss;

    ss << textureFile << rect.height << rect.left << rect.top << rect.width;
    auto key = ss.str();
    _textures[key] = texture;
    return &_textures[key];
}

TextureBag::TextureBag() : _textures() {}
