//
// Created by Hippolyte Barraud on 01/01/2017.
//

#ifndef R_TYPE_LOBBYSTATEPAYLOAD_HPP
#define R_TYPE_LOBBYSTATEPAYLOAD_HPP

#include <Serializer/ISerializable.hpp>
#include <Entities/PlayerRef.hpp>

class LobbyStatePayload : RType::ISerializable {
private:
    std::vector<PlayerRef> _players = std::vector<PlayerRef>();
    std::string _partitionName = "";
    int _gameInstanceId = -1;
    int _playerId = -1;


public:
    const std::vector<PlayerRef> &getPlayers() const {
        return _players;
    }

    void setPlayers(const std::vector<PlayerRef> &players) {
        LobbyStatePayload::_players = players;
    }

    const std::string &getPartitionName() const {
        return _partitionName;
    }

    void setPartitionName(const std::string &_partitionName) {
        LobbyStatePayload::_partitionName = _partitionName;
    }

    int getGameInstanceId() const {
        return _gameInstanceId;
    }

    void setGameInstanceId(int _gameInstanceId) {
        LobbyStatePayload::_gameInstanceId = _gameInstanceId;
    }

    int getPlayerId() const {
        return _playerId;
    }

    void setPlayerId(int _playerId) {
        LobbyStatePayload::_playerId = _playerId;
    }

    virtual void Serialize(RType::Packer &packer) override final {
        packer.PackSerializables(_players);
        packer.Pack(_partitionName);
        packer.Pack(_gameInstanceId);
        packer.Pack(_playerId);
    }
};

#endif //R_TYPE_LOBBYSTATEPAYLOAD_HPP
