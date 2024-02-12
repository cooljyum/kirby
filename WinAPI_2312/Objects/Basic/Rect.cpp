#include "Framework.h"
#include "Rect.h"

map<COLORREF, HPEN> Rect::pens;
bool Rect::isDraw = true;

Rect::Rect(Vector2 pos, Vector2 size) : pos(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
	pos.x = (left + right) * 0.5f;
	pos.y = (top + bottom) * 0.5f;

	size.x = abs(right - left);
	size.y = abs(bottom - top);
}

void Rect::Render(HDC hdc)
{
	if (!isActive) return;
	if (!isDraw) return;

	SelectObject(hdc, pens[color]);	

	//Rectangle(hdc, (int)Left(), (int)Top(), (int)Right(), (int)Bottom());
	MoveToEx(hdc, (int)Left(), (int)Top(), nullptr);
	LineTo(hdc, (int)Right(), (int)Top());

	MoveToEx(hdc, (int)Left(), (int)Top(), nullptr);
	LineTo(hdc, (int)Left(), (int)Bottom());

	MoveToEx(hdc, (int)Right(), (int)Top(), nullptr);
	LineTo(hdc, (int)Right(), (int)Bottom());

	MoveToEx(hdc, (int)Left(), (int)Bottom(), nullptr);
	LineTo(hdc, (int)Right(), (int)Bottom());
}

bool Rect::IsCollision(const Vector2& point) const
{
	if (!isActive) return false;

	if (point.x > Left() && point.x < Right())
	{
		if (point.y > Top() && point.y < Bottom())
			return true;
	}

	return false;
}

bool Rect::IsCollision(const Rect* rect, Vector2* overlap) const
{
	if (!isActive) return false;
	if (!rect->isActive) return false;

	//if (rect->Left() < Right() && rect->Right() > Left())
	//{
	//	if (rect->Top() < Bottom() && rect->Bottom() > Top())
	//	{
	//		return true;
	//	}
	//}

	float left = max(rect->Left(), Left());
	float right = min(rect->Right(), Right());
	float top = max(rect->Top(), Top());
	float bottom = min(rect->Bottom(), Bottom());

	if ((right - left) > 0 && (bottom - top) > 0)
	{
		if (overlap)
		{
			overlap->x = right - left;
			overlap->y = bottom - top;
		}
		return true;
	}

	return false;
}

void Rect::CreatePens()
{
	pens[RED] = CreatePen(PS_SOLID, 1, RED);
	pens[BLUE] = CreatePen(PS_SOLID, 1, BLUE);
	pens[GREEN] = CreatePen(PS_SOLID, 1, GREEN);
	pens[CYAN] = CreatePen(PS_SOLID, 1, CYAN);
	pens[MAGENTA] = CreatePen(PS_SOLID, 1, MAGENTA);
	pens[YELLOW] = CreatePen(PS_SOLID, 1, YELLOW);
	pens[BLACK] = CreatePen(PS_SOLID, 1, BLACK);
}

void Rect::DeletePens()
{
	//for (auto pen : pens)
	for (pair<COLORREF, HPEN> pen : pens)
		DeleteObject(pen.second);
}
