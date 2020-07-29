#pragma once

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		Segment();
		void Initialize(const Location& init_loc, const Color& init_c);
		void InitBody(const Color& init_c);
		void Place(const Location& here);
		void Follow(const Segment& previous);
		void MoveBy(const Location& delta_location);
		void Draw(Board& brd);
		Location GetLocation();
	private:
		Location loc = { 0,0 };
		Color c = Colors::MakeRGB(0,255,0);
	};
public:
	Snake(const Location& loc);
	void StartingPosition(const Location& loc);
	void Teleport(Segment& head);
	void MoveBy(const Location& delta_loc);
	void Grow();
	bool OverridingTheBody();
	bool OverridingTheFood(const Location& food_loc);
	int SnakeLength();
	Location GetHead();
	bool GoingBackward(const Location& delta_loc);
	void Draw(Board& brd);
private:
	static constexpr int MAXlength = 50*50;
	Segment segments[MAXlength];
	int nSegments = 4;
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
};