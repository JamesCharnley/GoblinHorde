#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "SFML_VectorMath.h"
#include "Collider.h"

Collider::Collider(GameObject* _gameObject)
{
	gameObject = _gameObject;
	collisionType = ECollisionType::Overlap;
}

bool Collider::CheckForCollision(GameObject* _other)
{
	int ignoreLength = ignoreObjects.size();
	for (int i = 0; i < ignoreLength; i++)
	{
		if (ignoreObjects[i] == _other)
		{
			return false;
		}
	}

	float dist = SFML_VectorMath::GetDistance(_other->GetPosition(), gameObject->GetPosition());
	float combinedRadius = _other->GetCollisionRadius() + gameObject->GetCollisionRadius();
	
	float intersectionSize = combinedRadius - dist;

	sf::Vector2f directionToOther = _other->GetPosition() - gameObject->GetPosition();
	directionToOther = SFML_VectorMath::Normalize(directionToOther);

	if (dist < combinedRadius)
	{
		if (collisionType == ECollisionType::Block && _other->GetCollider()->GetCollisionType() == ECollisionType::Block)
		{
			gameObject->SetPosition(gameObject->GetPosition() + -directionToOther * intersectionSize);
			
		}
		gameObject->OnCollision(_other);
		return true;
	}
	return false;
}

void Collider::SetCollisionType(ECollisionType _collisionType)
{
	collisionType = _collisionType;
}

ECollisionType Collider::GetCollisionType()
{
	return collisionType;
}

bool Collider::GetCheckForCollision()
{
	return isCheckForCollision;
}

void Collider::SetCheckForCollision(bool _checkForCollision)
{
	isCheckForCollision = _checkForCollision;
}

void Collider::AddIgnoreObject(GameObject* _object)
{
	ignoreObjects.push_back(_object);
}

float Collider::GetMass()
{
	return mass;
}

void Collider::SetMass(float _mass)
{
	mass = _mass;
}

