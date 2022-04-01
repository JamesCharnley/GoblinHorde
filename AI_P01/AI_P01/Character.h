#pragma once
#include "GameObject_Circle.h"

struct FInputs
{
public:

    sf::Keyboard::Key ForwardKey;
    sf::Keyboard::Key BackwardKey;
    sf::Keyboard::Key LeftKey;
    sf::Keyboard::Key RightKey;
    sf::Keyboard::Key ShootKey;
};
class Character :
    public GameObject_Circle
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Character(sf::RenderWindow* _window, class Scene* _scene);

    // override update
    virtual void Update(float _deltatime) override;

    virtual void Move(sf::Vector2f _movement);

    virtual void CheckForInput();

    void SetPlayersNumber(int _number);

protected:

    float moveSpeed = 100.0f;
    float rotateSpeed = 100.0f;

    sf::Vector2f velocity;

    FInputs selectedInputPreset;

    class Weapon* equippedWeapon = nullptr;
private:

    FInputs playerOnePreset = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space };
    FInputs playerTwoPreset = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Enter };
};

