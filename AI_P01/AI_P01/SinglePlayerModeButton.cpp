#include "SinglePlayerModeButton.h"
#include "Scene.h"
#include "MainMenu.h"
SinglePlayerModeButton::SinglePlayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Single Player", _window, _scene)
{
}

void SinglePlayerModeButton::Update(float _deltatime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			MainMenu* menu = dynamic_cast<MainMenu*>(scene);
			if (menu)
			{
				menu->ButtonAction(DisplayMode::SinglePlayer);
			}
		}
	}
}
