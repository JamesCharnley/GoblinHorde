#include "MainMenu.h"
#include "Button.h"
#include "Start_Button.h"
#include "Quit_Button.h"
#include "Title_Button.h"
#include "SinglePlayerModeButton.h"
#include "MultiplayerModeButton.h"
#include "BackButton.h"
#include "Utility.h"
#include "GameObject_Text.h"
MainMenu::MainMenu(Game* _gameClass, sf::RenderWindow* _window)
{
	window = _window;
	game = _gameClass;
}

void MainMenu::Start()
{

	window->setFramerateLimit(60);

	displayMode = DisplayMode::DefaultMode;

	messageText = new GameObject_Text(window, this, "");
	AddSceneObject(messageText);

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
		else
		{
			messageText->SetText("Not Enough Controllers Detected.");
			canStartGame = false;
		}
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
	quitButton = new Quit_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.75f));
	AddSceneObject(quitButton);
	//Title_Button* title = new Title_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.25f));
	//AddSceneObject(title);
	singleplayerButton = new SinglePlayerModeButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.3f, Utils::WindowHeight * 0.5f));
	AddSceneObject(singleplayerButton);
	multiplayerButton = new MultiplayerModeButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.6f, Utils::WindowHeight * 0.5f));
	AddSceneObject(multiplayerButton);
	
}

void MainMenu::ActivateModeSelectionDisplay()
{
}

void MainMenu::ActivateSinglePlayerDisplay()
{
	startButton = new Start_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.5f), numberOfPlayers);
	AddSceneObject(startButton);
}

void MainMenu::ActivateMultiplayerDisplay()
{
	startButton = new Start_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.5f), numberOfPlayers);
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
