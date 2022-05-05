#pragma once
#include "SFML\Graphics.hpp"

class GameText
{
public:
	GameText(sf::RenderWindow* window, std::string filePath, sf::Vector2f position);

	void SetString(std::string newText);
	void Render(sf::RenderWindow* window);

private:
	sf::Font m_Font;
	sf::Text m_Text;

	sf::RenderWindow* m_window;
};

