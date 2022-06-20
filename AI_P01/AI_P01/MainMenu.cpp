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
#include "LobbySlot.h"

MainMenu::MainMenu(Game* _gameClass, sf::RenderWindow* _window)
{
	if (Utils::IS_DEBUG)
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
	MenuTitle->SetPosition(sf::Vector2f(Utils::WINDOW_X / 2 - 375.0f, 100.0f));
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

	if (sf::Joystick::isButtonPressed(0, 0))
	{
		actionLock = true;
	}
	else
	{
		actionLock = false;
	}
}


void MainMenu::ButtonAction(DisplayMode _mode)
{
	if (actionLock)
	{
		return;
	}
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
		ActivateMultiplayerDisplay();
		break;
	case DisplayMode::PlayReady:
		ActivatePlayReadyDisplay();
		break;
	default:
		break;
	}
}

void MainMenu::AddPlayer()
{
	numberOfPlayers++;
	std::cout << "Players: " << numberOfPlayers << std::endl;
}

void MainMenu::RemovePlayer()
{
	numberOfPlayers--;
	std::cout << "Players: " << numberOfPlayers << std::endl;
}

void MainMenu::StartGame()
{
	if (numberOfPlayers > 0)
	{
		SetNumberOfPlayers(numberOfPlayers);
		ChangeScene("Level_One");
	}
}

void MainMenu::ClearMenu()
{
	selectedButton = nullptr;
	activeButtons.clear();

	numberOfPlayers = 0;

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
	DestroySceneObject(lobbySlot1);
	lobbySlot1 = nullptr;
	DestroySceneObject(lobbySlot2);
	lobbySlot2 = nullptr;
	DestroySceneObject(lobbySlot3);
	lobbySlot3 = nullptr;
	DestroySceneObject(lobbySlot4);
	lobbySlot4 = nullptr;
	
}

void MainMenu::ActivateDefaultDisplay()
{
	ClearMenu();

	//singleplayerButton = new SinglePlayerModeButton(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.4f));
	//AddSceneObject(singleplayerButton);
	//activeButtons.push_back(singleplayerButton);

	multiplayerButton = new MultiplayerModeButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.5f));
	AddSceneObject(multiplayerButton);
	activeButtons.push_back(multiplayerButton);

	quitButton = new QuitButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.6f));
	AddSceneObject(quitButton);
	activeButtons.push_back(quitButton);

	selectedButtonIndex = 0;

	ActivateModeSelectionDisplay();
	//Title_Button* title = new Title_Button(window, this, sf::Vector2f(Utils::WindowWidth * 0.5f, Utils::WindowHeight * 0.25f));
	//AddSceneObject(title);
	
	
}



void MainMenu::ActivateSinglePlayerDisplay()
{
	startButton = new StartButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.5f));
	AddSceneObject(startButton);
	activeButtons.push_back(startButton);
}

void MainMenu::ActivateMultiplayerDisplay()
{
	ClearMenu();

	backButton = new BackButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.4f));
	AddSceneObject(backButton);
	activeButtons.push_back(backButton);

	startButton = new StartButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.5f));
	AddSceneObject(startButton);
	activeButtons.push_back(startButton);

	lobbySlot1 = new LobbySlot(window, this, 0);
	lobbySlot1->SetPosition(sf::Vector2f((Utils::WINDOW_X / 4) * 1 - (Utils::WINDOW_X / 4) * 0.5f, Utils::WINDOW_Y * 0.75f));
	AddSceneObject(lobbySlot1);

	lobbySlot2 = new LobbySlot(window, this, 1);
	lobbySlot2->SetPosition(sf::Vector2f((Utils::WINDOW_X / 4) * 2 - (Utils::WINDOW_X / 4) * 0.5f, Utils::WINDOW_Y * 0.75f));
	AddSceneObject(lobbySlot2);

	lobbySlot3 = new LobbySlot(window, this, 2);
	lobbySlot3->SetPosition(sf::Vector2f((Utils::WINDOW_X / 4) * 3 - (Utils::WINDOW_X / 4) * 0.5f, Utils::WINDOW_Y * 0.75f));
	if (Utils::IS_DEBUG)
	{
		lobbySlot3->AutoActivate();
	}
	AddSceneObject(lobbySlot3);

	lobbySlot4 = new LobbySlot(window, this, 3);
	lobbySlot4->SetPosition(sf::Vector2f((Utils::WINDOW_X / 4) * 4 - (Utils::WINDOW_X / 4) * 0.5f, Utils::WINDOW_Y * 0.75f));
	if (Utils::IS_DEBUG)
	{
		lobbySlot4->AutoActivate();
	}
	AddSceneObject(lobbySlot4);
}

void MainMenu::ActivatePlayReadyDisplay()
{
}

void MainMenu::AddBackButton()
{
	ClearMenu();
	backButton = new BackButton(window, this, sf::Vector2f(Utils::WINDOW_X * 0.5f, Utils::WINDOW_Y * 0.4f));
	AddSceneObject(backButton);
	activeButtons.push_back(backButton);
}


void MainMenu::ActivateModeSelectionDisplay()
{
	//std::cout << "ActivateModeSelectionDisplay " << selectedButtonIndex << std::endl;
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
void MainMenu::SetSelectedButton(sf::Vector2f _stickAxis)
{
	//std::cout << "SetSelectedButton" << std::endl;
	if (_stickAxis.y < 0)
	{
		if (selectedButtonIndex - 1 >= 0)
		{
			selectedButtonIndex -= 1;
		}
	}
	else if (_stickAxis.y > 0)
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

	float dPadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
	if (dPadY != 0.0f)
	{
		SetSelectedButton(sf::Vector2f(0, -dPadY));
		//stickCoolDown = true;
		//stickTimer = stickCoolDownTime;
	}
	
}
