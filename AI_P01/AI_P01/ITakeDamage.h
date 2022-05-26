/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Interactable.h
Description : Abstract base class for objects that take damage
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
class ITakeDamage
{
public:

	virtual void TakeDamage(int _amount) = 0;
	virtual void TakeDamage(int _amount, class Character* _player) = 0;
};

