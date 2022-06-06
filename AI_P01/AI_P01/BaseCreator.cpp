#include "GameObjectRectangle.h"
#include "Utility.h"
#include "Scene.h"
#include "Collider.h"
#include "BaseCreator.h"

BaseCreator::BaseCreator(sf::RenderWindow* _window, Scene* _scene)
{
	GameObjectRectangle* baseGround = new GameObjectRectangle(_window, _scene);
	baseGround->AddSprite("Resources/Textures/BaseGroundPH.png");
	baseGround->SetColor(sf::Color::Transparent);
	baseGround->SetSize(sf::Vector2f(200.0f, 200.0f));
	baseGround->SetPosition(sf::Vector2f((float)Utils::WINDOW_X / 2.0f, (float)Utils::WINDOW_Y / 2.0f));

	_scene->AddSceneObject(baseGround);

	GameObjectRectangle* baseWall1 = new GameObjectRectangle(_window, _scene);
	baseWall1->AddSprite("Resources/Textures/BaseWallPH.png");
	baseWall1->SetColor(sf::Color::Transparent);
	baseWall1->SetSize(sf::Vector2f(25.0f, 75.0f));
	baseWall1->SetPosition(sf::Vector2f(baseGround->GetPosition().x - (baseGround->GetSize().x / 2), baseGround->GetPosition().y - ((baseGround->GetSize().y / 2) - (baseWall1->GetSize().y / 2))));
	baseWall1->AddCollider(ECollisionType::Block);
	baseWall1->GetCollider()->isStatic = true;
	_scene->AddSceneObject(baseWall1);
}

BaseCreator::BaseCreator()
{
}
