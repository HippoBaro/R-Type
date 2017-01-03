//
// Created by hippolyteb on 12/1/16.
//

#include <fstream>
#include <Messages/StartNewGameMessage.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "GameInstance/GameInstanceManager.hpp"

void GameInstanceManager::CreateInstance(const int id, const std::vector<std::shared_ptr<PlayerRef>> &players, const std::string &partitionName) {
    std::ifstream infile;
    infile.open(partitionName);

    if (!infile.is_open())
        throw new std::runtime_error("Unable to open partition file");

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    _instances.push_back(std::unique_ptr<GameInstance>(new GameInstance((uint16_t) id, players, _eventManager, data, std::chrono::steady_clock::now())));
}

GameInstanceManager::GameInstanceManager(const std::shared_ptr<RType::EventManager> &eventManager) :
        _eventManager(eventManager),
        _eventListener(eventManager)
{
    _eventListener.Subscribe<LobbyInstance, StartNewGameMessage>(RType::Event::START_NEW_GAME, [this](LobbyInstance *lobby, StartNewGameMessage *message) {
        CreateInstance(message->getId(), message->getPlayerRefs(), "medias/partitions/" + message->getPartition() + ".partition");
    });

    _eventListener.Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {
        RType::Packer packer(RType::READ, message->getPayload()->Payload);
        uint16_t instanceId;
        packer.Pack(instanceId);
        for (auto &i : _instances) {
            if (i->getId() == instanceId)
                i->ReceivedNetworkPayload(packer);
        }
    });
}

