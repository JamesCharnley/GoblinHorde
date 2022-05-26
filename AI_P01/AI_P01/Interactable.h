/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Interactable.h
Description : Abstract base class for interactable objects
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

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

