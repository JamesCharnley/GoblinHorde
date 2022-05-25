#include "Level_One.h"
#include "MainMenu.h"
#include "GoblinHorde.h"

GoblinHorde::GoblinHorde()
{
	// set start scene name
	// Original one So close to finishing this
	//defaultStartScene = "Level_One";

	defaultStartScene = "Main_Menu";

	// initialize defaults
	currentScene = nullptr;
	window = nullptr;
	nextScene = "";
}

void GoblinHorde::LoadScene(std::string _sceneName)
{
	// call LoadScene() in base class to delete current scene
	Game::LoadScene(_sceneName);

	if (_sceneName == "Level_One")
	{
		currentScene = new Level_One(this, window, numberOfPlayers);
		currentScene->Start();
	}

	
	if (_sceneName == "Main_Menu")
	{
		currentScene = new MainMenu(this, window);
		currentScene->Start();
	}

	
}
