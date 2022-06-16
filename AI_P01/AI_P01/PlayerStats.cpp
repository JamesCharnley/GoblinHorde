#include "PlayerStats.h"
#include "GameText.h"

PlayerStats::PlayerStats(sf::Vector2f _position, sf::Color _color) :
	 statsPosition(_position)
{
	//Each of the GameText would be display in a column
	playerNum = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x - 20, _position.y), _color);
	playerHealth = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x, _position.y + 30), _color);
	playerGold = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x - 25, _position.y + 60), _color);
	equippedWeapon = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x + 50, _position.y + 90), _color);
	playerAmmo = new GameText("Resources/Font/WarPriest.ttf", sf::Vector2f(_position.x - 15, _position.y + 120), _color);
}

//Renders each of the stats text to the window
void PlayerStats::Render(sf::RenderWindow* _window)
{
	playerNum->Render(_window);
	playerHealth->Render(_window);
	playerAmmo->Render(_window);
	playerGold->Render(_window);
	equippedWeapon->Render(_window);
}

void PlayerStats::setPlayerNumber(int _num)
{
	playerNum->SetString("Player " + std::to_string(_num));
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

void PlayerStats::UpdateEquippedWeapon(std::string _name, int _weaponLvl)
{
	equippedWeapon->SetString("Weapon: " + _name + " LV" + std::to_string(_weaponLvl));
}
