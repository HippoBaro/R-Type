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

void RTypeGameContext::Setup(std::string const &partitionFile) {
    _timer = std::make_shared<Timer>(std::chrono::steady_clock::now());
    _pool = std::make_shared<ClientEntityPool>(_timer, _eventManager);

    std::ifstream infile;
    infile.open(partitionFile);

    std::string data((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (data.empty())
        throw new std::runtime_error("Invalid partition file");

    _pool->LoadPartition(data);

    _eventListener->Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {
        auto packet = RType::Packer(RType::READ, message->getPayload()->Payload);
        EntityPacker entityPacker(packet, _pool->getFactory());

        if (_pool->Exist(entityPacker.getEntityId()) && !_pool->isPlayer(entityPacker.getEntityId()))
            return; //Drop the packet

        entityPacker.UnpackEntity(_timer, _pool->getEventManager());
        _mailbox.enqueue(entityPacker);
    });

    _eventListener->Subscribe<Entity, UserInputMessage>(UserInputMessage::EventType, [&](Entity *, UserInputMessage *message) {
        RType::Packer packer(RType::WRITE);
        message->Serialize(packer);
        _eventManager->Emit(SendNetworkPayloadMessage::EventType, new SendNetworkPayloadMessage(packer, "127.0.0.1"), this);
    });

    _eventManager->Emit(StartReceiveNetworkGamePayload::EventType, new StartReceiveNetworkGamePayload(), this);
}

bool didSyncTime = false;

void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::Black);

    EntityPacker entityPacker;
    while (_mailbox.try_dequeue(entityPacker))
        _pool->AddEntity(entityPacker.GetEntity(_timer, _pool->getEventManager()));
    if (entityPacker.getTimeStamp() != -1 && didSyncTime == false)
    {
        _timer->RecalibrateOrigin(entityPacker.getTimeStamp());
        didSyncTime = true;
    }

    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}

void RTypeGameContext::ReleaseListener() { }

RTypeGameContext::RTypeGameContext(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager),
                                                                                               _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager))),
                                                                                               _mailbox(100){
}
