#pragma once
#include "PickUp.h"
class WeaponUpgrade :
    public PickUp
{
public:

    WeaponUpgrade(sf::RenderWindow* _window, Scene* _scene);

    virtual bool InRange(class Player* _player) override;
    virtual bool AutoInteract() override;
    virtual bool HasActionText() override;
    virtual std::string GetActionText() override;

protected:

    std::string actionText = "";
};

