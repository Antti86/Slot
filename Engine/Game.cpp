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
	gfx( wnd ),
	Ic ( brd )
{
}

void Game::Go()
{
	gfx.BeginFrame();

	elapsedtime = ft.Mark();
	while (elapsedtime > 0.0f)
	{
		dt = std::min(0.0025f, elapsedtime);
		UpdateModel(dt);
		elapsedtime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	Keyboard::Event ke = wnd.kbd.ReadKey();
	Mouse::Event me = wnd.mouse.Read();
	if (Ic.RollActivation(brd, me, ke))
	{
		//for (int i = 0; i < 1000000; i++)
		//{
		//	
		//}
		brd.UpdateLogic();
	}
	Ic.ChangeBet(brd, me, ke);
	brd.UpdateGraphics(dt);

}

void Game::ComposeFrame()
{
	brd.Draw(gfx);
	Ic.Draw(gfx);
	
}
