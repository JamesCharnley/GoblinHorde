#pragma once
#include "GameObject.h"
class GameObject_Rectangle :
    public GameObject
{

public:

    // custom constructor for a rectangle shape. Takes ref to sf::RenderWindow and ref to Scene() class
    GameObject_Rectangle(sf::RenderWindow* _window, class Scene* _scene);

    // Render() override. called every frame from Scene() class
    virtual void Render() override;

    // return size of SFML shape
	sf::Vector2f GetSize();
    // set size of SFML shape
	void SetSize(sf::Vector2f _size);


protected:

    // private constructor: Class cannot work without the correct parameters passed to the custom constructor
    GameObject_Rectangle();

    // Must be assigned to 'objectShape' variable in constructor
    sf::RectangleShape rectangle;
};

