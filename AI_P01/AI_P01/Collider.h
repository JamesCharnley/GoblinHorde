/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Collider.h
Description : Collision detection implementation
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

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
	bool CheckForCollisionCircleToCircle(class GameObjectCircle* _thisCircle, class GameObjectCircle* _otherCircle);
	bool CheckForCollisionCircleToRectangle(class GameObjectCircle* _circle, class GameObjectRectangle* _rectangle);
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
