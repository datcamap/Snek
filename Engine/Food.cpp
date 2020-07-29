#include "Food.h"

Food::Food(std::mt19937& generator, Board& brd, Snake& snake)
	:
	rng(generator),
	brd(brd),
	snake(snake)
{
	Spawn();
}

void Food::Spawn()
{
	do
	{
		std::uniform_int_distribution<int> xDist(0, Board::GetGridWidth() - 1);
		std::uniform_int_distribution<int> yDist(0, Board::GetGridHeight() - 1);
		loc = { xDist(rng),yDist(rng) };
	} while (snake.OverridingTheFood(loc));
	isEated = false;
}

void Food::Draw()
{
	brd.DrawCell(loc, c);
}

bool Food::CheckEating()
{
	if (loc == snake.GetHead())
	{
		isEated = true;
	}
	else
	{
		isEated = false;
	}
	return isEated;
}
