#include "Board.h"

Board::Board(const Vei2 topleft)
	:
	topleft(topleft)
{
	winclass = { { 7, 3 }, {6, 5}, {5, 8}, {4, 14}, {3, 20}, {2, 30}, {1, 100}, {0, 200} };

	for (int i = 0; i < 4; i++)
	{
		gfxline0.emplace_back(Line0Pos, rng.rngtest(0, 8));
		gfxline1.emplace_back(Line1Pos, rng.rngtest(0, 8));
		gfxline2.emplace_back(Line2Pos, rng.rngtest(0, 8));
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

	//font.DrawTexts(bets, Vei2(topleft.x + spacewidth, topleft.y - borderheight), gfx, Colors::Green);
	//font.DrawTexts("BET", Vei2(topleft.x, topleft.y - borderheight), gfx, Colors::Green);

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

	if (line0.GetFruit() != line1.GetFruit())
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

void Board::RollLines(Fruits& line, Fruits* lastline, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float rolltime, float dt)
{
	if (line.GetRollStatus() == Fruits::Rollstatus::Fast)
	{
		for (auto& i : gfxline)
		{
			i.SetSpeed(700.0f);
			i.MoveLine(gfxline, StartPos, resetpos, dt);
		}
		if (line.TimerTest(dt, rolltime))
		{
			if (lastline == nullptr)
			{
				line.rollstatus = Fruits::Rollstatus::Slow;
			}
			else if (lastline->GetRollStatus() == Fruits::Rollstatus::Stop)
			{
				line.rollstatus = Fruits::Rollstatus::Slow;
			}
			
		}
	}
	else if (line.GetRollStatus() == Fruits::Rollstatus::Slow)
	{
		
		for (auto& i : gfxline)
		{
			i.SetSpeed(300.0f);
			i.MoveLine(gfxline, StartPos, resetpos, dt);
		}
		for (auto& i : gfxline)
		{
			if (i.GetGFXFruit() == line.GetFruit() && i.GetPos().y + 35 >= WinLinePos.y - 1 && i.GetPos().y + 35 <= WinLinePos.y + 1)
			{
				line.rollstatus = Fruits::Rollstatus::Stop;
			}
		}

	}
	
}

RectI Board::GetClippingRect() const
{
	return BorderRect;
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

