#pragma once

#include <string>

class Interactable
{
public:

    virtual bool CostsGold() = 0;
    virtual int GetPrice(class Player* _player) = 0;
    virtual bool InRange(class Player* _player) = 0;
    virtual bool HasActionText(class Player* _player) = 0;
    virtual std::string GetActionText() = 0;
    virtual bool AutoInteract() = 0;
    virtual bool CanInteract(class Player* _player) = 0;
    virtual void Interact(class Player* _player) = 0;
};

