#include "SFML_VectorMath.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "Base.h"

Enemy::Enemy(sf::RenderWindow* _window, Scene* _scene, Base* _base) : Character(_window, _scene)
{
	base = _base;
	moveSpeed = 100.0f;
	//circle.setFillColor(sf::Color::Red);
	AddCollider(ECollisionType::Block);
}

Enemy::Enemy(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner, Base* _base) : Character(_window, _scene)
{
	base = _base;
	moveSpeed = 150.0f;
	spawner = _spawner;
	//circle.setFillColor(sf::Color::Red);
	AddCollider(ECollisionType::Block);
}

void Enemy::Update(float _deltatime)
{
	damageTimer -= _deltatime;
	int length = (int)players.size();

	float shortestDist = 9999;
	for (int i = 0; i < length; i++)
	{
		float dist = SFML_VectorMath::GetDistance(GetPosition(), players[i]->GetPosition());
		if (!players[i]->isDead)
		{
			if (dist < shortestDist)
			{
				shortestDist = dist;
				closestPlayer = players[i];
			}
		}
		
	}

	baseDistance = SFML_VectorMath::GetDistance(GetPosition(), base->GetPosition());

	if (closestPlayer && baseDistance >= shortestDist)
	{
		velocity = closestPlayer->GetPosition() - GetPosition();
		velocity = SFML_VectorMath::Clamp(velocity);

		Move(velocity * (moveSpeed * _deltatime));

		//check if player is in range
		if (damageTimer <= 0.0f && closestPlayer->GetCollisionRadius() + GetCollisionRadius() >= shortestDist - attackRange)
		{
			//damage the player and reset timer
			closestPlayer->TakeDamage(damage);
			damageTimer = damageIntervial;
			
		}
	}
	else
	{
		velocity = base->GetPosition() - GetPosition();
		velocity = SFML_VectorMath::Clamp(velocity);
		if (baseDistance > base->GetCollisionRadius())
		{
			Move(velocity * (moveSpeed * _deltatime));
		}
		

		if (damageTimer <= 0.0f && base->GetCollisionRadius() + GetCollisionRadius() >= baseDistance - attackRange)
		{
			//damage the player and reset timer
			base->TakeDamage(damage);
			damageTimer = damageIntervial;

		}
	}
}

void Enemy::AddPlayer(Player* _player)
{
	players.push_back(_player);
}

void Enemy::TakeDamage(int _amount, Character* _player)
{
	currentHealth -= _amount;

	// Goblin Hit SFX.
	if (!buffer.loadFromFile("Resources/SFX/Hit.wav"))
	{

	}	
	hitSFX.setBuffer(buffer);
	hitSFX.play();

	if (currentHealth <= 0)
	{
		// Goblin Die SFX.
		if (!buffer.loadFromFile("Resources/SFX/GoblinDie.wav"))
		{

		}
		goblinDieSFX.setBuffer(buffer);
		goblinDieSFX.play();

		Player* player = dynamic_cast<Player*>(_player);
		if (player)
		{
			player->AddGold(goldReward);
		}
		Destroy();
	}
}

void Enemy::Destroy()
{
	if (spawner != nullptr)
	{
		spawner->EnemyDestroyed(this);
	}
	Character::Destroy();
}
