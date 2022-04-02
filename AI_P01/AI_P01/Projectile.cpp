#include "SFML_VectorMath.h"
#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow* _window, Scene* _scene, float _rotation)
{
	window = _window;
	_scene = scene;
	SetRotation(_rotation);
	direction = SFML_VectorMath::AngleToDirection(GetRotation());
	direction = SFML_VectorMath::Normalize(direction);
	SetRadius(20.0f);
}

void Projectile::Update(float _deltatime)
{
	SetPosition(GetPosition() + direction * (speed * _deltatime));
}
