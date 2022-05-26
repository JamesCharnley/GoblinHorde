/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : PickUp.h
Description : A pickupable GameObject
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Interactable.h"
#include "GameObjectCircle.h"

class PickUp :
    public GameObjectCircle, public Interactable
{

public:

    PickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual bool CostsGold() override;
    virtual int GetPrice(class Player* _player) override;
    virtual bool InRange(class Player* _player) override;
    virtual bool HasActionText(class Player* _player) override;
    virtual std::string GetActionText() override;
    virtual bool AutoInteract() override;
    virtual bool CanInteract(class Player* _player) override;
    virtual void Interact(class Player* _player) override;

protected:

    PickUp();
};

