#include "Projectile.h"
#include "Scene.h"
#include "Weapon.h"

Weapon::Weapon(sf::RenderWindow* _window, Scene* _scene, GameObject* _owner)
{
	window = _window;
	scene = _scene;
	owner = _owner;
	weaponData = FWeaponData();
	weaponData.ActionsPerSecond = 3;
}

void Weapon::Update(float _deltatime)
{
	SetPosition(owner->GetPosition());
	
	if (inAction)
	{
		Cooldown(_deltatime);
	}
}

void Weapon::PerformAction()
{
	if (!inAction)
	{
		// shoot 
		Projectile* proj = new Projectile(window, scene, GetRotation(), this);
		proj->SetPosition(GetPosition());
		scene->AddSceneObject(proj);
		cooldownTimer = 1 / weaponData.ActionsPerSecond;
		inAction = true;
	}
}

void Weapon::Cooldown(float _deltatime)
{

	if (cooldownTimer <= 0)
	{
		cooldownTimer = 0;
		inAction = false;
	}
	else
	{
		cooldownTimer -= _deltatime;
	}
}
