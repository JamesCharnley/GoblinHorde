#include "GameText.h"

GameText::GameText(std::string filePath, sf::Vector2f position)
{
	gameFont.loadFromFile(filePath);
	gameText.setFont(gameFont);
	gameText.setFillColor(sf::Color::White);
	gameText.setPosition(position);
}

void GameText::SetString(std::string newText)
{
	gameText.setString(newText);
	gameText.setOrigin(sf::Vector2f(gameText.getLocalBounds().width / 2, (gameText.getLocalBounds().height + gameText.getCharacterSize() / 2) / 2));
}


void GameText::Render(sf::RenderWindow* window)
{
	window->draw(gameText);
}
