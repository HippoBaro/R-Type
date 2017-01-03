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

    int initialPos = 200;
    for (auto &i : _players) {
        _pool->AddEntity("Player", i->GetId(), vec2<float>(0, initialPos), _timer->getCurrent());
        initialPos += 200;
    }
    _thread = std::unique_ptr<std::thread>(new std::thread(std::bind(&GameInstance::Start, this)));
}

void GameInstance::Start() {
    auto t = std::chrono::steady_clock::now();
    int cycle = 0;

    while (true)
    {
        if (_players.size() == 0)
            break;
        std::pair<int, std::set<UserEventType>> events;
        while (_inbox->try_dequeue(events))
            if (_pool->Exist((const uint16_t) events.first))
                dynamic_cast<IUserControlled *>(_pool->getEntityById((uint16_t) events.first)->GetInstance())->Action(events.second);

        _pool->ProcessEntities();
        _pool->BroadcastEntities(_id, _globalEventManager, _players);

        cycle++;
        if (cycle > 30) {
            _pool->BroadcastEntitiesThatStillExist(_id, _globalEventManager, _players);
            cycle = 0;
        }

        t += std::chrono::milliseconds(32); //We'll send entities 30 times per seconds
        std::this_thread::sleep_until(t);
    }
    std::cout << "Game instance prunned !" << std::endl;
}

void GameInstance::ReceivedNetworkPayload(RType::Packer &packer) {
    uint16_t playerid;
    packer.Pack(playerid);
    uint8_t type;
    packer.Pack(type);
    std::set<UserEventType> events;
    if (type == 1)
        packer.Pack(events);
    _inbox->enqueue(std::make_pair(playerid, events));
}