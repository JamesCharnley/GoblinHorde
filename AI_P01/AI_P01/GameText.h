/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GameText.h
Description : Text with it's own render function that does not inherit from GameObject
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML\Graphics.hpp"

class GameText
{
public:

	//Takes in a filepath string and vector 2F position. File path string used to create a font for the text
	GameText(std::string _filePath, sf::Vector2f _position);

	//Sets a string for the sf::Text
	void SetString(std::string newText);

	//Render the sf::Text to window
	void Render(sf::RenderWindow* window);

	void SetColor(sf::Color _color) { gameText.setFillColor(_color); };

private:
	sf::Font gameFont;
	sf::Text gameText;

	bool posChanged;
};

