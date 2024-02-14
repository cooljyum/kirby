#include "Framework.h"

Image::Image(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
	: maxFrame({ frameX, frameY })
{
	texture = Texture::Add(file, frameX, frameY, isTrans, transColor);
	size = texture->GetSize();

	camRect.SetSize(size);
}

Image::Image(Texture* texture) : texture(texture)
{
	if (texture == nullptr)
		return;

	size = texture->GetSize();
	maxFrame = texture->GetFrame();

	camRect.SetSize(size);
}

Image::~Image()
{
}

void Image::Render(HDC hdc, POINT curFrame)
{
	if (!isActive) return;

	texture->Render(hdc, this, curFrame);
	Rect::Render(hdc);
}

void Image::Render(HDC hdc, int alpha, POINT curFrame)
{
	if (!isActive) return;

	texture->Render(hdc, this, alpha, curFrame);
	Rect::Render(hdc);
}

void Image::CamRender(HDC hdc, POINT curFrame)
{
	if (!isActive) return;

	camRect.SetPos(pos - CAM->GetPos());
	texture->Render(hdc, &camRect, curFrame);
	camRect.Render(hdc);
}

void Image::CamRender(HDC hdc, int alpha, POINT curFrame)
{
	if (!isActive) return;

	camRect.SetPos(pos - CAM->GetPos());
	texture->Render(hdc, &camRect, alpha, curFrame);
	camRect.Render(hdc);
}

void Image::SetTexture(Texture* texture)
{
	this->texture = texture;
	size = texture->GetSize();
	camRect.SetSize(size);
	maxFrame = texture->GetFrame();
}
