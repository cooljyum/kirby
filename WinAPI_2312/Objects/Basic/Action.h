#pragma once

class Action : public Image
{
protected:
	enum State
	{
		LEFT, RIGHT
	};

public:		
	Action(wstring file, int frameX = 1, int frameY = 1, bool isTrans = false, COLORREF transColor = MAGENTA);
	Action(Texture* texture = nullptr);	
	Action(Rect* owner, Vector2 offset = Vector2(0, 35));
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
	void SetLeftTexture(Texture* texture) { leftTexture = texture; }
	void SetRightTexture(Texture* texture) { rightTexture = texture; }

	Texture* GetTexture(bool isRight) { return isRight ? this->rightTexture : this->leftTexture; }

	void SetSpeed(float speed) { this->speed = speed; }
	//float GetSpeed() { return speed; }

protected:
	void SetTex(bool isRight);

protected:
	Rect* owner = nullptr;

	map<int, Animation*> animations;
	map<int, function<void()>> events;

	int curState = -1;
	float speed = 200.0f;

	Texture* rightTexture;
	Texture* leftTexture;

	Vector2 velocity;
	Vector2 offset;

	Texture* landTexture = nullptr;
	


};