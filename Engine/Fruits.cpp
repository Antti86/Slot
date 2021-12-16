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

void Fruits::Procces(Keyboard& kbd, int min, int max)
{
	int counter = 3;
	//Fruit = rng.rngtest(min, max);

	for (int i = 0; i < counter; i++)
	{
		Fruit = rng.rngtest(min, max);
		if (Fruit < 4)
		{
			continue;
		}
		else
		{
			break;
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
