#pragma once

class Monster : public Character
{
public:
	enum AnimationState
	{
		IDLE, MOVE, ATTACK, HIT, DEAD, INHALED, END
	};
private:
	enum class ActionState
	{
		PATROL, TRACE, ATTACK, HIT, DEAD
	};
	const Vector2 SIZE = { 70.0f, 70.0f };

	const float PATROL_RANGE = 200.0f;
	const float TRACE_RANGE = 400.0f;
	const float ATTACK_RANGE = 100.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;
	const float HIT_DAMAGE_SPEED = 200.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float ATTACK_STAY_TIME = 2.0f;
	const float DIE_STAY_TIME = 2.0f;

	const float GRAVITY = 980.0f;

public:
	Monster( int x = 0, int y = 0, int hp = 100 );
	~Monster();

	void Update();
	void Render(HDC hdc);

	void SetTarget(Character* target) { this->target = target; }
	void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	void SetLandTexture(Texture* texture) { this->landTexture = texture; }
	
	AnimationState GetState() { return curState; }

	void InHaled();
	void Hit();

private:
	void SetActionState();

	void SetIdle();

	void Collision();

	void CreateTexture();
	void CreateAnimation();

	void SetAnimation(AnimationState state);

private:
	void DoAction(); // AnimationState ���� Action �Լ� ȣ��

	//Action �Լ���
	void Patrol();
	void Trace();
	void Attack();
	void Die();

	void SetDirectionState(); //Target ���� IsRight����

	void SetDestPos(); //Patrol �Ҷ� �Ÿ�����

	void SetAllActive(bool isActive); //������� ��� Rect Ű�� ��

private:
	bool isRight = false, isStay = true;

	Vector2 velocity, destPos;
	Vector2 offset = { 0, 35 };

	float stayTime = 0.0f;
	float stayAttackTime = 0.0f;
	float stayDieTime = 0.0f;

	AnimationState curState = IDLE;
	ActionState actionState = ActionState::PATROL;

	vector<vector<Animation*>> animations;

	Texture* leftTexture;
	Texture* rightTexture;
	Texture* landTexture;

	vector<Rect*> hitColliders;

	Character* target;

	Rect* traceRange;
	Rect* attackRange;

	Rect* attackCollider;

	Image* image;
};