//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPEGAMECONTEXT_HPP
#define R_TYPE_RTYPEGAMECONTEXT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <Queue/SingleReaderWriterQueue.hpp>
#include <EntityPacker/EntityPacker.hpp>
#include <Model/LobbyStatePayload.hpp>
#include "IRTypeDrawingContext.hpp"
#include "ClientEntityPool.hpp"

class RTypeGameContext : public IRTypeDrawingContext{
private:
    std::shared_ptr<Timer> _timer = nullptr;
    std::shared_ptr<ClientEntityPool> _pool = nullptr;
    std::shared_ptr<RType::EventManager> _eventManager;
    std::unique_ptr<RType::EventListener> _eventListener;
    RType::ReaderWriterQueue<EntityPacker> _mailbox;
    LobbyStatePayload _lobby;

public:
    RTypeGameContext(const std::shared_ptr<RType::EventManager> &eventManager);

    void Setup(const LobbyStatePayload &);
    void ReleaseListener() override final;
    void Draw(sf::RenderTexture &, TextureBag &) override final;
};

#endif //R_TYPE_RTYPEGAMECONTEXT_HPP
