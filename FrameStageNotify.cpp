#include "hooks.h"
#include "global.h"
#include "Menu.h"
#include "BacktrackingHelper.h"
#include "Resolver.h"
#include "xor.h"
#include "skinchanger.h"
#include <intrin.h>

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF



int get_model_index(int item_def_index)
{
	int ret = 0;
	switch (item_def_index)
	{
	case KNIFE:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
		break;
	case KNIFE_T:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		break;
	case KNIFE_KARAMBIT:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
		break;
	case KNIFE_BAYONET:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
		break;
	case KNIFE_M9_BAYONET:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
		break;
	case KNIFE_TACTICAL:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
		break;
	case KNIFE_GUT:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
		break;
	case KNIFE_FALCHION:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
		break;
	case KNIFE_PUSH:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
		break;
	case KNIFE_BUTTERFLY:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
		break;
	case KNIFE_FLIP:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
		break;
	case KNIFE_BOWIE:
		ret = g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
		break;
	default:
		break;
	}
	return ret;
}

std::vector<const char*> smoke_materials = {
	//"effects/overlaysmoke",
	"particle/beam_smoke_01",
	"particle/particle_smokegrenade",
	"particle/particle_smokegrenade1",
	"particle/particle_smokegrenade2",
	"particle/particle_smokegrenade3",
	"particle/particle_smokegrenade_sc",
	"particle/smoke1/smoke1",
	"particle/smoke1/smoke1_ash",
	"particle/smoke1/smoke1_nearcull",
	"particle/smoke1/smoke1_nearcull2",
	"particle/smoke1/smoke1_snow",
	"particle/smokesprites_0001",
	"particle/smokestack",
	"particle/vistasmokev1/vistasmokev1",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_nearcull",
	"particle/vistasmokev1/vistasmokev1_nearcull_fog",
	"particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev4_emods_nocull",
	"particle/vistasmokev1/vistasmokev4_nearcull",
	"particle/vistasmokev1/vistasmokev4_nocull"
};

void DrawBeam(Vector src, Vector end, Color color)
{
	BeamInfo_t beamInfo;
	beamInfo.m_nType = TE_BEAMPOINTS;
	beamInfo.m_pszModelName = "sprites/physbeam.vmt";
	beamInfo.m_nModelIndex = -1; // will be set by CreateBeamPoints if its -1
	beamInfo.m_flHaloScale = 0.0f;
	beamInfo.m_flLife = 1.0f;
	beamInfo.m_flWidth = 1.0f;
	beamInfo.m_flEndWidth = 1.0f;
	beamInfo.m_flFadeLength = 0.0f;
	beamInfo.m_flAmplitude = 2.0f;
	beamInfo.m_flBrightness = color.a();
	beamInfo.m_flSpeed = 0.2f;
	beamInfo.m_nStartFrame = 0;
	beamInfo.m_flFrameRate = 0.f;
	beamInfo.m_flRed = color.r();
	beamInfo.m_flGreen = color.g();
	beamInfo.m_flBlue = color.b();
	beamInfo.m_nSegments = 2;
	beamInfo.m_bRenderable = true;
	beamInfo.m_nFlags = 0;

	beamInfo.m_vecStart = src;
	beamInfo.m_vecEnd = end;

	Beam_t* myBeam = g_pViewRenderBeams->CreateBeamPoints(beamInfo);

	if (myBeam)
		g_pViewRenderBeams->DrawBeam(myBeam);
}


void __stdcall Hooks::FrameStageNotify(ClientFrameStage_t curStage)
{
	

		if (!G::LocalPlayer || !g_pEngine->IsConnected() || !g_pEngine->IsInGame())
			return;

		

		static Vector oldViewPunch;
		static Vector oldAimPunch;


		Vector* view_punch = G::LocalPlayer->GetViewPunchPtr();
		Vector* aim_punch = G::LocalPlayer->GetPunchAnglePtr();

		auto b_IsThirdPerson = g_pInput->m_fCameraInThirdPerson;//*reinterpret_cast<bool*>(reinterpret_cast<DWORD>(g_pInput) + 0xA5);//A5
		G::InThirdperson = b_IsThirdPerson;

		if (curStage == FRAME_RENDER_START && G::LocalPlayer->GetHealth() > 0)
		{
			if (g_pInput && g_pInput->m_fCameraInThirdPerson)
			{
				Utilities::Log("thirdperson");
				*reinterpret_cast<QAngle*>(reinterpret_cast<DWORD>(G::LocalPlayer + 0x31C8)) = G::AAAngle; //to visualize real/faked aa angles
			}
			else 
			{
				if (view_punch && aim_punch && VisualElements.Visual_Misc_NoRecoil->Checked)
				{
					oldViewPunch = *view_punch;
					oldAimPunch = *aim_punch;

					view_punch->Init();
					aim_punch->Init();
				}
			}

		

			for (int i = 1; i < g_pGlobals->maxClients; i++)
			{
				if (i == g_pEngine->GetLocalPlayer())
					continue;
				CBaseEntity* pEntity = g_pEntitylist->GetClientEntity(i);
				if (pEntity && pEntity->GetHealth() > 0)
				{
					if (pEntity->IsDormant())
						continue;

					g_resolver->Store(pEntity);
				}
			}
		}

		
	

		if (curStage == FRAME_NET_UPDATE_START)
		{
			if (VisualElements.Visual_Misc_Beams->Checked)
			{
				for (unsigned int i = 0; i < trace_logs.size(); i++) {

					auto *shooter = g_pEntitylist->GetClientEntity(g_pEngine->GetPlayerForUserID(trace_logs[i].userid));
					if (!shooter) return;

					Color color;
					if (shooter->GetTeamNum() == 3)
						color = Color(255, 0, 255, 255);
					else
						color = Color(255, 255, 0, 255);

					DrawBeam(trace_logs[i].start, trace_logs[i].position, color);

					trace_logs.erase(trace_logs.begin() + i);
				}
			}
				

			static bool oldEnable = false;
			if (oldEnable != VisualElements.Visual_Misc_NoSmoke->Checked) {
				for (auto material_name : smoke_materials) {
					IMaterial* mat = g_pMaterialSystem->FindMaterial(material_name, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, VisualElements.Visual_Misc_NoSmoke->Checked ? true : false);
				}

				oldEnable = VisualElements.Visual_Misc_NoSmoke->Checked;
			}

			if (VisualElements.Visual_Misc_NoSmoke->Checked) {
				static int* smokecount = *(int**)(Utilities::Memory::FindPatternIDA("client.dll", "A3 ? ? ? ? 57 8B CB") + 0x1);
				*smokecount = 0;
			}

			for (int i = 1; i < g_pGlobals->maxClients; i++)
			{

				CBaseEntity* pEntity = g_pEntitylist->GetClientEntity(i);
				if (pEntity)
				{
					if (pEntity->GetHealth() > 0)
					{
						if (i != g_pEngine->GetLocalPlayer())
						{
							VarMapping_t* map = pEntity->GetVarMap();
							if (map)
							{
								if (RagebotElements.Ragebot_Corrections_PositionAdjustment->Checked)
								{
									map->m_nInterpolatedEntries = 0;
								}
								else
								{
									if (map->m_nInterpolatedEntries == 0)
										map->m_nInterpolatedEntries = 6;
								}
							}

						}
					}
				}
			}



		}

		

		

		if (curStage == FRAME_RENDER_START)
		{
			for (int i = 1; i < g_pGlobals->maxClients; i++)
			{
				if (i == g_pEngine->GetLocalPlayer())
					continue;
				CBaseEntity* pEntity = g_pEntitylist->GetClientEntity(i);
				if (pEntity)
				{
					if (pEntity->GetHealth() > 0 && !pEntity->IsDormant())
					{
						*(int*)((uintptr_t)pEntity + 0xA30) = g_pGlobals->framecount; //we'll skip occlusion checks now
						*(int*)((uintptr_t)pEntity + 0xA28) = 0;//clear occlusion flags
					}
				}
			}
		}
	

	
		//skinchanger
		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && MiscElements.Misc_Windows_Skinchanger->Checked)
		{
			UINT* hWeapons = G::LocalPlayer->GetWeapons();
			for (int i = 0; hWeapons[i]; i++)
			{
				CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_pEntitylist->GetClientEntityFromHandle(hWeapons[i]);
				if (!weapon)
					continue;

				CBaseAttributableItem* attrib_item = (CBaseAttributableItem*)weapon;
				if (!attrib_item)
					continue;

				if (weapon->IsKnife())
				{
					if (GlobalSkinchanger->Skinchanger_Knife->SelectedIndex > 0)
					{
						switch (GlobalSkinchanger->Skinchanger_Knife->SelectedIndex)
						{
						case 1:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_KARAMBIT;
							break;
						case 2:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_BAYONET;
							break;
						case 3:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_M9_BAYONET;
							break;
						case 4:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_TACTICAL;
							break;
						case 5:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_GUT;
							break;
						case 6:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_FALCHION;
							break;
						case 7:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_PUSH;
							break;
						case 8:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_BUTTERFLY;
							break;
						case 9:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_FLIP;
							break;
						case 10:
							*attrib_item->GetItemDefinitionIndex() = KNIFE_BOWIE;
							break;
						default:
							break;
						}

					}
					else
					{
						if (G::LocalPlayer->GetTeamNum() == 2)
							*attrib_item->GetItemDefinitionIndex() = KNIFE_T;
						else if (G::LocalPlayer->GetTeamNum() == 3)
							*attrib_item->GetItemDefinitionIndex() = KNIFE;
					}

					int i = *attrib_item->GetItemDefinitionIndex();

					*(int*)((DWORD)weapon + offys.m_nModeIndex) = get_model_index(i);


					CBaseEntity* view_model = g_pEntitylist->GetClientEntityFromHandle_D(*(PDWORD)((DWORD)G::LocalPlayer + offys.m_hViewModel));
					if (view_model)
					{

						DWORD hViewModelWeapon = *(PDWORD)((DWORD)view_model + offys.m_hWeapon);
						CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)g_pEntitylist->GetClientEntityFromHandle_D(hViewModelWeapon);


						if (pViewModelWeapon)
						{

							//*(int*)((DWORD)pViewModelWeapon + offys.m_nModeIndex) = get_model_index(i);
							int p = *reinterpret_cast<int*>((DWORD)pViewModelWeapon + offys.m_nModeIndex);

						}
					}
					//attrib_item->SetModelIndex(get_model_index(*attrib_item->GetItemDefinitionIndex()));
				}
				

				g_Skinchanger->ApplyCustomSkin(attrib_item);


			}
		
		}


		if (curStage == FRAME_RENDER_START)
		{
			for (int i = 1; i < g_pGlobals->maxClients; i++)
			{
				CBaseEntity* pEntity = g_pEntitylist->GetClientEntity(i);
				if (pEntity)
				{
					if (pEntity->GetHealth() > 0 && !pEntity->IsDormant())
					{

						g_BacktrackHelper->UpdateBacktrackRecords(pEntity);
						g_BacktrackHelper->UpdateExtrapolationRecords(pEntity);

					}
				}
			}
		}

		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
					
			

			for (int i = 1; i < g_pGlobals->maxClients; i++)
			{
				if (i == g_pEngine->GetLocalPlayer())
					continue;
				CBaseEntity* pEntity = g_pEntitylist->GetClientEntity(i);
				if (pEntity && pEntity->GetHealth() > 0)
				{
					if (pEntity->IsDormant())
						continue;


					if (G::LocalPlayer && RagebotElements.Ragebot_Corrections_Resolver->Checked)
					{
						g_resolver->Resolve(pEntity);
					}
				}
				else
				{
					g_BacktrackHelper->PlayerRecord[i].records.clear();
				}
			}
		}

	
		clientVMT->GetOriginalMethod<FrameStageNotifyFn>(36)(curStage);

		if (G::LocalPlayer && G::LocalPlayer->GetHealth() > 0 && !b_IsThirdPerson)
		{

			if (VisualElements.Visual_Misc_NoRecoil->Checked)
			{
				*aim_punch = oldAimPunch;
				*view_punch = oldViewPunch;
			}
		}

		

	
	
}

int	__stdcall Hooks::IsBoxVisible(const Vector& mins, const Vector& maxs)
{
	if (!memcmp(_ReturnAddress(), "\x85\xC0\x74\x2D\x83\x7D\x10\x00\x75\x1C", 10))
		return 1;

	return engineVMT->GetOriginalMethod< IsBoxVisibleFn >(32)(mins, maxs);
}