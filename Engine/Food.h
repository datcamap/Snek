#pragma once

#include "Board.h"
#include "Snake.h"
#include <random>

class Food
{
public:
	Food(std::mt19937& generator, Board& brd, Snake& snake);
	void Spawn();
	void Draw();
	bool CheckEating();
private:
	std::mt19937& rng;
	Board& brd;
	Snake& snake;
	Location loc = { 0,0 };
	Color c = Colors::Red;
	bool isEated = false;
};