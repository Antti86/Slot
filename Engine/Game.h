/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Surface.h"
#include "SpriteEffect.h"
#include "Animation.h"
#include "FrameTimer.h"
#include "Bencher.h"
#include <fstream>
#include "Rng.h"
#include "Font.h"
#include "Board.h"
#include "InputControl.h"
#include "MenuScreens.h"

class Game
{
	enum class GameScreen
	{
		MainMenu,
		Slot,
		Exchange
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	/********************************/
	/*  User Variables              */
	/********************************/
	Bencher b;
	Board brd{Vec2(100.0f, 100.0f) };
	InputCtrl Ic;
	Rng rng;
	Surface back = { L"Kuvat//sky_background_green_hills.bmp" };
	MenuScreen menu{ "Slot\nExchange\nExit", Vei2(100, 100), Colors::Red, Colors::Blue, 2};
	float dt;
	float elapsedtime;
	GameScreen gs = GameScreen::MainMenu;
};