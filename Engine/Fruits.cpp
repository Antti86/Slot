#include "Fruits.h"
#include "Board.h"

Fruits::Fruits(Vec2 pos)			//logig ctr
	:
	pos(pos)
{
	Fruit = 0;
}

Fruits::Fruits(Vec2 pos, int Fruit) //graphics ctr
	:
	pos(pos),
	Fruit(Fruit)
{
	CalculateFruitPos();
}

void Fruits::Draw(Graphics& gfx, class Board& brd) const
{
	//gfx.DrawSprite((Vei2)pos, picslice, brd.GetClippingRect(), fruitsheet, SpriteEffect::Chroma{ Colors::White });
	gfx.DrawSprite((Vei2)pos, picslice, fruitsheet, SpriteEffect::NoChroma{});
}

void Fruits::Procces()
{
	rolling = true;
	Fruit = rng.rngtest(min, max);

	
}

int Fruits::GetFruit() const
{
	return Fruit;
}

void Fruits::MoveFruit(float dt)
{
	pos.y += speed * dt;
}

void Fruits::Timer(float dt, float TimerEnd)
{
	if ((TimerStart += dt) > TimerEnd)
	{
		TimerStart = 0.0f;
		rolling = false;
	}
	else
	{
		
		rolling = true;
	}
}

bool Fruits::IsRolling() const
{
	return rolling;
}

int Fruits::GetFruitDim() const
{
	return dim;
}

Vec2& Fruits::GetPos()
{
	return pos;
}

void Fruits::CalculateFruitPos()
{
	Fruit = TranslateFruitVal();
	currentXfruit = Fruit % width;
	currentYfruit = Fruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}

int Fruits::TranslateFruitVal()
{
	int ret = 0;

	if (Fruit >= 8 && Fruit <= 10)
	{
		ret = 7;
	}
	else if (Fruit >= 11 && Fruit <= 13)
	{
		ret = 6;
	}
	else if (Fruit >= 14 && Fruit <= 15)
	{
		ret = 5;
	}
	else if (Fruit >= 16 && Fruit <= 17)
	{
		ret = 4;
	}
	else if (Fruit == 18 )
	{
		ret = 3;
	}
	else if (Fruit == 19)
	{
		ret = 2;
	}
	else
	{
		ret = Fruit;
	}
	return ret;
}
