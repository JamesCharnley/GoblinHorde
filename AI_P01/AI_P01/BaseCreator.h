#pragma once
#include "SFML/Graphics.hpp"

class BaseCreator
{
public:

	BaseCreator(sf::RenderWindow* _window, class Scene* _scene);

protected:

	BaseCreator();
};

