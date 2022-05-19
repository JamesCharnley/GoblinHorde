#pragma once
#include "Interactable.h"
#include "GameObject_Circle.h"

class PickUp :
    public GameObject_Circle, public Interactable
{

public:

    PickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual bool CostsGold() override;
    virtual int GetPrice(class Player* _player) override;
    virtual bool InRange(class Player* _player) override;
    virtual bool HasActionText() override;
    virtual std::string GetActionText() override;
    virtual bool AutoInteract() override;
    virtual bool CanInteract(class Player* _player) override;
    virtual void Interact(class Player* _player) override;

protected:

    PickUp();
};

