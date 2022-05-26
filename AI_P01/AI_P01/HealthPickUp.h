/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : HealthPickup.h
Description : A pickup that gives health when picked up
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "StatEffectPickUp.h"
class HealthPickUp :
    public StatEffectPickUp
{
public:

    HealthPickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual void Interact(class Player* _player) override;
};

