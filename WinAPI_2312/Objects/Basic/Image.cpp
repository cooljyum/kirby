#include "Framework.h"

Image::Image(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
	: maxFrame({frameX, frameY})
{
	texture = Texture::Add(file, frameX, frameY, isTrans, transColor);
	size = texture->GetSize();
}

Image::Image(Texture* texture) : texture(texture)
{
	if (texture == nullptr)
		return;

	size = texture->GetSize();
	maxFrame = texture->GetFrame();
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

void Image::SetTexture(Texture* texture)
{
	this->texture = texture;
	size = texture->GetSize();
	maxFrame = texture->GetFrame();
}
