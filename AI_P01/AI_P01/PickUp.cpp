#include "Player.h"
#include "SFMLVectorMath.h"
#include "PickUp.h"

PickUp::PickUp(sf::RenderWindow* _window, Scene* _scene)
{
    window = _window;
    scene = _scene;  
}

bool PickUp::CostsGold()
{
    return false;
}

int PickUp::GetPrice(Player* _player)
{
    return 0;
}

bool PickUp::InRange(Player* _player)
{
    if (SFMLVectorMath::GetDistance(_player->GetPosition(), GetPosition()) <= GetCollisionRadius() + _player->GetCollisionRadius())
    {
        return true;
    }
    return false;
}

bool PickUp::HasActionText(class Player* _player)
{
    return false;
}

std::string PickUp::GetActionText()
{
    return std::string();
}

bool PickUp::AutoInteract()
{
    return true;
}

bool PickUp::CanInteract(Player* _player)
{
    return true;
}

void PickUp::Interact(Player* _player)
{
}

PickUp::PickUp()
{

}
