#include "Projectile.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Utility.h"

//assign weapon stats here
std::map<EWeapon, FWeapon::Data> FWeapon::dataMap =
{															      //dmg |   firerate  | ammo  | reload time  | bullet speed | name
	{EWeapon::Glock, Data(EWeapon::Glock, EWeaponType::Gun,			7.0f,		3.0f,	 7,			1.0f,		600.0f,		"Glock")},
	{EWeapon::SMG, Data(EWeapon::SMG, EWeaponType::Gun,				6.0f,		7.0f,	 35,		2.0f,		800.0f,		"SMG")},
	{EWeapon::Rifle, Data(EWeapon::Rifle, EWeaponType::Gun,			25.0f,		2.5f,	 5,			3.0f,		1000.0f,	"Rifle")},
	{EWeapon::DebugGun, Data(EWeapon::DebugGun, EWeaponType::Gun,	200.0f,		80.0f,	 INFINITY,	0.0f,		600.0f,		"Debug gun")},
};

Weapon::Weapon(sf::RenderWindow* _window, Scene* _scene, GameObject* _owner, EWeapon _weaponBase, float _gunshotVolumeScale)
{
	window = _window;
	scene = _scene;
	owner = _owner;
	weaponData = FWeapon::GetData(_weaponBase);
	name = weaponData.name;
	currentAmmo = weaponData.ammo;

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

	std::string sndFolder = "Resources/SFX/";

	if (!gunshotBuffer.loadFromFile(sndFolder + "Gunshot_" + weaponData.name + ".wav"))
	{

	}
	reloadStartBuffer.loadFromFile(sndFolder + "ReloadStart.wav");
	reloadEndBuffer.loadFromFile(sndFolder + "ReloadEnd.wav");
	ImplicitReloadBuffer.loadFromFile(sndFolder + "ImplicitReloadStart.wav");

	gunshotSound.setBuffer(gunshotBuffer);
	gunshotSound.setVolume(50.0f * _gunshotVolumeScale);
	reloadSound.setVolume(50.0f * _gunshotVolumeScale);
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
		//reload after a short delay if the weapon has no ammo
		if (currentAmmo <= 0)
		{
			const float IMPLICIT_RELOAD_DELAY = 0.3f;	
			inAction = true;
			cooldownTimer = IMPLICIT_RELOAD_DELAY;
			finishCoolDownDelegate = &Weapon::Reload;
			reloadSound.setBuffer(ImplicitReloadBuffer);
			reloadSound.play();
			return;
		}

		currentAmmo--;
		gunshotSound.play();

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

void Weapon::Reload()
{
	if (currentAmmo == weaponData.ammo || finishCoolDownDelegate == &Weapon::FinishReload)
	{
		return;
	}

	reloadSound.setBuffer(reloadStartBuffer);
	reloadSound.play();

	cooldownTimer = weaponData.reloadTime;
	inAction = true;
	finishCoolDownDelegate = &Weapon::FinishReload;
	//play sound
}

void Weapon::FinishReload()
{
	reloadSound.setBuffer(reloadEndBuffer);
	reloadSound.play();
	currentAmmo = weaponData.ammo;
	const float POST_RELOAD_DELAY = 0.3f;

	inAction = true;
	cooldownTimer = POST_RELOAD_DELAY;
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
		if (finishCoolDownDelegate != nullptr)
		{
			void(Weapon::* oldDelegate)() = finishCoolDownDelegate;
			(this->*finishCoolDownDelegate)();

			//clear completed delegate unless it has been changed in the called delegate
			if (oldDelegate == finishCoolDownDelegate)
			{
				finishCoolDownDelegate = nullptr;
			}
		}
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
