//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_IDRAWABLEMENU_HPP
#define R_TYPE_IDRAWABLEMENU_HPP

#include <utility>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Messages/UserInputMessage.hpp"
#include <Messages/SoundSystemMessage.hpp>
#include <EventDispatcher/EventManager.hpp>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventListener.hpp>

enum MenuType {
    VERTICAL,
    HORIZONTAL
};

class ADrawableMenu {
protected:
    std::map<unsigned int, std::pair<bool, std::string>> _menuMap = std::map<unsigned int, std::pair<bool, std::string>>();
    std::map<UserEventType, std::function<void()>> _move = std::map<UserEventType, std::function<void()>>();
    std::shared_ptr<RType::EventManager> _eventManager = nullptr;
    std::unique_ptr<RType::EventListener> _eventListener = nullptr;

    std::string _menuName = std::string();
    MenuType _menuType = VERTICAL;
    bool _active = false;
    bool _canMove = true;

private:
    std::string getSelection();

    bool isCreateOrJoin(std::unique_ptr<ADrawableMenu> &elem);

    void checkIfUserStopWaiting();

    void checkIfUserIsReady();

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void changeTextColor(std::pair<const unsigned int, std::pair<bool, std::string>> &elem, sf::Text &text);

    virtual void specialDrawing(sf::RenderTexture &context, sf::Text &text);

    virtual const std::string getChannelName();

public:
    ADrawableMenu();

    virtual ~ADrawableMenu();

    void moveSelection(UserEventType type);

    bool moveInSubMenu(std::vector<std::unique_ptr<ADrawableMenu>> &allMenu);

    void Draw(sf::RenderTexture &context, sf::Text &text);
};

#endif //R_TYPE_IDRAWABLEMENU_HPP
