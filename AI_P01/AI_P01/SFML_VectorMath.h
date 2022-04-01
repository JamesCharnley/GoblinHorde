#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class SFML_VectorMath
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


	static sf::Vector2f Normalize(sf::Vector2f _vec)
	{
		// get magnitude/length of vector
		float magnitude = GetMagnitude(_vec);

		// normalize if length is greater than 1
		if (magnitude > 1)
		{
			// normalize
			_vec.x = _vec.x / magnitude;
			_vec.y = _vec.y / magnitude;
		}

		// return vector
		return _vec;
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
		_angle = _angle / 180.0f * 3.14159265359f;
		float x = std::cos(_angle);
		x = std::sin(x);
		float y = std::cos(_angle);
		y = std::sin(y);
		return sf::Vector2f(x, y);
	}
};

