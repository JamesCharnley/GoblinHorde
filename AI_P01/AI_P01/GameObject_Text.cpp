#include "GameObject_Text.h"

GameObjectText::GameObjectText(sf::RenderWindow* _window, Scene* _scene, std::string _text)
{
	window = _window;
	scene = _scene;

	font.loadFromFile("Resources/Font/WarPriest.ttf");
	textObject.setFont(font);

	text = _text;
	textObject.setString(text);
}

void GameObjectText::Render()
{
	window->draw(textObject);
}

void GameObjectText::SetText(std::string _text)
{
	text = _text;
	textObject.setString(text);
}
