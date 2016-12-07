//
// Created by hippolyteb on 12/7/16.
//

#ifndef R_TYPE_TEXTUREBAG_HPP
#define R_TYPE_TEXTUREBAG_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class TextureBag {
private:
    std::map<std::string, sf::Texture> _textures;

public:
    TextureBag();

public:
    sf::Texture *getSprite(std::string const &, sf::IntRect const &);
    sf::Texture *AddSprite(std::string const &, sf::IntRect const &, sf::Texture const &texture);
};


#endif //R_TYPE_TEXTUREBAG_HPP
