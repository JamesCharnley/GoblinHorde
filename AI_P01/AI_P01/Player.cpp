#include "SFML_VectorMath.h"
#include "Scene.h"
#include "Weapon.h"
#include "Player.h"
#include "GoblinHordeUI.h"
#include "PlayerStats.h"
#include <vector>

Player::Player(sf::RenderWindow* _window, Scene* _scene) : Character(_window, _scene)
{
	weapons.push_back(new Weapon(window, scene, this, "pistol"));
	weapons.push_back(new Weapon(window, scene, this, "rifle"));
	equippedWeapon = weapons.at(equippedWeaponIndex);

	for(Weapon* weapon : weapons)
	{
		scene->AddSceneObject(weapon);
	}

	selectedInputPreset = playerOnePreset;
	playerNum = 1;

	moveSpeed = 200.0f;

	AddCollider(ECollisionType::Block);

	font.loadFromFile("Resources/Font/WarPriest.ttf");
	actionText.setFont(font);
	actionText.setString(actionTextString);
	actionText.setCharacterSize(20);
	actionText.setOrigin(sf::Vector2f(actionText.getGlobalBounds().width / 2, actionText.getGlobalBounds().height / 2));
	actionText.setFillColor(sf::Color::Red);
}

void Player::Update(float _deltatime)
{
	Character::Update(_deltatime);

	if (playerNum == 1)
	{
		scene->GetUI()->getPlayer1Stats()->UpdateHealth(0);
		scene->GetUI()->getPlayer1Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer1Stats()->UpdateAmmo(0);
	}

	else if (playerNum == 2)
	{
		scene->GetUI()->getPlayer2Stats()->UpdateHealth(0);
		scene->GetUI()->getPlayer2Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer2Stats()->UpdateAmmo(0);
	}

	CheckForInput(playerNumber);
	if (rotationDelayTimer <= 0 && !lockRotation)
	{
		SetRotation(targetRotation);
	}
	else
	{
		rotationDelayTimer -= _deltatime;
	}

	// check current interactable
	if (currentInteractable)
	{
		if (currentInteractable->InRange(this))
		{
			// display action text
			if (currentInteractable->HasActionText())
			{
				actionTextString = "";
				actionTextString += currentInteractable->GetActionText();

				actionText.setString(actionTextString);
				actionText.setOrigin(sf::Vector2f(actionText.getGlobalBounds().width / 2, actionText.getGlobalBounds().height / 2));
			}
			// check if can interact
			if (currentInteractable->CanInteract(this))
			{
				if (sf::Joystick::isButtonPressed(playerNumber - 1, 0))
				{
					currentInteractable->Interact(this);
					currentInteractable = nullptr;
					actionTextString = "";
					actionText.setString(actionTextString);
					actionText.setOrigin(sf::Vector2f(actionText.getGlobalBounds().width / 2, actionText.getGlobalBounds().height / 2));
				}
			}
		}
		else
		{
			// remove current interactable
			currentInteractable = nullptr;
			actionTextString = "";
			actionText.setString(actionTextString);
		}
	}
	if (actionTextString != "")
	{
		actionText.setPosition(GetPosition() - sf::Vector2f(0, GetRadius() + GetRadius() * 0.75f));
		
	}
}

void Player::Render()
{
	GameObject_Circle::Render();
	window->draw(actionText);
}

void Player::SetPlayersNumber(int _number)
{
	playerNumber = _number;
	if (_number == 1)
	{
		selectedInputPreset = playerOnePreset;
		playerNum = 1;
	}
	else if (_number == 2)
	{
		selectedInputPreset = playerTwoPreset;
		playerNum = 2;
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
	//std::cout << "Left Stick:";
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::X) << ", ";	//left sick
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Y) << "\n";

	//std::cout << "Right Stick: ";
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::U) << ", ";	//right sick
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::V) << "\n";

	//std::cout << "Triggers: ";
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Z) << "\n";	//triggers

	//std::cout << "DPad: ";
	//std::cout << sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::PovX) << ", " << sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) << " \n";

	std::vector<std::string> pressedButtonNames;

	for (int i = 0; i <= 9; i++)
	{
		if (sf::Joystick::isButtonPressed(_controllerIndex, i))
		{
			pressedButtonNames.push_back(GetButtonMapping(i));
			std::cout << "Pressed: " << i << std::endl;
		}
	}

	for (std::string buttonName : pressedButtonNames)
	{
		//std::cout << buttonName << ", ";
	}
	
}

std::string Player::GetButtonMapping(int _button)
{
	return "";
}

void Player::OnCollision(GameObject* _other)
{
	Interactable* interactable = dynamic_cast<Interactable*>(_other);
	if (interactable)
	{
		if (interactable->AutoInteract())
		{
			interactable->Interact(this);
		}
		else
		{
			currentInteractable = interactable;
		}
	}
}

void Player::CheckForInput(int _player)
{
	velocity.x = 0;
	velocity.y = 0;

	PollController(0);
	float deadZone = 15.0f;

	float lStickX = sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::X);	//left sick
	float lStickY = sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::Y);

	if (lStickX > -deadZone && lStickX < deadZone)
	{
		lStickX = 0;
	}
	if (lStickY > -deadZone && lStickY < deadZone)
	{
		lStickY = 0;
	}

	float rStickX = sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::U);
	float rStickY = sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::V);

	if (rStickX > -deadZone && rStickX < deadZone)
	{
		rStickX = 0;
	}
	if (rStickY > -deadZone && rStickY < deadZone)
	{
		rStickY = 0;
	}

	if (lStickX > 0)
	{
		//lStickX /= 100;
	}
	if (lStickY > 0)
	{
		//lStickY /= 100;
	}
	if (!lastFrameSwitchWeapon && sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::PovX) > 0.0f)
	{
		NextWeapon();
		lastFrameSwitchWeapon = true;
	}
	else if (!lastFrameSwitchWeapon && sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::PovX) < 0.0f)
	{
		PreviousWeapon();
		lastFrameSwitchWeapon = true;
	}
	else if (sf::Joystick::getAxisPosition(_player - 1, sf::Joystick::Axis::PovX) == 0.0f)
	{
		lastFrameSwitchWeapon = false;
	}

	velocity.x = lStickX;
	velocity.y = lStickY;

	sf::Vector2f rotVelocity;

	rotVelocity.x = rStickX;
	rotVelocity.y = rStickY;

	rotVelocity = SFML_VectorMath::Clamp(rotVelocity);

	targetRotation = SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + rotVelocity);
	
	bool isKeyboard = false;

	//keyboard
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.ForwardKey))
	{
		velocity.y += -1;
		isKeyboard = true;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.BackwardKey))
	{
		velocity.y += 1;
		isKeyboard = true;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.LeftKey))
	{
		velocity.x += -1;
		isKeyboard = true;
	}
	if (sf::Keyboard::isKeyPressed(selectedInputPreset.RightKey))
	{
		velocity.x += 1;
		isKeyboard = true;
	}

	if (sf::Keyboard::isKeyPressed(selectedInputPreset.LockRotationKey))
	{
		lockRotation = true;
	}
	else
	{
		lockRotation = false;
	}

	if (isKeyboard && SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity) != targetRotation && (velocity.x != 0 || velocity.y != 0))
	{
		targetRotation = SFML_VectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity);
		rotationDelayTimer = rotationDelay;
	}


	if (sf::Joystick::isButtonPressed(_player - 1, 5) || sf::Keyboard::isKeyPressed(selectedInputPreset.ShootKey))
	{
		// shoot
		if (equippedWeapon != nullptr)
		{
			equippedWeapon->PerformAction();
		}
	}

	velocity = SFML_VectorMath::Clamp(velocity);
}

void Player::NextWeapon()
{
	equippedWeaponIndex++;
	if (equippedWeaponIndex >= weapons.size())
	{
		equippedWeaponIndex = 0;
	}
	equippedWeapon = weapons.at(equippedWeaponIndex);

	std::cout << "Player " << playerNum << " equipped " << equippedWeapon->name << "\n";
}

void Player::PreviousWeapon()
{
	equippedWeaponIndex--;
	if (equippedWeaponIndex < 0)
	{
		equippedWeaponIndex = weapons.size() - 1;
	}
	equippedWeapon = weapons.at(equippedWeaponIndex);

	std::cout << "Player " << playerNum << " equipped "<< equippedWeapon->name << "\n";
}
