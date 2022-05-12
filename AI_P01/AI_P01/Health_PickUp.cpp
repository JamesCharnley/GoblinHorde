#include "Player.h"
#include "Health_PickUp.h"

Health_PickUp::Health_PickUp(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;

	SetRadius(30);
}

void Health_PickUp::Interact(Player* _player)
{
	if (_player)
	{
		_player->AddHealth(effectAmount);
	}
	Destroy();
}
