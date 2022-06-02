#include "MultiplayerModeButton.h"
#include "MainMenu.h"
MultiplayerModeButton::MultiplayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Play", _window, _scene)
{
	
	
}

void MultiplayerModeButton::PerformAction()
{
	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		menu->ButtonAction(DisplayMode::MultiPlayer);
	}
}


