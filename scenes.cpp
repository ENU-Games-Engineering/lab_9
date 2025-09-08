#include <random>
#include "scenes.hpp"
#include "renderer.hpp"
#include "graphics_cmps.hpp"
#include "ctrl_cmps.hpp"
#include "ai_cmps.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"
#include "astar.hpp"
#include "states.hpp"

using gs = GameSystem;
using ls = LevelSystem;
using param = Parameters;

std::shared_ptr<Scene> Scenes::menu;
std::shared_ptr<Scene> Scenes::state;
std::shared_ptr<Scene> Scenes::decision;

void MenuScene::update(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        gs::set_active_scene(Scenes::state);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        gs::set_active_scene(Scenes::decision);
    }
    Scene::update(dt);
}

void MenuScene::render() {
    Renderer::queue(&_text);
    Scene::render();
}

void MenuScene::load() {
    _font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(60);
    _text.setString("Movement Demos\nPress 1 for Steering\nPress 2 for Pathfinding");
}

void MenuScene::unload(){}


void StateScene::load(){
    std::shared_ptr<Entity> player = make_entity();
    player->set_position(sf::Vector2f(param::game_width / 2.f,param::game_height / 2.f));
    auto s = player->add_component<ShapeComponent>();
    s->set_shape<sf::CircleShape>(10.0f);
    s->get_shape().setFillColor(sf::Color::Red);
    player->add_component<KeyboardMovementComponent>();
    
    std::shared_ptr<Entity> enemy = make_entity();
    enemy->set_position(sf::Vector2f(50.0f, 50.0f));
    s = enemy->add_component<ShapeComponent>();
    s->set_shape<sf::CircleShape>(10.0f);
    s->get_shape().setFillColor(sf::Color::Blue);
    
    std::shared_ptr<StateMachineComponent> sm = enemy->add_component<StateMachineComponent>();
    sm->add_state("normal", std::make_shared<NormalState>(player));
    sm->add_state("near", std::make_shared<NearState>(player));
    sm->change_state("normal");
}

void StateScene::unload() { 
    Scene::unload(); 
}

void StateScene::update(const float& dt) { 
    Scene::update(dt); 
}

void StateScene::render() { 
    Scene::render(); 
}

void DecisionScene::load() {
    std::shared_ptr<Entity> player = make_entity();
    player->set_position(sf::Vector2f(param::game_width / 2, 
        param::game_height / 2));
    std::shared_ptr<ShapeComponent> s = player->add_component<ShapeComponent>();
    s->set_shape<sf::CircleShape>(10.0f);
    s->get_shape().setFillColor(sf::Color::Red);
    player->add_component<KeyboardMovementComponent>();
    
    std::random_device dev;
    std::default_random_engine engine(dev());
    std::uniform_real_distribution<float> x_dist(0.0f, param::game_width);
    std::uniform_real_distribution<float> y_dist(0.0f, param::game_height);
    
    for (size_t n = 0; n < 100; ++n)
    {
        std::shared_ptr<Entity> enemy = make_entity();
        enemy->set_position(sf::Vector2f(x_dist(engine), y_dist(engine)));
        std::shared_ptr<ShapeComponent> s = enemy->add_component<ShapeComponent>();
        s->set_shape<sf::CircleShape>(10.0f);
        s->get_shape().setFillColor(sf::Color::Blue);
        
        auto sm = enemy->add_component<StateMachineComponent>();
        sm->add_state("stationary", std::make_shared<SteeringState>(SteeringBehaviours::stationary,player,50.f,sf::Color::Yellow));
        sm->add_state("seek", std::make_shared<SteeringState>(SteeringBehaviours::seek,player,50.f,sf::Color::Red));
        sm->add_state("flee", std::make_shared<SteeringState>(SteeringBehaviours::flee,player,50.f,sf::Color::Green));
        
        auto decision = std::make_shared<DistanceDecision>(
            player,
            50.0f,
            std::make_shared<SteeringDecision>("flee"),
            std::make_shared<DistanceDecision>(
                player,
                100.0f,
                std::make_shared<RandomDecision>(
                    std::make_shared<SteeringDecision>("seek"),
                    std::make_shared<SteeringDecision>("stationary")),
               std::make_shared<SteeringDecision>("seek")));
        
        enemy->add_component<DecisionTreeComponent>(decision);
    }
}


void DecisionScene::unload() { Scene::unload(); }

void DecisionScene::update(const float &dt){
    Scene::update(dt);
}

void DecisionScene::render(){
    Scene::render();
}