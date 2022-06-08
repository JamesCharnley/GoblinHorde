#include "SFMLVectorMath.h"
#include "Scene.h"
#include "Player.h"
#include "GoblinHordeUI.h"
#include "PlayerStats.h"
#include <vector>
#include "Base.h"


Player::Player(sf::RenderWindow* _window, Scene* _scene) : Character(_window, _scene, 100.0f)
{
	weapons.push_back(new Weapon(_window, _scene, this, EWeapon::Glock));
	//weapons.push_back(new Weapon(_window, _scene, this, EWeapon::Rifle));
	equippedWeapon = weapons.at(equippedWeaponIndex);

	//for(Weapon weapon : weapons)
	//{
	//	scene->AddSceneObject(&weapon);
	//}

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

	base = nullptr;
}

Player::~Player()
{
	for (Weapon* weapon : weapons)
	{
		delete weapon;
	}
}

void Player::Update(float _deltatime)
{
	if (isDead) return;
	Character::Update(_deltatime);
	if (equippedWeapon != nullptr)
	{
		equippedWeapon->Update(_deltatime);
	}

	if (playerNum == 1)
	{
		scene->GetUI()->getPlayer1Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer1Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer1Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer1Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
	}

	else if (playerNum == 2)
	{
		scene->GetUI()->getPlayer2Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer2Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer2Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer2Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
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
		PollInteractable();
	}

	if (base != nullptr && currentInteractable == nullptr)
	{
		if (base->InRange(this))
		{
			if (base->GetCurrentHealth() < base->GetMaxHealth())
			{
				actionTextString = "Repair Base";
				actionText.setString(actionTextString);
				if (sf::Joystick::isButtonPressed(playerNumber - 1, 0))
				{
					base->Repair(_deltatime);
				}
			}
			else
			{
				actionTextString = "";
				actionText.setString(actionTextString);
				base = nullptr;
			}
			
		}
		else
		{
			actionTextString = "";
			actionText.setString(actionTextString);
			base = nullptr;
		}
	}

	if (currentInteractable || base)
	{
		UpdateActionText();
	}

}

void Player::Render()
{
	
	GameObjectCircle::Render();
	window->draw(actionText);
	if (equippedWeapon != nullptr)
	{
		equippedWeapon->Render();
	}
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
	//std::cout << "Gold: " << currentGold << std::endl;
	if (!buffer.loadFromFile("Resources/SFX/Gold.wav"))
	{

	}
	PlayerGoldSFX.setBuffer(buffer);
	PlayerGoldSFX.setVolume(25);
	PlayerGoldSFX.play();
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
			//std::cout << "Pressed: " << i << std::endl;
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

int Player::GetWeaponLevel()
{
	return weapons[equippedWeaponIndex]->GetLevel();
}

void Player::UpgradeWeapon()
{
	weapons[equippedWeaponIndex]->Upgrade();
}

void Player::AddWeapon(Weapon* _weapon)
{
	Weapon* newWeapon = new Weapon(*_weapon);
	newWeapon->SetOwner(this);
	weapons.push_back(newWeapon);
}

bool Player::HasWeapon(EWeapon _weapon)
{
	for (Weapon* weapon : weapons)
	{
		if (weapon->GetWeaponData().weapon == _weapon)
		{
			return true;
		}
	}
	return false;
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
	Base* isBase = dynamic_cast<Base*>(_other);
	if (isBase)
	{
		base = isBase;
	}
}

void Player::TakeDamage(int _amount)
{
	currentHealth -= _amount;

	if (currentHealth <= 0)
	{
		// Player Death SFX.
		if (!buffer.loadFromFile("Resources/SFX/PlayerDie.wav"))
		{

		}
		PlayerDieSFX.setBuffer(buffer);
		PlayerDieSFX.play();
		isDead = true;

	}
}

void Player::Respawn()
{
	currentHealth = maxHealth;
	SetPosition(spawnpoint);
	isDead = false;
}

void Player::SetSpawnPoint(sf::Vector2f _pos)
{
	spawnpoint = _pos;
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
		rStickX = 0.0f;
	}
	if (rStickY > -deadZone && rStickY < deadZone)
	{
		rStickY = 0.0f;
	}

	if (lStickX != 0.0f)
	{
		lStickX /= (100.0f - deadZone);
	}
	if (lStickY != 0.0f)
	{
		lStickY /= (100.0f - deadZone);
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

	rotVelocity = SFMLVectorMath::Clamp(rotVelocity);

	targetRotation = SFMLVectorMath::DirectionToAngle(GetPosition(), GetPosition() + rotVelocity);
	
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

	if (isKeyboard && SFMLVectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity) != targetRotation && (velocity.x != 0 || velocity.y != 0))
	{
		targetRotation = SFMLVectorMath::DirectionToAngle(GetPosition(), GetPosition() + velocity);
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

	velocity = SFMLVectorMath::Clamp(velocity);
}

void Player::PollInteractable()
{
	if (currentInteractable->InRange(this))
	{
		// display action text
		if (currentInteractable->HasActionText(this))
		{
			actionTextString = "";
			actionTextString += currentInteractable->GetActionText();

			if (currentInteractable->CostsGold())
			{
				actionTextString += ": " + std::to_string(currentInteractable->GetPrice(this));
			}
		}
		// check if can interact
		if (currentInteractable->CanInteract(this))
		{
			if (sf::Joystick::isButtonPressed(playerNumber - 1, 0) && actionButtonPressed == false)
			{
				actionButtonPressed = true;
				currentInteractable->Interact(this);
				currentInteractable = nullptr;
				actionTextString = "";
				UpdateActionText();
			}
		}
	}
	else
	{
		// remove current interactable
		currentInteractable = nullptr;
		actionTextString = "";
		UpdateActionText();
	}

	if (!sf::Joystick::isButtonPressed(playerNumber - 1, 0))
	{
		actionButtonPressed = false;
	}
	
}

void Player::UpdateActionText()
{
	actionText.setString(actionTextString);
	actionText.setOrigin(sf::Vector2f(actionText.getGlobalBounds().width / 2, actionText.getGlobalBounds().height / 2));
	if (actionTextString != "")
	{
		actionText.setPosition(GetPosition() - sf::Vector2f(0, GetRadius() + GetRadius() * 0.75f));
	}
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
