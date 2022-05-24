#pragma once
#include "GameObject_Rectangle.h"

class Button : public GameObject_Rectangle
{
public:
	Button(sf::Vector2f position, std::string text, sf::RenderWindow* _window, Scene* _scene);
	virtual void Render() override;

private:
	class GameText* buttonText;
};

