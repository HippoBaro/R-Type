//
// Created by hippolyteb on 12/7/16.
//

#ifndef R_TYPE_TEXTUREBAG_HPP
#define R_TYPE_TEXTUREBAG_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <sstream>

class TextureBag {
private:
    std::map<std::string, sf::Texture> _textures;

public:
    TextureBag() : _textures() {};

public:
    sf::Texture *getTexture(std::string const &textureFile, sf::IntRect const &rect){
        std::stringstream ss;

        ss << textureFile << rect.height << rect.left << rect.top << rect.width;

        auto key = ss.str();
        if (_textures.count(key))
            return &_textures[key];
        return nullptr;
    }

    sf::Texture *AddTexture(std::string const &textureFile, sf::IntRect const &rect, sf::Texture const &texture) {
        std::stringstream ss;

        ss << textureFile << rect.height << rect.left << rect.top << rect.width;
        auto key = ss.str();
        _textures[key] = texture;
        return &_textures[key];
    }
};


#endif //R_TYPE_TEXTUREBAG_HPP
