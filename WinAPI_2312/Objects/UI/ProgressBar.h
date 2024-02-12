#pragma once

class ProgressBar : public Image
{
public:
	ProgressBar(Texture* frontTexture, Texture* backTexture = nullptr);
	~ProgressBar();

	void Render(HDC hdc);

	void SetValue(const float& value) { this->value = value; }
private:	
	Texture* backTexture;

	float value;
};