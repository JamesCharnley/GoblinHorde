#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameObjectCircle.h"
#include "GameObjectRectangle.h"
#include "SFMLVectorMath.h"
#include "Collider.h"

Collider::Collider(GameObject* _gameObject)
{
	gameObject = _gameObject;
	collisionType = ECollisionType::Overlap;
}

bool Collider::CheckForCollision(GameObject* _other)
{
	if (_other == nullptr) return false;
	int ignoreLength = ignoreObjects.size();
	for (int i = 0; i < ignoreLength; i++)
	{
		if (ignoreObjects[i] == _other)
		{
			return false;
		}
	}

	GameObjectCircle* thisCircle = dynamic_cast<GameObjectCircle*>(gameObject);
	GameObjectCircle* otherCircle = dynamic_cast<GameObjectCircle*>(_other);

	if (thisCircle && otherCircle)
	{
		return CheckForCollisionCircleToCircle(thisCircle, otherCircle);
	}

	GameObjectRectangle* thisRectangle = dynamic_cast<GameObjectRectangle*>(gameObject);
	GameObjectRectangle* otherRectangle = dynamic_cast<GameObjectRectangle*>(_other);

	if (thisRectangle && otherCircle)
	{
		return CheckForCollisionCircleToRectangle(otherCircle, thisRectangle);
	}

	if (thisCircle && otherRectangle)
	{
		return CheckForCollisionCircleToRectangle(thisCircle, otherRectangle);
	}

	float dist = SFMLVectorMath::GetDistance(_other->GetPosition(), gameObject->GetPosition());
	float combinedRadius = _other->GetCollisionRadius() + gameObject->GetCollisionRadius();
	
	float intersectionSize = combinedRadius - dist;

	sf::Vector2f directionToOther = _other->GetPosition() - gameObject->GetPosition();
	directionToOther = SFMLVectorMath::Clamp(directionToOther);

	if (dist < combinedRadius)
	{
		if (collisionType == ECollisionType::Block && _other->GetCollider()->GetCollisionType() == ECollisionType::Block)
		{
			if (!isStatic)
			{
				gameObject->SetPosition(gameObject->GetPosition() + -directionToOther * intersectionSize);
			}
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

bool Collider::CheckForCollisionCircleToCircle(GameObjectCircle* _thisCircle, GameObjectCircle* _otherCircle)
{
	if (_thisCircle == nullptr || _otherCircle == nullptr) return false;
	float dist = SFMLVectorMath::GetDistance(_otherCircle->GetPosition(), _thisCircle->GetPosition());
	float combinedRadius = _otherCircle->GetCollisionRadius() + _thisCircle->GetCollisionRadius();

	float intersectionSize = combinedRadius - dist;

	sf::Vector2f directionToOther = _otherCircle->GetPosition() - _thisCircle->GetPosition();
	directionToOther = SFMLVectorMath::Clamp(directionToOther);

	if (dist < combinedRadius)
	{
		if (collisionType == ECollisionType::Block && _otherCircle->GetCollider()->GetCollisionType() == ECollisionType::Block)
		{
			if (!isStatic)
			{
				_thisCircle->SetPosition(gameObject->GetPosition() + -directionToOther * intersectionSize);
			}
		}
		_thisCircle->OnCollision(_otherCircle);
		return true;
	}
	return false;
}

bool Collider::CheckForCollisionCircleToRectangle(GameObjectCircle* _circle, GameObjectRectangle* _rectangle)
{
	sf::Vector2f circleDistance;
	circleDistance.x = abs(_circle->GetPosition().x - _rectangle->GetPosition().x);
	circleDistance.y = abs(_circle->GetPosition().y - _rectangle->GetPosition().y);

	if (circleDistance.x > (_rectangle->GetSize().x / 2 + _circle->GetRadius())) { return false; }
	if (circleDistance.y > (_rectangle->GetSize().y / 2 + _circle->GetRadius())) { return false; }

	if (circleDistance.x <= (_rectangle->GetSize().x / 2)) { return true; }
	if (circleDistance.y <= (_rectangle->GetSize().y / 2)) { return true; }

	float cornerDistance_sq = ((circleDistance.x - _rectangle->GetSize().x / 2) * (circleDistance.x - _rectangle->GetSize().x / 2)) +
		((circleDistance.y - _rectangle->GetSize().y / 2) * (circleDistance.y - _rectangle->GetSize().y / 2));

	GameObject* _other = nullptr;
	if (_circle != gameObject)
	{
		_other = _circle;
	}
	else
	{
		_other = _rectangle;
	}

	if (cornerDistance_sq <= (_circle->GetRadius() * _circle->GetRadius()))
	{
		sf::Vector2f directionToOther = _other->GetPosition() - gameObject->GetPosition();
		directionToOther = SFMLVectorMath::Clamp(directionToOther);

		float intersectionSize = cornerDistance_sq - (_circle->GetRadius() * _circle->GetRadius());

		if (collisionType == ECollisionType::Block && _other->GetCollider()->GetCollisionType() == ECollisionType::Block)
		{
			if (!isStatic)
			{
				gameObject->SetPosition(gameObject->GetPosition() + -directionToOther * intersectionSize);
			}
			
		}
		std::cout << "Colliding" << std::endl;
		return true;
	}
	
	return false;
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

