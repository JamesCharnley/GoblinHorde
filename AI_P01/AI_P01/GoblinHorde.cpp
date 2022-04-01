#include "Level_One.h"
#include "GoblinHorde.h"

GoblinHorde::GoblinHorde()
{
	// set start scene name
	defaultStartScene = "Level_One";

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
		currentScene = new Level_One(this, window);
		currentScene->Start();
	}
}
