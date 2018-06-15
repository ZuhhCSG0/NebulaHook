#include "hooks.h"
#include "GameUtils.h"
#include "Draw.h"
#include "Menu.h"
#include "Render.h"
#include "ESP.h"
#include "Misc.h"
#include "global.h"
#include "SpoofedConvar.h"
#include "Hitmarker.h"
#include <chrono>

bool ThirdPerson = false;

bool first_frame_passed = false;
std::string sPanel = XorStr("FocusOverlayPanel");
void __fastcall Hooks::PaintTraverse(void* ecx/*thisptr*/, void* edx, unsigned int vgui_panel, bool force_repaint, bool allow_force)
{
		if (g_pEngine->IsConnected() && g_pEngine->IsInGame() && strstr(XorStr("HudZoom"), g_pPanel->GetName(vgui_panel)) && VisualElements.Visual_Misc_NoScope->Checked && G::LocalPlayer && G::LocalPlayer->IsScoped())
			return;

		panelVMT->GetOriginalMethod<PaintTraverseFn>(41)(ecx, vgui_panel, force_repaint, allow_force);

		const char* pszPanelName = g_pPanel->GetName(vgui_panel);


		if (!strstr(pszPanelName, sPanel.data()))
			return;

		int cur_height, cur_width; g_pEngine->GetScreenSize(cur_width, cur_height);

		if (!first_frame_passed || cur_width != G::Screen.width || cur_height != G::Screen.height)
		{
			first_frame_passed = true;
			g_Draw.Init();

			g_pEngine->GetScreenSize(cur_width, cur_height);
			G::Screen.height = cur_height;
			G::Screen.width = cur_width;
		}

		
		if (g_pEngine->IsInGame() && g_pEngine->IsConnected() && G::LocalPlayer)
		{
		//	static auto ThirdPerson = false;
			

			static std::string old_Skyname = "";
			static bool OldNightmode;
			static int OldSky;
			g_Misc->HandleClantag();
			ConVar* r_DrawSpecificStaticProp = nullptr;

			if (OldNightmode != VisualElements.Visual_Misc_Nightmode->Checked)
			{

				if (!r_DrawSpecificStaticProp)
					r_DrawSpecificStaticProp = g_pCvar->FindVar("r_DrawSpecificStaticProp");

				r_DrawSpecificStaticProp->SetValue(0);

				for (MaterialHandle_t i = g_pMaterialSystem->FirstMaterial(); i != g_pMaterialSystem->InvalidMaterial(); i = g_pMaterialSystem->NextMaterial(i))
				{
					IMaterial* pMaterial = g_pMaterialSystem->GetMaterial(i);

					if (!pMaterial)
						continue;

					if (strstr(pMaterial->GetTextureGroupName(), "World") || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
					{
						if (VisualElements.Visual_Misc_Nightmode->Checked)
							if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
								pMaterial->ColorModulate(0.3f, 0.3f, 0.3f);
							else
								pMaterial->ColorModulate(0.05f, 0.05f, 0.05f);
						else
							pMaterial->ColorModulate(1.0f, 1.0f, 1.0f);
					}

				}
				OldNightmode = VisualElements.Visual_Misc_Nightmode->Checked;
			}

			if (OldSky != VisualElements.Visual_Misc_Skybox->SelectedIndex)
			{
				auto LoadNamedSky = reinterpret_cast< void(__fastcall*)(const char*) >(FindPatternIDA("engine.dll", "55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45"));
				if (old_Skyname == "")
				{
					//old_Skyname = g_pCvar->FindVar("sv_skyname")->GetName();
				}

				int type = VisualElements.Visual_Misc_Skybox->SelectedIndex;

				/*if(type == 0)
				LoadNamedSky(old_Skyname.c_str());
				else */if (type == 1)
	LoadNamedSky("cs_baggage_skybox_");
				else if (type == 2)
					LoadNamedSky("cs_tibet");
				else if (type == 3)
					LoadNamedSky("italy");
				else if (type == 4)
					LoadNamedSky("jungle");
				else if (type == 5)
					LoadNamedSky("office");
				else if (type == 6)
					LoadNamedSky("sky_cs15_daylight02_hdr");
				else if (type == 7)
					LoadNamedSky("sky_csgo_night02");
				else if (type == 8)
					LoadNamedSky("vertigo");

				OldSky = VisualElements.Visual_Misc_Skybox->SelectedIndex;
			}


			std::chrono::high_resolution_clock timer;
			 auto delay = timer.now();

			 static DWORD lastpress = 0;

			if (GetAsyncKeyState(MiscElements.Misc_General_Thirdperson_Key_Bind->Key) & 1 && GetTickCount() - lastpress > 500)
			{
				tp2 = !tp2;
				lastpress = GetTickCount();
			}

			if (MiscElements.Misc_General_Thirdperson->Checked)
			{
				/*auto svcheats = g_pCvar->FindVar("sv_cheats");
				auto svcheatsspoof = new SpoofedConvar(svcheats);
				svcheatsspoof->SetInt(1);

				if (G::LocalPlayer->GetHealth() > 0)
				{
					if (!ThirdPerson && tp2)
					{
						g_pEngine->ClientCmd("thirdperson");
						ThirdPerson = true;
					}
					else if (!tp2 && ThirdPerson)
					{
						g_pEngine->ClientCmd("firstperson");
						ThirdPerson = false;
					}
				}
				else
				{
					if (ThirdPerson && !tp2)
					{
						g_pEngine->ClientCmd("firstperson");
						ThirdPerson = false;
					}
				}*/
				static Vector vecAngles;
				g_pEngine->GetViewAngles(vecAngles);

				if (g_pInput)
				{
					if (G::LocalPlayer)
					{
						if (tp2 && G::LocalPlayer->isAlive())
						{
							if (!g_pInput->m_fCameraInThirdPerson)
							{
								g_pInput->m_fCameraInThirdPerson = true;
								g_pInput->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, 120.0f);
							}
						}
						else
						{
							g_pInput->m_fCameraInThirdPerson = false;
							g_pInput->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, 0);
						}
					}
				}

			}
			/*else if (ThirdPerson)
			{
				ThirdPerson = false;
				g_pEngine->ClientCmd("firstperson");
			}*/

			if (VisualElements.Visual_Misc_NoScope->Checked)
			{
				g_ESP->DrawScope(G::LocalPlayer);
				auto postprocessing = g_pCvar->FindVar("mat_postprocess_enable");
				auto postprocessingspoof = new SpoofedConvar(postprocessing);
				postprocessingspoof->SetInt(0);
			
			}

			//use that for endscene rendering -> bad tho, really bad xD
			//g_ESP->Update();
			g_ESP->Loop();
			//somewhy fixes endscene rendering
			g_Draw.Box(0, 0, 0, 0, 255, 255, 255, 255);

			/*lby anzeige*/
			if (G::LocalPlayer->GetHealth() > 0)
			{
				if (G::LocalPlayer->GetFlags() & FL_ONGROUND && G::LocalPlayer->GetVelocity().Length2D() > 0.1)
					G::lby_update_end_time = g_pGlobals->curtime;

				if (G::lby_update_end_time < g_pGlobals->curtime)
					g_Draw.StringA(g_Draw.font_build, false, 10, G::Screen.height - 80, 0, 255, 0, 255, "%s", "LBY");
				else
					g_Draw.StringA(g_Draw.font_build, false, 10, G::Screen.height - 80, 255, 0, 0, 255, "%s", "LBY");
			}
		}
}