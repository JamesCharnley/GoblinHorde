#include "Utility.h"
#include "Base.h"
#include "SFMLVectorMath.h"
#include "Player.h"
#include "Scene.h"

Base::Base(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;

	AddSprite("Resources/Textures/BaseGroundPH.png");
	SetColor(sf::Color::Transparent);
	SetRadius(125.0f);
	SetPosition(sf::Vector2f((float)Utils::WindowWidth / 2.0f, (float)Utils::WindowHeight / 2.0f));
	AddCollider(ECollisionType::Overlap);
	collisionRadius = 125.0f;
	
	currentHealth = maxHealth * 0.9f;

	healthBar = new GameObjectRectangle(_window, _scene);
	healthBar->SetColor(sf::Color::Red);
	healthBar->SetSize(sf::Vector2f(GetRadius(), 20.0f));
	healthBar->SetPosition(GetPosition());
	healthBar->SetScale(sf::Vector2f(currentHealth / maxHealth, 1));
}

Base::~Base()
{
	if (healthBar != nullptr)
	{
		delete healthBar;
	}
	
}

void Base::Render()
{
	GameObjectCircle::Render();

	healthBar->Render();
}

void Base::TakeDamage(int _amount)
{
	if ((currentHealth - _amount) <= 0)
	{
		currentHealth = 0;
		//gameover
		scene->ChangeScene("Main_Menu");
	}
	else
	{
		currentHealth -= _amount;
	}
	healthBar->SetScale(sf::Vector2f(currentHealth / maxHealth, 1));
}

void Base::TakeDamage(int _amount, Character* _player)
{
	if ((currentHealth - _amount) <= 0)
	{
		currentHealth = 0;
	}
	else
	{
		currentHealth -= _amount;
	}
	healthBar->SetScale(sf::Vector2f(currentHealth / maxHealth, 1));
}

bool Base::InRange(Player* _player)
{
	if (SFMLVectorMath::GetDistance(_player->GetPosition(), GetPosition()) <= GetCollisionRadius() + _player->GetCollisionRadius())
	{
		return true;
	}
	return false;
}

void Base::Repair(float _repairAmount)
{
	if (currentHealth + _repairAmount <= maxHealth)
	{
		currentHealth += _repairAmount;
	}
	else
	{
		currentHealth = maxHealth;
	}
	healthBar->SetScale(sf::Vector2f(currentHealth / maxHealth, 1));
}

