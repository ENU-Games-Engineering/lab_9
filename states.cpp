#include "states.hpp"
#include "graphics_cmps.hpp"
#include <cmath>

void NormalState::execute(Entity *owner, const float &dt){
    auto length = [](sf::Vector2f v) -> float{
        return std::sqrt(v.x*v.x + v.y*v.y);
    };
    std::shared_ptr<ShapeComponent> s = owner->get_components<ShapeComponent>()[0];
    s->get_shape().setFillColor(sf::Color::Blue);
    
    if (length(owner->get_position() - _player->get_position()) < 100.0f){
        std::shared_ptr<StateMachineComponent> sm = owner->get_components<StateMachineComponent>()[0];
        sm->change_state("near");
    }
}

void NearState::execute(Entity *owner, const float &dt){
    auto length = [](sf::Vector2f v) -> float{
        return std::sqrt(v.x*v.x + v.y*v.y);
    };
    std::shared_ptr<ShapeComponent> s = owner->get_components<ShapeComponent>()[0];
    s->get_shape().setFillColor(sf::Color::Green);
    
    if (length(owner->get_position() - _player->get_position()) > 100.0f){
        std::shared_ptr<StateMachineComponent> sm = owner->get_components<StateMachineComponent>()[0];
        sm->change_state("normal");
    }
}