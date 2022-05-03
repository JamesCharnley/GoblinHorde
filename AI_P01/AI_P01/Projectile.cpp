#include "SFML_VectorMath.h"
#include "Collider.h"
#include "Weapon.h"
#include "Scene.h"
#include "ITakeDamage.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow* _window, Scene* _scene, float _rotation, GameObject* _owner)
{
	window = _window;
	scene = _scene;
	SetRotation(_rotation);
	direction = SFML_VectorMath::AngleToDirection(GetRotation());
	direction = SFML_VectorMath::Normalize(direction);
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
