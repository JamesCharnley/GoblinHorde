#include "SFML_VectorMath.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* _window, Scene* _scene) : Character(_window, _scene)
{
	moveSpeed = 100.0f;
	circle.setFillColor(sf::Color::Red);
	AddCollider(ECollisionType::Block);
}

Enemy::Enemy(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner) : Character(_window, _scene)
{
	moveSpeed = 150.0f;
	spawner = _spawner;
	circle.setFillColor(sf::Color::Red);
	AddCollider(ECollisionType::Block);
}

void Enemy::Update(float _deltatime)
{
	int length = (int)players.size();

	float shortestDist = 0;
	for (int i = 0; i < length; i++)
	{
		float dist = SFML_VectorMath::GetDistance(GetPosition(), players[i]->GetPosition());
		if (i == 0)
		{
			shortestDist = dist;
			closestPlayer = players[i];
		}
		else if (dist < shortestDist)
		{
			shortestDist = dist;
			closestPlayer = players[i];
		}
	}

	if (closestPlayer)
	{
		velocity = closestPlayer->GetPosition() - GetPosition();
		velocity = SFML_VectorMath::Normalize(velocity);

		Move(velocity * (moveSpeed * _deltatime));
	}
}

void Enemy::AddPlayer(Player* _player)
{
	players.push_back(_player);
}

void Enemy::TakeDamage(int _amount, Character* _player)
{
	currentHealth -= _amount;

	if (currentHealth <= 0)
	{
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
