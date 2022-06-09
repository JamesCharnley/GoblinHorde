#include "LobbySlot.h"
#include "SpriteComponent.h"
#include "Utility.h"
#include "MainMenu.h"

LobbySlot::LobbySlot(sf::RenderWindow* _window, Scene* _scene, int _controllerIndex)
{
	// initialize and set defaults. 
	rectangle = sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &rectangle;
	rectangle.setFillColor(sf::Color::Transparent);
	// set refs to sf::RenderWindow and Scene() class
	window = _window;
	scene = _scene;

	AddSprite("Resources/Textures/LobbySlot_BG.png");
	sprite->SetTransparency(0.85f);

	SetSize(sf::Vector2f(Utils::WINDOW_X * 0.2f, Utils::WINDOW_X * 0.2f));

	controllerIconTexture.loadFromFile("Resources/Textures/ControllerIcon.png");
	controllerIcon.setTexture(controllerIconTexture);
	controllerIcon.setScale(sprite->GetScale());
	controllerIcon.setOrigin(sprite->GetOrigin());

	buttonPromptIconTexture.loadFromFile("Resources/Textures/ButtonPrompt.png");
	buttonPromptIcon.setTexture(buttonPromptIconTexture);
	buttonPromptIcon.setScale(sprite->GetScale());
	buttonPromptIcon.setOrigin(sprite->GetOrigin());

	font.loadFromFile("Resources/Font/times.ttf");
	statusMessage.setFont(font);
	statusMessage.setString(statusMessageString);
	statusMessage.setCharacterSize(16);
	
	promptMessage.setFont(font);
	promptMessage.setString("Activate Controller");
	promptMessage.setCharacterSize(18);

	controllerIndex = _controllerIndex;

	currentFluct = promptFluctMin + promptFluctMin * 0.1f;
}

void LobbySlot::Update(float _deltaTime)
{
	GameObjectRectangle::Update(_deltaTime);
	
	if (isAutoActive)
	{
		if (!activeStatus)
		{
			ActivatedStatus();
		}
	}

	if (activeStatus)
	{
		statusMessage.setCharacterSize(24);
		statusMessage.setOrigin(sf::Vector2f(statusMessage.getLocalBounds().width / 2, (statusMessage.getLocalBounds().height + statusMessage.getCharacterSize() / 2) / 2));
		statusMessage.setPosition(GetPosition() + sf::Vector2f(0, GetSize().y * 0.25f));
	}
	else
	{
		statusMessage.setCharacterSize(16);
		statusMessage.setOrigin(sf::Vector2f(statusMessage.getLocalBounds().width / 2, (statusMessage.getLocalBounds().height + statusMessage.getCharacterSize() / 2) / 2));
		statusMessage.setPosition(GetPosition() + sf::Vector2f(0, -GetSize().y * 0.4f));
	}
	
	
	promptMessage.setOrigin(sf::Vector2f(promptMessage.getLocalBounds().width / 2, (promptMessage.getLocalBounds().height + promptMessage.getCharacterSize() / 2) / 2));
	promptMessage.setPosition(GetPosition() + sf::Vector2f(0, GetSize().y * 0.2f));

	controllerIcon.setPosition(GetPosition());
	buttonPromptIcon.setPosition(GetPosition());

	if (sf::Joystick::isConnected(controllerIndex) && !isAutoActive)
	{
		if (!unActiveStatus && !activeStatus)
		{
			UnActivatedStatus();
		}
	}
	else if(!isAutoActive)
	{
		if (!noControllerStatus)
		{
			NoControllerStatus();
		}
	}
	if (unActiveStatus)
	{
		if (!activeStatus)
		{
			if (sf::Joystick::isButtonPressed(controllerIndex, 2))
			{
				ActivatedStatus();
			}
		}

		if (currentFluct <= promptFluctMax && currentFluct >= promptFluctMin)
		{
			currentFluct += promptFluctSpeed * _deltaTime;
		}
		else if (currentFluct > promptFluctMax || currentFluct < promptFluctMin)
		{
			if (promptFluctSpeed > 0)
			{
				currentFluct = promptFluctMax;
			}
			else
			{
				currentFluct = promptFluctMin;
			}
			promptFluctSpeed *= -1;
		}
		buttonPromptIcon.setColor(sf::Color(255 * currentFluct, 255 * currentFluct, 255 * currentFluct, 255 * currentFluct));
		//std::cout << currentFluct << std::endl;
	}
}

void LobbySlot::Render()
{
	GameObjectRectangle::Render();
	window->draw(controllerIcon);
	window->draw(statusMessage);
	if (unActiveStatus)
	{
		window->draw(buttonPromptIcon);
		window->draw(promptMessage);
	}
}

void LobbySlot::AutoActivate()
{
	isAutoActive = true;
}

void LobbySlot::NoControllerStatus()
{
	if (activeStatus)
	{
		MainMenu* menu = dynamic_cast<MainMenu*>(scene);
		if (menu)
		{
			menu->RemovePlayer();
		}
	}
	activeStatus = false;
	unActiveStatus = false;
	noControllerStatus = true;
	statusMessageString = "STATUS: NO CONTROLLER DETECTED";
	statusMessage.setString(statusMessageString);

	controllerIcon.setColor(sf::Color(255 * 0.5f, 255 * 0.5f, 255 * 0.5f, 255 * 0.5f));
}

void LobbySlot::UnActivatedStatus()
{
	if (activeStatus)
	{
		MainMenu* menu = dynamic_cast<MainMenu*>(scene);
		if (menu)
		{
			menu->RemovePlayer();
		}
	}
	activeStatus = false;
	noControllerStatus = false;
	unActiveStatus = true;

	statusMessageString = "STATUS: CONTROLLER DETECTED";
	statusMessage.setString(statusMessageString);

	controllerIcon.setColor(sf::Color(255, 255, 255, 255));
	
}

void LobbySlot::ActivatedStatus()
{
	MainMenu* menu = dynamic_cast<MainMenu*>(scene);
	if (menu)
	{
		menu->AddPlayer();
	}

	noControllerStatus = false;
	unActiveStatus = false;
	activeStatus = true;

	statusMessageString = "READY!";
	statusMessage.setString(statusMessageString);
}
