#include "Player.h"
#include "WeaponPurchase.h"

WeaponPurchase::WeaponPurchase(sf::RenderWindow* _window, Scene* _scene, EWeapon _weapon)
{
    window = _window;
    scene = _scene;
    weapon = new Weapon(_window, _scene, nullptr, _weapon);
    SetRadius(30);
    AddCollider(ECollisionType::Overlap);
    SetCollisionRadius(GetRadius());
}

bool WeaponPurchase::CostsGold()
{
    return true;
}

int WeaponPurchase::GetPrice(Player* _player)
{
    return 100;
}

bool WeaponPurchase::HasActionText()
{
    return true;
}

std::string WeaponPurchase::GetActionText()
{
    return "Purchase Weapon";
}

bool WeaponPurchase::AutoInteract()
{
    return false;
}

bool WeaponPurchase::CanInteract(Player* _player)
{
    if (_player->GetGold() >= GetPrice(_player))
    {
        return true;
    }
    return false;
}

void WeaponPurchase::Interact(Player* _player)
{
    if (CanInteract(_player))
    {
        _player->RemoveGold(GetPrice(_player));
        _player->AddWeapon(weapon);
    }
}
