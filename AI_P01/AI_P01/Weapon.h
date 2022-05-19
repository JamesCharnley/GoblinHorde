#pragma once
#include "GameObject_Circle.h"

enum class EWeapon
{
    Glock
};
enum class EWeaponType
{
    Gun
};

struct FWeaponData
{
    EWeapon Weapon;
    EWeaponType WeaponType;
    int Damage;
    float ActionsPerSecond;
    bool HasAmmo;
    int Ammo;
    int Level;
};
class Weapon :
    public GameObject_Circle
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Weapon(sf::RenderWindow* _window, class Scene* _scene, GameObject* _owner, std::string _name = "weapon");

    virtual void Update(float _deltatime) override;

    // implement attack action
    void PerformAction();

    GameObject* GetOwner() { return owner; };

    std::string name; // debug

    FWeaponData GetWeaponData();

protected:

    void Cooldown(float _deltatime);
    float cooldownTimer = 0;
    FWeaponData weaponData;
    GameObject* owner = nullptr;
    bool inAction = false;

};

