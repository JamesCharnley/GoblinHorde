#include "Level_One.h"
#include "GameObject_Rectangle.h"
#include "Character.h"
#include "Collider.h"
#include "Utility.h"

Level_One::Level_One(class Game* _gameClass, sf::RenderWindow* _window) 
{
	window = _window;
	
	
}

void Level_One::Start()
{

	// set fps limit
	window->setFramerateLimit(60);

	// create all GameObjects
	Character* player1 = new Character(window, this);
	player1->SetRadius(50.0f);
	player1->SetPlayersNumber(1);
	player1->SetCollisionRadius(50.f);
	player1->GetCollider()->SetCollisionType(ECollisionType::Block);
	AddSceneObject(player1);

	Character* player2 = new Character(window, this);
	player2->SetRadius(50.0f);
	player2->SetPlayersNumber(2);
	player2->SetCollisionRadius(50.f);
	player2->GetCollider()->SetCollisionType(ECollisionType::Block);
	AddSceneObject(player2);

	//Start scene
	Scene::Start();
}

