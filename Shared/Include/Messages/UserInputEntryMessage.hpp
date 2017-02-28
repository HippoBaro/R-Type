//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_USERINPUTENTRYMESSAGE_HPP
#define R_TYPE_USERINPUTENTRYMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <vec2.hpp>
#include <EventDispatcher/Events.h>


class UserInputEntryMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::USER_INPUT_ENTRY;

private:
    char _letter = ' ';

public:
    UserInputEntryMessage(char letter) : _letter(letter) {}

    const char &getUserLetter() const {
        return _letter;
    }
};

#endif //R_TYPE_USERINPUTENTRYMESSAGE_HPP