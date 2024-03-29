#include "SpawnPoint.h"
#include <random>
#include "SFMLVectorMath.h"

//constructors
SpawnLine::SpawnLine(float _startX, float _startY, float _endX, float _endY) : startPoint(_startX, _startY), endPoint(_endX, _endY), dist(new std::uniform_real_distribution<float>(0.0f, 1.0f))
{
	std::random_device hwRand;
	rng = new std::mt19937(hwRand());
}

SpawnLine::~SpawnLine()
{
	delete rng;
	delete dist;
}

SpawnBorder::SpawnBorder(sf::Vector2f _topLeft, sf::Vector2f _topRight, sf::Vector2f _bottomLeft, sf::Vector2f _bottomRight) : dist(new std::uniform_real_distribution<float>(0.0f, 4.0f))
{
	std::random_device hwRand;
	rng = new std::mt19937(hwRand());

	lines[0] = new SpawnLine(_topLeft, _topRight);
	lines[1] = new SpawnLine(_topRight, _bottomRight);
	lines[2] = new SpawnLine(_bottomRight, _bottomLeft);
	lines[3] = new SpawnLine(_bottomLeft, _topLeft);
}
SpawnBorder::~SpawnBorder()
{
	for (int i = 0; i < 4; i++)
	{
		delete lines[i];
	}
	delete rng;
	delete dist;
}

//returns the point
sf::Vector2f SpawnPoint::GetSpawnPosition() const
{
	return point;
}

//returns a random point on the line
sf::Vector2f SpawnLine::GetSpawnPosition() const
{
	float t = (*dist)(*rng);
	return SFMLVectorMath::Lerp(startPoint, endPoint, t);
}

//returns a random point on a random line
sf::Vector2f SpawnBorder::GetSpawnPosition() const
{

	const int POS = (int)(*dist)(*rng);
	return lines[POS]->GetSpawnPosition();
}