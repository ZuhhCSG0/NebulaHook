#include "sdk.h"
#include "controls.h"
#include "Menu.h"
#include "Render.h"
MDropdown::MDropdown(MBaseElement* parent, std::string name, std::string caption, MCategory* SaveCategory, std::string savename, std::vector<string> Items)
{
	this->parent = parent;
	this->name = name;
	this->size = Vector(parent->size.x - 20, 31);
	this->caption = caption;
	this->FileIdentifier = savename;
	this->FileControlType = UIControlTypes::UIC_DropDown;
	this->Items = Items;

	/*Set save parent array*/


	parent->AddChildControl(this);


	if (SaveCategory != nullptr)
		SaveCategory->SaveChildren.emplace_back(this);
}

void Polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = g_pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
	unsigned char buffer[4] = { 255, 255, 255, 255 };//{ color.r(), color.g(), color.b(), color.a() };

	g_pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
	g_pSurface->SetDrawColor(color); // keep this full color and opacity use the RGBA @top to set values.
	g_pSurface->DrawSetTexture(Texture); // bind texture

	g_pSurface->DrawTexturedPolygon(count, Vertexs);
}

#include <chrono>

bool Holding(int iXStart, int iYStart, int iXEnd, int iYEnd)
{
	if (GetAsyncKeyState(VK_LBUTTON))
		if (m_pMenu->MainWindow->InBounds(Vector(iXStart, iYStart), Vector(iXEnd, iYEnd)))
			return true;

	return false;
}


bool m_bActiveComboBox = false;
void MDropdown::Draw()
{

	static std::chrono::high_resolution_clock timer;
	static auto delay = timer.now();

	this->position = this->parent->position;
	this->position.x += 30;
	this->position.y += 10;

	this->size.x = parent->size.x - 50;


	MTab* pTab = (MTab*)parent;


	for (int i = 0; i < this->parent->Children.size(); i++)
		if (this->parent->Children.at(i) != (MBaseElement*)this)
		{
			this->position.y += this->parent->Children.at(i)->size.y + 10; //boxes are 15 px big, that means 5 difference is natural
		}
		else
			break;


	auto nSize = Items.size();

	int alpha = m_pMenu->alpha;




	g_pRender->Text((char*)name.c_str(), position.x + 0.5, position.y - 1, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

	int bar_height = 18;
	int y_pos = this->position.y + 12;
	int width = this->size.x;

	bool bHovering = m_pMenu->MainWindow->InBounds(Vector(position.x, y_pos), Vector(width, bar_height));
	if (m_pMenu->MainWindow->BlockInput && m_pMenu->MainWindow->BlockingElement != (MBaseElement*)this)
		bHovering = false;



	if (!m_pMenu->MainWindow->BlockInput || m_pMenu->MainWindow->BlockInput && m_pMenu->MainWindow->BlockingElement == this)
	{
		if (m_pMenu->MainWindow->Clicked(Vector(position.x, y_pos), Vector(width, bar_height)) && !holding && ((timer.now() - delay) > std::chrono::milliseconds(400)))
		{
			IsOpen = !IsOpen;
			holding = true;
			delay = timer.now();
		}
		else if (!Holding(position.x, y_pos, width, bar_height))
		{
			holding = false;
		}
	}
	/*
	if ((m_pMenu->MainWindow->Clicked(Vector(position.x, y_pos), Vector(width, bar_height))) && ((timer.now() - delay) > std::chrono::milliseconds(500)))
	{
	IsOpen = !IsOpen;
	m_bActiveComboBox = !m_bActiveComboBox;
	m_pMenu->MainWindow->BlockInput = false;
	m_pMenu->MainWindow->BlockingElement = nullptr;
	delay = timer.now();
	}*/

	//if (IsOpen)

	if (bHovering || IsOpen)
		g_pRender->FilledBoxOutlined(this->position.x, y_pos, width, bar_height, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	else
		g_pRender->GradientBoxOutlined(this->position.x, y_pos, width, bar_height, 1, D3DCOLOR_ARGB(alpha, 45, 45, 45), D3DCOLOR_ARGB(alpha, 25, 25, 25), BLACK(alpha), true);



	//if (bHovering)
	//g_Draw.StringA(g_Draw.font_menu, true, m_pMenu->MainWindow->position.x + m_pMenu->MainWindow->width / 2, m_pMenu->MainWindow->position.y + m_pMenu->MainWindow->size.y + m_pMenu->MainWindow->dragYoffset + m_pMenu->MainWindow->dragYoffset / 2-6, m_pMenu->MainWindow->ActiveFontColor.r(), m_pMenu->MainWindow->ActiveFontColor.g(), m_pMenu->MainWindow->ActiveFontColor.b(), m_pMenu->MainWindow->ActiveFontColor.a(), "%s", this->caption.c_str());



	if (Items.size() > 0)
	{
		if (IsOpen)
		{
		//	m_bActiveComboBox = true;

			m_pMenu->MainWindow->BlockInput = true;
			m_pMenu->MainWindow->BlockingElement = this;
			auto Y = y_pos + bar_height;


			for (int i = 0; i < Items.size(); i++)
			{
				auto bHover = m_pMenu->MainWindow->InBounds(Vector(position.x, Y + i*bar_height), Vector(size.x, bar_height));

				g_pRender->FilledBox(position.x, Y + i*bar_height, width, bar_height, D3DCOLOR_ARGB(alpha, 35, 35, 35));

				//	if (bHover)
				//		g_pRender->Text((char*)Items[i].c_str(), position.x + 10, Y + i*bar_height, text_alignment::lefted, g_pRender->Fonts.menu_control, true, D3DCOLOR_ARGB(255, 255, 0, 0), BLACK(alpha));
				//	else
				//	g_pRender->FilledBox(position.x, Y + i*bar_height, width, bar_height, D3DCOLOR_ARGB(alpha, 35, 35, 35));

				if (bHover)
					g_pRender->Text((char*)Items[i].c_str(), position.x + 10, Y + i*bar_height + bar_height / 2 - g_pRender->menu_control_size / 2, text_alignment::lefted, g_pRender->Fonts.menu_control, true, D3DCOLOR_ARGB(255, 255, 0, 0), BLACK(alpha));
				else
					g_pRender->Text((char*)Items[i].c_str(), position.x + 10, Y + i*bar_height + bar_height / 2 - g_pRender->menu_control_size / 2, text_alignment::lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

				if (bHover && m_pMenu->MainWindow->bMouse1released)
				{
					m_pMenu->MainWindow->BlockInput = false;
					m_pMenu->MainWindow->BlockingElement = nullptr;
				//	m_bActiveComboBox = false;
					IsOpen = false;
					SelectedIndex = i;
				}

				if (m_pMenu->MainWindow->bMouse1pressed && !m_pMenu->MainWindow->InBounds(Vector(position.x, Y), Vector(width, bar_height * Items.size())))
				{
					IsOpen = false;
					//m_bActiveComboBox = false;
					m_pMenu->MainWindow->BlockInput = false;
					m_pMenu->MainWindow->BlockingElement = nullptr;
				}

			}
			g_pRender->BorderedBox(this->position.x, Y, width, bar_height*nSize, BLACK(alpha));
		}
	}



	Vertex_t Verts2[3];
	Verts2[0].m_Position.x = position.x + this->size.x - 10;
	Verts2[0].m_Position.y = this->position.y + 21;
	Verts2[1].m_Position.x = position.x + this->size.x - 5;
	Verts2[1].m_Position.y = this->position.y + 21;
	Verts2[2].m_Position.x = position.x + this->size.x - 7.5;
	Verts2[2].m_Position.y = this->position.y + 24;

	g_pRender->FillARGBTriangle(Verts2[0].m_Position.x, Verts2[0].m_Position.y, Verts2[1].m_Position.x, Verts2[1].m_Position.y, Verts2[2].m_Position.x, Verts2[2].m_Position.y, D3DCOLOR_RGBA(200, 200, 200, 255));

	if (this->SelectedIndex >= 0 && this->SelectedIndex < Items.size())
		g_pRender->Text((char*)Items[this->SelectedIndex].c_str(), position.x + 10, y_pos + bar_height / 2 - g_pRender->menu_control_size / 2, text_alignment::lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

}