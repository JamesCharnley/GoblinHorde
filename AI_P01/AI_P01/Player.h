#pragma once
#include "Character.h"

struct FInputs
{
public:
   
    sf::Keyboard::Key ForwardKey;
    sf::Keyboard::Key BackwardKey;
    sf::Keyboard::Key LeftKey;
    sf::Keyboard::Key RightKey;
    sf::Keyboard::Key LockRotationKey;
    sf::Keyboard::Key ShootKey;
};
class Player :
    public Character
{
public:

    Player(sf::RenderWindow* _window, Scene* _scene);

    virtual void Update(float _deltatime) override;

    void SetPlayersNumber(int _number);

    void AddGold(int _amount);
    void RemoveGold(int _amount);
    int GetGold() { return currentGold; };

protected:

    FInputs selectedInputPreset;

    virtual void CheckForInput();

    float rotationDelay = 0.0f;
    float rotationDelayTimer = 0;

    bool lockRotation = false;

    int currentGold = 0;

private:

    FInputs playerOnePreset = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::LControl, sf::Keyboard::Space };
    FInputs playerTwoPreset = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl, sf::Keyboard::Enter };
};

