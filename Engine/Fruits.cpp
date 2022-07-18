#include "Fruits.h"
#include "Board.h"



Fruits::Fruits(Vec2 pos, int GfxFruit) //graphics ctr
	:
	pos(pos),
	GfxFruit(GfxFruit)
{
	CalculateFruitPos();
}

void Fruits::Draw(Graphics& gfx, class Board& brd) const
{
	gfx.DrawSprite((Vei2)pos, picslice, brd.GetClippingRect(), fruitsheet, SpriteEffect::Chroma{ Colors::White });
	/*gfx.DrawSprite((Vei2)pos, picslice, fruitsheet, SpriteEffect::NoChroma{});*/
}

void Fruits::Procces()
{
	rollstatus = Rollstatus::Fast;
	Fruit = rng.rngtest(min, max);
	Fruit = TranslateFruitVal(Fruit);
}

int Fruits::GetFruit() const
{
	return Fruit;
}

int Fruits::GetGFXFruit() const
{
	return GfxFruit;
}

void Fruits::MoveFruit(float dt)
{
	pos.y += speed * dt;
}

bool Fruits::Timer(float dt, float TimerEnd)
{
	if ((TimerStart += dt) > TimerEnd)
	{
		TimerStart = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

const Fruits::Rollstatus& Fruits::GetRollStatus() const
{
	return rollstatus;
}

int Fruits::GetFruitDim() const
{
	return dim;
}

Vec2 Fruits::GetPos() const
{
	return pos;
}

void Fruits::CalculateFruitPos()
{
	GfxFruit = TranslateFruitVal(GfxFruit);
	currentXfruit = GfxFruit % width;
	currentYfruit = GfxFruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}

void Fruits::MoveLine(Fruits& line, std::vector<Fruits>& gfxline, const Vec2& StartPos, const Vec2& resetpos, float dt)
{
	MoveFruit(dt);
	if (pos.y >= resetpos.y) // checks if fruit gone out of the board
	{
		if (line.rollstatus == Rollstatus::Slow) //if slow mode, this block makes sure that right fruit appear after 7 fails
		{
			if (line.testcounter == 7)
			{
				GfxFruit = line.Fruit;
				line.testcounter = 0;
			}
			else
			{
				GfxFruit = rng.rngtest(min, max);
				line.testcounter += 1;
			}
		}
		else
		{
			GfxFruit = rng.rngtest(min, max);
		}
		
		float t = pos.y - 430.0f;
		for (auto& s : gfxline)	//Correcting fruit line position, no caps appearing between fruits
		{
			s.pos.y -= t;
		}
		pos = StartPos;		//Moving fruit back to the top
	}
}

void Fruits::SetSpeed(float s)
{
	speed = s;
}


int Fruits::TranslateFruitVal(int f)
{
	int ret = 0;

	if (f >= 8 && f <= 10)
	{
		ret = 7;
	}
	else if (f >= 11 && f <= 13)
	{
		ret = 6;
	}
	else if (f >= 14 && f <= 15)
	{
		ret = 5;
	}
	else if (f >= 16 && f <= 17)
	{
		ret = 4;
	}
	else if (f == 18 )
	{
		ret = 3;
	}
	else if (f == 19)
	{
		ret = 2;
	}
	else
	{
		ret = f;
	}
	return ret;
}
