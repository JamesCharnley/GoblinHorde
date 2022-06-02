#pragma once
#include "GameObject_Rectangle.h"

class Button : public GameObject_Rectangle
{
public:
	Button(sf::Vector2f position, std::string text, sf::RenderWindow* _window, Scene* _scene);
	virtual void Render() override;

	void SetSelectedDisplay(bool _active);
	bool IsSelectedDisplay() { return selectedDisplayMode; };

protected:

	Button();
	class GameText* buttonText;

	bool selectedDisplayMode = false;

	sf::Vector2f originSize;
};

