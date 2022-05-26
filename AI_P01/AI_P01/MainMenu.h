#pragma once

#include "Scene.h"
#include <SFML/Audio.hpp>

enum class DisplayMode
{
	DefaultMode,
	ModeSelection,
	SinglePlayer,
	MultiPlayer,
	PlayReady
};

class MainMenu :
	public Scene
{
public:
	MainMenu(class Game* _gameClass, sf::RenderWindow* window);

	virtual void Start() override;

	virtual void Update(float _dtime) override;

	void ButtonAction(DisplayMode _mode);

private:

	DisplayMode displayMode;

	class StartButton* startButton;
	class SinglePlayerModeButton* singleplayerButton;
	class QuitButton* quitButton;
	class MultiplayerModeButton* multiplayerButton;
	class BackButton* backButton;

	class GameObjectText* messageText;
	class GameObjectRectangle* MenuTitle;
	class GameObjectRectangle* MenuBackground;
	sf::Music music;

	bool canStartGame = false;

	int numberOfPlayers = 1;

	void ClearMenu();
	void ActivateDefaultDisplay();
	void ActivateModeSelectionDisplay();
	void ActivateSinglePlayerDisplay();
	void ActivateMultiplayerDisplay();
	void ActivatePlayReadyDisplay();
	void AddBackButton();

	#ifdef _DEBUG
		bool isDebug = true;
	#else
		bool isDebug = false;
	#endif
};

