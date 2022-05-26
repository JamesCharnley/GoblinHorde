/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : GameObjectText.h
Description : GameObject with a sf::text
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObject.h"
class GameObjectText :
    public GameObject
{
public:

    GameObjectText(sf::RenderWindow* _window, class Scene* _scene, std::string _text);
    // Render() override. called every frame from Scene() class
    virtual void Render() override;

    void SetText(std::string _text);

protected:

    sf::Text textObject;
    sf::Font font;
    std::string text = "";
};

