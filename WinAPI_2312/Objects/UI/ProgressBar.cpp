#include "Framework.h"

ProgressBar::ProgressBar(Texture* frontTexture, Texture* backTexture)
	: Image(frontTexture), backTexture(backTexture)
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
	if (backTexture)
	{
		backTexture->Render(hdc, this);
	}

	GdiTransparentBlt(
		hdc,
		(int)Left(), (int)Top(),
		(int)(size.x * value), (int)size.y,
		texture->GetMemDC(),
		0, 0, (int)(size.x * value), (int)size.y,
		texture->GetTransColor()
	);
}
