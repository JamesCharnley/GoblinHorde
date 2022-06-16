#include "SFMLVectorMath.h"
#include "Scene.h"
#include "Player.h"
#include "GoblinHordeUI.h"
#include "PlayerStats.h"
#include <vector>
#include "Base.h"
#include "Utility.h"


Player::Player(sf::RenderWindow* _window, Scene* _scene, float _playerCount) : Character(_window, _scene, 100.0f)
{
	weapons.push_back(new Weapon(_window, _scene, this, EWeapon::Glock, 1.0f / _playerCount));
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
	playerSFX.setVolume(20);

	purchaseBuffer.loadFromFile("Resources/SFX/Purchase.wav");
	goldBuffer.loadFromFile("Resources/SFX/Gold.wav");
	hurtSFXBuffer.loadFromFile("Resources/SFX/PlayerHurt.wav");
	dieSFXBuffer.loadFromFile("Resources/SFX/PlayerDie.wav");
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
		scene->GetUI()->getPlayer1Stats()->setPlayerNumber(playerNum);
		scene->GetUI()->getPlayer1Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer1Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer1Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer1Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
	}

	else if (playerNum == 2)
	{
		scene->GetUI()->getPlayer2Stats()->setPlayerNumber(playerNum);
		scene->GetUI()->getPlayer2Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer2Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer2Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer2Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
	}

	else if (playerNum == 3)
	{
		scene->GetUI()->getPlayer3Stats()->setPlayerNumber(playerNum);
		scene->GetUI()->getPlayer3Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer3Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer3Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer3Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
	}

	else if (playerNum == 4)
	{
		scene->GetUI()->getPlayer4Stats()->setPlayerNumber(playerNum);
		scene->GetUI()->getPlayer4Stats()->UpdateHealth(currentHealth);
		scene->GetUI()->getPlayer4Stats()->UpdateGold(currentGold);
		scene->GetUI()->getPlayer4Stats()->UpdateAmmo(0);
		scene->GetUI()->getPlayer4Stats()->UpdateEquippedWeapon(equippedWeapon->name, GetWeaponLevel());
	}

	//populate input struct
	PollController(playerNumber - 1);

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
				if (input.button.A)
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


	checkConstraints();
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
	playerNum = _number;
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

	playerGoldSFX.setVolume(15);
	playerGoldSFX.setBuffer(goldBuffer);
	playerGoldSFX.play();
}

void Player::RemoveGold(int _amount)
{
	currentGold -= _amount;
	playerGoldSFX.setVolume(50);
	playerGoldSFX.setBuffer(purchaseBuffer);
	playerGoldSFX.play();

}



void Player::PollController(int _controllerIndex)
{
	//left stick
	input.axis.LS.x = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::X);
	input.axis.LS.y = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Y);

	//right stick
	input.axis.RS.x = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::U);
	input.axis.RS.y = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::V);

	//triggers
	input.axis.Trig = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::Z);	//triggers

	//Dpad
	input.axis.DPad.x = sf::Joystick::getAxisPosition(_controllerIndex, sf::Joystick::Axis::PovX);
	input.axis.DPad.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

	input.button.DPad.up = input.axis.DPad.y > 0;
	input.button.DPad.down = input.axis.DPad.y < 0;
	input.button.DPad.right = input.axis.DPad.x > 0;
	input.button.DPad.left = input.axis.DPad.x < 0;


	for (int i = 0; i < input.button.count; i++)
	{
		input.button.Set(i, sf::Joystick::isButtonPressed(_controllerIndex, i));
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
		playerSFX.setBuffer(dieSFXBuffer);
		playerSFX.play();
		isDead = true;
	}
	else
	{
		playerSFX.setBuffer(hurtSFXBuffer);
	}
	playerSFX.play();
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

	//movement input
	float deadZone = 15.0f;
	if (input.axis.LS.x > -deadZone && input.axis.LS.x < deadZone)
	{
		input.axis.LS.x = 0;
	}
	if (input.axis.LS.y > -deadZone && input.axis.LS.y < deadZone)
	{
		input.axis.LS.y = 0;
	}

	if (input.axis.RS.x > -deadZone && input.axis.RS.x < deadZone)
	{
		input.axis.RS.x = 0.0f;
	}
	if (input.axis.RS.y > -deadZone && input.axis.RS.y < deadZone)
	{
		input.axis.RS.y = 0.0f;
	}

	if (input.axis.LS.x != 0.0f)
	{
		input.axis.LS.x /= (100.0f - deadZone);
	}
	if (input.axis.LS.y != 0.0f)
	{
		input.axis.LS.y /= (100.0f - deadZone);
	}

	//weapon switching
	if (!lastFrameSwitchWeapon && input.button.DPad.left)
	{
		NextWeapon();
		lastFrameSwitchWeapon = true;
	}
	else if (!lastFrameSwitchWeapon && input.button.DPad.right)
	{
		PreviousWeapon();
		lastFrameSwitchWeapon = true;
	}
	else if (input.axis.DPad.x == 0.0f)
	{
		lastFrameSwitchWeapon = false;
	}

	//appy movement
	velocity.x = input.axis.LS.x;
	velocity.y = input.axis.LS.y;

	sf::Vector2f rotVelocity;

	rotVelocity.x = input.axis.RS.x;
	rotVelocity.y = input.axis.RS.y;

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


	//handle actions

	//shoot
	if (input.button.RB || sf::Keyboard::isKeyPressed(selectedInputPreset.ShootKey))
	{
		// shoot
		if (equippedWeapon != nullptr)
		{
			equippedWeapon->PerformAction();
		}
	}

	//reload
	if (input.button.X)
	{
		ReloadWeapon();
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
			if (input.button.A && actionButtonPressed == false)
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

	if (!input.button.A)
	{
		actionButtonPressed = false;
	}
	
}

void Player::ReloadWeapon()
{
	if (equippedWeapon != nullptr)
	{
		equippedWeapon->Reload();
	}
}

void Player::checkConstraints()
{
	if (this->GetPosition().x < 0 + GetRadius() / 2)
	{
		this->SetPosition(sf::Vector2f(0 + GetRadius() / 2, this->GetPosition().y));
	}

	if (this->GetPosition().x > Utils::WINDOW_X - GetRadius() / 2)
	{
		this->SetPosition(sf::Vector2f(Utils::WINDOW_X, this->GetPosition().y));
	}

	if (this->GetPosition().y < 0 + GetRadius() / 2)
	{
		this->SetPosition(sf::Vector2f(this->GetPosition().x, 0 + GetRadius() / 2));
	}

	if (this->GetPosition().y > Utils::WINDOW_Y - GetRadius() / 2)
	{
		this->SetPosition(sf::Vector2f(this->GetPosition().x, Utils::WINDOW_Y - GetRadius() / 2));
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
