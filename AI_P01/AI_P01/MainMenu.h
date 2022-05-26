#pragma once

#include "Scene.h"

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

	class Start_Button* startButton;
	class SinglePlayerModeButton* singleplayerButton;
	class Quit_Button* quitButton;
	class MultiplayerModeButton* multiplayerButton;
	class BackButton* backButton;

	class GameObject_Text* messageText;

	bool canStartGame = false;

	int numberOfPlayers = 1;

	void ClearMenu();
	void ActivateDefaultDisplay();
	void ActivateModeSelectionDisplay();
	void ActivateSinglePlayerDisplay();
	void ActivateMultiplayerDisplay();
	void ActivatePlayReadyDisplay();
	void AddBackButton();

};

