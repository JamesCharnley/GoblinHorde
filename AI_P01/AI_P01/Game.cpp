#include "Scene.h"
#include "Utility.h"
#include "Game.h"

Game::Game()
{
	// initialize defaults
	currentScene = nullptr;
	window = nullptr;
	nextScene = "";
}

Game::~Game()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
	if (window != nullptr)
	{
		delete window;
	}
}

void Game::Start()
{
	//Create RenderWindow
	CreateGameWindow();

	//Open default scene, DefaultStartScene must be set to the name of an existing scene
	ChangeScene(defaultStartScene);

	sf::Clock deltaClock;
	float deltaTime = 0;

	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if (currentScene != nullptr)
		{
			//Call Update() in current scene class
			deltaTime = deltaClock.restart().asSeconds();
			currentScene->Update(deltaTime);
		}
		if (newScene)
		{
			//Load a new scene class if NewScene is true
			LoadScene(nextScene);
		}
		window->setTitle(sf::String("Goblin horde " + std::to_string((int)(1.0f / deltaTime)) + " FPS / " + std::to_string(deltaTime) + "ms"));
	}
}

void Game::ChangeScene(std::string _name)
{
	//Store the name of the scene that should be opened so LoadScene() knows what class to instantiate
	nextScene = _name;
	//Set bool to trigger LoadScene() at the end of the current while loop
	newScene = true;
}

void Game::Exit()
{
	window->close();
}

void Game::CreateGameWindow()
{
	//Store RenderWindow in GameWindow ptr
	window = new sf::RenderWindow(sf::VideoMode(Utils::WINDOW_X, Utils::WINDOW_Y), gameName);
}

void Game::LoadScene(std::string _sceneName)
{
	//Delete current scene class and set ptr to nullptr
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
	//Reset bool
	newScene = false;
}
