#include "Framework.h"

Character::Character() : Rect()
{

}

Character::~Character()
{
}

void Character::Render(HDC hdc)
{
	image->Render(hdc);
	Rect::Render(hdc);
}

void Character::Move()
{
}
