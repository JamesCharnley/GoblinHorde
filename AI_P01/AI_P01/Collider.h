#pragma once
#include <iostream>

enum class ECollisionType
{
	Block,
	Overlap
};

class Collider
{
public:

	Collider(class GameObject* _gameObject);

	virtual bool CheckForCollision(class GameObject* _other);

	void SetCollisionType(ECollisionType _collisionType);
	ECollisionType GetCollisionType();

	bool GetCheckForCollision();
	bool CheckForCollisionCircleToCircle(class GameObject_Circle* _thisCircle, class GameObject_Circle* _otherCircle);
	bool CheckForCollisionCircleToRectangle(class GameObject_Circle* _circle, class GameObject_Rectangle* _rectangle);
	void SetCheckForCollision(bool _checkForCollision);

	void AddIgnoreObject(GameObject* _object);

	float GetMass();
	void SetMass(float _mass);

	bool isStatic = false;

protected:

	class GameObject* gameObject;

	ECollisionType collisionType;

	bool isCheckForCollision = true;

	std::vector<class GameObject*> ignoreObjects;

	float mass = 0;

};
