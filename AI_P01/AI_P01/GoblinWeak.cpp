#include "GoblinWeak.h"

GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene) : Enemy(_window, _scene)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;
}

GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner) : Enemy(_window, _scene, _spawner)
{
	//Set the unique stats such as health, movespeed and sprite 
	moveSpeed = 150.f;
	currentHealth = 100.f;
	
	sf::Texture* text;
	text = new sf::Texture();
	text->loadFromFile("Resources/Textures/EnemyPHWeak.png");
	circle.setTexture(text);
}
