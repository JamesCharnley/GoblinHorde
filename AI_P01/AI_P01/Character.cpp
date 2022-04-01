#include "SFML_VectorMath.h"
#include "Character.h"

Character::Character(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;

	selectedInputPreset = playerOnePreset;
}

void Character::Update(float _deltatime)
{
	CheckForInput();

	Move(velocity * (moveSpeed * _deltatime));
}

void Character::SetPlayersNumber(int _number)
{
	if (_number == 1)
	{
		selectedInputPreset = playerOnePreset;
	}
	else if (_number == 2)
	{
		selectedInputPreset = playerTwoPreset;
	}
}

void Character::Move(sf::Vector2f _movement)
{
	SetPosition(GetPosition() + _movement);
}

void Character::CheckForInput()
{
	velocity.x = 0;
	velocity.y = 0;

	if (sf::Keyboard::isKeyPressed(selectedInputPreset.ForwardKey))
	{
		velocity.y += -1;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.BackwardKey))
	{
		velocity.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.LeftKey))
	{
		velocity.x += -1;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.RightKey))
	{
		velocity.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.ShootKey))
	{
		// shoot
	}

	velocity = SFML_VectorMath::Normalize(velocity);
}
