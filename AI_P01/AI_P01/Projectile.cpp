#include "SFML_VectorMath.h"
#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow* _window, Scene* _scene, float _rotation, sf::Vector2f _dir)
{
	window = _window;
	_scene = scene;
	direction = _dir;
	direction = SFML_VectorMath::Normalize(direction);
	SetRotation(_rotation);
	SetRadius(20.0f);
}

void Projectile::Update(float _deltatime)
{
	SetPosition(GetPosition() + direction * (speed * _deltatime));
}
