#include "Framework.h"

Kirby::Kirby() : Character()
{
	image = new Image(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	startRectSize = size;
	startImageSize = image->GetSize();
	this->imageOffset = imageOffset;
	startOffset = imageOffset;
}

Kirby::~Kirby()
{
}

void Kirby::Update()
{
	Move();
	image->SetPos(pos + imageOffset);
}

void Kirby::Render(HDC hdc)
{
	Character::Render(hdc);
	image->Render(hdc);
}

void Kirby::Move()
{
}
