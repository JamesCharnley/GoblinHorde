#include "StartButton.h"
#include "Scene.h"
#include "GoblinHorde.h"
#include "MainMenu.h"
#include "SpriteComponent.h"
#include "GameText.h"
#include "Utility.h"

StartButton::StartButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position) : Button(_position, "Start", _window, _scene)
{
	rectangle.setFillColor(sf::Color::Transparent);
}

void StartButton::PerformAction()
{
	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		if (menu->GetNumberOfPlayers() > 0 || Utils::IS_DEBUG)
		{
			menu->StartGame();
		}
		
	}
}

void StartButton::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);

	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		if (menu->GetNumberOfPlayers() > 0 || Utils::IS_DEBUG)
		{
			sprite->SetTransparency(1.0f);
			buttonText->SetColor(sf::Color::White);
		}
		else
		{
			sprite->SetTransparency(0.5f);
			sf::Color white = sf::Color::White;
			white = sf::Color(white.r, white.g, white.b, white.a * 0.5f);
			buttonText->SetColor(white);
		}

	}

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


