#include "Projectile.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Utility.h"

//assign weapon stats here
std::map<EWeapon, FWeapon::Data> FWeapon::dataMap =
{															      //dmg | firerate | ammo | bullet speed
	{EWeapon::Glock, Data(EWeapon::Glock, EWeaponType::Gun,			7.0f,		3.0f,	 100,	600.0f,		"Glock")},
	{EWeapon::SMG, Data(EWeapon::SMG, EWeaponType::Gun,				6.0f,		7.0f,	 150,	800.0f,		"SMG")},
	{EWeapon::Rifle, Data(EWeapon::Rifle, EWeaponType::Gun,			25.0f,		5.0f,	 100,	1000.0f,	"Rifle")},
	{EWeapon::DebugGun, Data(EWeapon::DebugGun, EWeaponType::Gun,	200.0f,		80.0f,	 100,	600.0f,		"Debug gun")},
};

Weapon::Weapon(sf::RenderWindow* _window, Scene* _scene, GameObject* _owner, EWeapon _weaponBase, float _gunshotVolumeScale)
{
	window = _window;
	scene = _scene;
	owner = _owner;
	weaponData = FWeapon::GetData(_weaponBase);
	name = weaponData.name;
	if (name == "Glock")
	{
		bulletSpriteFile = "Resources/Textures/GlockBullet.png";
	}
	else if (name == "SMG")
	{
		bulletSpriteFile = "Resources/Textures/SMGBullet.png";
	}
	else if (name == "Rifle")
	{
		bulletSpriteFile = "Resources/Textures/RifleBullet.png";
	}
	else
	{
		bulletSpriteFile = "Resources/Textures/GlockBullet.png";
	}
	if (!buffer.loadFromFile("Resources/SFX/Gunshot.wav"))
	{

	}
	gunshotSFX.setBuffer(buffer);
	gunshotSFX.setVolume(50.0f * _gunshotVolumeScale);
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
		gunshotSFX.play();

		// shoot 
		Projectile* proj = new Projectile(window, scene, GetRotation(), this, weaponData.damage, weaponData.speed, bulletSpriteFile);
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

	float oldDmg = weaponData.damage;
	float oldFireRate = weaponData.actionsPerSecond;
	float oldSpeed = weaponData.speed;


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
	weaponData.speed += (GetBaseWeaponData().speed * (BASE_PERCENT_SPEED / 100.0f)); //add basePercent of base damage each upgrade

	if (Utils::IS_DEBUG)
	{
		std::cout << "\n**Upgraded weapon**\n";
		std::cout << "DMG: " << oldDmg << " > " << weaponData.damage << "\n";
		std::cout << "APS: " << oldFireRate << " > " << weaponData.actionsPerSecond << "\n";
		std::cout << "SPD: " << oldSpeed << " > " << weaponData.speed << "\n";
		std::cout << "DPS: " << oldDmg * oldFireRate << " > " << weaponData.damage * weaponData.actionsPerSecond << "\n\n";
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

FWeapon::Data Weapon::GetBaseWeaponData()
{
	return FWeapon::GetData(weaponData.weapon);
}
