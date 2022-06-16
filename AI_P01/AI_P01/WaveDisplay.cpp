#include "WaveDisplay.h"
#include "GameText.h"

WaveDisplay::WaveDisplay(sf::Vector2f _position) :
	displayPosition(_position)
{
	waveTimerVal = 0.0f;
	numOfEnemies = new GameText("Resources/Font/WarPriest.ttf", _position, sf::Color::White);
	waveNumber = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x, _position.y + 30), sf::Color::White);
	waveTimer = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x, _position.y + 60), sf::Color::White);
}

void WaveDisplay::Render(sf::RenderWindow* _window)
{
	numOfEnemies->Render(_window);
	waveNumber->Render(_window);

	if (waveTimerVal > 1)
		waveTimer->Render(_window);
}

void WaveDisplay::UpdateWaveTimer(float _num)
{
	waveTimerVal = _num;
	waveTimer->SetString("Enemies Spawn in: " + std::to_string((int)_num));
}

void WaveDisplay::UpdateEnemiesNum(int _num)
{
	numOfEnemies->SetString(std::to_string(_num) + " X");
}

void WaveDisplay::UpdateWaveNum(int _num)
{
	waveNumber->SetString("Wave: " + std::to_string(_num));
}
