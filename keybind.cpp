#include "sdk.h"
#include "controls.h"
#include "Render.h"
#include "Menu.h"
char* KeyStrings[254] = { "not bound", "left mouse", "right mouse", "control+break", "middle mouse", "mouse 4", "mouse 5",
nullptr, "backspace", "tab", nullptr, nullptr, nullptr, "enter", nullptr, nullptr, "shift", "ctrl", "alt", "pause",
"caps lock", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "esc", nullptr, nullptr, nullptr, nullptr, "spacebar",
"pg up", "pg down", "end", "home", "left", "up", "right", "down", nullptr, "print", nullptr, "print screen", "insert",
"delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
"y", "z", "left windows", "right windows", nullptr, nullptr, nullptr, "num 0", "num 1", "num 2", "num 3", "num 4", "num 5", "num 6",
"num 7", "num 8", "num 9", "*", "+", "_", "-", ".", "/", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12",
"f13", "f14", "f15", "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "num lock", "scroll lock", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "lshift", "rshift", "lcontrol", "rcontrol", "lmenu", "rmenu", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "next track", "previous track", "stop", "play/pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

MKeybind::MKeybind(MBaseElement* parent, std::string name, std::string caption, MCategory* SaveCategory, string savename)
{
	this->parent = parent;
	this->name = name;
	this->caption = caption;
	this->FileIdentifier = savename;
	this->FileControlType = UIControlTypes::UIC_KeyBind;
	/*Set save parent array*/
	parent->AddChildControl(this);
	SaveCategory->SaveChildren.push_back(this);
}
void MKeybind::Draw()
{
	this->position = this->parent->position;
	this->position.x += 30;
	this->position.y += 10;

	this->size.x = parent->size.x - 50;
	this->size.y = 18;


	for (int i = 0; i < this->parent->Children.size(); i++)
		if (this->parent->Children.at(i) != (MBaseElement*)this)
		{
			this->position.y += this->parent->Children.at(i)->size.y + 10; //boxes are 15 px big, that means 5 difference is natural
		}
		else
			break;

	bool bHovering = false;




	char* KeyName = "";


	if (!m_pMenu->MainWindow->BlockInput)
	{
		bHovering = m_pMenu->MainWindow->InBounds(position, size);
		if (bHovering && m_pMenu->MainWindow->bMouse1released)
			IsGettingKey = true;
	}
	int alpha = m_pMenu->alpha;


	if (IsGettingKey || bHovering)
		g_pRender->FilledBoxOutlined(this->position.x, this->position.y + 10, this->size.x, this->size.y, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	else
		g_pRender->GradientBoxOutlined(this->position.x, this->position.y + 10, this->size.x, this->size.y, 1, D3DCOLOR_ARGB(alpha, 45, 45, 45), D3DCOLOR_ARGB(alpha, 25, 25, 25), BLACK(alpha), true);

	if (IsGettingKey)
	{
		KeyName = "press a key";
		for (int i = 0; i < 255; i++)
		{
			if (m_pMenu->MainWindow->ToggleButton(i))
			{
				if (i == VK_ESCAPE)
				{
					IsGettingKey = false;
					Key = -1;
					return;
				}

				Key = i;
				IsGettingKey = false;
				return;
			}
		}
	}
	else
	{
		if (Key >= 0)
		{
			KeyName = KeyStrings[Key];
		}
	}

	char buf[256];
	sprintf_s(buf, "%s", KeyName);


	g_pRender->Text((char*)name.c_str(), position.x, position.y - 1, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

	if (IsGettingKey)
		g_pRender->Text(buf, position.x + 5, position.y + 10 + size.y / 2 - g_pRender->menu_control_size / 2, lefted, g_pRender->Fonts.menu_control, true, RED(alpha), BLACK(alpha));
	else
		g_pRender->Text(buf, position.x + 5, position.y + 10 + size.y / 2 - g_pRender->menu_control_size / 2, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
}