#include "GameObject_Text.h"

GameObject_Text::GameObject_Text(sf::RenderWindow* _window, Scene* _scene, std::string _text)
{
	window = _window;
	scene = _scene;

	font.loadFromFile("Resources/Font/WarPriest.ttf");
	textObject.setFont(font);

	text = _text;
	textObject.setString(text);
}

void GameObject_Text::Render()
{
	window->draw(textObject);
}

void GameObject_Text::SetText(std::string _text)
{
	text = _text;
	textObject.setString(text);
}
