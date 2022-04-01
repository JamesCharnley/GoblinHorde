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

	sf::Vector2f MultiplyVector(sf::Vector2f _vecA, float _num)
	{
		sf::Vector2f result(_vecA.x * _num, _vecA.y * _num);

		return result;
	}
};

