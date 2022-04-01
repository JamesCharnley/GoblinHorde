#pragma once
#include "Game.h"
class GoblinHorde :
    public Game
{

public:

    GoblinHorde();

protected:

	//If NewScene is set to true, this function will be called at the end of the current whie loop
	//and open a new scene class
	virtual void LoadScene(std::string _sceneName) override;
};

