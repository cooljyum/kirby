#pragma once

class KirbySit : public Action
{
public:
	KirbySit(Rect* owner);
	~KirbySit();

	void Update() override;

	void Start(bool isRight) override;
};