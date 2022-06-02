/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Button.h
Description : A clickable menu button
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectRectangle.h"

class Button : public GameObjectRectangle
{
public:
	Button(sf::Vector2f position, std::string text, sf::RenderWindow* _window, Scene* _scene);
	virtual void Render() override;
	virtual void Update(float _deltaTime) override;
	void SetSelectedDisplay(bool _active);
	bool IsSelectedDisplay() { return selectedDisplayMode; };

	virtual void PerformAction();

protected:

	Button();
	class GameText* buttonText;

	bool selectedDisplayMode = false;

	sf::Vector2f originSize;
};

