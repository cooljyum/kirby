#include "Framework.h"

Effect::Effect(Texture* texture, float speed, bool loop, int imageX, int imageY)
	: Image(texture)
{
	animation = new Animation(texture->GetFrame(), speed);

	if (imageX != -1)
		animation->SetPart(imageX, imageY, loop);
	else
		animation->SetDefault(loop);

	animation->SetEndEvent(bind(&Effect::Stop, this));
}

Effect::~Effect()
{
	delete animation;
}

void Effect::Update()
{
	if (!isActive) return;

	animation->Update();
}

void Effect::Render(HDC hdc)
{
	Image::CamRender(hdc, animation->GetFrame());
}

void Effect::Play(const Vector2& pos)
{
	this->isActive = true;
	this->pos = pos;
	animation->Play();
}

void Effect::Stop()
{
	this->isActive = false;
}