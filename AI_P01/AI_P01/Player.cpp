#include "SFML_VectorMath.h"
#include "Scene.h"
#include "Weapon.h"
#include "Player.h"

Player::Player(sf::RenderWindow* _window, Scene* _scene) : Character(_window, _scene)
{
	equippedWeapon = new Weapon(window, scene, this);
	scene->AddSceneObject(equippedWeapon);

	selectedInputPreset = playerOnePreset;

	moveSpeed = 200.0f;
}

void Player::Update(float _deltatime)
{
	if (equippedWeapon != nullptr)
	{
		equippedWeapon->SetPosition(GetPosition());
		equippedWeapon->SetRotation(GetRotation());
	}
	CheckForInput();
	Move(velocity * (moveSpeed * _deltatime));

	if (rotationDelayTimer <= 0)
	{
		SetRotation(targetRotation);
	}
	else
	{
		rotationDelayTimer -= _deltatime;
	}
}

void Player::SetPlayersNumber(int _number)
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

void Player::CheckForInput()
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

	if (SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity) != targetRotation && (velocity.x != 0 || velocity.y != 0))
	{
		targetRotation = SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity);
		rotationDelayTimer = rotationDelay;
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