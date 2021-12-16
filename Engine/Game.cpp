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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();

	float elapsedtime = ft.Mark();
	while (elapsedtime > 0.0f)
	{
		float dt = std::min(0.0025f, elapsedtime);
		UpdateModel(dt);
		elapsedtime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	const Keyboard::Event e = wnd.kbd.ReadKey();
	if (e.IsPress() && e.GetCode() == VK_SPACE)
	{
		f0.Procces(wnd.kbd, 0, 7);
		int f1min = f0.GetFruit() - 1;
		int f1max = f0.GetFruit() + 1;
		if (f1min < 0)
		{
			f1min = 0;
		}
		if (f1max > 7)
		{
			f1max = 7;
		}
		f1.Procces(wnd.kbd, f1min, f1max);
		f2.Procces(wnd.kbd, f1min, f1max);
	}

}

void Game::ComposeFrame()
{
	f0.Draw(gfx);
	f1.Draw(gfx);
	f2.Draw(gfx);

}
