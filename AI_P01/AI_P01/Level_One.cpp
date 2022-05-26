#include "Level_One.h"
#include "GameObject_Rectangle.h"
#include "Player.h"
#include "Collider.h"
#include "EnemySpawner.h"
#include "Base.h"
#include "WaveManager.h"
#include "Utility.h"
#include "SpawnPoint.h"
#include "Health_PickUp.h"
#include "WeaponUpgrade.h"
#include "WeaponPurchase.h"
#include "Button.h"
#include "GoblinHordeUI.h"
#include <SFML/Audio.hpp>

Level_One::Level_One(class Game* _gameClass, sf::RenderWindow* _window, int _numberOfPlayers = 1)
{
	window = _window;
	game = _gameClass;
	numberOfPlayers = _numberOfPlayers;
}

void Level_One::Start()
{
	// set fps limit
	window->setFramerateLimit(60);

	GameObject_Rectangle* bg = new GameObject_Rectangle(window, this);
	bg->SetPosition(sf::Vector2f(Utils::WindowWidth / 2, Utils::WindowHeight / 2));
	bg->AddSprite("Resources/Textures/Grass.png");
	bg->SetSize(sf::Vector2f(Utils::WindowWidth, Utils::WindowHeight));
	AddSceneObject(bg);

	Base* base = new Base(window, this);
	AddSceneObject(base);

	WeaponPurchase* weaponPurchase = new WeaponPurchase(window, this, EWeapon::SMG);
	weaponPurchase->SetPosition(sf::Vector2f(base->GetPosition().x - base->GetRadius() * 0.5f, base->GetPosition().y - base->GetRadius() * 0.5f));
	AddSceneObject(weaponPurchase);

	weaponPurchase = new WeaponPurchase(window, this, EWeapon::Rifle);
	weaponPurchase->SetPosition(sf::Vector2f(base->GetPosition().x + base->GetRadius() * 0.5f, base->GetPosition().y - base->GetRadius() * 0.5f));
	AddSceneObject(weaponPurchase);

	WeaponUpgrade* weaponUpgrade = new WeaponUpgrade(window, this);
	weaponUpgrade->SetPosition(sf::Vector2f(base->GetPosition().x, base->GetPosition().y + base->GetRadius() * 0.5f));
	AddSceneObject(weaponUpgrade);

	WaveManager* spawner = new WaveManager(window, this, base, numberOfPlayers);
	spawner->SetPosition(sf::Vector2f(-100, -100));

	// create all GameObjects
	Player* player1 = new Player(window, this);
	player1->AddSprite("Resources/Textures/Player1.png");
	player1->SetColor(sf::Color::Transparent);
	player1->SetRadius(25.0f);
	player1->SetPlayersNumber(1);
	player1->SetCollisionRadius(25.0f);
	player1->GetCollider()->SetCollisionType(ECollisionType::Block);
	player1->SetPosition(sf::Vector2f(Utils::WindowWidth / 2 - player1->GetRadius() * 3, Utils::WindowHeight / 2));
	player1->SetSpawnPoint(player1->GetPosition());
	AddSceneObject(player1);

	spawner->AddPlayer(player1);

	if (numberOfPlayers == 2)
	{
		Player* player2 = new Player(window, this);
		player2->AddSprite("Resources/Textures/Player2.png");
		player2->SetColor(sf::Color::Transparent);
		player2->SetRadius(25.0f);
		player2->SetPlayersNumber(2);
		player2->SetCollisionRadius(25.0f);
		player2->GetCollider()->SetCollisionType(ECollisionType::Block);
		player2->SetPosition(sf::Vector2f(Utils::WindowWidth / 2 + player1->GetRadius() * 3, Utils::WindowHeight / 2));
		player2->SetSpawnPoint(player2->GetPosition());
		AddSceneObject(player2);
		spawner->AddPlayer(player2);
	}
	
	spawner->AddSpawn(new SpawnBorder(sf::Vector2f(), sf::Vector2f(window->getSize().x, 0.0f), sf::Vector2f(0.0f, window->getSize().y), sf::Vector2f(window->getSize().x, window->getSize().y)));
	AddSceneObject(spawner);

	// Set Level Music to loop.

	if (!music.openFromFile("Resources/SFX/Boss.ogg"))
	{

	}
	music.setVolume(5.0f);
	music.play();
	music.setLoop(true);
	
	//Start scene
	Scene::Start();
}

void Level_One::Update(float _dtime)
{
	Scene::Update(_dtime);
	userInterface->Render(window);
}




