//
// Created by pasteu_e on 27/11/16.
//

#include <Time/Timer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"
#include <fstream>
#include <Messages/StartReceiveNetworkGamePayload.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <EntityPacker/EntityPacker.hpp>
#include <future>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include <Messages/UserInputMessage.hpp>
#include <IUserControlled.hpp>

void RTypeGameContext::Setup(const LobbyStatePayload &lobby) {
    _lobby = lobby;
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer, _eventManager);

    std::ifstream infile;

    std::stringstream str;
    str << "medias/partitions/" << _lobby.getPartitionName() << ".partition";

    infile.open(str.str());

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    _pool->LoadPartition(data);

    _eventListener->Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {
        auto packet = RType::Packer(RType::READ, message->getPayload()->Payload);

        uint8_t typePack;
        packet.Pack(typePack);

        if (typePack == 0) {
            std::set<uint16_t> entities;
            packet.Pack(entities);
            _mailboxExist.enqueue(entities);
        }
        else {
            EntityPacker entityPacker(packet, _pool->getFactory());

            if (_pool->Exist(entityPacker.getEntityId()) && !_pool->isPlayer(entityPacker.getEntityId()))
            {
                RType::Packer packer(RType::WRITE);
                uint16_t id = (uint16_t) _lobby.getGameInstanceId();
                packer.Pack(id);
                uint16_t playerId = (uint16_t) _lobby.getPlayerId();
                packer.Pack(playerId);
                uint8_t type = 0;
                packer.Pack(type);
                _eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer), this);
                return;
            } //Drop the packet

            entityPacker.UnpackEntity(_timer, _pool->getEventManager());
            _mailbox.enqueue(entityPacker);
        }
    });

    _eventListener->Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        RType::Packer packer(RType::WRITE);
        uint16_t id = (uint16_t) _lobby.getGameInstanceId();
        packer.Pack(id);
        uint16_t playerId = (uint16_t) _lobby.getPlayerId();
        packer.Pack(playerId);
        uint8_t type = 1;
        packer.Pack(type);
        message->Serialize(packer);
        _eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer), this);
        //if (_pool->Exist(2))
        //    dynamic_cast<IUserControlled *>(_pool->getEntityById(2).GetInstance())->Action(message->getPressed());
    });

    _eventManager->Emit(StartReceiveNetworkGamePayload::EventType, new StartReceiveNetworkGamePayload(), this);
}


void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::Black);

    EntityPacker entityPacker;
    while (_mailbox.try_dequeue(entityPacker))
        _pool->AddEntity(entityPacker.GetEntity(_timer, _pool->getEventManager()));
    if (entityPacker.getTimeStamp() != 0)
        _timer->RecalibrateOrigin(entityPacker.getTimeStamp());

    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}

void RTypeGameContext::ReleaseListener() { }

RTypeGameContext::RTypeGameContext(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager),
                                                                                               _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager))),
                                                                                               _mailbox(100),
                                                                                               _mailboxExist(1) {
}
