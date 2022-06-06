#include "GoblinWeak.h"
#include "Base.h"

//Set the unique stats such as health, movespeed and sprite 
GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class Base* _base, float _health, float _damage) : Enemy(_window, _scene, _base, _health, _damage)
{
	moveSpeed = 200.f;
}

GoblinWeak::GoblinWeak(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner, class Base* _base, float _health, float _damage) : Enemy(_window, _scene, _spawner, _base, _health, _damage)
{
	moveSpeed = 200.f;
	sf::Texture* text;
	text = new sf::Texture();
	text->loadFromFile("Resources/Textures/Orc.png");
	circle.setTexture(text);
}
