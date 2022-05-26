#include "Button.h"
#include "GameText.h"
#include "Scene.h"

Button::Button(sf::Vector2f position, std::string text, sf::RenderWindow* _window, Scene* _scnene) : 
	GameObjectRectangle(_window, _scnene) //Potential Error
{
	window = _window;
	buttonText = new GameText("Resources/Font/WarPriest.ttf", position);
	buttonText->SetString(text);

														//change 30 to getCharacterSize() from gameText
	rectangle.setSize(sf::Vector2f(text.length() * 17, 30));
	rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color::Red);
}

void Button::Render()
{
	GameObjectRectangle::Render();

	buttonText->Render(window);
}

Button::Button()
{
}
