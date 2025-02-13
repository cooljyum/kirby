#include "Framework.h"

Action::Action(wstring file, int frameX, int frameY, bool isTrans, COLORREF transColor)
	: Image(file, frameX, frameY, isTrans, transColor)
{
}

Action::Action(Texture* texture)
	: Image(texture)
{
}

Action::Action(Rect* owner, Vector2 offset) : Image(nullptr), owner(owner), offset(offset)
{
}

Action::~Action()
{
	for (pair<int, Animation*> animation : animations)
		delete animation.second;
}

void Action::Update()
{
	owner->Translate(velocity * DELTA);
	pos = owner->GetPos() + offset;	

	animations[curState]->Update();
}

void Action::Render(HDC hdc)
{
	Image::CamRender(hdc, animations[curState]->GetFrame());
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
	pos = owner->GetPos() + offset;

	if (isRight)
		texture = rightTexture;
	else
		texture = leftTexture;
}
