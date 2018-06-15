#pragma once
class MSlider : public MBaseElement
{
public:
	MSlider() {}
	
	bool bActive;
	MBaseElement* parent;
	float min, max, value;
	bool round;
	int width;
	bool percentage;
	bool degrees;
	MSlider(MBaseElement* parent, std::string name, std::string caption, float min, float max, bool round, MCategory* SaveCategory, std::string savename, bool percent = false, bool degrees = false);
	virtual void Draw() override;
};