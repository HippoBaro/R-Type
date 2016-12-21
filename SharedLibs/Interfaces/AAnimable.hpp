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
  int _loopDuration = 0;
  bool isTextureSetInit = false;
  std::vector<sf::IntRect> _frames;
  std::string _pathToFile = "";
  bool _backAndForth = true;

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
    this->_loopDuration = duration;
    this->_pathToFile = FilePath;
    this->_backAndForth = backAndForth;

    // Init textures
    for (auto it = Frames.begin() ; it != Frames.end() ; it++)
    {
      _frames.push_back(*it);
      sf::Texture newtexture;
      newtexture.loadFromFile(_pathToFile, *it);
      bag.AddTexture(_pathToFile, *it, newtexture);
    }
  };


  // Determines if should draw the next frame
  void updateAnimation(sf::RenderTexture *rect, TextureBag &bag) {
    sf::Texture *texture = bag.getTexture(_pathToFile, _frames[_currentFrame]);
    sf::Sprite sprite;

    int timeElapsed = _clock.getElapsedTime().asMilliseconds();
    // Time has come, refresh the texture
    if ((size_t)timeElapsed > (this->_loopDuration / this->_frames.size()))
    {
      _currentFrame++;
      if (_currentFrame >= this->_frames.size())
      {
        if (_backAndForth)
          std::reverse(_frames.begin(), _frames.end());
        _currentFrame = 0;
      }
      _clock.restart();

      rect->clear(sf::Color::Transparent);
      sprite.setTexture(*texture);
      sprite.setScale(sf::Vector2f(0.7f, 0.7f));
      rect->draw(sprite);
    }
  };







  void stopAnimation() {};
  // True if last frame is reached. Usefull for callbacks
  bool reachedLastFrame() { return true; };
  // Returns the texture associated with the current frame to draw it

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
