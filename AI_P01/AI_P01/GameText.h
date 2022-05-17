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

private:
	sf::Font gameFont;
	sf::Text gameText;
};

