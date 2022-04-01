#include "Projectile.h"
#include "Scene.h"
#include "Weapon.h"

Weapon::Weapon(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;
	weaponData = FWeaponData();
	weaponData.ActionsPerSecond = 3;
}

void Weapon::Update(float _deltatime)
{
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
		Projectile* proj = new Projectile(window, scene, GetRotation());
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
