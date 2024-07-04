#include "InputControl.h"

InputCtrl::InputCtrl(Board& brd)
	:
	RollBpos(brd.GetPos().x - 80.0f, brd.GetPos().y),
	RollB(RectF(RollBpos.x, RollBpos.x + 40.0f, RollBpos.y, RollBpos.y + 40.0f )),
	BetMinusPos(brd.GetPos().x + 170.0f, brd.GetPos().y - 58),
	BetMinusBox(RectF(BetMinusPos.x, BetMinusPos.x + 40, BetMinusPos.y, BetMinusPos.y + 40)),
	BetPlusPos(brd.GetPos().x + 290.0f, brd.GetPos().y - 60),
	BetPlusBox(RectF(BetPlusPos.x, BetPlusPos.x + 40, BetPlusPos.y, BetPlusPos.y + 40)),
	buttons(L"Kuvat//InputButtons.png")
{
}

void InputCtrl::Draw(Graphics& gfx) const
{
	//Plus
	gfx.DrawSprite(BetPlusPos, RectI(0, 65, 0, 55), buttons, SpriteEffect::Chroma{ Colors::Black });
	//Minus
	gfx.DrawSprite(BetMinusPos, RectI(0, 65, 55, 54 * 2), buttons, SpriteEffect::Chroma{ Colors::Black });
	//Roll
	gfx.DrawSprite(RollBpos, RectI(0, 65, 55 * 2, 55 * 3), buttons, SpriteEffect::Chroma{ Colors::Black });
}

bool InputCtrl::RollActivation(Board& brd, Mouse::Event& me, Keyboard::Event& ke) const
{
	if (brd.AllStop())
	{
		if (ke.IsPress() && ke.GetCode() == VK_SPACE)
		{
			return true;
		}
		if (me.LeftIsPressed() && RollB.IsInside((Vec2)me.GetPos()))
		{
			return true;
		}
	}
    return false;
}

void InputCtrl::ChangeBet(Board& brd, Mouse::Event& me, Keyboard::Event& ke)
{

	if (brd.AllStop())
	{
		if (ke.IsPress() && ke.GetCode() == VK_LEFT)
		{
			brd.SetBet('-');
		}
		if (me.GetType() == Mouse::Event::Type::LPress && BetMinusBox.IsInside((Vec2)me.GetPos()))
		{
			brd.SetBet('-');
		}
		if (ke.IsPress() && ke.GetCode() == VK_RIGHT)
		{
			brd.SetBet('+');
		}
		if (me.GetType() == Mouse::Event::Type::LPress && BetPlusBox.IsInside((Vec2)me.GetPos()))
		{
			brd.SetBet('+');
		}
		
	}

}
