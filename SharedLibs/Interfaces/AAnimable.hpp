//
// Created by aguado_e on 12/21/16.
//

#ifndef R_TYPE_AANIMABLE_HPP
#define R_TYPE_AANIMABLE_HPP

#include <cstdint>
#include <SFML/System/Clock.hpp>

class AAnimable : public IDrawable {
protected:
  sf::Clock _clock;
  uint8_t _currentFrame = 0;
  bool isTextureSetInit = false;
  std::vector<sf::IntRect> _frames;

  ////////////////////////////////////////////////////
  //// Set animations frames and store them into the texture bag
  //// backAndForth means the animation will go 1>2>3>2>1 instead of 1>2>3>1>2>3
  //// Duration in milliseconds
  ////////////////////////////////////////////////////
  void setAnimation(
    std::string FilePath,
    std::vector<sf::IntRect> & Frames,
    TextureBag &bag,
    int duration = 100,
    bool shouldLoop = true,
    bool backAndForth = true)
  {
    for (auto it = Frames.begin() ; it != Frames.end() ; it++)
    {
      _frames.push_back(*it);
      sf::Texture newtexture;
      newtexture.loadFromFile("medias/images/deathStar.png", *it);
      bag.AddTexture("medias/images/deathStar.png", *it, newtexture);
    }
  };


  // Determines if should draw the next frame
  void updateAnimation(sf::RenderTexture *rect, TextureBag &bag) {
    sf::Texture *texture = bag.getTexture("medias/images/deathStar.png", _frames[0]);
    sf::Sprite sprite;

    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
    rect->draw(sprite);
  };







  void stopAnimation() {};
  // True if last frame is reached. Usefull for callbacks
//  bool reachedLastFrame() {};
  // Returns the texture associated with the current frame to draw it
//  sf::Texture *GetCurrentFrameTexture() {};

  void toto() {

    int elapsed1 = _clock.getElapsedTime().asMilliseconds();
    if (elapsed1 > 2000)
    {
      _clock.restart();
      std::cout << "The clock says TICK !" << std::endl;
    }
  }

public:
  virtual void Draw(sf::RenderTexture *rect, TextureBag &) = 0;
  virtual void Cycle() = 0;

  AAnimable() :
    _clock(),
    _frames()
  {}

};

#endif //R_TYPE_AANIMABLE_HPP
