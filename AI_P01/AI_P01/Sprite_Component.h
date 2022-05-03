#pragma once
#include "SFML/Graphics.hpp"

class Sprite_Component
{
public:

    Sprite_Component(class GameObject* _owner, sf::Texture _texture);

    void Update();
    void Render(sf::RenderWindow* _window);

    void UpdateSize(sf::Vector2f _size);

protected:
    Sprite_Component();
    // sprite overlay
    sf::Sprite sprite;
    sf::Texture texture;

    class GameObject* owner = nullptr;
};

