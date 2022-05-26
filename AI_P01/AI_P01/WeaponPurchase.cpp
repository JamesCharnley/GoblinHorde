#include "Player.h"
#include "WeaponPurchase.h"
#include "Weapon.h"
WeaponPurchase::WeaponPurchase(sf::RenderWindow* _window, Scene* _scene, EWeapon _weapon)
{
    
    window = _window;
    scene = _scene;
    weapon = new Weapon(_window, _scene, nullptr, _weapon);
    SetRadius(30);
    AddCollider(ECollisionType::Overlap);
    SetCollisionRadius(GetRadius());

    for (const std::pair<EWeapon, int> entry : prices)
    {
        if (entry.first == weapon->GetWeaponData().weapon)
        {
            price = entry.second;
        }
    }
}

bool WeaponPurchase::CostsGold()
{
    return true;
}

int WeaponPurchase::GetPrice(Player* _player)
{
    return price;
}

bool WeaponPurchase::HasActionText(class Player* _player)
{
    return !_player->HasWeapon(weapon->GetWeaponData().weapon);
}

std::string WeaponPurchase::GetActionText()
{
    return "Purchase " + weapon->name;
}

bool WeaponPurchase::AutoInteract()
{
    return false;
}

bool WeaponPurchase::CanInteract(Player* _player)
{
    if (_player->GetGold() >= GetPrice(_player) && !_player->HasWeapon(weapon->GetWeaponData().weapon))
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
