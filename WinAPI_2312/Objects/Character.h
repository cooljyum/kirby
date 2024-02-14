#pragma once

class Character : public Rect
{
public:
	Character();
	~Character();

	void Render(HDC hdc);

	//virtual void Move();
	
	bool IsDie() { if (this->hp <= 0)return true; else return false; }
	
	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; }

	void DamageHp(int damage) { hp -= damage; }



public:
	Image* image;
	Vector2 imageOffset = { 0, 0 };
	Vector2 startRectSize, startImageSize, startOffset;
	int hp = 100;
	float velocity = 0.0f;

};