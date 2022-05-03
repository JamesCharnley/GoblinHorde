#pragma once
class ITakeDamage
{
public:

	virtual void TakeDamage(int _amount) = 0;
	virtual void TakeDamage(int _amount, class Character* _player) = 0;
};

