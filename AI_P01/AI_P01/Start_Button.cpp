#include "Start_Button.h"
#include "Scene.h"

Start_Button::Start_Button(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Start", _window, _scene)
{

}

void Start_Button::Update(float _deltatime)
{
	//When the mouse clicks on the button, scene changes to level one
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			scene->ChangeScene("Level_One");
		}
	}
}
