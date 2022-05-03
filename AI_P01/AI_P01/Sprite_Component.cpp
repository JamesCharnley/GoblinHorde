#include "GameObject.h"
#include "Sprite_Component.h"

Sprite_Component::Sprite_Component()
{
}

Sprite_Component::Sprite_Component(GameObject* _owner, sf::Texture _texture)
{
	texture = _texture;
	sprite.setTexture(texture);

	owner = _owner;
}

void Sprite_Component::Update()
{
	// update sprite rotation and position to match shape
	sprite.setPosition(owner->GetPosition());
	sprite.setRotation(owner->GetRotation());
}

void Sprite_Component::Render(sf::RenderWindow* _window)
{
	// render sprite
	_window->draw(sprite);
}

void Sprite_Component::UpdateSize(sf::Vector2f _size)
{

	// update scale of sprite to match shape
	sf::Vector2u texSize = texture.getSize();
	float newSizeX = _size.x / (float)texSize.x;
	float newSizeY = _size.y / (float)texSize.y;
	sprite.setScale(sf::Vector2f(newSizeX, newSizeY));
	sprite.setOrigin(sf::Vector2f((float)texSize.x / 2, (float)texSize.y / 2));
}
