#include "Board.h"
#include "Assert.h"

Board::Board(Graphics& gra, Location& brd_loc)
	:
	grid_loc(brd_loc),
	gfx(gra)
{
}

void Board::DrawCell(const Location& loc, const Color& c)
{
	assert(loc.x >= 0);
	assert(loc.x <= gridWidth - 1);
	assert(loc.y >= 0);
	assert(loc.y <= gridHeight - 1);
	int x_loc = grid_loc.x + border_width + loc.x * width;
	int y_loc = grid_loc.y + border_width + loc.y * height;
	//gfx.DrawRectDim(x_loc, y_loc, width, height, border_color);
	gfx.DrawRectDim(x_loc + gap, y_loc + gap, width - gap*2, height - gap*2, c);	
}

void Board::DrawBorder()
{
	gfx.DrawRectDim((grid_loc.x), (grid_loc.y), (border_width*2 + gridWidth * width), border_width, border_color);
	gfx.DrawRectDim((grid_loc.x), (grid_loc.y + gridHeight * width + border_width), (border_width * 2 + gridWidth * width), border_width, border_color);
	gfx.DrawRectDim((grid_loc.x), (grid_loc.y + border_width), border_width, (gridHeight * height), border_color);
	gfx.DrawRectDim((grid_loc.x + border_width + gridWidth * width), (grid_loc.y + border_width), border_width, (gridHeight * height), border_color);

}

int Board::GetGridWidth()
{
	return gridWidth;
}

int Board::GetGridHeight()
{
	return gridHeight;
}
