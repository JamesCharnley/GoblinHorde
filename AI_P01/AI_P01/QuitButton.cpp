#include "QuitButton.h"
#include "Scene.h"

QuitButton::QuitButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Quit", _window, _scene)
{

}

void QuitButton::Update(float _deltatime)
{
	GameObject_Rectangle::Update(_deltatime);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			scene->Quit();
		}
	}
}