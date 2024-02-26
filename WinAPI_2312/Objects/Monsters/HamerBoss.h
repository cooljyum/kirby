#pragma once

class HamerBoss : public Monster
{
private:
	const Vector2 SIZE = { 150.0f, 100.0f };

	const float PATROL_RANGE = 200.0f;
	const float TRACE_RANGE = 800.0f;
	const float ATTACK_RANGE = 400.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;
	const float HIT_DAMAGE_SPEED = 200.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float ATTACK_STAY_TIME = 3.0f;
	const float DIE_STAY_TIME = 5.0f;

	const float JUMP_POWER = 500.0f;

	const float TREASURE_OFFSET_Y = 25.0f;

	const int DAMAGE_STAR = 50;
	const int ATTACK_STAR = 30;

public:
	HamerBoss(int x = 0, int y = 0, int hp = 100);

	void Update();
	void Render(HDC hdc) override;

	//override
	void Collision() override;
	
	void CreateTexture() override;
	void CreateAnimation() override;

	void Attack() override;

	void Die() override;
	
	//Boss Function
	void MonsterSpawn();
	void TreasureSpawn();

	void AttackEnd(bool isRight);

private:
	float attackColliderTime = 0.0f;

	Vector2 offset = { 0, 50 };

};
