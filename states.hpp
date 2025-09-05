#pragma once
#include "ai_cmps.hpp"

class NormalState : public State
{
private:
    std::shared_ptr<Entity> _player;
public:
    NormalState(std::shared_ptr<Entity> player) : _player(player) { }
    void execute(Entity*, const float &) override;
};

class NearState : public State
{
private:
    std::shared_ptr<Entity> _player;
public:
    NearState(std::shared_ptr<Entity> player) : _player(player) { }
    void execute(Entity*, const float &) override;
};