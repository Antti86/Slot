#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "Board.h"


class InputCtrl
{
public:
	InputCtrl(Board& brd);
	void Draw(Graphics& gfx) const;
	bool RollActivation(Board& brd, Mouse::Event& me, Keyboard::Event& ke) const;
	void ChangeBet(Board& brd, Mouse::Event& me, Keyboard::Event& ke);
private:
	Vec2 RollBpos;
	RectF RollB;

	Vec2 BetMinusPos;
	RectF BetMinusBox;

	Vec2 BetPlusPos;
	RectF BetPlusBox;
};