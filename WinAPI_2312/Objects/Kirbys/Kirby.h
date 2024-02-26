#pragma once

//Kirby -> Character (Inheritance)
class Kirby : public Character
{
private:

	Vector2 SIZE = { 70.0f, 70.0f };

	int DEMAGE_MONSTER = 1;
	int ATTACK_MONSTER = 10;

	float PUSH_FORCE = 800.0f;

public:
	//Mode State
	enum ModeState
	{
		DEFAULT, EAT 
	};

	//Action State
	enum ActionState
	{
		IDLE, WALK, SIT, ATTACK, JUMPUP, JUMPDOWN , HIT, DIE, DANCE
	};
	
public :
	//Set
	Kirby();
	~Kirby();

	void Render(HDC hdc);
	void Update();

	//Bottom Target Set
	void SetLandTexture(Texture* texture);

	//Key Controls
	void Move();
	void Control();
	void Attack();

	//Action & Mode Controls
	void CreateActions();
	void CreateModeAction(ModeState mode);

	void SetMode(ModeState state) { curModeState = state; }
	void SetAction(ActionState state, bool isRight, bool isForce = false);
	
	ModeState GetModeState() { return curModeState; }
	ActionState GetActionState() { return curActionState; }

	//Default Action
	void SetIdle();

	//Kirby Hit State
	void Hit();
	bool GetIsHit() { return isHit; }
	void SetIsHit(bool isHit) { this->isHit = isHit; }

	void Die();

	void Dance();

private:
	//Collision Check
	void Collision();

public:
	//static
	//Collider
	static void AddCollider(Rect* collider);
	static Rect* AttackCollision(Rect* rect);


private:
	bool isHit = false;
	bool isRight = true;

	float dieStayTime = 0.0f;

	map<ModeState, vector<Action*>> actions;

	ModeState curModeState = DEFAULT;
	ActionState curActionState = IDLE;
	
	static vector<Rect*> colliders;

public:
	static bool isEatBullet;
};