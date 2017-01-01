//
// Created by hippolyteb on 12/1/16.
//

#ifndef R_TYPE_GAMEINSTANCE_HPP
#define R_TYPE_GAMEINSTANCE_HPP

#include <thread>
#include <ServerEntityPool/ServerEntityPool.hpp>
#include <Queue/SingleReaderWriterQueue.hpp>
#include <Messages/SendNetworkPayloadMessage.hpp>
#include <Entities/PlayerRef.hpp>
#include <IUserControlled.hpp>

class GameInstance {
private:
    std::unique_ptr<std::thread> _thread = nullptr;
    uint16_t _id = -1;
    std::unique_ptr<ServerEntityPool> _pool = nullptr;
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<RType::EventManager> _eventManager = std::shared_ptr<RType::EventManager>(new RType::EventManager());
    std::shared_ptr<RType::EventManager> _globalEventManager = std::shared_ptr<RType::EventManager>(new RType::EventManager());
    std::unique_ptr<RType::ReaderWriterQueue<std::pair<int, std::set<UserEventType>>>> _inbox = std::unique_ptr<RType::ReaderWriterQueue<std::pair<int, std::set<UserEventType>>>>(new RType::ReaderWriterQueue<std::pair<int, std::set<UserEventType>>>(100));
    std::unique_ptr<RType::EventListener> _sub;
    std::vector<std::shared_ptr<PlayerRef>> _players;

public:
    GameInstance(uint16_t id, const std::vector<std::shared_ptr<PlayerRef>> &, const std::shared_ptr<RType::EventManager> globalEventManager, std::string const &partition, std::chrono::steady_clock::time_point const&);

    void ReceivedNetworkPayload(RType::Packer &packer);

    uint16_t getId() const {
        return _id;
    }

private:
    void Start();
};

#endif //R_TYPE_GAMEINSTANCE_HPP
