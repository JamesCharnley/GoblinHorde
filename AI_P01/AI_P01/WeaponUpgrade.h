#pragma once
#include "PickUp.h"
class WeaponUpgrade :
    public PickUp
{
public:

    WeaponUpgrade(sf::RenderWindow* _window, Scene* _scene);

    virtual bool CostsGold() override;
    virtual int GetPrice(class Player* _player) override;
    virtual bool InRange(class Player* _player) override;
    virtual bool AutoInteract() override;
    virtual bool HasActionText(class Player* _player) override;
    virtual std::string GetActionText() override;
    virtual bool CanInteract(class Player* _player) override;
    virtual void Interact(class Player* _player) override;

protected:

    std::string actionText = "";
};

