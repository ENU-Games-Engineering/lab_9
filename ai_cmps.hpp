#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.hpp>


// Output from a steering behaviour.
struct SteeringOutput
{
    // Direction of travel.
    sf::Vector2f direction;
    // Rotation of travel.
    float rotation;
};


struct SteeringBehaviours{
    static SteeringOutput seek(const sf::Vector2f &,const sf::Vector2f &);
    static SteeringOutput flee(const sf::Vector2f &,const sf::Vector2f &);
};

class SteeringComponent : public Component{
protected:
    Entity *_player;
    float _max_speed;
    bool valid_move(const sf::Vector2f&) const;
public:
    void update(const float &) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override { }
    explicit SteeringComponent(Entity *p, Entity *player, float _max_speed);
    SteeringComponent() = delete;
};

class PathfindingComponent : public Component {
protected:
  std::vector<sf::Vector2i> _path;
  size_t _index = 0;
  double _elapsed = 0.0;

public:
  void update(const float &) override;
  void render() override {}
  void set_path(std::vector<sf::Vector2i>& path);
  explicit PathfindingComponent(Entity* p);
  PathfindingComponent() = delete;
};


class State
{
public:
    virtual ~State() = default;
    virtual void execute(Entity*,const float &) = 0;
};


class StateMachineComponent : public Component
{
private:
    std::unordered_map<std::string, std::shared_ptr<State>> _states;
    std::shared_ptr<State> _current_state;
    std::string _current_state_name = "";
public:
    StateMachineComponent() = delete;    
    explicit StateMachineComponent(Entity *p);

    void update(const float &) override;
    void render() override { }
    void add_state(const std::string&, std::shared_ptr<State>);
    std::shared_ptr<State> get_state(const std::string&) const;
    void remove_state(const std::string&);
    void change_state(const std::string&);
    const std::string& current_state() const {return _current_state_name; }
};