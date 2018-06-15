#include "sdk.h"
#include "controls.h"
#include "Render.h"
#include "Menu.h"

MButton::MButton(MBaseElement* parent, std::string name, std::string caption,ButtonCallback_t Function)
{
	this->name = name;
	this->caption = caption;
	this->parent = parent;
	this->CallBack = Function;

	parent->AddChildControl(this);
}

void MButton::Draw()
{
	this->position = this->parent->position;
	this->position.y += 10;
	this->position.x += 30;

	for (int i = 0; i < this->parent->Children.size(); i++)
		if (this->parent->Children.at(i) != (MBaseElement*)this)
		{
			this->position.y += this->parent->Children.at(i)->size.y + 10; //boxes are 15 px big, that means 5 difference is natural
		}
		else
			break;

	this->size.y = 30;
	this->size.x = parent->size.x - 50;

	bool bHover = m_pMenu->MainWindow->InBounds(position, size);


	g_pRender->GradientBox(position.x , position.y , size.x , size.y , D3DCOLOR_RGBA(34, 34, 34, 255), D3DCOLOR_RGBA(26, 26, 26, 255), false);


	if (m_pMenu->MainWindow->bMouse1pressed && bHover)
		g_pRender->FilledBox(position.x , position.y , size.x , size.y , D3DCOLOR_RGBA(50, 50, 50, 255));
	else if (bHover)
		g_pRender->FilledBox(position.x , position.y , size.x , size.y , D3DCOLOR_RGBA(50, 50, 50, 255));

	g_pRender->String(position.x + size.x / 2, position.y + size.y / 4 + 1, centered, g_pRender->Fonts.menu_control, false, D3DCOLOR_RGBA(200, 200, 200, 255), "%s", name.c_str());


	g_pRender->BorderedBoxOutlined(position.x, position.y, size.x, size.y, 1, D3DCOLOR_RGBA(0, 0, 0, 255), 1);
	g_pRender->BorderedBoxOutlined(position.x + 1, position.y + 1, size.x - 2, size.y - 2, 1, D3DCOLOR_RGBA(35, 35, 35, 255), 1);

	if (bHover && m_pMenu->MainWindow->bMouse1released)
		if (CallBack)
			CallBack();
}