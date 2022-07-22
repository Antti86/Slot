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



void Fruits::MoveFruit(float dt)
{
	pos.y += speed * dt;
}


Vec2 Fruits::GetPos() const
{
	return pos;
}

void Fruits::CalculateFruitPos()
{
	currentXfruit = GfxFruit % width;
	currentYfruit = GfxFruit / width;
	rectpos = { currentXfruit * dim, currentYfruit * dim };
	picslice = RectI(rectpos, dim, dim);
}


void Fruits::SetSpeed(float s)
{
	speed = s;
}