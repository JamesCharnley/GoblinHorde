#include "Button.h"
#include "GameText.h"
#include "Scene.h"

Button::Button(sf::Vector2f position, std::string text, sf::RenderWindow* _window, Scene* _scnene) : 
	GameObjectRectangle(_window, _scnene) //Potential Error
{
	window = _window;
	buttonText = new GameText("Resources/Font/WarPriest.ttf", position);
	buttonText->SetString(text);
	
	AddSprite("Resources/Textures/ButtonSprite.png");
														//change 30 to getCharacterSize() from gameText
	SetSize(sf::Vector2f(text.length() * 17, 30));
	SetPosition(position);
	rectangle.setFillColor(sf::Color::White);
	originSize = GetSize();
}

void Button::Render()
{
	GameObjectRectangle::Render();
	buttonText->Render(window);
}

void Button::Update(float _deltaTime)
{
	GameObjectRectangle::Update(_deltaTime);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

		if (rectangle.getGlobalBounds().contains(mousePos))
		{
			PerformAction();

		}
	}
	if (IsSelectedDisplay())
	{
		if (sf::Joystick::isConnected(0))
		{
			if (sf::Joystick::isButtonPressed(0, 0))
			{
				PerformAction();
			}
		}
	}
}

void Button::SetSelectedDisplay(bool _active)
{
	selectedDisplayMode = _active;

	if (_active)
	{
		//std::cout << "selecteddisplay active" << std::endl;
		SetSize(GetSize() * 1.1f);
	}
	else
	{
		//std::cout << "selecteddisplay not active" << std::endl;
		SetSize(originSize);
	}
}

void Button::PerformAction()
{
	
}

Button::Button()
{
	buttonText = nullptr;
}
