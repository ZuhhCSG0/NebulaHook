#pragma once
#include "sdk.h"
#include "controls.h"
#include "Draw.h"
#include "Menu.h"
#include "Render.h"

#define LIST_ITEM_HEIGHT 16
#define LIST_SCROLL_WIDTH 16

MListBox::MListBox(MBaseElement* parent, std::string name, std::string caption, MCategory* SaveCategory, std::string savename, Vector sizes, Vector positions)
{
	this->parent = parent;
	this->name = name;
	this->size = sizes; //14 for font, then 2 space and 14 for slider 
	this->caption = caption;
	this->FileIdentifier = savename;
	this->FileControlType = UIControlTypes::UIC_Listbox;
	this->position = m_pMenu->MainWindow->position;
	this->position.x = m_pMenu->MainWindow->position.x + positions.x + 25;
	this->position.y += m_pMenu->MainWindow->dragYoffset + positions.y + 50;
	/*Set save parent array*/
	parent->AddChildControl(this);

	if (SaveCategory != nullptr)
		SaveCategory->SaveChildren.emplace_back(this);
}


void MListBox::OnClick()
{
	int ItemsToDraw = this->size.y / LIST_ITEM_HEIGHT;

	// Check the items
	if (items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < items.size() && drawnItems < ItemsToDraw); i++)
		{
			if (m_pMenu->MainWindow->Clicked(Vector(this->position.x + 1, this->position.y + 1 + drawnItems * 16), Vector(this->size.x - 10 - 2, 16)))
			{
				this->Selected = i;
				return;
			}
			drawnItems++;
		}
	}
}

void MListBox::OnUpdate()
{


	int ItemsToDraw = this->size.y / LIST_ITEM_HEIGHT;

	// Did we click in the scrollbar??
	if (m_pMenu->MainWindow->InBounds(Vector(this->position.x + this->size.x - 10, this->position.y + 1), Vector(8, this->size.y)) && GetAsyncKeyState(VK_LBUTTON))
	{
		// Ratio of how many visible to how many are hidden
		float ratio = float(ItemsToDraw) / float(items.size());
		POINT m;
		HWND Window = FindWindow(NULL, "Counter-Strike: Global Offensive");
		GetCursorPos(&m);
		ScreenToClient(Window, &m);
		m.y -= this->position.y;

		float sizeRatio = float(ItemsToDraw) / float(items.size());
		sizeRatio *= this->size.y;
		float heightDelta = m.y + sizeRatio - m_iHeight;
		if (heightDelta > 0)
			m.y -= heightDelta;

		float mPosRatio = float(m.y) / float(m_iHeight);
		ScrollTop = mPosRatio*items.size();
		if (ScrollTop < 0)
			ScrollTop = 0;
	}
}

void MListBox::AddChild(std::string child_name)
{
	this->items.push_back(child_name);
}

void MListBox::Draw()
{
	this->OnUpdate();
	this->OnClick();


	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;

	g_pRender->BorderedBoxOutlined(this->position.x, this->position.y, this->size.x, this->size.y + 2, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_RGBA(66, 66, 66, 255));

	if (items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < items.size() && drawnItems < ItemsToDraw); i++)
		{
			D3DCOLOR textColor = D3DCOLOR_RGBA(100, 100, 100, 255);
			RECT ItemRegion = { this->position.x + 1, this->position.y + 1 + drawnItems * 16, this->size.x - 10 - 2 , 16 };

			if (i == Selected)
			{
				textColor = D3DCOLOR_RGBA(200, 200, 200, 255);
				g_pRender->FilledBox(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, D3DCOLOR_RGBA(50, 50, 50, 200));
			}
			else if (m_pMenu->MainWindow->InBounds(Vector(ItemRegion.left, ItemRegion.top), Vector(ItemRegion.right, ItemRegion.bottom)))
			{
				textColor = D3DCOLOR_RGBA(200, 200, 200, 255);
				g_pRender->FilledBox(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, D3DCOLOR_RGBA(50, 50, 50, 150));
			}

			g_pRender->Text((char*)items[i].c_str(), ItemRegion.left + 4, ItemRegion.top + 2, lefted, g_pRender->Fonts.menu_control, false, textColor, textColor);
			drawnItems++;
		}

		// Ratio of how many visible to how many are hidden
		float sizeRatio = float(ItemsToDraw) / float(items.size());
		if (sizeRatio > 1.f) sizeRatio = 1.f;
		float posRatio = float(ScrollTop) / float(items.size());
		if (posRatio > 1.f) posRatio = 1.f;

		sizeRatio *= m_iHeight;
		posRatio *= m_iHeight;

		g_pRender->FilledBox(this->position.x + this->position.y - 10, this->size.x + posRatio, 10, sizeRatio, D3DCOLOR_RGBA(200, 200, 200, 255));
	}
}