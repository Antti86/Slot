#include "Fruits.h"

Fruits::Fruits(Vei2 pos)
	:
	pos(pos)
{
}

void Fruits::Draw(Graphics& gfx) const
{
	gfx.DrawSprite(pos, picslice, fruitsheet, SpriteEffect::Chroma{ Colors::White });
}

void Fruits::Procces(int counter, bool biggersheet)
{
	int min = 0;
	int max;
	if (biggersheet)
	{
		max = 20;
	}
	else
	{
		max = 8;
	}
	Fruit = rng.rngtest(min, max);

	/*if (counter == 0)
	{
		Fruit = rng.rngtest(min, max);
	}
	else
	{
		for (int i = 0; i < counter; i++)
		{
			Fruit = rng.rngtest(min, max);
			if (Fruit < 2)
			{
				continue;
			}
			else if (Fruit >= 2 && Fruit < 4)
			{
				counter--;
				continue;
			}
			else if (Fruit >= 4 && Fruit < 6)
			{
				counter -= 2;
				
				continue;
			}
			else
			{
				break;
			}
		}
	}*/
	Fruit = TranslateFruitVal();
	currentXfruit = Fruit % width;
	currentYfruit = Fruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}

int Fruits::GetFruit() const
{
	return Fruit;
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
