#pragma once
#include "game_system.hpp"
#include "ai_cmps.hpp"

class MenuScene: public Scene{
public:
    MenuScene() = default;
    void update(const float &dt) override;
    void render() override;
    void load()override;
    void unload() override;
private:
    sf::Text _text;
    sf::Font _font;
};


class StateScene: public Scene{
public:
    StateScene() = default;
    void update(const float &dt) override;
    void render() override;
    void load()override;
    void unload() override;
};


class DecisionScene : public Scene
{
public:
    DecisionScene() = default;
    void load() override;
    void unload() override;
    void update(const float &dt) override;
    void render() override;
};

struct Scenes{
    static std::shared_ptr<Scene> menu;
    static std::shared_ptr<Scene> state;
    static std::shared_ptr<Scene> decision;
};
