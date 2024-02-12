#pragma once

class Kirby : public Character
{
public :
	Kirby();
	~Kirby();

	void Update();
	void Render(HDC hdc);

	void Move();

private:



};