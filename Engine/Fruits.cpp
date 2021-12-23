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

void Fruits::Procces(int counter, int min, int max)
{
	//Fruit = rng.rngtest(min, max);

	if (counter == 0)
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
	}

	currentXfruit = Fruit % width;
	currentYfruit = Fruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}

int Fruits::GetFruit() const
{
	return Fruit;
}
