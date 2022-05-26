/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : WaveDisplay.h
Description : UI elements that display current wave information
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML\Graphics.hpp"

class WaveDisplay
{
public:

	//Constructor takes in a vector 2f which is the position of the Wave display
	WaveDisplay(sf::Vector2f _position);

	//Renders each of the wave data: wave timer, number of enemies, wave number
	void Render(sf::RenderWindow* _window);


	//The update functions would be called in the WaveManager.cpp whenever a value is changing e.g. wave number increase
	void UpdateWaveTimer(float _num);
	void UpdateEnemiesNum(int _num);
	void UpdateWaveNum(int _num);

private:

	//Use to render the wave timer if the waveTimerVal > 0
	float waveTimerVal;

	//Position of the Wave Display
	sf::Vector2f displayPosition;

	// pointer to GameText for each of the wave data
	class GameText* waveTimer;
	class GameText* numOfEnemies;
	class GameText* waveNumber;
};

