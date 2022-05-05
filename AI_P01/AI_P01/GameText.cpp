#include "GameText.h"

GameText::GameText(sf::RenderWindow* window, std::string filePath, sf::Vector2f position)
{
	m_window = window;

	m_Font.loadFromFile(filePath);
	m_Text.setFont(m_Font);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setPosition(position);
}

void GameText::SetString(std::string newText)
{
	m_Text.setString(newText);
}


void GameText::Render(sf::RenderWindow* window)
{
	window->draw(m_Text);
}
