#include "Projectile.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

//assign weapon stats here
std::map<EWeapon, FWeapon::Data> FWeapon::dataMap =
{															      //dmg | firerate | ammo | bullet speed
	{EWeapon::Glock, Data(EWeapon::Glock, EWeaponType::Gun,			20,		4.0f,	 100,	600.0f)},
	{EWeapon::Rifle, Data(EWeapon::Rifle, EWeaponType::Gun,			50,		2.0f,	 100,	1000.0f)},
	{EWeapon::DebugGun, Data(EWeapon::DebugGun, EWeaponType::Gun,	200,	80.0f,	 100,	600.0f)},
};

Weapon::Weapon(sf::RenderWindow* _window, Scene* _scene, GameObject* _owner, EWeapon _weaponBase, std::string _name)
{
	window = _window;
	scene = _scene;
	owner = _owner;
	weaponData = FWeapon::GetData(_weaponBase);
	name = _name;
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
		Projectile* proj = new Projectile(window, scene, GetRotation(), this, weaponData.damage, weaponData.speed);
		proj->SetPosition(GetPosition());
		scene->AddSceneObject(proj);
		cooldownTimer = 1.0f / weaponData.actionsPerSecond;
		inAction = true;

		Enemy* enemy = dynamic_cast<Enemy*>(owner);
		if (enemy)
		{
			proj->SetDontDamageEnemies();
		}
		Player* player = dynamic_cast<Player*>(owner);
		if (player)
		{
			proj->SetDontDamagePlayers();
		}
	}
}

FWeapon::Data Weapon::GetWeaponData()
{
	return weaponData;
}

void Weapon::Upgrade()
{
	weaponData.level++;

	//set weaponData to the base atribute + the level bonus

	//fire rate
	float c = 1.5f;
	float a = 0.1f;
	float f = 0.8f;
	float aps = (log(pow(pow(weaponData.level, 10.0f), c)) * a + 1.0f) * f - f;
	weaponData.actionsPerSecond = GetBaseWeaponData().actionsPerSecond + aps;

	//damage
	const float BASE_PERCENT_DMG = 10.0f;
	weaponData.damage += (GetBaseWeaponData().damage * (BASE_PERCENT_DMG / 100.0f)); //add basePercent of base damage each upgrade

	//projectile speed
	const float BASE_PERCENT_SPEED = 10.0f;
	weaponData.damage += (GetBaseWeaponData().speed * (BASE_PERCENT_SPEED / 100.0f)); //add basePercent of base damage each upgrade

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

FWeapon::Data Weapon::GetBaseWeaponData()
{
	return FWeapon::GetData(weaponData.weapon);
}
