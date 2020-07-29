#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Colors.h"

class Board
{
public:
	Board(Graphics& gra, Location& brd_loc);
	void DrawCell(const Location& loc, const Color& c);
	void DrawBorder();
	static int GetGridWidth();
	static int GetGridHeight();
private:
	Color border_color = Colors::Gray;
	static constexpr int border_width = 10;
	static constexpr int gridWidth = 40;
	static constexpr int gridHeight = 30;
	static constexpr int width = 12;
	static constexpr int height = 12;
	static constexpr int gap = 1;
	Location& grid_loc;
	Graphics& gfx;
};