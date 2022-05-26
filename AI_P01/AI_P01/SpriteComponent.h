#pragma once
#include "SFML/Graphics.hpp"

class SpriteComponent
{
public:

    SpriteComponent(class GameObject* _owner, sf::Texture _texture);

    void Update();
    void Render(sf::RenderWindow* _window);

    void UpdateSize(sf::Vector2f _size);

protected:
    SpriteComponent();
    // sprite overlay
    sf::Sprite sprite;
    sf::Texture texture;

    class GameObject* owner = nullptr;
};

