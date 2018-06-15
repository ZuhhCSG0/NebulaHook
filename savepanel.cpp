#include "sdk.h"
#include "controls.h"
#include "dirent.h"
#include "Render.h"
#include "Menu.h"
char* KeyStringsSave[254] = { "Not Bound", "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };


char* KeyDigitss[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
char* KeyDigitsss[254] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
"y", "z", nullptr, nullptr, nullptr, nullptr, nullptr, "0", "1", "2", "3", "4", "5", "6",
"7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

void MSavePanel::HandleKeys(int key)
{



	switch (key)
	{
	case VK_LSHIFT:
	case VK_RSHIFT:
	case VK_LCONTROL:
	case VK_RCONTROL:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_CAPITAL:
	case VK_LBUTTON:
	case VK_RBUTTON:
		return;


	case VK_RETURN:
	case VK_ESCAPE:
		textboxactive = false;
		return;

	case VK_SPACE:
		command.append(" ");
		return;

	case VK_BACK:
		if (command.length() > 0)
		{
			command.erase(command.length() - 1);
			return;
		}


	default:

		if (GetAsyncKeyState(VK_SHIFT) && KeyDigitss[key] != nullptr)
		{
			char* KeyName = KeyDigitss[key];

			if (KeyName != "Backspace" && KeyName != "CTRL" && KeyName != "ALT")
				command.append(KeyName);

			return;
		}
		else if (KeyDigitsss[key] != nullptr)
		{
			char* KeyName = KeyDigitsss[key];

			if (KeyName != "Backspace" && KeyName != "CTRL" && KeyName != "ALT")
				command.append(KeyName);

			return;
		}
	}
}
MSavePanel::MSavePanel(MBaseElement* parent)
{
	this->parent = parent;
	this->parent->AddChildControl(this);
}
char* stringToLower(char *string)
{
	int i;
	int len = strlen(string);
	for (i = 0; i<len; i++) {
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] += 32;
		}
	}
	return string;
}


bool bIsDigitInString(std::string pszString)
{
	for (int ax = 0; ax < 9; ax++)
	{
		char buf[MAX_PATH];

		_snprintf_s(buf, (size_t)255, "%d", ax);

		if (strstr(pszString.c_str(), buf))
		{
			return true;
		}
	}
	return false;
}

void MSavePanel::Draw()
{
	static std::string strPath, BasePath;
	static bool doOnce = true;
	if (doOnce)
	{
		char* szPath = new char[255];
		GetModuleFileNameA(GetModuleHandle(NULL), szPath, 255);
		for (int i = strlen(szPath); i > 0; i--)
		{
			if (szPath[i] == '\\')
			{
				szPath[i + 1] = 0;
				break;
			}
		}

		strPath = szPath;
		delete[] szPath;
		BasePath = strPath;
		doOnce = false;

	}
	int alpha = m_pMenu->alpha;
	//this->position = m_pMenu->MainWindow->position;
	//this->position.x += 10;
	//this->position.y += m_pMenu->MainWindow->dragYoffset + 10;
	//this->size.x = (m_pMenu->MainWindow->size.x - 20) / 2; //left, right and middle shit offsets
	this->position = this->parent->position;
	this->position.x += 10;
	this->position.y += 10;
	this->size.y = this->parent->size.y - 20;
	
	


	/*textbox*/
	int textbox_x = position.x;
	int textbox_y = position.y + size.y - 20 * 3 - 10 - 70;
	int textbox_h = 20;
	int textbox_w = 150;
	bool bTexthover = m_pMenu->MainWindow->InBounds(Vector(textbox_x, textbox_y, 0), Vector(textbox_w, textbox_h, 0));

	if (!this->textboxactive && bTexthover && m_pMenu->MainWindow->bMouse1released)
	{

		this->textboxactive = !this->textboxactive;
	}

	
	if (textboxactive)
		g_pRender->FilledBoxOutlined(textbox_x , textbox_y , textbox_w, textbox_h, D3DCOLOR_ARGB(alpha, 55, 55, 55), BLACK(alpha));
	else if (bTexthover)
		g_pRender->FilledBoxOutlined(textbox_x , textbox_y, textbox_w, textbox_h , D3DCOLOR_ARGB(alpha, 45, 45, 45), BLACK(alpha));
	else
		g_pRender->FilledBoxOutlined(textbox_x, textbox_y, textbox_w, textbox_h, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	if (this->textboxactive)
	{
		for (int i = 0; i < 255; i++)
		{
			if (m_pMenu->MainWindow->GetKeyPress(i))
			{
				HandleKeys(i);
			}
		}
		if (m_pMenu->MainWindow->bMouse1pressed && !m_pMenu->MainWindow->InBounds(Vector(textbox_x, textbox_y, 0), Vector(textbox_w, textbox_h, 0)))
		{
			this->textboxactive = false;
		}
	}

	auto textsize = g_pRender->GetTextWidth(command.c_str(), g_pRender->Fonts.menu_control);

	if (textboxactive)
	{
		g_pRender->Text("_", textbox_x + 6 + textsize , textbox_y + textbox_h / 2 - g_pRender->menu_control_size / 2, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	}

	if (command.empty() && !(bTexthover && m_pMenu->MainWindow->bMouse1pressed) && !textboxactive)
		g_pRender->Text("", textbox_x + 5, textbox_y + textbox_h / 2 - g_pRender->menu_control_size / 2, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	
	g_pRender->Text((char*)command.c_str(), textbox_x + 5, textbox_y +textbox_h/2 - g_pRender->menu_control_size/2, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	/*end textbox*/

	/*save button*/
	int save_new_button_x = position.x;
	int save_new_button_h = 20;
	int save_new_button_y = position.y + size.y - save_new_button_h * 3 - 10 - 40;
	int save_new_button_w = 150;
	bool save_new_button_hover = m_pMenu->MainWindow->InBounds(Vector(save_new_button_x, save_new_button_y, 0), Vector(save_new_button_w, save_new_button_h, 0));

	if (save_new_button_hover && m_pMenu->MainWindow->bMouse1pressed)
		g_pRender->FilledBoxOutlined(save_new_button_x, save_new_button_y, save_new_button_w, save_new_button_h, D3DCOLOR_ARGB(alpha, 55, 55, 55), BLACK(alpha));
	else if (save_new_button_hover)
		g_pRender->FilledBoxOutlined(save_new_button_x, save_new_button_y, save_new_button_w, save_new_button_h, D3DCOLOR_ARGB(alpha, 45, 45, 45), BLACK(alpha));
	else
		g_pRender->FilledBoxOutlined(save_new_button_x, save_new_button_y, save_new_button_w, save_new_button_h, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	
	g_pRender->Text("add new config", save_new_button_x + save_new_button_w/2, save_new_button_y + save_new_button_h/2 - g_pRender->menu_control_size/2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

	if (!this->textboxactive && save_new_button_hover && m_pMenu->MainWindow->bMouse1released)
	{
		m_pMenu->SaveWindowState(command);
		command.clear();
	}
	/*end save button*/

	
	/*config list getting*/
	strPath = BasePath;
	std::vector<string> ConfigList;
	DIR *pDIR;
	struct dirent *entry;
	std::string buffer;
	if (pDIR = opendir(strPath.c_str())) 
	{
		while (entry = readdir(pDIR))
		{
			
			if (strstr(entry->d_name, ".xml"))
			{
				buffer = entry->d_name;
				if (!buffer.find("_walkbot") != std::string::npos)
				{
					string str2 = buffer.substr(0, buffer.length() - 4);
					ConfigList.push_back(str2);
				}

			}
		}
		closedir(pDIR);
	}
	/*end config list getting*/
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	/*config list*/
	int list_x = position.x + 180;
	int list_y = position.y;
	int list_y2 = position.y + 10;
	int list_w = 200;
	int list_item_h = 15;
	for (int i = 0; i < ConfigList.size(); i++)
	{
		if (m_pMenu->MainWindow->bMouse1pressed && m_pMenu->MainWindow->InBounds(Vector(list_x, list_y2 + list_item_h * i, 0), Vector(list_w,list_item_h, 0)))
		{
			this->SelectIndex = i;
		}

		if (i == this->SelectIndex)
			g_pRender->FilledBox(list_x + 1, list_y2 + list_item_h * i, list_w - 2, list_item_h, D3DCOLOR_ARGB(alpha, 55, 55, 55));
		else
		{
			if (m_pMenu->MainWindow->InBounds(Vector(list_x, list_y + list_item_h * i, 0), Vector(200, 20, 0)))
				g_pRender->FilledBox(list_x + 1, list_y2 + list_item_h * i, list_w - 2, list_item_h, D3DCOLOR_ARGB(alpha, 45, 45, 45));
		}


		g_pRender->Text((char*)ConfigList.at(i).c_str(), list_x + 5, list_y2 + list_item_h * i + list_item_h / 2 - g_pRender->menu_control_size / 2, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	}

	g_pRender->BorderBoxOutlinedText2(list_x, list_y, list_w, list_item_h * 19 - 5, 1, BLACK(alpha), D3DCOLOR_RGBA(50, 50, 50, 255), "config list", g_pRender->Fonts.menu_control);
	g_pRender->BorderBoxOutlinedText(list_x + 1, list_y + 1, list_w - 2, list_item_h * 19 - 5 - 2, 1, BLACK(alpha), BLACK(alpha), "config list", g_pRender->Fonts.menu_control);
	/*end config list*/

	/*current config*/

	//g_pRender->Text((char*)current_config.c_str(), position.x, position.y + size.y / 2 - g_pRender->menu_control_size, lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

	/*end current config*/





	/*save button*/
	int save_button_w = 150;
	int save_button_h = 20;
	int save_button_x = position.x;
	int save_button_y = position.y + size.y - save_button_h*3 - 10 - 10 ;

	bool save_button_hover = m_pMenu->MainWindow->InBounds(Vector(save_button_x, save_button_y, 0), Vector(save_button_w, save_button_h, 0));



	if (save_button_hover && m_pMenu->MainWindow->bMouse1pressed)
		g_pRender->FilledBoxOutlined(save_button_x, save_button_y, save_button_w, save_button_h, D3DCOLOR_ARGB(alpha, 55, 55, 55), BLACK(alpha));
	else if (save_button_hover)
		g_pRender->FilledBoxOutlined(save_button_x, save_button_y, save_button_w, save_button_h, D3DCOLOR_ARGB(alpha, 45, 45, 45), BLACK(alpha));
	else
		g_pRender->FilledBoxOutlined(save_button_x, save_button_y, save_button_w, save_button_h, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	g_pRender->Text("save", save_button_x + save_button_w / 2, save_button_y + save_button_h / 2 - g_pRender->menu_control_size / 2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	if (save_button_hover && m_pMenu->MainWindow->bMouse1released)
	{
		m_pMenu->SaveWindowState(ConfigList.at(this->SelectIndex));
	}
	/*end save button*/
	/*load button*/
	int load_button_w = 150;
	int load_button_h = 20;
	int load_button_x = position.x;
	int load_button_y = position.y + size.y - load_button_h*2 - 10 ;

	bool load_button_button_hover = m_pMenu->MainWindow->InBounds(Vector(load_button_x, load_button_y, 0), Vector(load_button_w, load_button_h, 0));



	if (load_button_button_hover && m_pMenu->MainWindow->bMouse1pressed)
		g_pRender->FilledBoxOutlined(load_button_x, load_button_y, load_button_w, load_button_h, D3DCOLOR_ARGB(alpha, 55, 55, 55), BLACK(alpha));
	else if (load_button_button_hover)
		g_pRender->FilledBoxOutlined(load_button_x, load_button_y, load_button_w, load_button_h, D3DCOLOR_ARGB(alpha, 45, 45, 45), BLACK(alpha));
	else
		g_pRender->FilledBoxOutlined(load_button_x, load_button_y, load_button_w, load_button_h, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	g_pRender->Text("load", load_button_x + load_button_w / 2, load_button_y + load_button_h / 2 - g_pRender->menu_control_size / 2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	if (load_button_button_hover && m_pMenu->MainWindow->bMouse1released)
	{
		m_pMenu->LoadWindowState(ConfigList.at(this->SelectIndex));
		current_config = ConfigList.at(this->SelectIndex);
	}
	/*end load button*/
	/*delete button*/
	int delete_w = 150;
	int delete_h = 20;
	int delete_x = position.x;
	int delete_y = position.y + size.y - delete_h;

	bool delete_button_hover = m_pMenu->MainWindow->InBounds(Vector(delete_x, delete_y, 0), Vector(delete_w, delete_h, 0));



	if (delete_button_hover && m_pMenu->MainWindow->bMouse1pressed)
		g_pRender->FilledBoxOutlined(delete_x, delete_y, delete_w, delete_h, D3DCOLOR_ARGB(alpha, 55, 55, 55), BLACK(alpha));
	else if (delete_button_hover)
		g_pRender->FilledBoxOutlined(delete_x, delete_y, delete_w, delete_h, D3DCOLOR_ARGB(alpha, 45, 45, 45), BLACK(alpha));
	else
		g_pRender->FilledBoxOutlined(delete_x, delete_y, delete_w, delete_h, D3DCOLOR_ARGB(alpha, 35, 35, 35), BLACK(alpha));
	g_pRender->Text("delete", delete_x + delete_w / 2, delete_y + delete_h / 2 - g_pRender->menu_control_size / 2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	
	if (delete_button_hover && m_pMenu->MainWindow->bMouse1released)
	{
		if (SelectIndex != -1)
		{
			std::string buf = strPath;
			buf.append("\\");
			buf.append(ConfigList.at(this->SelectIndex));
			buf.append(".xml");

			DeleteFileA(buf.c_str());
		}
	}
}