//
// Created by pasteu_e on 17/12/16.
//

#ifndef R_TYPE_LOBBYINSTANCE_HPP
#define R_TYPE_LOBBYINSTANCE_HPP

#include <EventDispatcher/EventManager.hpp>
#include <chrono>
#include <Entities/PlayerRef.hpp>
#include <Socket/IRTypeSocket.hpp>
#include <Serializer/Packer.hpp>
#include <Serializer/ISerializable.hpp>

class LobbyInstance {
private:
    std::string _roomName;
    std::map<uint8_t, std::shared_ptr<PlayerRef>> _players = std::map<uint8_t, std::shared_ptr<PlayerRef>>();
    std::map<uint8_t, std::shared_ptr<IRTypeSocket>> _clients = std::map<uint8_t, std::shared_ptr<IRTypeSocket>>();
    std::shared_ptr<RType::EventManager> _eventManager;

private:
    void NotifyClients();

public:
    const std::map<uint8_t, std::shared_ptr<PlayerRef>> getPlayerRefs() const;
    const std::string &getRoomName() const;
    LobbyInstance(const std::shared_ptr<RType::EventManager> &eventManager, std::string roomName);
    bool AddPlayerToInstance(const uint8_t id, const std::shared_ptr<IRTypeSocket> &client, const std::shared_ptr<PlayerRef> &ref);
    void SetReady(uint8_t id, bool ready);
    void PlayerLeft(uint8_t id);
    bool IsReady();
    bool IsThereAnyone();
    bool HaveYouSeenThisPlayer(uint8_t id);
};


#endif //R_TYPE_LOBBYINSTANCE_HPP
