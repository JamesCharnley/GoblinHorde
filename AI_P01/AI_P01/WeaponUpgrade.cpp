#include "SFML_VectorMath.h"
#include "Player.h"
#include "WeaponUpgrade.h"

WeaponUpgrade::WeaponUpgrade(sf::RenderWindow* _window, Scene* _scene)
{
    window = _window;
    scene = _scene;

    actionText = "Upgrade Weapon";

    SetRadius(30);
    AddCollider(ECollisionType::Overlap);
    SetCollisionRadius(GetRadius());
}

bool WeaponUpgrade::InRange(Player* _player)
{
    if (SFML_VectorMath::GetDistance(_player->GetPosition(), GetPosition()) <= GetCollisionRadius() + _player->GetCollisionRadius())
    {
        return true;
    }
    return false;
}

bool WeaponUpgrade::AutoInteract()
{
    return false;
}

bool WeaponUpgrade::HasActionText()
{
    return true;
}

std::string WeaponUpgrade::GetActionText()
{
    return actionText;
}
