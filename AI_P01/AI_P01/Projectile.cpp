#include "SFML_VectorMath.h"
#include "Collider.h"
#include "Weapon.h"
#include "Scene.h"
#include "ITakeDamage.h"
#include "Enemy.h"
#include "Base.h"
#include "Player.h"
#include "Utility.h"
#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow* _window, Scene* _scene, float _rotation, GameObject* _owner, float _damage)
{
	window = _window;
	scene = _scene;
	damage = _damage;

	// set rotation of projectile
	SetRotation(_rotation);

	// calculate direction it will travel
	direction = SFML_VectorMath::AngleToDirection(GetRotation());
	direction = SFML_VectorMath::Normalize(direction);

	// set radius and setup collider
	SetRadius(5.0f);
	AddCollider(ECollisionType::Block);
	SetCollisionRadius(GetRadius());
	GetCollider()->SetCollisionType(ECollisionType::Overlap);
	GetCollider()->AddIgnoreObject(_owner);
	Weapon* projectileOwner = dynamic_cast<Weapon*>(_owner);
	if (projectileOwner)
	{
		GameObject* weaponOwner = projectileOwner->GetOwner();
		if (weaponOwner)
		{
			GetCollider()->AddIgnoreObject(weaponOwner);
			owningCharacter = dynamic_cast<Character*>(weaponOwner);
		}
		
	}
	
}

void Projectile::Update(float _deltatime)
{
	SetPosition(GetPosition() + direction * (speed * _deltatime));

	// destroy projectile if it leaves window
	if (GetPosition().x > (float)Utils::WindowWidth || GetPosition().x < 0 || GetPosition().y > (float)Utils::WindowHeight || GetPosition().y < 0)
	{
		Destroy();
	}
}

void Projectile::OnCollision(GameObject* _other)
{

	if (dontDamageEnemies)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(_other);
		if (enemy)
		{
			return;
		}
	}
	if (dontDamagePlayers)
	{
		Player* player = dynamic_cast<Player*>(_other);
		if (player)
		{
			return;
		}
	}
	Base* base = dynamic_cast<Base*>(_other);
	if (base)
	{
		return;
	}
	// take damage code
	ITakeDamage* takesDamage = dynamic_cast<ITakeDamage*>(_other);
	if (takesDamage)
	{
		Player* ownerIsPlayer = dynamic_cast<Player*>(owningCharacter);
		if (ownerIsPlayer)
		{
			takesDamage->TakeDamage(damage, owningCharacter);
		}
		else
		{
			takesDamage->TakeDamage(damage);
		}
	}
	Destroy();
}
