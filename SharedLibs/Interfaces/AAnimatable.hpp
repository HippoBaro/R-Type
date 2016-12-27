//
// Created by aguado_e on 12/21/16.
//

#ifndef R_TYPE_ANIMATABLE_HPP
#define R_TYPE_ANIMATABLE_HPP

#include <cstdint>
#include <SFML/System/Clock.hpp>
#include "IDrawable.hpp"

class AAnimatable : public IDrawable {
private:
    sf::Clock _clock;
    std::vector<sf::IntRect> _frames;
    std::string _pathToFile = "";
    uint8_t _currentFrame = 0;

    // SMFL Options
    sf::Vector2f _scale = sf::Vector2f(1.0f, 1.0f);

    // Animation options
    int _loopDuration = 0;
    bool _backAndForth = true;
    bool _inPause = false;
    bool _shouldLoop = true;


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
        const bool loopEndReached = this->isLastFrame() && !this->_shouldLoop;

        return (
                _shouldLoop &&
                (timeElapsed > timeToNextFrame) &&
                !_inPause &&
                !loopEndReached
        );
    }

    ////////////////////////////////////////////////////
    /// \brief Increases or decreases _currentFrame
    ///
    ////////////////////////////////////////////////////
    void updateCurrentFrame() {
        _currentFrame++;
        if (this->isLastFrame())
        {
            if (_backAndForth)
                std::reverse(_frames.begin(), _frames.end());
            _currentFrame = 0;
        }
        _clock.restart();
    }


    bool NeedRedraw() override {
        return this->shouldUpdateFrame();
    }

protected:
    // Customize animation
    void setScale(sf::Vector2f s) { this->_scale = s; }
    void setLoopDuration(int duration) { this->_loopDuration = duration; }
    void setLoop(bool v = true) { this->_shouldLoop = v; }
    void setLoopBackAndForth(bool v = true) { this->_backAndForth = v; }

    ////////////////////////////////////////////////////
    /// \brief Set animations frames and store them into the texture bag
    ///
    /// \param filePath      Path to spritesheet
    /// \param frames        A vector of sf::IntRect. Represents every frame
    ///                      of the animation
    /// \param bag           A reference to a TextureBag
    ///
    ////////////////////////////////////////////////////
    void setAnimation(
            std::string filePath,
            std::vector<sf::IntRect> &frames,
            TextureBag &bag)
    {
        this->_pathToFile = filePath;

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
    /// Should be called every frame !
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
            sprite.setScale(sf::Vector2f(4.0f, 4.0f));
            rect->draw(sprite);
        }
    };

    ////////////////////////////////////////////////////
    /// \brief Tells if last frame has been reached
    ///
    /// \return True if loop is over. False otherwise
    ///
    ////////////////////////////////////////////////////
    bool isLastFrame() const { return this->_currentFrame == this->_frames.size() - 1; };

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
    // TODO: this should be done in the constructor
    bool isTextureSetInit = false;

    AAnimatable() :
            _clock(),
            _frames()
    {}
};

#endif //R_TYPE_ANIMATABLE_HPP
