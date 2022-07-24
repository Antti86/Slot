#include "Board.h"

Board::Board(const Vei2 topleft)
	:
	topleft(topleft)
{
	winclass = { { 7, 3 }, {6, 5}, {5, 8}, {4, 14}, {3, 20}, {2, 30}, {1, 100}, {0, 200} };

	for (int i = 0; i < 4; i++)
	{
		gfxline0.emplace_back(Fruits(Line0Pos, rng.CreateInt(0, 7)));
		gfxline1.emplace_back(Fruits(Line1Pos, rng.CreateInt(0, 7)));
		gfxline2.emplace_back(Fruits(Line2Pos, rng.CreateInt(0, 7)));
		Line0Pos.y += 70 + borderheight;
		Line1Pos.y += 70 + borderheight;
		Line2Pos.y += 70 + borderheight;
	}
}

void Board::Draw(Graphics& gfx)
{
	std::string money1 = std::to_string(money);
	std::string numrolls = std::to_string(NumberOfrolls);
	std::string Numwins = std::to_string(NumberOfWins);
	std::string bets = std::to_string(bet);
	std::string r0 = std::to_string(range01);
	std::string r1 = std::to_string(range23);
	std::string r2 = std::to_string(range45);
	std::string r3 = std::to_string(range67);

	DrawBorders(gfx);

	font.DrawTexts(bets, Vei2(topleft.x + spacewidth, topleft.y - borderheight), gfx, Colors::Green);
	font.DrawTexts("BET", Vei2(topleft.x, topleft.y - borderheight), gfx, Colors::Green);

	font.DrawTexts(money1, Vei2(topleft.x + width + borderwidth + spacewidth, topleft.y), gfx, Colors::Green);
	font.DrawTexts("Money", Vei2(topleft.x + width + borderwidth, topleft.y), gfx, Colors::Green);

	font.DrawTexts(numrolls, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + borderheight), gfx, Colors::Green);
	font.DrawTexts("Number Of Rolls", Vei2(topleft.x + width + borderwidth, topleft.y + borderheight), gfx, Colors::Green);

	font.DrawTexts(Numwins, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + borderheight + borderheight), gfx, Colors::Green);
	font.DrawTexts("Number Of Wins", Vei2(topleft.x + width + borderwidth, topleft.y + borderheight + borderheight), gfx, Colors::Green);

	font.DrawTexts(r0, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 3)),
		gfx, Colors::Green);
	font.DrawTexts(r1, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 4)),
		gfx, Colors::Green);
	font.DrawTexts(r2, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 5)),
		gfx, Colors::Green);
	font.DrawTexts(r3, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 6)),
		gfx, Colors::Green);
	DrawWinLine(gfx);
	for (auto& i : gfxline0)
	{
		i.CalculateFruitPos();
		i.Draw(gfx, *this);
	}
	for (auto& i : gfxline1)
	{
		i.CalculateFruitPos();
		i.Draw(gfx, *this);
	}
	for (auto& i : gfxline2)
	{
		i.CalculateFruitPos();
		i.Draw(gfx, *this);
	}
}

void Board::UpdateLogic()
{
	int counter = 5;

	line0.Procces();
	line1.Procces();

	if (line0.GetFruit() != line1.GetFruit()) //Increasing odds to have same fruit in lines 0 and 1
	{
		for (int i = 0; i < counter; i++)
		{
			if (line0.GetFruit() != line1.GetFruit())
			{
				line1.Procces();
			}
			else
			{
				break;
			}
		}
	}
	line2.Procces();

	money -= bet;
	NumberOfrolls++;
	if (CheckWin())
	{
		money += CalculateWin();
		//Statics
		NumberOfWins++;
		if (line0.GetFruit() < 2) 
		{
			range01++;
		}
		else if (line0.GetFruit() >= 2 && line0.GetFruit() < 4)
		{
			range23++;
		}
		else if (line0.GetFruit() >= 4 && line0.GetFruit() < 6)
		{
			range45++;
		}
		else
		{
			range67++;
		}
	}
}

void Board::UpdateGraphics(float dt)
{
	RollLines(line0, nullptr, gfxline0, Startpos0, resetpos0, 2.0f, dt);
	RollLines(line1, &line0, gfxline1, Startpos1, resetpos1, 2.0f, dt);
	RollLines(line2, &line1, gfxline2, Startpos2, resetpos2, 2.0f, dt);
}

Vec2 Board::GetPos() const
{
	return Vec2((float)topleft.x, (float)topleft.y);
}

void Board::RollLines(LineLogic& line, LineLogic* previous, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float rolltime, float dt)
{
	if (line.rollstatus == LineLogic::Rollstatus::Fast)
	{
		MoveLine(line, gfxline, StartPos, resetpos, dt);
		for (auto& i : gfxline) //Moving all the fruits
		{
			i.SetSpeed(700.0f);
		}
		if (line.Timer(dt, rolltime)) //Checks when it´s time to go slow
		{
			//Makes sure that lines stops in order 0, 1, 2
			if (previous == nullptr) //if it´s line 0, go slow immediately after the timer runs out
			{
				line.rollstatus = LineLogic::Rollstatus::Slow;
			}
			else if (previous->rollstatus == LineLogic::Rollstatus::Stop) // if not line 0, checks that previous line have stopped before going slow
			{
				line.rollstatus = LineLogic::Rollstatus::Slow;
			}
		}
	}
	else if (line.rollstatus == LineLogic::Rollstatus::Slow)
	{
		MoveLine(line, gfxline, StartPos, resetpos, dt);
		for (auto& i : gfxline) //Moving all the fruits
		{
			i.SetSpeed(300.0f);
		}
		for (auto& i : gfxline) //Checks that the logic fruit is the same as graphics fruit and that gfx fruit is in the winline
		{
			if (i.GfxFruit == line.GetFruit() && i.GetPos().y + 35 >= WinLinePos.y - 1 && i.GetPos().y + 35 <= WinLinePos.y + 1)
			{
				line.rollstatus = LineLogic::Rollstatus::Stop;
			}
		}
	}
}

RectI Board::GetClippingRect() const
{
	return BorderRect;
}

bool Board::AllStop() const
{
	if (line0.rollstatus == LineLogic::Rollstatus::Stop && line1.rollstatus == LineLogic::Rollstatus::Stop &&
		line2.rollstatus == LineLogic::Rollstatus::Stop)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::SetBet(char plus_minus)
{
	if (bet > 1 && plus_minus == '-')
	{
		bet -= 1;
	}
	if (bet < 5 && plus_minus == '+')
	{
		bet += 1;
	}
}

void Board::DrawBorders(Graphics& gfx) const
{
	gfx.DrawRectLines(BorderRect, Colors::Blue);
}

bool Board::CheckWin() const
{
	std::vector<int> win;
	int i = line0.GetFruit();
	win.push_back(line1.GetFruit());
	win.push_back(line2.GetFruit());
	return std::all_of(win.begin(), win.end(), [&i](int l) {return l == i; });
}

int Board::CalculateWin() const
{
	return winclass.find(line0.GetFruit())->second * bet;
}

void Board::DrawWinLine(Graphics& gfx) const
{
	gfx.DrawRect(BorderRect.left, WinLinePos.y - 2, BorderRect.right, WinLinePos.y + 2, Colors::Red);
}

void Board::MoveLine(LineLogic& line, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float dt)
{
	for (auto& i : gfxline)
	{
		i.MoveFruit(dt);
		if (i.GetPos().y >= resetpos.y)
		{
			if (line.rollstatus == LineLogic::Rollstatus::Slow) //if slow mode, this block makes sure that right fruit appear after 7 fails
			{
				if (line.testcounter == 7)
				{
					i.GfxFruit = line.GetFruit();
					line.testcounter = 0;
				}
				else
				{
					i.GfxFruit = rng.CreateInt(0, 7);
					line.testcounter += 1;
				}
			}
			else
			{
				i.GfxFruit = rng.CreateInt(0, 7);
			}
			float t = i.pos.y - 430.0f;
			for (auto& s : gfxline)	//Correcting fruit line position, no caps appearing between fruits
			{
				s.pos.y -= t;
			}
			i.pos = StartPos;		//Moving fruit back to the top
		}
	}
}

