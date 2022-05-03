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

	AddCollider(ECollisionType::Block);
}

void Player::Update(float _deltatime)
{
	Character::Update(_deltatime);

	CheckForInput();
	if (rotationDelayTimer <= 0 && !lockRotation)
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

void Player::AddGold(int _amount)
{
	currentGold += _amount;
}

void Player::RemoveGold(int _amount)
{
	currentGold -= _amount;
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

	if (sf::Keyboard::isKeyPressed(selectedInputPreset.LockRotationKey))
	{
		lockRotation = true;
	}
	else
	{
		lockRotation = false;
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