#include <iostream>
#include "Scene.h"
#include "Collider.h"
#include "Sprite_Component.h"
#include "GameObject.h"

GameObject::GameObject()
{
	// initialize defaults
	objectShape = nullptr;
	window = nullptr;
	scene = nullptr;
	collider = nullptr;
	sprite = nullptr;
}

GameObject::~GameObject()
{
	
	if (collider != nullptr)
	{
		delete collider;
	}
	// delete sprite
	if (sprite != nullptr)
	{
		delete sprite;
	}
	std::cout << "GameObject Destructor" << std::endl;
}

void GameObject::Update(float _deltaTime)
{
	if (sprite != nullptr)
	{
		sprite->Update();
	}
}

void GameObject::Render()
{
	if (sprite != nullptr)
	{
		sprite->Render(window);
	}
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

void GameObject::AddSprite(const char* _filePath)
{
	// load texture file
	texture.loadFromFile(_filePath);
	// create sprite class and give it the loaded texture
	sprite = new Sprite_Component(this, texture);
}

void GameObject::SetColor(sf::Color _color)
{
	objectShape->setFillColor(_color);
}

void GameObject::AddCollider(ECollisionType _collisionType)
{
	collider = new Collider(this);
	collider->SetCollisionType(_collisionType);
}


