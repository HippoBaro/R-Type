//
// Created by aguado_e on 12/21/16.
//

#ifndef R_TYPE_AANIMABLE_HPP
#define R_TYPE_AANIMABLE_HPP

#include <cstdint>
#include <SFML/System/Clock.hpp>
#include "IDrawable.hpp"

class AAnimable : public IDrawable {
private:
  sf::Clock _clock;
  std::vector<sf::IntRect> _frames;
  std::string _pathToFile = "";
  uint8_t _currentFrame = 0;

  // Options
  int _loopDuration = 0;
  bool _backAndForth = true;
  bool _inPause = false;


  ////////////////////////////////////////////////////
  /// \brief Determines if the texture should be updated
  ///
  /// \return True if
  ///           - Enough time has past
  ///           - Animation is not in pause
  ///           - Loop is not over
  ///
  ////////////////////////////////////////////////////
  bool shouldUpdateFrame() const {
    // Enough time spent
    const size_t timeElapsed = static_cast<const size_t>(_clock.getElapsedTime().asMilliseconds());
    const size_t timeToNextFrame = this->_loopDuration / this->_frames.size();

    // Is the animation in pause ?
    const bool loopIsOver = this->isLoopOver();

    return
      timeElapsed > timeToNextFrame &&
      !_inPause &&
      !loopIsOver;
  }

  ////////////////////////////////////////////////////
  /// \brief Increases or decreases _currentFrame
  ///
  ////////////////////////////////////////////////////
  void updateCurrentFrame() {
    _currentFrame++;
    if (this->isLoopOver())
    {
      if (_backAndForth)
        std::reverse(_frames.begin(), _frames.end());
      _currentFrame = 0;
    }
    _clock.restart();
  }

protected:
  ////////////////////////////////////////////////////
  /// \brief Set animations frames and store them into the texture bag
  ///
  /// \param filePath      Path to spritesheet
  /// \param frames        A vector of sf::IntRect. Represents every frame
  ///                      of the animation
  /// \param bag           A reference to a TextureBag
  /// \param duration      Time necessary for a loop to occur in milliseconds
  /// \param shouldLoop    Should the animation loop or not
  /// \param backAndForth  means the animation will go 1>2>3>2>1 instead of 1>2>3>1>2>3
  ///
  ////////////////////////////////////////////////////
  void setAnimation(
    std::string filePath,
    std::vector<sf::IntRect> &frames,
    TextureBag &bag,
    int duration = 100,
    bool shouldLoop = true,
    bool backAndForth = true)
  {
    this->_loopDuration = duration;
    this->_pathToFile = filePath;
    this->_backAndForth = backAndForth;

    // Init textures
    for (auto it = frames.begin() ; it != frames.end() ; it++)
    {
      _frames.push_back(*it);
      sf::Texture newtexture;
      newtexture.loadFromFile(_pathToFile, *it);
      bag.AddTexture(_pathToFile, *it, newtexture);
    }
  };

  ////////////////////////////////////////////////////
  /// \brief Determines if should draw the next frame
  ///
  /// Automatically updates the animation frames according to
  /// time and options (Back&Forth ? Loop ?)
  ////////////////////////////////////////////////////
  void updateAnimation(sf::RenderTexture *rect, TextureBag &bag) {
    if (this->shouldUpdateFrame())
    {
      this->updateCurrentFrame();

      // Replace old texture by a new one
      rect->clear(sf::Color::Transparent);
      sf::Sprite sprite;
      sf::Texture *texture = bag.getTexture(_pathToFile, _frames[_currentFrame]);
      sprite.setTexture(*texture);
      sprite.setScale(sf::Vector2f(0.7f, 0.7f));
      rect->draw(sprite);
    }
  };

  ////////////////////////////////////////////////////
  /// \brief Tells if the loop is over
  ///
  /// \return True if loop is over. False otherwise
  ///
  ////////////////////////////////////////////////////
  bool isLoopOver() const { return this->_currentFrame == this->_frames.size() - 1; };

  ////////////////////////////////////////////////////
  /// \brief Pause the animation in the current frame
  ///
  ////////////////////////////////////////////////////
  void stopAnimation() { this->_inPause = true; };

  ////////////////////////////////////////////////////
  /// \brief Resume the animation as normal
  ///
  ////////////////////////////////////////////////////
  void resumeAnimation() { this->_inPause = false; };

public:
  // TODO: this should be done in the controller
  bool isTextureSetInit = false;

  virtual void Draw(sf::RenderTexture *rect, TextureBag &) = 0;
  virtual void Cycle() = 0;

  AAnimable() :
    _clock(),
    _frames()
  {}

};

#endif //R_TYPE_AANIMABLE_HPP
