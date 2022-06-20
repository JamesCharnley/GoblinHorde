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
struct ControllerState
{
    struct Buttons
    {
    private:
        std::vector<bool*> buttons = { &A, &B, &X, &Y, &LB, &RB, &Back, &Menu, &LS, &RS};

    public:
        Buttons()
        {
            count = buttons.size();
        }
        bool A = false;
        bool B = false;
        bool X = false;
        bool Y = false;
        bool LB = false;
        bool RB = false;
        bool Back = false;
        bool Menu = false;
        bool LS = false;
        bool RS = false;
        int count;

        struct HatSwitch
        {
            bool up     = false;
            bool down   = false;
            bool left   = false;
            bool right  = false;
        };
        HatSwitch DPad;

        void Set(int _index, bool _value)
        {
            *buttons.at(_index) = _value;
        }
    };

    struct Axis
    {
        struct XYAxis
        {
            float x = 0.0f;
            float y = 0.0f;
        };

        XYAxis LS;
        XYAxis RS;
        XYAxis DPad;
        float Trig = 0.0f;
    };
    Buttons button;
    Axis axis;
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
    void ReloadWeapon();

    //Checks if player is near the edges
    void checkConstraints();

private:
    ControllerState input;
    std::vector<Weapon*> weapons;
    int equippedWeaponIndex = 0;

    bool lastFrameSwitchWeapon = false;
    void NextWeapon();
    void PreviousWeapon();
    FInputs playerOnePreset = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::LControl, sf::Keyboard::Space };
    FInputs playerTwoPreset = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl, sf::Keyboard::Enter };

    sf::Vector2f spawnpoint;


    sf::Sound playerSFX;
    sf::Sound playerGoldSFX;
    sf::SoundBuffer purchaseBuffer;
    sf::SoundBuffer hurtSFXBuffer;
    sf::SoundBuffer dieSFXBuffer;
    sf::SoundBuffer goldBuffer;

    sf::Sound PlayerDieSFX;
    sf::Sound PlayerGoldSFX;
    sf::SoundBuffer buffer;

    sf::Sound baseRepairSFX;
    sf::SoundBuffer baseRepairSFXBuffer;

    float baseRepairSFXInterval = 1;
    float baseRepairSFXTimer = 0;

};

