//
// Created by aguado_e on 12/29/16.
//

#ifndef R_TYPE_STARTNEWGAMEMESSAGE_HPP
#define R_TYPE_STARTNEWGAMEMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>
#include <string>
#include <Entities/PlayerRef.hpp>
#include "../../../Server/Include/LobbyInstance/LobbyInstance.hpp"

class StartNewGameMessage : public IMessage {
public:
    static constexpr RType::Event EventType = RType::Event::START_NEW_GAME;

private:
    std::string _partitionName;
    std::vector<std::shared_ptr<PlayerRef>> _playerRefs;
    int _instanceId;

public:
    StartNewGameMessage(std::string &partition, std::vector<std::shared_ptr<PlayerRef>> &refs, int id) :
            _partitionName(partition),
            _playerRefs(refs),
            _instanceId(id) {}

    int getId() const {
        return _instanceId;
    }

    const std::vector<std::shared_ptr<PlayerRef>> getPlayerRefs() const {
        return _playerRefs;
    }

    const std::string &getPartition() const {
        return _partitionName;
    }
};

#endif //R_TYPE_STARTNEWGAMEMESSAGE_HPP
