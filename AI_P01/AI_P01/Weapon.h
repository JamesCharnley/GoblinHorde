/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Weapon.h
Description : A reusable weapon class that uses stats from a FWeapon
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectCircle.h"

enum class EWeapon
{
    Glock,
    SMG,
    Rifle,
    DebugGun,
};
enum class EWeaponType
{
    Gun
};

struct FWeapon
{
    struct Data
    {
        Data()
            : weapon(EWeapon::SMG), weaponType(EWeaponType::Gun), damage(20), actionsPerSecond(8.0f), hasAmmo(true), ammo(100), level(1), name("Weapon") {}
        Data(EWeapon _weapon, EWeaponType _weaponType, int _damage, float _actionsPerSecond, int _ammo, float _bulletSpeed, const char* _name)
            : weapon(_weapon), weaponType(_weaponType), damage(_damage), actionsPerSecond(_actionsPerSecond), hasAmmo(true), ammo(_ammo), speed(_bulletSpeed), level(1), name(_name) {}

        EWeapon weapon;
        EWeaponType weaponType;
        int damage;
        float actionsPerSecond;
        float speed;
        bool hasAmmo;
        int ammo;
        int level;
        const char* name;
    };
    static std::map<EWeapon, Data> dataMap;
    static inline FWeapon::Data GetData(EWeapon _weapon) { return dataMap.at(_weapon); }
};


class Weapon :
    public GameObjectCircle
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Weapon(sf::RenderWindow* _window, class Scene* _scene, GameObject* _owner, EWeapon _weaponBase = EWeapon::Glock);
    virtual void Update(float _deltatime) override;
    void PerformAction();
    inline GameObject* GetOwner() { return owner; };
    inline void SetOwner(GameObject* _owner) { owner = _owner; }
    FWeapon::Data GetWeaponData();

    inline int GetLevel() { return weaponData.level; }
    //increment this weapon's level
    void Upgrade();

    std::string name; // debug

protected:

    void Cooldown(float _deltatime);
    float cooldownTimer = 0;
    FWeapon::Data weaponData;
    GameObject* owner = nullptr;
    bool inAction = false;

    const char* bulletSpriteFile;

private:
    FWeapon::Data GetBaseWeaponData();

};


static struct WeaponData
{
    static std::map<Weapon, FWeapon> weaponData;
};

