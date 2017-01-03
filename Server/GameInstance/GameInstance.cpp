//
// Created by hippolyteb on 12/1/16.
//

#include <Messages/ReceivedNetworkPayloadMessage.hpp>
#include "GameInstance/GameInstance.hpp"

GameInstance::GameInstance(uint16_t id, const std::vector<std::shared_ptr<PlayerRef>> &players,
                           const std::shared_ptr<RType::EventManager> globalEventManager,
                           std::string const &partition,
                           std::chrono::steady_clock::time_point const &origin) : _id(id),
                                                                                  _globalEventManager(globalEventManager),
                                                                                  _sub(std::unique_ptr<RType::EventListener>(new RType::EventListener(_globalEventManager))),
                                                                                  _players(players) {
    _timer = std::make_shared<Timer>(origin);
    _pool = std::unique_ptr<ServerEntityPool>(new ServerEntityPool(_timer, _eventManager));
    _pool->LoadPartition(partition);
    for (auto &i : _players) {
        _pool->AddEntity("Player", i->GetId(), vec2<float>(0, 100 * i->GetId()), _timer->getCurrent());
    }
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&GameInstance::Start, this)));
}

void GameInstance::Start() {
    auto t = std::chrono::steady_clock::now();

    while (true) //todo : loop must break when game is over
    {
        std::pair<int, std::set<UserEventType>> events;
        while (_inbox->try_dequeue(events))
            if (_pool->Exist(events.first))
                dynamic_cast<IUserControlled *>(_pool->getEntityById((uint16_t) events.first)->GetInstance())->Action(events.second);

        _pool->ProcessEntities();
        _pool->BroadcastEntities(_globalEventManager, _players);
        t += std::chrono::milliseconds(32); //We'll send entities 30 times per seconds
        std::this_thread::sleep_until(t);
    }
}

void GameInstance::ReceivedNetworkPayload(RType::Packer &packer) {
    uint16_t playerid;
    packer.Pack(playerid);
    uint8_t type;
    packer.Pack(type);
    std::set<UserEventType> events;
    stc::cout << "payload type is " << type << std::endl;
    if (type == 1)
        packer.Pack(events);
    _inbox->enqueue(std::make_pair(playerid, events));
}