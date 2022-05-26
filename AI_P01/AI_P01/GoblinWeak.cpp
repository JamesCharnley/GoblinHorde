#include "GoblinWeak.h"
#include "Base.h"
GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class Base* _base) : Enemy(_window, _scene, _base)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;
}

GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner, class Base* _base) : Enemy(_window, _scene, _spawner, _base)
{
	//Set the unique stats such as health, movespeed and sprite 
	moveSpeed = 150.f;
	currentHealth = 100.f;
	
	sf::Texture* text;
	text = new sf::Texture();
	text->loadFromFile("Resources/Textures/EnemyPHWeak.png");
	circle.setTexture(text);
}
