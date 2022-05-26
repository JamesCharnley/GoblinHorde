/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : GoblinHorde.h
Description : 
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Game.h"
class GoblinHorde :
    public Game
{

public:

    GoblinHorde();

	int numberOfPlayers = 1;

protected:

	//If NewScene is set to true, this function will be called at the end of the current whie loop
	//and open a new scene class
	virtual void LoadScene(std::string _sceneName) override;
};

