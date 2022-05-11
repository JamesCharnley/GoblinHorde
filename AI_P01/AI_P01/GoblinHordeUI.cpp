#include "GoblinHordeUI.h"
#include "GameText.h"
#include "Scene.h"
#include "Player.h"

GoblinHordeUI::GoblinHordeUI(sf::RenderWindow* window)
{
	m_WaveText = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(100.0f, 40.0f));
	m_WaveNum = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(200.0f, 40.0f));
	m_EnemyText = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(100.0f, 0.0f));
	m_EnemyNum = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(500.0f, 0.0f));

	m_player1Text = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(100.0f, 90.0f));
	m_player1Stats = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(300.0f, 90.0f));
	m_player2Text = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(100.0f, 200.0f));
	m_player2Stats = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(300.0f, 200.0f));
	m_waveTimer = new GameText(window, "Resources/Font/WarPriest.ttf", sf::Vector2f(500.0f, 500.0f));

	m_WaveText->SetString("Wave: ");
	m_EnemyText->SetString("Number of Enemies Left: ");

	m_player1Text->SetString("P1 Gold: ");
	m_player2Text->SetString("P2 Gold: ");
}

GoblinHordeUI::~GoblinHordeUI()
{
	delete m_WaveText;
	delete m_WaveNum;
	delete m_EnemyText;
	delete m_EnemyNum;
	delete m_player1Text;
	delete m_player1Stats;
	delete m_player2Text;
	delete m_player2Stats;
}


//updates the text based off the current level or wave of the scene
void GoblinHordeUI::setCurrentWave(int currWave)
{
	//m_WaveNum->SetString(std::to_string(currWave));
	m_WaveNum->SetString(std::to_string(currWave));
}

//Updates the text based off the amount of enemies on the scene
void GoblinHordeUI::setNumberOfEnemies(int numEnemies)
{
	m_EnemyNum->SetString(std::to_string(numEnemies));
}

void GoblinHordeUI::setWaveTimer(int timer)
{
	m_waveTimer->SetString(std::to_string(timer));
}

void GoblinHordeUI::setPlayer1Stats(int gold)
{
	m_player1Stats->SetString(std::to_string(gold));
}

void GoblinHordeUI::setPlayer2Stats(int gold)
{
	m_player2Stats->SetString(std::to_string(gold));
}

//Renders all the game texts
void GoblinHordeUI::Render(sf::RenderWindow* window)
{
	m_WaveText->Render(window);
	m_WaveNum->Render(window);
	m_EnemyText->Render(window);
	m_EnemyNum->Render(window);

	m_player1Text->Render(window);
	m_player1Stats->Render(window);
	m_player2Text->Render(window);
	m_player2Stats->Render(window);

	m_waveTimer->Render(window);
}
