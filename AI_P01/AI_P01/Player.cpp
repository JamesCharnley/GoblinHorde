#include "SFML_VectorMath.h"
#include "Scene.h"
#include "Weapon.h"
#include "Player.h"
#include <vector>

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
	std::cout << "Gold: " << currentGold << std::endl;
}

void Player::RemoveGold(int _amount)
{
	currentGold -= _amount;
}



void Player::PollController(int _controllerIndex)
{
	std::cout << "Left Stick:";
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::X) << ", ";	//left sick
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Y) << "\n";

	std::cout << "Right Stick: ";
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::U) << ", ";	//right sick
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::V) << "\n";

	std::cout << "Triggers: ";
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Z) << "\n";	//triggers

	std::cout << "DPad: ";
	std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::PovX) << ", " << sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) << " \n";

	std::vector<std::string> pressedButtonNames;

	for (int i = 0; i <= 9; i++)
	{
		if (sf::Joystick::isButtonPressed(_controllerIndex, i))
		{
			pressedButtonNames.push_back(GetButtonMapping(i));
		}
	}

	for (std::string buttonName : pressedButtonNames)
	{
		std::cout << buttonName << ", ";
	}
	system("cls");
}

std::string Player::GetButtonMapping(int _button)
{
	switch (_button)
	{
	case 0:
		return "A";
	case 1:
		return "B";
	case 2:
		return "X";
	case 3:
		return "Y";
	case 4:
		return "LB";
	case 5:
		return "RB";
	case 6:
		return "Back";
	case 7:
		return "Menu";
	case 8:
		return "LS";
	case 9:
		return "RS";
	default:
		return "Invalid button index";
	}
}


void Player::CheckForInput()
{
	velocity.x = 0;
	velocity.y = 0;

	PollController(0);

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

	velocity = SFML_VectorMath::Clamp(velocity);
}