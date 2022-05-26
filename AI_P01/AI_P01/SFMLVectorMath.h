/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : SMFLVectorMath.h
Description : Header only extention functions that operate on sfml vectors
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class SFMLVectorMath
{
public:

	static float GetDistance(sf::Vector2f _vecA, sf::Vector2f _vecB)
	{
		float dist = std::sqrt(((_vecA.x - _vecB.x) * (_vecA.x - _vecB.x)) + ((_vecA.y - _vecB.y) * (_vecA.y - _vecB.y)));
		return dist;
	}

	static float GetMagnitude(sf::Vector2f _vec)
	{
		return std::sqrt((_vec.x * _vec.x) + (_vec.y * _vec.y));
	}

	//normalize regardless of inital magnitude
	static sf::Vector2f Normalize(sf::Vector2f _vec)
	{
		return _vec / GetMagnitude(_vec);
	}

	static sf::Vector2f Clamp(sf::Vector2f _vec, float _maxMag = 1.0f)
	{
		// normalize if length is greater than _maxMag and multiply by _maxMag, clamping the length to _maxMag
		if (GetMagnitude(_vec) > _maxMag)
		{
			return Normalize(_vec) * _maxMag;
		}
		else
		{
			return _vec;
		}
	}

	static sf::Vector2f MultiplyVector(sf::Vector2f _vecA, float _num)
	{
		sf::Vector2f result(_vecA.x * _num, _vecA.y * _num);
		return result;
	}

	static float DirectionToAngle(sf::Vector2f _position, sf::Vector2f _dir)
	{
		float angle = atan2(_dir.y - _position.y, _dir.x - _position.x);
		return (angle * 180.0f / 3.14159265359f);
	}

	static sf::Vector2f AngleToDirection(float _angle)
	{
		_angle = _angle * 3.14159265359f / 180.0f;
		float x = std::cos(_angle);
		float y = std::sin(_angle);
		
		return sf::Vector2f(x, y);
	}
	
	static sf::Vector2f Lerp(sf::Vector2f _vecA, sf::Vector2f _vecB, float _t)
	{
		sf::Vector2f result;
		result.x = _vecA.x + _t * (_vecB.x - _vecA.x);
		result.y = _vecA.y + _t * (_vecB.y - _vecA.y);
		return result;
	}

	static float Dot(sf::Vector2f _vecA, sf::Vector2f _vecB)
	{
		return _vecA.x * _vecB.x + _vecA.y * _vecB.y;
	}
};

namespace sf
{
	//printing
	inline std::ostream& operator << (std::ostream& os, const Vector2f& _vec)
	{
		os << _vec.x << ", " << _vec.y;
		return os;
	}
}

