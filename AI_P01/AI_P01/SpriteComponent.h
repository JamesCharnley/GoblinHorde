/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : SpriteComponent.h
Description : A component to hold and draw a sprite
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"

class SpriteComponent
{
public:

    SpriteComponent(class GameObject* _owner, sf::Texture _texture);

    void Update();
    void Render(sf::RenderWindow* _window);

    void UpdateSize(sf::Vector2f _size);
    sf::Vector2f GetScale() { return sprite.getScale(); };
    sf::Vector2f GetOrigin() { return sprite.getOrigin(); };
    void SetTransparency(float _value);

protected:
    SpriteComponent();
    // sprite overlay
    sf::Sprite sprite;
    sf::Texture texture;

    class GameObject* owner = nullptr;
};

