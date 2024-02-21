#pragma once

class Kirby : public Character
{
private:
	float INVINCIBILITY_TIME = 2.0f;

public:
	//커비 모드 상태
	enum ModeState
	{
		DEFAULT, EAT , FLY
	};

	//커비 액션 상태들
	enum ActionState
	{
		IDLE, WALK, SIT, ATTACK, JUMPUP, JUMPDOWN , HIT
	};

public :
	Kirby();
	~Kirby();

	void Update();
	void Render(HDC hdc);

	void SetLandTexture(Texture* texture);

	void Move();
	void Control();
	void Attack();
	void Hit();

	void CreateActions();
	void CreateModeAction(ModeState mode);

	void SetIdle();

	void SetMode(ModeState state) { curModeState = state; }
	void SetAction(ActionState state, bool isRight, bool isForce = false);
	
	ModeState GetModeState() { return curModeState; }
	ActionState GetActionState() { return curActionState; }

	bool GetIsHit() { return isHit; }
	void SetIsHit(bool isHit) { this->isHit=isHit; }

private:
	void Collision();

public:
	static void AddCollider(Rect* collider);
	static Rect* AttackCollision(Rect* rect);

private:
	bool isHit = false;
	float invincibilityTime = 0.0f;

	map<ModeState, vector<Action*>> actions;

	ModeState curModeState = DEFAULT;
	ActionState curActionState = IDLE;

	bool isRight = true;

	static vector<Rect*> colliders;
};