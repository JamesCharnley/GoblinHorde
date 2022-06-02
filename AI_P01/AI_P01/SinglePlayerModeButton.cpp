#include "SinglePlayerModeButton.h"
#include "Scene.h"
#include "MainMenu.h"
SinglePlayerModeButton::SinglePlayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Single Player", _window, _scene)
{
}

void SinglePlayerModeButton::PerformAction()
{
	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		menu->ButtonAction(DisplayMode::SinglePlayer);
	}
}
