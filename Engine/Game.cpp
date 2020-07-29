/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	rng(rd()),
	wnd(wnd),
	gfx(wnd),
	brd(gfx, boardLocation),
	snek(init_loc),
	food(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	if (!(wnd.kbd.KeyIsEmpty()) && !gameOver)
	{
		UpdateModel();
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver)
	{
		Location tempo_delta_loc = delta_location;
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			tempo_delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			tempo_delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			tempo_delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			tempo_delta_loc = { 1,0 };
		}
		if (tempo_delta_loc != delta_location)
		{
			if (!snek.GoingBackward(tempo_delta_loc))
			{
				delta_location = tempo_delta_loc;
				snek.MoveBy(delta_location);
				rate = 0;
			}
		}
		if (rate > framePerMove)
		{
			snek.MoveBy(delta_location);
			rate = 0;
		}
		++rate;

		if (food.CheckEating())
		{
			snek.Grow();
			food.Spawn();
		}

		if (snek.OverridingTheBody())
		{
			gameOver = true;
		}
	}
}

void Game::ComposeFrame()
{
	brd.DrawBorder();
	food.Draw();
	snek.Draw(brd);

	if (gameOver)
	{
		std::uniform_int_distribution<int> colorDist(0, 255);
		for (int x = 0; x < brd.GetGridWidth(); ++x)
		{
			for (int y = 0; y < brd.GetGridHeight(); ++y)
			{
				Location loc = { x,y };
				Color c(colorDist(rng), colorDist(rng), colorDist(rng));
				brd.DrawCell(loc, c);
			}
		}
	}
	
}
