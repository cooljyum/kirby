#include "Framework.h"

MapItem::MapItem(Texture* texture, float speed, bool loop)
	: Image(texture)
{
	animation = new Animation(texture->GetFrame(), speed);
	animation->SetDefault(loop);
}

MapItem::~MapItem()
{
	delete animation;
}

void MapItem::Update()
{
	if (!isActive) return;

	animation->Update();
}

void MapItem::Render(HDC hdc)
{
	Image::CamRender(hdc, animation->GetFrame());
}

void MapItem::Play(const Vector2& pos)
{
	this->isActive = true;
	this->pos = pos;
	animation->Play();
}
