//
// Created by hippolyteb on 12/1/16.
//

#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "GameInstance/GameInstance.hpp"

GameInstance::GameInstance(uint16_t id, const std::shared_ptr<RType::EventManager> globalEventManager,
                           std::string const &partition,
                           std::chrono::steady_clock::time_point const &origin) : _id(id),
                                                                                  _globalEventManager(globalEventManager),
                                                                                  _sub(std::unique_ptr<RType::EventListener>(new RType::EventListener(_globalEventManager))) {
    _timer = std::make_shared<Timer>(origin);
    _pool = std::unique_ptr<ServerEntityPool>(new ServerEntityPool(_timer, _eventManager));
    _pool->LoadPartition(partition);
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&GameInstance::Start, this)));

    _sub->Subscribe<void, ReceivedNetworkPayloadMessage>(ReceivedNetworkPayloadMessage::EventType, [&](void *sender, ReceivedNetworkPayloadMessage *message) {
        std::cout << "Received User Input" << std::endl;
        RType::Packer packer(RType::READ, message->getPayload()->Payload);
        std::set<UserEventType> events;
        packer.Pack(events);
        _inbox->enqueue(events);
    });
}

void GameInstance::Start() {
    auto t = std::chrono::steady_clock::now();

    while (true) //todo : loop must break when game is over
    {
        std::set<UserEventType> events;
        while (_inbox->try_dequeue(events)) {
            dynamic_cast<IUserControlled *>(_pool->getEntityById(2)->GetInstance())->Action(events);
        }

        _pool->ProcessEntities();
        _pool->BroadcastEntities(_globalEventManager);
        t += std::chrono::milliseconds(32); //We'll send entities 30 times per seconds
        std::this_thread::sleep_until(t);
    }
}