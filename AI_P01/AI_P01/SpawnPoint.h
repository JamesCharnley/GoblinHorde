/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : SpawnPoint.h
Description : Different types of spawns: SpawnPoint, SpawnLine and SpawnBorder
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/System/Vector2.hpp"

namespace std
{
	//mt19937 forward declaration
	template <class _Ty, size_t _Wx, size_t _Nx, size_t _Mx, size_t _Rx, _Ty _Px, size_t _Ux, _Ty _Dx, size_t _Sx, _Ty _Bx,
		size_t _Tx, _Ty _Cx, size_t _Lx, _Ty _Fx>
	class mersenne_twister_engine;
	using mt19937 = mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15,
		0xefc60000, 18, 1812433253>;

	template <typename T>
	class uniform_real_distribution;
}

class Spawn
{
public:
	virtual sf::Vector2f GetSpawnPosition() const = 0;
};

class SpawnPoint : public Spawn
{
public:
	inline SpawnPoint(float _x, float _y) : point(_x, _y) {}
	virtual sf::Vector2f GetSpawnPosition() const override;

protected:
	sf::Vector2f point;
};

class SpawnLine : public Spawn
{
public:
	SpawnLine(float _startX, float _startY, float _endX, float _endY);
	inline SpawnLine(sf::Vector2f _start, sf::Vector2f _end) : SpawnLine(_start.x, _start.y, _end.x, _end.y) {}

	~SpawnLine();
	virtual sf::Vector2f GetSpawnPosition() const override;

protected:
	sf::Vector2f startPoint;
	sf::Vector2f endPoint;
	std::mt19937* rng;
	std::uniform_real_distribution<float>* dist;
};

class SpawnBorder : public Spawn
{
public:
	SpawnBorder(sf::Vector2f _topLeft, sf::Vector2f _topRight, sf::Vector2f _bottomLeft, sf::Vector2f _bottomRight);
	virtual ~SpawnBorder();
	virtual sf::Vector2f GetSpawnPosition() const override;

protected:
	SpawnLine* lines[4];
	std::mt19937* rng;
	std::uniform_real_distribution<float>* dist;
};
