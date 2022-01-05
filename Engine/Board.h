#pragma once
#include "Fruits.h"
#include "Font.h"
#include <vector>
#include <algorithm>
#include <map>


class Board
{
	
public:
	Board(const Vec2 topleft);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	void Timer(float dt);
	bool rolling = false;
private:
	void DrawBorders(Graphics& gfx) const;

	bool CheckWin() const;
	int CalculateWin() const;



private:
	Vec2 topleft;
	Fruits line0{ Vec2(topleft.x + borderwidth, topleft.y + borderheight) };
	Fruits line1{ Vec2(topleft.x + borderwidth + spacewidth, topleft.y + borderheight) };
	Fruits line2{ Vec2(topleft.x + borderwidth + (spacewidth * 2), topleft.y + borderheight) };
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
	
	float TimerStart = 0;
	float TimerEnd = 5.0f;
	
};