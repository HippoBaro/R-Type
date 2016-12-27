//
// Created by Etienne Pasteur on 27/12/2016.
//

#ifndef R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP
#define R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP

#include <EventDispatcher/IMessage.hpp>
#include <string>
#include <EventDispatcher/Events.h>
#include <Entities/PlayerRef.hpp>
#include <vector>


class MenuStateUpdateMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::LOBBY_STATE_CHANGE;

private:
    std::string _textToWrite;

public:
    MenuStateUpdateMessage(const std::string &textToWrite) : _textToWrite(textToWrite) {}

    const std::string &GetTextToWrite() const {
        return _textToWrite;
    }

};

#endif //R_TYPE_MENUSTATESUPDATEMESSAGE_HPP_HPP
