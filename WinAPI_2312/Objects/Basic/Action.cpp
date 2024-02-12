#include "Framework.h"

Action::Action(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
	: Image(file, frameX, frameY, isTrans, transColor)
{
}

Action::Action(Texture* texture)
	: Image(texture)
{
}

Action::Action(Rect* owner) : Image(nullptr), owner(owner)
{
}

Action::~Action()
{
	for (pair<int, Animation*> animation : animations)
		delete animation.second;
}

void Action::Update()
{
	pos = owner->GetPos();
	owner->Translate(velocity * DELTA);
	animations[curState]->Update();
}

void Action::Render(HDC hdc)
{
	Image::Render(hdc, animations[curState]->GetFrame());
}

void Action::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight);
}

void Action::SetState(int state, bool isForce, bool isPlay)
{
	if (!isForce && curState == state)
		return;

	curState = state;

	if(isPlay)
		animations[state]->Play();
}

Animation* Action::AddAnimation(int key, float speed)
{
	if (animations.count(key) > 0)
		return animations[key];

	animations[key] = new Animation(maxFrame, speed);

	return animations[key];
}

void Action::SetTex(bool isRight)
{
	if (isRight)
		texture = rightTexture;
	else
		texture = leftTexture;
}
