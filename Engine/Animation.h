#pragma once
#include "Graphics.h"
#include "Surface.h"
#include <vector>
#include "SpriteEffect.h"


class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& sprite, float HoldTime, Color chroma );
	void Draw(Vei2& pos, Graphics& gfx) const;
	void Update(float dt);
private:
	void Advance();
private:
	Color chroma;
	const Surface& sprite;
	std::vector<RectI> frames;
	int iCurrentFrame = 0;
	float HoldTime;
	float CurrentFrameTime = 0.0f;

};