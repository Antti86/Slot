#include "InputControl.h"

InputCtrl::InputCtrl(Board& brd)
	:
	RollBpos(brd.GetPos().x - 80.0f, brd.GetPos().y),
	RollB(RectF(RollBpos.x, RollBpos.x + 40.0f, RollBpos.y, RollBpos.y + 40.0f ))
{
}

void InputCtrl::Draw(Graphics& gfx) const
{
	gfx.DrawRectLines(RollB, Colors::Green);
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
		if (ke.IsPress() && ke.GetCode() == VK_RIGHT)
		{
			brd.SetBet('+');
		}
	}

}
