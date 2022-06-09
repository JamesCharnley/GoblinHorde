/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Player.h
Description : Player class, handles input, player movement and all player interaction
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Interactable.h"
#include "Character.h"
#include "Weapon.h"
#include <SFML/Audio.hpp>

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

    Player(sf::RenderWindow* _window, Scene* _scene, float _playerCount);
    ~Player();
    virtual void Update(float _deltatime) override;
    virtual void Render() override;

    void SetPlayersNumber(int _number);

    void AddGold(int _amount);
    void RemoveGold(int _amount);
    int GetGold() { return currentGold; };
    void PollController(int _controllerIndex); //temp
    std::string GetButtonMapping(int _button); //temp

    int GetWeaponLevel();
    void UpgradeWeapon();
    void AddWeapon(Weapon* _weapon);
    //check if a player has a weapon type in their inventory
    bool HasWeapon(EWeapon _weapon);

    virtual void OnCollision(GameObject* _other) override;

    virtual void TakeDamage(int _amount) override;
    
    // UI for displaying prompts above player object
    sf::Font font;
    sf::Text actionText;
    std::string actionTextString = "";

    // pointer to Interactable object currently in range of
    Interactable* currentInteractable = nullptr;

    bool isDead = false;

    void Respawn();

    void SetSpawnPoint(sf::Vector2f _pos);

    void ResetHealth() { currentHealth = maxHealth; };

protected:

    FInputs selectedInputPreset;
    int playerNum;

    virtual void CheckForInput(int _player);

    float rotationDelay = 0.0f;
    float rotationDelayTimer = 0;

    bool lockRotation = false;

    int currentGold = 0;

    int playerNumber = 0;

    bool actionButtonPressed = false;

    void PollInteractable();

    class Base* base;

    void UpdateActionText();

private:
    std::vector<Weapon*> weapons;
    int equippedWeaponIndex = 0;

    bool lastFrameSwitchWeapon = false;
    void NextWeapon();
    void PreviousWeapon();
    FInputs playerOnePreset = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::LControl, sf::Keyboard::Space };
    FInputs playerTwoPreset = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl, sf::Keyboard::Enter };

    sf::Vector2f spawnpoint;

    sf::Sound PlayerDieSFX;
    sf::Sound PlayerGoldSFX;
    sf::SoundBuffer buffer;
};

