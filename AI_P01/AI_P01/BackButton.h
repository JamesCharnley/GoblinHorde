/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : BackButton.h
Description : A button to go back
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Button.h"
class BackButton :
    public Button
{
public:

    BackButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
    virtual void PerformAction() override;
};

