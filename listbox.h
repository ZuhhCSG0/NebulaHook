#pragma once
class MListBox : public MBaseElement
{
public:
	MListBox() {}

	bool bActive;
	MBaseElement* parent;
	float min, max, value;
	bool round;
	int width;
	bool percentage;
	bool degrees;
	std::vector<std::string> items;
	void AddChild(std::string child_name);
	void OnClick();
	void OnUpdate();
	MListBox(MBaseElement* parent, std::string name, std::string caption, MCategory* SaveCategory, std::string savename, Vector sizes, Vector positions);
	virtual void Draw() override;
	int ScrollTop;
	int Selected;
	int m_iHeight;
	void SetHeight();
};