#include "GoblinHordeUI.h"
#include "GameText.h"
#include "Scene.h"
#include "Player.h"
#include "PlayerStats.h"
#include "WaveDisplay.h"
#include "Utility.h"

GoblinHordeUI::GoblinHordeUI()
{	
	playerStats[0] = new PlayerStats(sf::Vector2f(100, 15), sf::Color::Red);
	playerStats[1] = new PlayerStats(sf::Vector2f(Utils::WINDOW_X - 210, 15), sf::Color::Blue);
	playerStats[2] = new PlayerStats(sf::Vector2f(100, Utils::WINDOW_Y - 150), sf::Color::Yellow);
	playerStats[3] = new PlayerStats(sf::Vector2f(Utils::WINDOW_X - 210, Utils::WINDOW_Y - 150), sf::Color::Cyan);
	waveDisplay = new WaveDisplay(sf::Vector2f(800, 15));
}

GoblinHordeUI::~GoblinHordeUI()
{
	for (int i = 0; i < sizeof(playerStats) / sizeof(playerStats[0]); i++)
	{
		if (playerStats[i] != nullptr)
		{
			delete playerStats[i];
			playerStats[i] = nullptr;
		}
	}
	delete waveDisplay;
	waveDisplay = nullptr;
}

//Renders all the game texts
void GoblinHordeUI::Render(sf::RenderWindow* _window)
{
	for (int i = 0; i < sizeof(playerStats) / sizeof(playerStats[0]); i++)
	{
		if (playerStats[i] != nullptr)
		{
			playerStats[i]->Render(_window);
		}
	}
	waveDisplay->Render(_window);
}

PlayerStats* GoblinHordeUI::GetPlayerStats(int _playerNum)
{
	if (_playerNum > 4 || _playerNum < 0)
	{
		throw "Invalid player number, array out of bounds";
	}
	return playerStats[_playerNum - 1];
}

//Wave manage class will be able to display the breakTimer, current num of enemies and current wave onto the UI
WaveDisplay* GoblinHordeUI::GetWaveDisplay()
{
	return waveDisplay;
}
