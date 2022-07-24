#pragma once
#include "Fruits.h"
#include "Font.h"
#include <vector>
#include <algorithm>
#include <map>
#include "LineLogic.h"


class Board
{
public:
	Board(const Vei2 topleft);
	//Interface func
	void Draw(Graphics& gfx);
	void UpdateLogic();
	void UpdateGraphics(float dt);
	//Getters
	Vec2 GetPos() const;
	RectI GetClippingRect() const;
	int bet = 1;	//Encap this when tests are over!
	bool AllStop() const;
	void SetBet(char plus_minus); //Incr or Decr bet based on parameter "+", "-"
private:
	//Rolling checks and logic
	void RollLines(LineLogic& line, LineLogic* previous, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float rolltime, float dt);
	void DrawBorders(Graphics& gfx) const;
	bool CheckWin() const;
	int CalculateWin() const; //Dont call this without CheckWin first
	void DrawWinLine(Graphics& gfx) const;
	void MoveLine(LineLogic& line, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float dt);
private:
	const Vei2 topleft;
	const RectI BorderRect = { topleft.x, topleft.x + width, topleft.y, topleft.y + height };

	Vei2 WinLinePos = BorderRect.GetCenter();

	Vec2 Line0Pos = { Vec2(topleft.x + (float)borderwidth, topleft.y - 70.0f) };
	Vec2 Line1Pos = { Vec2(topleft.x + (float)borderwidth + (float)spacewidth, topleft.y - 70.0f )};
	Vec2 Line2Pos = { Vec2(topleft.x + (float)borderwidth + ((float)spacewidth * 2.0f), topleft.y - 70.0f)};

	Vec2 Startpos0 = { Vec2(topleft.x + (float)borderwidth, topleft.y - 70.0f) };
	Vec2 Startpos1 = { Vec2(topleft.x + (float)borderwidth + (float)spacewidth, topleft.y - 70.0f) };
	Vec2 Startpos2 = { Vec2(topleft.x + (float)borderwidth + ((float)spacewidth * 2.0f), topleft.y - 70.0f) };

	Vec2 resetpos0 = { Line0Pos.x, (float)topleft.y + (float)height  };
	Vec2 resetpos1 = { Line0Pos.x, (float)topleft.y + (float)height };
	Vec2 resetpos2 = { Line0Pos.x, (float)topleft.y + (float)height };

	LineLogic line0;
	LineLogic line1;
	LineLogic line2;

	std::vector<Fruits> gfxline0;
	std::vector<Fruits> gfxline1;
	std::vector<Fruits> gfxline2;
	Rng rng;
	Font font = { L"Kuvat//Consolas13x24.bmp" };
	
	int money = 0;
	static constexpr int width = 330;
	static constexpr int height = 330;
	static constexpr int borderwidth = 30;
	static constexpr int borderheight = 30;
	static constexpr int spacewidth = 100;
	int NumberOfrolls = 0;
	int NumberOfWins = 0;
	std::map<int, int> winclass;


	int range01 = 0;
	int range23 = 0;
	int range45 = 0;
	int range67 = 0;
	
	
};