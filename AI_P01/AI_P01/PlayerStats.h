/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : PlayerStats.h
Description : Tracks the stats of a player
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML\Graphics.hpp"

class PlayerStats
{
public:

	//Constructor takes in a vector 2f which is the position of the PlayerStats display
	PlayerStats(sf::Vector2f _position);

	//Renders each of the players stats: health, gold, ammo
	void Render(sf::RenderWindow* _window);

	//The update functions would be called in the Player.cpp whenever a stat value is changing e.g. gold increase
	void UpdateHealth(int _num);
	void UpdateGold(int _num);
	void UpdateAmmo(int _num);
	void UpdateEquippedWeapon(std::string _name, int _weaponLvl);

private:

	//Position of the playerStats
	sf::Vector2f statsPosition;

	// pointer to GameText for each of the players stat
	class GameText* playerHealth;
	class GameText* playerGold;
	class GameText* playerAmmo;
	class GameText* equippedWeapon;
};

