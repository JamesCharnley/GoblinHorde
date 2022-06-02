/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : MainMenu.h
Description : The main menu of the game
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

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

	std::vector<class Button*> activeButtons;
	class Button* selectedButton = nullptr;
	int selectedButtonIndex = 0;
	bool stickCoolDown = false;
	float stickCoolDownTime = 0.8f;
	float stickTimer = 0;

	void SetSelectedButton(sf::Vector2f _stickAxis);

	void CheckForControllerInput();

	#ifdef _DEBUG
		bool isDebug = true;
	#else
		bool isDebug = false;
	#endif
};

