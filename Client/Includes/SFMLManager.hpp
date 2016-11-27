//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_SFMLMANAGER_HPP
#define R_TYPE_SFMLMANAGER_HPP


#include <IRtypeDrawingContext.hpp>
#include "RTypeInputListener.hpp"

class SFMLManager {
private:
    std::unique_ptr<RTypeInputListener> _inputListener;
    std::unique_ptr<IRtypeDrawingContext> _gameContext;
    std::unique_ptr<IRtypeDrawingContext> _menuContext;

public:
    SFMLManager();
    void Run();
};


#endif //R_TYPE_SFMLMANAGER_HPP
