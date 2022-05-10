#pragma once
#include "Interactable.h"
#include "GameObject_Rectangle.h"

class PickUp :
    public GameObject_Rectangle, public Interactable
{

public:

    PickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual bool HasActionText() override;
    virtual std::string GetActionText() override;
    virtual bool AutoInteract() override;
    virtual bool CanInteract(class Player* _player) override;
    virtual void Interact(class Player* _player) override;

protected:

    PickUp();
};

