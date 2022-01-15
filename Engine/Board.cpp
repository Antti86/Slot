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
	gfx.DrawRect(topleft.x, winpos.y - 2, topleft.x + 330, winpos.y + 2, Colors::Red);
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

void Board::RollLines(float dt)
{
	
	if (line0.IsRolling())
	{
		for (auto& i : gfxline0)
		{
			i.speed = 700.0f;
		}
		MoveLine(dt, gfxline0, Startpos0, resetpos0);
		line0.Timer(dt, 1.0f);
	}
	else if (line0.slowtimer == true)
	{
		for (auto& i : gfxline0)
		{
			i.speed = 100.0f;
		}
		MoveLine(dt, gfxline0, Startpos0, resetpos0);
		int frut = line0.GetFruit();
		auto it = std::find_if(gfxline0.begin(), gfxline0.end(), [&frut](Fruits& l) {return l.GetFruit() == frut; });
		if (it != gfxline0.end())
		{
			if (it->pos.y + 35 <= winpos.y - 1 && it->pos.y + 35 >= winpos.y + 1)
			{
				line0.slowtimer = true;
			}
			else
			{
				line0.slowtimer = false;

			}

		}
	}
	if (line1.IsRolling())
	{
		for (auto& i : gfxline1)
		{
			i.speed = 700.0f;
		}
		MoveLine(dt, gfxline1, Startpos1, resetpos1);
		line1.Timer(dt, 2.0f);
	}
	else if (line1.slowtimer == true)
	{
		for (auto& i : gfxline1)
		{
			i.speed = 100.0f;
		}
		MoveLine(dt, gfxline1, Startpos1, resetpos1);
		int frut = line1.GetFruit();
		auto it = std::find_if(gfxline1.begin(), gfxline1.end(), [&frut](Fruits& l) {return l.GetFruit() == frut; });
		if (it != gfxline1.end())
		{
			if (it->pos.y + 35 <= winpos.y - 1 && it->pos.y + 35 >= winpos.y + 1)
			{
				line1.slowtimer = true;
			}
			else
			{
				line1.slowtimer = false;

			}

		}
	}
	if (line2.IsRolling())
	{
		for (auto& i : gfxline2)
		{
			i.speed = 700.0f;
		}
		MoveLine(dt, gfxline2, Startpos2, resetpos2);
		line2.Timer(dt, 3.0f);
	}
	else if (line2.slowtimer == true)
	{
		for (auto& i : gfxline2)
		{
			i.speed = 100.0f;
		}
		MoveLine(dt, gfxline2, Startpos2, resetpos2);
		int frut = line2.GetFruit();
		auto it = std::find_if(gfxline2.begin(), gfxline2.end(), [&frut](Fruits& l) {return l.GetFruit() == frut; });
		if (it != gfxline2.end())
		{
			if (it->pos.y + 35 <= winpos.y - 1 && it->pos.y + 35 >= winpos.y + 1)
			{
				line2.slowtimer = true;
			}
			else
			{
				line2.slowtimer = false;

			}

		}
	}
}

void Board::SlowRollLines(float dt)
{

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

void Board::MoveLine(float dt, std::vector<Fruits>& line, const Vec2& StartPos, const Vec2& resetpos)
{
	for (auto& i : line)
	{
		i.MoveFruit(dt);
		if (i.pos.y >= resetpos.y)
		{

			i.Fruit = rng.rngtest(0, 8);
			float t = i.pos.y - 430.0f;

			for (auto& s : line)
			{
				s.pos.y -= t;
			}
			i.pos = StartPos;
		}
	}
}

