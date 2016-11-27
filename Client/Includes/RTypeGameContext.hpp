//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEGAMECONTEXT_HPP
#define R_TYPE_RTYPEGAMECONTEXT_HPP


#include "IRtypeDrawingContext.hpp"

class RTypeGameContext : public IRtypeDrawingContext{
public:
    void Draw() override final;
};


#endif //R_TYPE_RTYPEGAMECONTEXT_HPP
