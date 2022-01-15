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
	void Draw(Graphics& gfx);
	void UpdateLogic();
	void RollLines(float dt);
	void SlowRollLines(float dt);
	RectI GetClippingRect() const;
private:
	void DrawBorders(Graphics& gfx) const;
	bool CheckWin() const;
	int CalculateWin() const;
	void MoveLine(float dt, std::vector<Fruits>& line, const Vec2& StartPos, const Vec2& resetpos);

private:
	const Vei2 topleft;
	const RectI BorderRect = { topleft.x, topleft.x + width, topleft.y, topleft.y + height };
	Vei2 winpos = BorderRect.GetCenter();

	Vec2 Line0Pos = { Vec2(topleft.x + (float)borderwidth, topleft.y - 70.0f) };
	Vec2 Line1Pos = { Vec2(topleft.x + (float)borderwidth + (float)spacewidth, topleft.y - 70.0f )};
	Vec2 Line2Pos = { Vec2(topleft.x + (float)borderwidth + ((float)spacewidth * 2.0f), topleft.y - 70.0f)};

	const Vec2 Startpos0 = { Vec2(topleft.x + (float)borderwidth, topleft.y - 70.0f) };
	const Vec2 Startpos1 = { Vec2(topleft.x + (float)borderwidth + (float)spacewidth, topleft.y - 70.0f) };
	const Vec2 Startpos2 = { Vec2(topleft.x + (float)borderwidth + ((float)spacewidth * 2.0f), topleft.y - 70.0f) };

	const Vec2 resetpos0 = { Line0Pos.x, (float)topleft.y + (float)height  };
	const Vec2 resetpos1 = { Line1Pos.x , (float)topleft.y + (float)height };
	const Vec2 resetpos2 = { Line2Pos.x, (float)topleft.y + (float)height };

	Fruits line0{ Line0Pos };
	Fruits line1{ Line1Pos };
	Fruits line2{ Line2Pos };

	std::vector<Fruits> gfxline0;
	std::vector<Fruits> gfxline1;
	std::vector<Fruits> gfxline2;
	Rng rng;
	Font font = { L"Kuvat//Consolas13x24.bmp" };
	int bet = 1;
	int money = 0;
	static constexpr int width = 330;
	static constexpr int height = 330;
	static constexpr int borderwidth = 30;
	static constexpr int borderheight = 30;
	static constexpr int spacewidth = 100;
	int NumberOfrolls = 0;
	int NumberOfWins = 0;
	std::map<int, int> winclass;
	float timerend = 1.0f;

	int range01 = 0;
	int range23 = 0;
	int range45 = 0;
	int range67 = 0;
	
	
};