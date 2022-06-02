#include "BackButton.h"
#include "MainMenu.h"

BackButton::BackButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Back", _window, _scene)
{

}

void BackButton::PerformAction()
{
	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		menu->ButtonAction(DisplayMode::DefaultMode);
	}
}

