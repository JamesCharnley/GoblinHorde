#include "MainMenu.h"
#include "Button.h"
#include "StartButton.h"
#include "QuitButton.h"
#include "TitleButton.h"
#include "SinglePlayerModeButton.h"
#include "MultiplayerModeButton.h"
#include "BackButton.h"
#include "Utility.h"
#include "GameObject_Text.h"
MainMenu::MainMenu(Game* _gameClass, sf::RenderWindow* _window)
{
	if (isDebug)
	{
		std::cout << "**Debug build**\n";
	}
	window = _window;
	game = _gameClass;
}

void MainMenu::Start()
{
	window->setFramerateLimit(60);

	displayMode = DisplayMode::DefaultMode;

	// Set Menu Background.
	MenuBackground = new GameObjectRectangle(window, this);
	MenuBackground->AddSprite("Resources/Textures/Grass.png");
	AddSceneObject(MenuBackground);

	messageText = new GameObjectText(window, this, "");
	AddSceneObject(messageText);

	// Set Menu Title, half window width - half its own width.
	MenuTitle = new GameObjectRectangle(window, this);
	MenuTitle->SetPosition(sf::Vector2f(Utils::WindowWidth / 2 -375.0f, 100.0f));
	MenuTitle->AddSprite("Resources/Textures/MenuTitle.png");
	AddSceneObject(MenuTitle);

	// Set music and to loop.
	if (!music.openFromFile("Resources/SFX/InGame.ogg"))
	{

	}
	music.setVolume(10.0f);
	music.play();
	music.setLoop(true);

	ActivateDefaultDisplay();

	Scene::Start();
}

void MainMenu::Update(float _dtime)
{
	Scene::Update(_dtime);


	if (displayMode == DisplayMode::SinglePlayer)
	{
		if (sf::Joystick::isConnected(0))
		{
			messageText->SetText("Controller Connected. Ready to start game.");
			if (canStartGame == false)
			{
				canStartGame = true;
				numberOfPlayers = 1;
				ActivateSinglePlayerDisplay();
			}
			
		}
		else
		{
			messageText->SetText("No Controller Detected. Controls default to keyboard.");
			canStartGame = false;
		}
	}
	if (displayMode == DisplayMode::MultiPlayer)
	{
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			messageText->SetText("Two Controllers Connected. Ready to start game.");
			if (canStartGame == false)
			{
				canStartGame = true;
				numberOfPlayers = 2;
				ActivateMultiplayerDisplay();
			}

		}
		else if (isDebug)
		{
			messageText->SetText("Debug build: skipping controller requirement");
			if (canStartGame == false)
			{
				canStartGame = true;
				numberOfPlayers = 2; 
				ActivateMultiplayerDisplay();
			}

		}
		else
		{
			messageText->SetText("Not Enough Controllers Detected.");
			canStartGame = false;
		}
	}

	if (stickTimer > 0)
	{
		stickTimer -= _dtime;
	}
	else
	{
		if (stickCoolDown)
		{
			stickCoolDown = false;
		}
	}
	if (!stickCoolDown)
	{
		CheckForControllerInput();
	}
}


void MainMenu::ButtonAction(DisplayMode _mode)
{
	displayMode = _mode;

	switch (displayMode)
	{
	case DisplayMode::DefaultMode:
		ActivateDefaultDisplay();
		break;
	case DisplayMode::ModeSelection:
		ActivateModeSelectionDisplay();
		break;
	case DisplayMode::SinglePlayer:
		AddBackButton();
		break;
	case DisplayMode::MultiPlayer:
		AddBackButton();
		break;
	case DisplayMode::PlayReady:
		ActivatePlayReadyDisplay();
		break;
	default:
		break;
	}
}

void MainMenu::ClearMenu()
{
	selectedButton = nullptr;
	activeButtons.clear();

	canStartGame = false;
	DestroySceneObject(quitButton);
	quitButton = nullptr;
	DestroySceneObject(backButton);
	backButton = nullptr;
	DestroySceneObject(singleplayerButton);
	singleplayerButton = nullptr;
	DestroySceneObject(multiplayerButton);
	multiplayerButton = nullptr;
	DestroySceneObject(startButton);
	startButton = nullptr;
	messageText->SetText(" ");

	
}

void MainMenu::ActivateDefaultDisplay()
{
	ClearMenu();

	singleplayerButton = new SinglePlayerModeButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.4f));
	AddSceneObject(singleplayerButton);
	activeButtons.push_back(singleplayerButton);

	multiplayerButton = new MultiplayerModeButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.5f));
	AddSceneObject(multiplayerButton);
	activeButtons.push_back(multiplayerButton);

	quitButton = new QuitButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.75f));
	AddSceneObject(quitButton);
	activeButtons.push_back(quitButton);

	selectedButtonIndex = 0;

	ActivateModeSelectionDisplay();
	//Title_Button* title = new Title_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.25f));
	//AddSceneObject(title);
	
	
}

void MainMenu::ActivateModeSelectionDisplay()
{
	if (selectedButtonIndex < activeButtons.size())
	{
		if (activeButtons[selectedButtonIndex] != nullptr)
		{
			if (selectedButton != nullptr)
			{
				selectedButton->SetSelectedDisplay(false);
			}
			selectedButton = activeButtons[selectedButtonIndex];
			if (!selectedButton->IsSelectedDisplay())
			{
				selectedButton->SetSelectedDisplay(true);
			}
		}
	}
}

void MainMenu::ActivateSinglePlayerDisplay()
{
	startButton = new StartButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.5f), numberOfPlayers);
	AddSceneObject(startButton);
}

void MainMenu::ActivateMultiplayerDisplay()
{
	startButton = new StartButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.5f), numberOfPlayers);
	AddSceneObject(startButton);
}

void MainMenu::ActivatePlayReadyDisplay()
{
}

void MainMenu::AddBackButton()
{
	ClearMenu();
	backButton = new BackButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.75f, Utils::WindowHeight * 0.25f));
	AddSceneObject(backButton);
}

void MainMenu::SetSelectedButton(sf::Vector2f _stickAxis)
{
	std::cout << "SetSelectedButton" << std::endl;
	if (_stickAxis.x > 0)
	{
		if (selectedButtonIndex - 1 > 0)
		{
			selectedButtonIndex -= 1;
		}
	}
	else if (_stickAxis.x < 0)
	{
		if (selectedButtonIndex + 1 < activeButtons.size())
		{
			selectedButtonIndex += 1;
		}
	}
	ActivateModeSelectionDisplay();
}

void MainMenu::CheckForControllerInput()
{
	float deadZone = 15.0f;

	float lStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);	//left sick
	float lStickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);

	if (lStickX > -deadZone && lStickX < deadZone)
	{
		lStickX = 0;
	}
	if (lStickY > -deadZone && lStickY < deadZone)
	{
		lStickY = 0;
	}

	if (lStickX != 0 || lStickY != 0)
	{
		SetSelectedButton(sf::Vector2f(lStickX, lStickY));
		stickCoolDown = true;
		stickTimer = stickCoolDownTime;
	}
	
}
