#include "Player.h"
#include "HealthPickUp.h"

HealthPickUp::HealthPickUp(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;

	SetRadius(30);
	AddCollider(ECollisionType::Overlap);
	SetCollisionRadius(GetRadius());
}

void HealthPickUp::Interact(Player* _player)
{
	if (_player)
	{
		_player->AddHealth(effectAmount);
	}
	Destroy();
}
