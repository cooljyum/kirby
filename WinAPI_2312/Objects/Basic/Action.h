#pragma once

class Action : public Image
{
protected:
	enum State
	{
		LEFT, RIGHT
	};

	const float MOVE_SPEED = 200.0f;

public:		
	Action(wstring file, int frameX = 1, int frameY = 1, bool isTrans = false, COLORREF transColor = MAGENTA);
	Action(Texture* texture = nullptr);	
	Action(Rect* owner);
	~Action();

	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Start(bool isRight);
	virtual void End() {}

	void SetState(int state, bool isForce = false, bool isPlay = true);

	Animation* AddAnimation(int key, float speed = 1.0f);
	Animation* CurAnimation() { return animations[curState]; }
	Animation* GetAnimation(int state) { return animations[state]; }

	void SetOwer(Rect* owner) { this->owner = owner; }
	void SetLandTexture(Texture* texture) { landTexture = texture; }

protected:
	void SetTex(bool isRight);

protected:
	Rect* owner = nullptr;

	map<int, Animation*> animations;
	map<int, function<void()>> events;
	int curState = -1;

	Texture* rightTexture;
	Texture* leftTexture;

	Vector2 velocity;

	Texture* landTexture = nullptr;
};