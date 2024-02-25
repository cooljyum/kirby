#include "Framework.h"

ProgressBar::ProgressBar(Texture* frontTexture, Texture* backTexture, bool isActive)
	: Image(frontTexture), backTexture(backTexture)
{
	this->SetActive(isActive);
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
	if (!this->IsActive()) return;

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
