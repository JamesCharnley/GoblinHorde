#include "PlayerStats.h"
#include "GameText.h"

PlayerStats::PlayerStats(sf::Vector2f _position) :
	 statsPosition(_position)
{
	//Each of the GameText would be display in a column
	playerHealth = new GameText("Resources/Font/WarPriest.ttf", _position);
	playerAmmo = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x, _position.y + 30));
	playerGold = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x, _position.y + 60));
}

//Renders each of the stats text to the window
void PlayerStats::Render(sf::RenderWindow* _window)
{
	playerHealth->Render(_window);
	playerAmmo->Render(_window);
	playerGold->Render(_window);
}

//Updates the stats value
void PlayerStats::UpdateHealth(int _num)
{
	playerHealth->SetString("Health: " + std::to_string(_num));
}

void PlayerStats::UpdateGold(int _num)
{
	playerGold->SetString("Gold:   " + std::to_string(_num));
}

void PlayerStats::UpdateAmmo(int _num)
{
	playerAmmo->SetString("Ammo:   " + std::to_string(_num));
}
