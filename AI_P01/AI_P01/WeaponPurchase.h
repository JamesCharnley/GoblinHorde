#pragma once
#include "PickUp.h"
#include "Weapon.h"

class WeaponPurchase :
    public PickUp
{
public:

    WeaponPurchase(sf::RenderWindow* _window, Scene* _scene, EWeapon _weapon);
    inline ~WeaponPurchase() { delete weapon; }

    Weapon* weapon;

    virtual bool CostsGold() override;
    virtual int GetPrice(class Player* _player) override;
    virtual bool HasActionText() override;
    virtual std::string GetActionText() override;
    virtual bool AutoInteract() override;
    virtual bool CanInteract(class Player* _player) override;
    virtual void Interact(class Player* _player) override;
    //TODO: render weapon
};

