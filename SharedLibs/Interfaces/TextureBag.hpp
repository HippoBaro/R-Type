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
    std::map<std::string, std::shared_ptr<const sf::Texture>> _textures;

public:
    TextureBag() : _textures() {}

public:
    std::shared_ptr<const sf::Texture> getTexture(std::string const &textureFile, sf::IntRect const &rect) {
        std::stringstream ss;

        ss << textureFile << rect.height << rect.left << rect.top << rect.width;

        auto key = ss.str();
        if (_textures.count(key))
            return _textures[key];
        return nullptr;
    }

    std::shared_ptr<const sf::Texture> &AddTexture(std::string const &textureFile, sf::IntRect const &rect, std::shared_ptr<const sf::Texture> const &texture) {
        std::stringstream ss;

        ss << textureFile << rect.height << rect.left << rect.top << rect.width;
        auto key = ss.str();
        _textures[key] = texture;
        return _textures[key];
    }
};


#endif //R_TYPE_TEXTUREBAG_HPP
