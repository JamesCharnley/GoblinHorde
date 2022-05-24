#include "MainMenu.h"
#include "Button.h"
#include "Start_Button.h"
#include "Quit_Button.h"
#include "Title_Button.h"

MainMenu::MainMenu(Game* _gameClass, sf::RenderWindow* _window)
{
	window = _window;
	game = _gameClass;
}

void MainMenu::Start()
{

	window->setFramerateLimit(60);

	//This is where all the buttons are going to appear for the menu
	Start_Button* start = new Start_Button(window, this, sf::Vector2f(850, 500));
	AddSceneObject(start);

	Quit_Button* quit = new Quit_Button(window, this, sf::Vector2f(850, 700));
	AddSceneObject(quit);

	Title_Button* title = new Title_Button(window, this, sf::Vector2f(800, 300));
	AddSceneObject(title);

	Scene::Start();
}
