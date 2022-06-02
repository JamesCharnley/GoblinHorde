#include "StartButton.h"
#include "Scene.h"
#include "GoblinHorde.h"

StartButton::StartButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position, int _numOfPlayers) : Button(_position, "Start", _window, _scene)
{
	numberOfPlayers = _numOfPlayers;
}

void StartButton::PerformAction()
{
	scene->SetNumberOfPlayers(numberOfPlayers);
	scene->ChangeScene("Level_One");
}


