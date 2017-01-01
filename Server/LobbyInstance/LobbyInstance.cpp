//
// Created by pasteu_e on 17/12/16.
//

#include <iostream>
#include <Messages/SendTCPNetworkPayloadMessage.hpp>
#include <Model/LobbyStatePayload.hpp>
#include "LobbyInstance/LobbyInstance.hpp"

LobbyInstance::LobbyInstance(const std::shared_ptr<RType::EventManager> &eventManager, std::string roomName) :
        _roomName(roomName),
        _eventManager(eventManager)
{}

bool LobbyInstance::AddPlayerToInstance(const uint8_t id, const std::shared_ptr<IRTypeSocket> &client, const std::shared_ptr<PlayerRef> &ref) {
    if (_players.size() < 4) {
        _clients[id] = client;
        _players[id] = ref;
        NotifyClients();
        return true;
    }
    return false;
}

void LobbyInstance::SetReady(uint8_t id, bool ready) {
    if (_players.find(id) != _players.end()) {
        _players[id]->setReady(ready);
        NotifyClients();
    }
}

void LobbyInstance::PlayerLeft(uint8_t id) {
    if (_players.find(id) != _players.end()) {
        _clients.erase(id);
        _players.erase(id);
        NotifyClients();
    }
}

bool LobbyInstance::IsReady() {
    for (auto const &player : _players) {
        if (!player.second->isReady())
            return false;
    }
    return true;
}

bool LobbyInstance::IsThereAnyone() {
    return _players.size() != 0;
}

void LobbyInstance::NotifyClients() {
    auto packer = RType::Packer(RType::WRITE);
    auto tmpPlayers = std::vector<PlayerRef>();
    for (const auto &i : _players)
        tmpPlayers.push_back(*i.second);
    auto lobbyState = new LobbyStatePayload();
    lobbyState->setPlayers(tmpPlayers);

    lobbyState->Serialize(packer);
    for (auto const &cli : _clients)
        _eventManager->Emit(SendTCPNetworkPayloadMessage::EventType, new SendTCPNetworkPayloadMessage(packer, cli.second), this);
}

bool LobbyInstance::HaveYouSeenThisPlayer(uint8_t id) {
    for (const auto &i : _players) {
        if (i.first == id)
            return true;
    }
    return false;
}

const std::string &LobbyInstance::getRoomName() const {
    return _roomName;
}

const std::map<uint8_t, std::shared_ptr<PlayerRef>> LobbyInstance::getPlayerRefs() const
{
    return _players;
}

void LobbyInstance::NotifyGameStarted(const std::string &partition, uint16_t instanceId) {
    for (auto const &cli : _clients) {
        auto packer = RType::Packer(RType::WRITE);
        auto tmpPlayers = std::vector<PlayerRef>();
        for (const auto &i : _players)
            tmpPlayers.push_back(*i.second);
        LobbyStatePayload lobbyState;
        lobbyState.setPlayers(tmpPlayers);
        lobbyState.setPartitionName(partition);
        lobbyState.setGameInstanceId(instanceId);
        lobbyState.setPlayerId(cli.first);
        lobbyState.Serialize(packer);
        _eventManager->Emit(SendTCPNetworkPayloadMessage::EventType, new SendTCPNetworkPayloadMessage(packer, cli.second), this);
    }
}

LobbyStatePayload LobbyInstance::getState() {
    return _state;
}

void LobbyInstance::setState(const LobbyStatePayload &payload) {
    _state = payload;
}
