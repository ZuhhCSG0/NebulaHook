#pragma once
typedef void(*ButtonCallback_t)(void);

class MButton : public MBaseElement
{
public:

	ButtonCallback_t CallBack;
	MButton() {}
	Vector pos;
	MBaseElement* parent;
	void* Function;
	MButton::MButton(MBaseElement* parent, std::string name, std::string caption, ButtonCallback_t Function);
	virtual void Draw() override;
};