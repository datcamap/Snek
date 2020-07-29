#include "Snake.h"
#include <assert.h>
#include <random>

Snake::Snake(const Location& loc)
{
	assert(loc.x + nSegments <= Board::GetGridWidth());
	segments[0].Initialize(loc, headColor);
	StartingPosition(loc);
}

void Snake::StartingPosition(const Location& start_loc)
{
	Location lct = start_loc;
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Place(lct);
		++lct.x;
	}
}

void Snake::Teleport(Segment& head)
{
	if (head.GetLocation().x > Board::GetGridWidth() - 1)
	{
		Location teleport = { 0,head.GetLocation().y };
		head.Place(teleport);
	}
	else if (head.GetLocation().x < 0)
	{
		Location teleport = { Board::GetGridWidth() - 1,head.GetLocation().y };
		head.Place(teleport);
	}
	else if (head.GetLocation().y > Board::GetGridHeight() - 1)
	{
		Location teleport = { head.GetLocation().x,0 };
		head.Place(teleport);
	}
	else if (head.GetLocation().y < 0)
	{
		Location teleport = { head.GetLocation().x,Board::GetGridHeight() - 1 };
		head.Place(teleport);
	}
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
	Teleport(segments[0]);
}

void Snake::Grow()
{
	if (nSegments <= MAXlength - 1)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> cDist(100, 255);
		Color c = Colors::MakeRGB(0,cDist(rng), 0);
		segments[nSegments].Initialize(segments[nSegments - 1].GetLocation(),c);
		++nSegments;
	}
}

bool Snake::OverridingTheBody()
{
	for (int i = 4; i <= nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == segments[0].GetLocation())
		{
			return true;
		}
	}
	return false;
}

bool Snake::OverridingTheFood(const Location& food_loc)
{
	for (int i = 0; i <= nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == food_loc)
		{
			return true;
		}
	}
	return false;
}

int Snake::SnakeLength()
{
	return nSegments;
}

Location Snake::GetHead()
{
	return segments[0].GetLocation();
}

bool Snake::GoingBackward(const Location& delta_loc)
{
	Location future_location = segments[0].GetLocation();
	future_location.Add(delta_loc);
	Segment future_head;
	future_head.Place(future_location);
	Teleport(future_head);
	if (future_head.GetLocation() == segments[1].GetLocation())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::Draw(Board& brd)
{
	for (int i = nSegments - 1; i >= 0; --i)
	{
		segments[i].Draw(brd);
	}
}

Snake::Segment::Segment()
{
}

void Snake::Segment::Initialize(const Location& init_loc, const Color& init_c)
{
	loc = init_loc;
	c = init_c;
}

void Snake::Segment::InitBody(const Color& init_c)
{
	Initialize(loc, c);
}

void Snake::Segment::Place(const Location& here)
{
	Initialize(here, c);
}

void Snake::Segment::Follow(const Segment& previous)
{
	loc = previous.loc;
}

void Snake::Segment::MoveBy(const Location& delta_location)
{
	assert((abs(delta_location.x) + abs(delta_location.y)) <= 1);
	loc.Add(delta_location);
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

Location Snake::Segment::GetLocation()
{
	return loc;
}
