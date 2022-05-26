#include "GoblinNormal.h"
#include "Base.h"

GoblinNormal::GoblinNormal(sf::RenderWindow* _window, Scene* _scene, Base* _base) : Enemy(_window, _scene, _base)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;
}

GoblinNormal::GoblinNormal(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner, Base* _base) : Enemy(_window, _scene, _spawner, _base)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;

	sf::Texture* text;
	text = new sf::Texture();
	text->loadFromFile("Resources/Textures/Orc.png");
	circle.setTexture(text);
}
