#include "SFML_VectorMath.h"
#include "Weapon.h"
#include "Scene.h"
#include "Character.h"

Character::Character(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;

	selectedInputPreset = playerOnePreset;

	equippedWeapon = new Weapon(window, scene, this);
	scene->AddSceneObject(equippedWeapon);
}

void Character::Update(float _deltatime)
{
	if (equippedWeapon != nullptr)
	{
		equippedWeapon->SetPosition(GetPosition());
		equippedWeapon->SetRotation(GetRotation());
	}

	
	std::cout << GetRotation() << std::endl;
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
		SetRotation(SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity));
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.BackwardKey))
	{
		velocity.y += 1;
		SetRotation(SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity));
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.LeftKey))
	{
		velocity.x += -1;
		SetRotation(SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity));
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.RightKey))
	{
		velocity.x += 1;
		SetRotation(SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity));
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.ShootKey))
	{
		// shoot
		if (equippedWeapon != nullptr)
		{
			equippedWeapon->PerformAction();
		}
	}

	velocity = SFML_VectorMath::Normalize(velocity);
}
