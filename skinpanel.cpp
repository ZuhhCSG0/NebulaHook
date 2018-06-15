#include "sdk.h"
#include "controls.h"
#include "Render.h"
#include "Menu.h"

MSkinchanger* GlobalSkinchanger;


void update_callback()
{
	auto* var = g_pCvar->FindVar("cl_fullupdate");

	if (var)
		var->m_fnChangeCallbacksV1();

/*	if (g_pClientState)
		if (g_pClientState->m_nDeltaTick != -1)
			g_pClientState->m_nDeltaTick = -1;
*/
}

MSkinchanger::MSkinchanger(MBaseElement* parent)
{
	this->parent = parent;
	this->parent->AddChildControl(this);

	Skinchanger_Knife = new MDropdown(this, "knife model", "Select the knife you want", MiscElements.MiscCat, "skin_knife_model", std::vector<string>{"default", "karambit", "bayonet", "m9 bayonet", "huntsman", "gut", "falchion", "daggers", "butterfly", "flip", "bowie"});
	Skinchanger_Glove = new MDropdown(this, "glove model", "Select the glove you want", MiscElements.MiscCat, "skin_glove_model", std::vector<string>{"default", "blood hound", "hand wrap", "driver", "sport", "moto", "specialist" });
	Skinchanger_Wear = new MSlider(this, "wear", "wear value", 0, 1, false, MiscElements.MiscCat, "skin_weapon_wear");
	Skinchanger_Seed = new MSlider(this, "seed", "seed value",0, 1000,true, MiscElements.MiscCat, "skin_weapon_seed");
	Skinchanger_Apply = new MButton(this, "apply", "Apply Changes", update_callback);
}

void MSkinchanger::DrawList1()
{
	int alpha = m_pMenu->alpha;

	int rx = this->position.x + 25;
	int ry = this->position.y + 20;

	g_pRender->BorderedBox(rx, ry, 200, 300, BLACK(alpha));
	g_pRender->BorderedBox(rx + 199, ry, 6, 300,BLACK(alpha));

	static int current = 3;
	static int scrollamount = 0;
	static int scry = 0;
	static int bWasntHolding = false;
	static int bGrabbing = false;
	static int iOffsetY = 0;

	static auto& _skininfo = SkinsUtil::pSkins->GetSkinInfo();

	int i = 0;
	std::string name;
	for (auto& w : _skininfo)
	{
		if (w.first.find("glove") != std::string::npos)
			continue;
		if (w.first.find("leather") != std::string::npos)
			continue;

		int j = i - scrollamount;
		if (j > -1 && j < 21)
		{
			bool bHover = m_pMenu->MainWindow->InBounds(Vector(rx + 1, ry + 3 + (j * 14), 0), Vector(198, 14, 0));

			if (i == current)
			{
				currentWepName = w.first;
				currentWep = w.second;
				g_pRender->FilledBox(rx + 2, ry + 3 + (j * 14), 196, 14, D3DCOLOR_ARGB(alpha, 255, 0, 0));
			}
			else if (bHover)
			{
				g_pRender->FilledBox(rx + 2, ry + 3 + (j * 14), 196, 14, D3DCOLOR_ARGB(alpha, 200, 0, 0));
			}

			if (bHover && m_pMenu->MainWindow->bMouse1released && !bGrabbing)
				current = i;

			name = w.first;

			if (name.find("weapon") != std::string::npos)
				name = name.substr(7, name.length() - 7);

			if (name.find("bayonet") != std::string::npos && !(name.find("m9") != std::string::npos))
				name = "knife_bayonet";

			g_pRender->String(rx + 5, ry +3+ (j * 14), lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), "%s", name.c_str());
		}
		i++;
	}

	POINT Cur = m_pMenu->MainWindow->Cur;

	if (m_pMenu->MainWindow->InBounds(Vector(rx + 200, ry + scry + 1, 0), Vector(5, 31, 0)) && m_pMenu->MainWindow->bMouse1pressed && !bGrabbing/* && bWasntHolding*/)
	{
		bGrabbing = true;
		iOffsetY = ry + scry - Cur.y;
	}
	else if (bGrabbing && !m_pMenu->MainWindow->bMouse1pressed)
	{
		bGrabbing = false;
		iOffsetY = 0;
	}

	bWasntHolding = m_pMenu->MainWindow->InBounds(Vector(rx + 200, ry + scry + 1, 0), Vector(5, 31, 0)) && !m_pMenu->MainWindow->bMouse1pressed;

	if (bGrabbing)
	{
		scry = Cur.y + iOffsetY - ry;

		if (scry < 0)
			scry = 0;
		if (scry > 265)
			scry = 265;

		float diff = (265.f / (float(_skininfo.size()) - 25.f));
		scrollamount = scry / diff;

	}

	g_pRender->FilledBox(rx + 200, ry + scry + 2, 5, 31, D3DCOLOR_ARGB(alpha, 55, 55, 55));
}

void MSkinchanger::DrawList2()
{
	int alpha = m_pMenu->alpha;

	int rx = this->position.x + 30;
	int ry = this->position.y + 20;
	int _rx = rx + 226;

	g_pRender->BorderedBox(_rx, ry, 200, 300, BLACK(alpha));
	static int current = 3;
	static int scrollamount = 0;
	static int scry = 0;
	static int bWasntHolding = false;
	static int bGrabbing = false;
	static int iOffsetY = 0;

	static auto& _skininfo = SkinsUtil::pSkins->GetSkinInfo();
	int i = 0;
	for (auto& w : currentWep)
	{
		std::unordered_map<std::string, int>::iterator data = SkinsUtil::data.find(currentWepName);
		if (data == SkinsUtil::data.end())
			continue;

		int j = i - scrollamount;
		if (j > -1 && j < 21)
		{
			bool bHover = m_pMenu->MainWindow->InBounds(Vector(_rx + 1, ry + 3 + (j * 14), 0), Vector(138, 14, 0));

			if (w.nFallbackPaintKit == data->second)
				g_pRender->FilledBox(_rx + 2, ry + 3 + (j * 14), 196, 14, D3DCOLOR_ARGB(alpha, 255, 0, 0));
			else if(bHover)
				g_pRender->FilledBox(_rx + 2, ry + 3 + (j * 14), 196, 14, D3DCOLOR_ARGB(alpha, 200, 0, 0));
			if (bHover && m_pMenu->MainWindow->bMouse1released && !bGrabbing)
			{
				Reload = true;
				data->second = w.nFallbackPaintKit;
			}
			
			g_pRender->String(_rx + 5, ry + 3 + (j * 14), lefted, g_pRender->Fonts.menu_control, true, WHITE(alpha), "%s", w._name.c_str());
		}

		i++;
	}

	if (currentWep.size() <= 25)
	{
		iOffsetY = 0;
		return;
	}

	POINT Cur;
	HWND Window = FindWindow(NULL, "Counter-Strike: Global Offensive");
	GetCursorPos(&Cur);
	ScreenToClient(Window, &Cur);

	g_pRender->BorderedBox(_rx + 199, ry, 6, 300, BLACK(alpha));

	if (m_pMenu->MainWindow->InBounds(Vector(_rx + 200, ry + scry + 1, 0), Vector(5, 31, 0)) && m_pMenu->MainWindow->bMouse1pressed && !bGrabbing /*&& bWasntHolding*/)
	{
		bGrabbing = true;
		iOffsetY = ry + scry - Cur.y;
	}
	else if (bGrabbing && !GetAsyncKeyState(VK_LBUTTON))
	{
		bGrabbing = false;
		iOffsetY = 0;
	}

	//bWasntHolding = m_pMenu->MainWindow->InBounds(Vector(_rx + 140, ry + scry + 1, 0), Vector(9, 31, 0)) && !GetAsyncKeyState(VK_LBUTTON);

	if (bGrabbing)
	{
		scry = Cur.y + iOffsetY - ry;

		if (scry < 0)
			scry = 0;
		if (scry > 265)
			scry = 265;

		float diff = (265.f / (float(currentWep.size()) - 25.f));
		scrollamount = scry / diff;
	}

	g_pRender->FilledBox(_rx + 200, ry + scry + 2, 5, 31, D3DCOLOR_ARGB(alpha, 55, 55, 55));
}
void ForceUpdate()
{
	
	
}
void MSkinchanger::Draw()
{
//	if (!MiscElements.Misc_General_Skinchanger->Checked)
		//return;
	this->position.x = parent->position.x + 10;
	this->position.y = parent->position.y +  m_pMenu->MainWindow->dragYoffset/2;
	this->size.y = parent->size.y;
	this->size.x = parent->size.x - 15;
	static int OldKnife = 0;
	static float OldSeed = 0;
	static float OldWear = 0;
	static float OldStattrackKills = 0;
	static bool OldStattrack = false;

	if (OldKnife != Skinchanger_Knife->SelectedIndex)
	{
		Reload = true;
		OldKnife = Skinchanger_Knife->SelectedIndex;
	}
	if (OldWear != Skinchanger_Wear->value)
	{
		Reload = true;
		OldWear = Skinchanger_Wear->value;
	}
	if (OldSeed != Skinchanger_Seed->value)
	{
		Reload = true;
		OldSeed = Skinchanger_Seed->value;
	}
	

	DrawList1();
	DrawList2();

	this->position.y += 320;

	for (int i = Children.size() - 1; i >= 0 ; i--)
		Children[i]->Draw();

	
}