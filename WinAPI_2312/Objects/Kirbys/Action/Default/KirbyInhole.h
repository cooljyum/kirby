#pragma once

class KirbyInhole : public Action
{
public:
	KirbyInhole(Rect* owner);
	~KirbyInhole();

	void Render(HDC hdc) override;
	void Update() override;

	void Start(bool isRight) override;

protected:
	Rect* collider;

};