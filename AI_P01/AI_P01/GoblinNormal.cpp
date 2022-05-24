#include "GoblinNormal.h"

GoblinNormal::GoblinNormal(sf::RenderWindow* _window, Scene* _scene) : Enemy(_window, _scene)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;
}

GoblinNormal::GoblinNormal(sf::RenderWindow* _window, Scene* _scene, EnemySpawner* _spawner) : Enemy(_window, _scene, _spawner)
{
	moveSpeed = 150.f;
	currentHealth = 100.f;

	sf::Texture* text;
	text = new sf::Texture();
	text->loadFromFile("Resources/Textures/EnemyPH.png");
	circle.setTexture(text);
}
