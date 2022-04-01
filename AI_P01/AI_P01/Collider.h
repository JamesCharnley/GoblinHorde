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
	void SetCheckForCollision(bool _checkForCollision);

	void AddIgnoreObject(GameObject* _object);

	float GetMass();
	void SetMass(float _mass);

protected:

	class GameObject* gameObject;

	ECollisionType collisionType;

	bool isCheckForCollision = true;

	std::vector<class GameObject*> ignoreObjects;

	float mass = 0;

};
