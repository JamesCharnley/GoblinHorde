#include "SFMLVectorMath.h"
#include "Player.h"
#include "WeaponUpgrade.h"

WeaponUpgrade::WeaponUpgrade(sf::RenderWindow* _window, Scene* _scene)
{
    window = _window;
    scene = _scene;

    actionText = "Upgrade Weapon";
    AddSprite("Resources/Textures/Upgrade.png");
    SetColor(sf::Color::Transparent);
    SetRadius(30);
    AddCollider(ECollisionType::Overlap);
    SetCollisionRadius(GetRadius());
}

bool WeaponUpgrade::CostsGold()
{
    return true;
}

int WeaponUpgrade::GetPrice(Player* _player)
{
    return _player->GetWeaponLevel() * 50;
}

bool WeaponUpgrade::InRange(Player* _player)
{
    //return false if player already has this weapon so text isn't shown
    if (SFMLVectorMath::GetDistance(_player->GetPosition(), GetPosition()) <= GetCollisionRadius() + _player->GetCollisionRadius())
    {
        return true;
    }
    return false;
}

bool WeaponUpgrade::AutoInteract()
{
    return false;
}

bool WeaponUpgrade::HasActionText(class Player* _player)
{
    return true;
}

std::string WeaponUpgrade::GetActionText()
{
    return actionText;
}

bool WeaponUpgrade::CanInteract(Player* _player)
{
    if (_player->GetGold() >= GetPrice(_player))
    {
        return true;
    }
    return false;
}

void WeaponUpgrade::Interact(Player* _player)
{
    if (CanInteract(_player))
    {
        _player->RemoveGold(GetPrice(_player));
        _player->UpgradeWeapon();
    }
}
