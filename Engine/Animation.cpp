#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface& sprite, float HoldTime, Color chroma)
	:
	sprite(sprite),
	HoldTime(HoldTime),
	chroma(chroma)
{
	for (int i = 0; i <= count; i++)
	{
		frames.emplace_back(x * i, x * i + width, y, y + height);
	}

}

void Animation::Draw(Vei2& pos, Graphics& gfx) const
{
	gfx.DrawSprite(pos, frames[iCurrentFrame], sprite, SpriteEffect::Chroma(chroma));
}

void Animation::Update(float dt)
{
	CurrentFrameTime += dt;
	while (CurrentFrameTime >= HoldTime )
	{
		Advance();
		CurrentFrameTime -= HoldTime;
	}
	
}

void Animation::Advance()
{
	if (++iCurrentFrame >= frames.size())
	{
		iCurrentFrame = 0;
	}
}
