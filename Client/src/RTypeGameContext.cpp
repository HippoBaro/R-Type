//
// Created by pasteu_e on 27/11/16.
//

#include <Time/Timer.hpp>
#include <LibraryLoader/ManagedExternalInstance.hpp>
#include <LibraryLoader/ExternalClassFactoryLoader.hpp>
#include "RTypeGameContext.hpp"
#include <fstream>
#include <Messages/ReceiveNetworkPayloadMessage.hpp>
#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include <EntityPacker/EntityPacker.hpp>

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
}

std::chrono::time_point<std::chrono::system_clock> point = std::chrono::system_clock::now();

void RTypeGameContext::Draw(sf::RenderTexture &context, TextureBag &bag) {
    context.clear(sf::Color::Black);
    std::cout << "sent receive command" << std::endl;

    _eventManager->Emit(ReceiveNetworkPayloadMessage::EventType, new ReceiveNetworkPayloadMessage(
            (uint16_t) (_pool->getEntityCount() + 10)), this);
    _pool->ProcessEntities();
    _pool->Draw(context, bag);
    context.display();
}

void RTypeGameContext::ReleaseListener() {

}

RTypeGameContext::RTypeGameContext(const std::shared_ptr<RType::EventManager> &eventManager) : _eventManager(eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager))) {
    _eventListener->Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {
        auto packet = RType::Packer(RType::READ, message->getPayload()->Payload);
        EntityPacker entityPacker(packet, _pool->getFactory());
        std::cout << "deserializing" << std::endl;

            _timer->RecalibrateOrigin(entityPacker.getTimeStamp());
            if (_pool->Exist(entityPacker.getEntityId()))
                return; //Drop the packet

            auto entity = entityPacker.GetEntity(_timer, _pool->getEventManager());
            _pool->AddEntity(entity);
    });
}
