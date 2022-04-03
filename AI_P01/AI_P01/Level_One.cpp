#include "Level_One.h"
#include "GameObject_Rectangle.h"
#include "Player.h"
#include "Collider.h"
#include "EnemySpawner.h"
#include "Utility.h"

Level_One::Level_One(class Game* _gameClass, sf::RenderWindow* _window) 
{
	window = _window;
	game = _gameClass;
}

void Level_One::Start()
{

	// set fps limit
	window->setFramerateLimit(60);

	// create all GameObjects
	Player* player1 = new Player(window, this);
	player1->SetRadius(50.0f);
	player1->SetPlayersNumber(1);
	player1->SetCollisionRadius(50.f);
	player1->GetCollider()->SetCollisionType(ECollisionType::Block);
	player1->SetPosition(sf::Vector2f(Utils::WindowWidth / 2 - player1->GetRadius() * 3, Utils::WindowHeight / 2));
	AddSceneObject(player1);

	Player* player2 = new Player(window, this);
	player2->SetRadius(50.0f);
	player2->SetPlayersNumber(2);
	player2->SetCollisionRadius(50.f);
	player2->GetCollider()->SetCollisionType(ECollisionType::Block);
	player2->SetPosition(sf::Vector2f(Utils::WindowWidth / 2 + player1->GetRadius() * 3, Utils::WindowHeight / 2));
	AddSceneObject(player2);

	EnemySpawner* spawner = new EnemySpawner(window, this);
	spawner->SetPosition(sf::Vector2f(-100, -100));
	spawner->AddPlayer(player1);
	spawner->AddPlayer(player2);
	AddSceneObject(spawner);
	
	spawner = new EnemySpawner(window, this);
	spawner->SetPosition(sf::Vector2f(-100, -100));
	spawner->AddPlayer(player1);
	spawner->AddPlayer(player2);
	AddSceneObject(spawner);
	//Start scene
	Scene::Start();
}

