#include "GameObject.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::SpriteComponent(GameObject* _owner, sf::Texture _texture)
{
	texture = _texture;
	sprite.setTexture(texture);

	owner = _owner;
}

void SpriteComponent::Update()
{
	// update sprite rotation and position to match shape
	sprite.setPosition(owner->GetPosition());
	sprite.setRotation(owner->GetRotation());
}

void SpriteComponent::Render(sf::RenderWindow* _window)
{
	// render sprite
	_window->draw(sprite);
}

void SpriteComponent::UpdateSize(sf::Vector2f _size)
{

	// update scale of sprite to match shape
	sf::Vector2u texSize = texture.getSize();
	float newSizeX = _size.x / (float)texSize.x;
	float newSizeY = _size.y / (float)texSize.y;
	sprite.setScale(sf::Vector2f(newSizeX, newSizeY));
	sprite.setOrigin(sf::Vector2f((float)texSize.x / 2, (float)texSize.y / 2));
}

void SpriteComponent::SetTransparency(float _value)
{
	//std::cout << (int)sprite.getColor().r << ", " << (int)sprite.getColor().g << ", " << (int)sprite.getColor().b << ", " << (int)sprite.getColor().a << std::endl;
	sprite.setColor(sf::Color(255 * _value, 255 * _value, 255 * _value, 255 * _value));
	//std::cout << (int)sprite.getColor().r << ", " << (int)sprite.getColor().g << ", " << (int)sprite.getColor().b << ", " << (int)sprite.getColor().a << std::endl;
	
}
