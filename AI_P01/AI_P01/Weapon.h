#pragma once
#include "GameObject_Circle.h"

enum class EWeapon
{
    Glock,
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
            : weapon(EWeapon::Glock), weaponType(EWeaponType::Gun), damage(20), actionsPerSecond(8.0f), hasAmmo(true), ammo(100), level(1) {}
        Data(EWeapon _weapon, EWeaponType _weaponType, int _damage, float _actionsPerSecond, int _ammo)
            : weapon(_weapon), weaponType(_weaponType), damage(_damage), actionsPerSecond(_actionsPerSecond), hasAmmo(true), ammo(_ammo), level(1) {}

        EWeapon weapon;
        EWeaponType weaponType;
        int damage;
        float actionsPerSecond;
        bool hasAmmo;
        int ammo;
        int level;
    };
    static std::map<EWeapon, Data> dataMap;
    static inline FWeapon::Data GetData(EWeapon _weapon) { return dataMap.at(_weapon); }
};


class Weapon :
    public GameObject_Circle
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Weapon(sf::RenderWindow* _window, class Scene* _scene, GameObject* _owner, EWeapon _weaponBase = EWeapon::Glock, std::string _name = "weapon");
    virtual void Update(float _deltatime) override;
    void PerformAction();
    GameObject* GetOwner() { return owner; };
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

private:
    FWeapon::Data GetBaseWeaponData();
};



static struct WeaponData
{
    static std::map<Weapon, FWeapon> weaponData;
};

