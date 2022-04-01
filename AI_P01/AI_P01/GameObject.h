#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{

public:

	virtual ~GameObject();

	// Called every frame from Game.cpp
	virtual void Update(float _deltaTime);

	//ABSTRACT: MUST OVERRIDE
	// Called every frame from Game.cpp. 
	virtual void Render() = 0;

	// Sets position of SFML shape
	// IMPORTANT: If GameObject is using a Rigidbody you most likely want to set the position using Rigidbody::SetPosition()
	void SetPosition(sf::Vector2f _position);

	// return SFML shapes current position
	sf::Vector2f GetPosition();

	// Sets rotation of SFML shape 
	// IMPORTANT: If GameObject is using a Rigidbody you most likely want to set the rotation using Rigidbody::SetRotation()
	void SetRotation(float _angle);

	// return SFML shapes current rotation
	float GetRotation();

	// returns SFML shape's scale
	sf::Vector2f GetScale();
	// Sets SFML shape's scale
	void SetScale(sf::Vector2f _scale);

	// called on start of collision if Rigidbody class is being used
	virtual void StartContact(GameObject* _other);
	// called on end of collision if Rigidbody class is being used
	virtual void EndContact(GameObject* _other);

	// Destroy this GameObject. NOTE: Will not be destroyed until all GameObjects in current scene have been updated
	virtual void Destroy();

	// get collision radius. all objects will be treated as circles with collision detection.
	float GetCollisionRadius();

	// set collision radius
	void SetCollisionRadius(float _radius);

	class Collider* GetCollider();

	virtual void OnCollision(GameObject* _other);

protected:

	// private constructor. This is an abstract class so the contructor should never be called from an outside class
	GameObject();

	// pointer to the sf::Shape this class will use. This must be given a reference to the sf::Shape being used in sub class
	sf::Shape* objectShape;

	// pointer to sf::RenderWindow
	sf::RenderWindow* window;

	// pointer to current Scene() class
	class Scene* scene = nullptr;

	float collisionRadius = 1;
	
	class Collider* collider = nullptr;
};

