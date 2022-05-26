/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : StatEffectPickUp.h
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "PickUp.h"
class StatEffectPickUp :
    public PickUp
{

public:

    StatEffectPickUp(sf::RenderWindow* _window, Scene* _scene);

protected:

    StatEffectPickUp();

    float effectAmount = 0;
};

