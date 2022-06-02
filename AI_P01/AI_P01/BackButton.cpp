#include "BackButton.h"
#include "MainMenu.h"

BackButton::BackButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Back", _window, _scene)
{

}

void BackButton::Update(float _deltatime)
{
	GameObjectRectangle::Update(_deltatime);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			MainMenu* menu = dynamic_cast<MainMenu*>(scene);
			if (menu)
			{
				menu->ButtonAction(DisplayMode::DefaultMode);
			}
		}
	}
}
