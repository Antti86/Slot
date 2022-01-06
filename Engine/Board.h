#pragma once
#include "Fruits.h"
#include "Font.h"
#include <vector>
#include <algorithm>
#include <map>


class Board
{
	
public:
	Board(const Vei2 topleft);
	void Draw(Graphics& gfx) const;
	void Update();
	void RollLines(float dt);
	
private:
	void DrawBorders(Graphics& gfx) const;

	bool CheckWin() const;
	int CalculateWin() const;


private:
	const Vei2 topleft;
	
	Fruits line0{ Vec2(topleft.x + (float)borderwidth, topleft.y + (float)borderheight) };
	Fruits line1{ Vec2(topleft.x + (float)borderwidth + (float)spacewidth, topleft.y + (float)borderheight) };
	Fruits line2{ Vec2(topleft.x + (float)borderwidth + ((float)spacewidth * 2.0f), topleft.y + (float)borderheight) };
	Font font = { L"Kuvat//Consolas13x24.bmp" };
	int bet = 1;
	int money = 0;
	static constexpr int width = 300;
	static constexpr int height = 200;
	static constexpr int borderwidth = 30;
	static constexpr int borderheight = 50;
	static constexpr int spacewidth = 80;
	int NumberOfrolls = 0;
	int NumberOfWins = 0;
	std::map<int, int> winclass;


	int range01 = 0;
	int range23 = 0;
	int range45 = 0;
	int range67 = 0;
	
	
};