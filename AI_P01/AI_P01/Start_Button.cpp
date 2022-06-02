#include "Start_Button.h"
#include "Scene.h"
#include "GoblinHorde.h"

Start_Button::Start_Button(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position, int _numOfPlayers) : Button(_position, "Start", _window, _scene)
{
	numberOfPlayers = _numOfPlayers;
}

void Start_Button::Update(float _deltatime)
{
	GameObject_Rectangle::Update(_deltatime);
	//When the mouse clicks on the button, scene changes to level one
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			scene->SetNumberOfPlayers(numberOfPlayers);
			scene->ChangeScene("Level_One");
		}
	}
}
