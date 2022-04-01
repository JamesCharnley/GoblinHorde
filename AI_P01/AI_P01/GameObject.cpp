#include <iostream>
#include "Scene.h"
#include "Collider.h"
#include "GameObject.h"

GameObject::GameObject()
{
	// initialize defaults
	objectShape = nullptr;
	window = nullptr;
	collider = new Collider(this);
}

GameObject::~GameObject()
{
	if (collider != nullptr)
	{
		delete collider;
	}
}

void GameObject::Update(float _deltaTime)
{

}

void GameObject::SetPosition(sf::Vector2f _position)
{
	objectShape->setPosition(_position);
}

sf::Vector2f GameObject::GetPosition()
{
	return objectShape->getPosition();
}

void GameObject::SetRotation(float _angle)
{
	objectShape->setRotation(_angle);
}

float GameObject::GetRotation()
{
	return objectShape->getRotation();
}

sf::Vector2f GameObject::GetScale()
{
	return objectShape->getScale();
}

void GameObject::SetScale(sf::Vector2f _scale)
{
	objectShape->setScale(_scale);;
}

void GameObject::StartContact(GameObject* _other)
{
	
}

void GameObject::EndContact(GameObject* _other)
{
	
}

void GameObject::Destroy()
{
	// call Scene class to queue this class to be deleted at end of current loop
	scene->DestroySceneObject(this);
}

float GameObject::GetCollisionRadius()
{
	return collisionRadius;
}

void GameObject::SetCollisionRadius(float _radius)
{
	collisionRadius = _radius;
}

Collider* GameObject::GetCollider()
{
	return collider;
}

void GameObject::OnCollision(GameObject* _other)
{
}

