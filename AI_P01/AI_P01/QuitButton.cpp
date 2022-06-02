#include "QuitButton.h"
#include "Scene.h"

QuitButton::QuitButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Quit", _window, _scene)
{

}

void QuitButton::PerformAction()
{
	scene->Quit();
}
