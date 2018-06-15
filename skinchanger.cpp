#include "sdk.h"
#include <unordered_map>
#include "skinchanger.h"
#include <random>
#include "Menu.h"
#include "global.h"
CSkinchanger* g_Skinchanger = new CSkinchanger;

std::unordered_map<std::string, EconomyItemCfg> g_SkinChangerCfg;

typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);

char easytolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}
int _get_model_index(int item_def_index)
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
void ViewModel_Index_Proxy(CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	if (((*(int*)((DWORD)pDataConst + 0x8) == g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")) || *(int*)((DWORD)pDataConst + 0x8) == g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")))
	{
		auto KnifeType = GlobalSkinchanger->Skinchanger_Knife->SelectedIndex;
		if (KnifeType > 0)
		{
			UINT* hWeapons = G::LocalPlayer->GetWeapons();
			for (int i = 0; hWeapons[i]; i++)
			{
				CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_pEntitylist->GetClientEntityFromHandle(hWeapons[i]/* & 0xFFF*/);
				if (!weapon)
					continue;

				CBaseAttributableItem* attrib_item = (CBaseAttributableItem*)weapon;
				if (!attrib_item)
					continue;

				if (weapon->IsKnife())
				{
					*(int*)((DWORD)pDataConst + 0x8) = _get_model_index(weapon->WeaponID());
				}
			}
		}
	}
	
	*(int*)((DWORD)pOut) = *(int*)((DWORD)pDataConst + 0x8);
}

static CreateClientClassFn GetWearableCreateFn()
{
	auto clazz = g_pClient->GetAllClasses();

	while (strcmp(clazz->m_pNetworkName, "CEconWearable"))
		clazz = clazz->m_pNext;

	return clazz->m_pCreateFn;
}
IClientNetworkable* CL_CreateDLLEntity(int iEnt, int iClass, int iSerialNum)
{
	ClientClass* pClient = g_pClient->GetAllClasses();
	if (!pClient)
		return false;

	while (pClient)
	{
		if (pClient->m_ClassID == iClass)
			return pClient->m_pCreateFn(iEnt, iSerialNum);
		pClient = pClient->m_pNext;
	}
	return false;
}

float random_number_range(float min, float max)
{
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_real_distribution<> distribution(min, max);
	return static_cast< float >(distribution(engine));
}

void DoGloves()
{
	std::vector<int> glove_ids = { 5027, 5032, 5031, 5030, 5033, 5034 };

	CBaseEntity *local = g_pEntitylist->GetClientEntity(g_pEngine->GetLocalPlayer());
	player_info_t localPlayerInfo;
	if (!g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localPlayerInfo)) return;


	auto wearables = local->GetWearables();
	static ULONG glove_handle = 0;

	if (!wearables)
		return;

	auto glove = reinterpret_cast<CBaseAttributableItem*>(g_pEntitylist->GetClientEntityFromHandle(wearables[0]));

	if (!local->isAlive())
	{
		// We are dead but we have a glove, destroy it
		if (glove)
		{
			glove->GetNetworkable()->SetDestroyedOnRecreateEntities();
			glove->GetNetworkable()->Release();
		}

		return;
	}

	if (!glove)
	{
		for (ClientClass* pClass = g_pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID == (int)CSGOClassID::CEconWearable)
			{
				int iEntry = g_pEntitylist->GetHighestEntityIndex() + 1;
				int iSerial = random_number_range(0x0, 0xFFF);
				pClass->m_pCreateFn(iEntry, iSerial);
				local->GetWearables()[0] = iEntry | (iSerial << 16);
				glove = (CBaseAttributableItem*)g_pEntitylist->GetClientEntity(local->GetWearables()[0]);
				break;
			}
		}

	}

	

	std::string weaponstr;

	

	if (glove)
	{
		*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;

		int nWeaponIndex = *glove->GetItemDefinitionIndex();


		switch (nWeaponIndex)
		{
		case 5027:
			weaponstr.assign("STUDDED_BLOODHOUND_GLOVES");
			break;
		case 5030:
			weaponstr.assign("SPORTY_GLOVES");
			break;
		case 5031:
			weaponstr.assign("SLICK_GLOVES");
			break;
		case 5032:
			weaponstr.assign("LEATHER_HANDWRAPS");
			break;
		case 5033:
			weaponstr.assign("MOTORCYCLE_GLOVES");
			break;
		case 5034:
			weaponstr.assign("SPECIALIST_GLOVES");
			break;
		}

		std::transform(weaponstr.begin(), weaponstr.end(), weaponstr.begin(), easytolower);

		g_SkinChangerCfg[weaponstr].nFallbackPaintKit = SkinsUtil::data.find(weaponstr)->second;

	//	*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;

		switch (GlobalSkinchanger->Skinchanger_Glove->SelectedIndex)
		{
		case 1: //bloodhound
		{
		//	if (*glove->GetItemDefinitionIndex() != 5027)
		//	{
				*glove->GetItemDefinitionIndex() = 5027;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
		//		*glove->GetFallbackPaintKit() = 10006;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
		//		*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
		//	}
		}
		break;
		case 2: //sporty
		{
		//	if (*glove->GetItemDefinitionIndex() != 5030 )
		//	{
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				*glove->GetItemDefinitionIndex() = 5030;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
			//	*glove->GetFallbackPaintKit() = 10037;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
		//	}
		}
		break;
		case 3://SLICK_GLOVES
		{
		//	if (*glove->GetItemDefinitionIndex() != 5031 )
		//	{
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				*glove->GetItemDefinitionIndex() = 5031;
		//		*glove->GetFallbackPaintKit() = 10016;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
		//	}
		}
		break;
		case 4://LEATHER_HANDWRAPS
		{
		//	if (*glove->GetItemDefinitionIndex() != 5032 )
		//	{
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				*glove->GetItemDefinitionIndex() = 5032;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
			//	*glove->GetFallbackPaintKit() = 10009;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
		//	}
		}
		break;
		case 5://MOTORCYCLE_GLOVES
		{
		//	if (*glove->GetItemDefinitionIndex() != 5033 )
		//	{
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				*glove->GetItemDefinitionIndex() = 5033;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
			//	*glove->GetFallbackPaintKit() = 10026;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			//}
		}
		break;
		case 6://SPECIALIST_GLOVES
		{
		//	if (*glove->GetItemDefinitionIndex() != 5034 )
		//	{
				glove->SetModelIndex(g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				*glove->GetItemDefinitionIndex() = 5034;
				*glove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
			//	*glove->GetFallbackPaintKit() = 10033;
				*glove->GetEntityQuality() = 4;
				*glove->GetFallbackSeed() = 0;
				*glove->GetFallbackWear() = 0.001f;
				*glove->GetFallbackStatTrak() = -1;
				*glove->GetItemIDHigh() = -1;
			//	*glove->GetAccountID() = localPlayerInfo.m_nXuidLow;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
		//	}
		}
		break;
		}
	
			

		
		
	}
}

int RandomInt(int min, int max)
{
	return rand() % max + min;
}

void ApplyCustomGloveModel()
{

	if (!MiscElements.Misc_Windows_Skinchanger->Checked)
		return;

	if (!g_pEngine->IsConnected() || !g_pEngine->IsInGame())
		return;

	auto *pLocal = g_pEntitylist->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (!pLocal)
		return;
	player_info_t localplayer_info;

	if (!g_pEngine->GetPlayerInfo(pLocal->GetIndex(), &localplayer_info))
		return;

	if (!pLocal->isAlive())
		return;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pLocal->GetWeapon();
	if (!pWeapon)
		return;

	if (!pLocal->GetWearables())
		return;

	CBaseAttributableItem* pGlove = (CBaseAttributableItem*)g_pEntitylist->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
	if (!pGlove)
	{
		for (ClientClass* pClass = g_pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID == (int)CSGOClassID::CEconWearable)
			{
				int iEntry = g_pEntitylist->GetHighestEntityIndex() + 1;
				int iSerial = RandomInt(0x0, 0xFFF);
				pClass->m_pCreateFn(iEntry, iSerial);
				pLocal->GetWearables()[0] = iEntry | (iSerial << 16);
				pGlove = (CBaseAttributableItem*)g_pEntitylist->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
				break;
			}
		}

		if (!pGlove)
			return;

		*reinterpret_cast<int*>(uintptr_t(pGlove) + 0x64) = -1;

		int modelIndex = 0;
		int paintkit = 0;
		int itemdef;

		switch (GlobalSkinchanger->Skinchanger_Glove->SelectedIndex)
		{
		case 1:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl");
			itemdef = 5027;
			break;
		case 2:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl");
			itemdef = 5032;
			break;
		case 3:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl");
			itemdef = 5031;
			break;
		case 4:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl");
			itemdef = 5030;
			break;
		case 5:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl");
			itemdef = 5033;
			break;
		case 6:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl");
			itemdef = 5034;
			break;
		default:
			break;
		}

		int nWeaponIndex = *pGlove->GetItemDefinitionIndex();

		std::string weaponstr;

		switch (nWeaponIndex)
		{
		case 5027:
			weaponstr.assign("STUDDED_BLOODHOUND_GLOVES");
			break;
		case 5030:
			weaponstr.assign("SPORTY_GLOVES");
			break;
		case 5031:
			weaponstr.assign("SLICK_GLOVES");
			break;
		case 5032:
			weaponstr.assign("LEATHER_HANDWRAPS");
			break;
		case 5033:
			weaponstr.assign("MOTORCYCLE_GLOVES");
			break;
		case 5034:
			weaponstr.assign("SPECIALIST_GLOVES");
			break;
		}

		std::transform(weaponstr.begin(), weaponstr.end(), weaponstr.begin(), easytolower);

		g_SkinChangerCfg[weaponstr].nFallbackPaintKit = SkinsUtil::data.find(weaponstr)->second;


		*pGlove->GetItemDefinitionIndex() = itemdef;
	
		*pGlove->GetItemIDHigh() = -1;
		*pGlove->GetFallbackWear() = 0.000001f;
		*pGlove->GetFallbackSeed() = 0;
		*pGlove->GetFallbackStatTrak() = -1;
		*pGlove->GetEntityQuality() = 4;
		*pGlove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
		pGlove->SetModelIndex(modelIndex);
		pGlove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
		

	}
}


bool CSkinchanger::ApplyCustomSkin(CBaseAttributableItem* attrib_item) {
	// Get the weapon entity from the provided handle.

	if (!attrib_item)
		return false;

	if (!G::LocalPlayer)
		return false;

	if (!G::LocalPlayer->GetWearables())
		return false;


//	ApplyCustomGloveModel();

	// Get the weapons item definition index.
	int nWeaponIndex = *attrib_item->GetItemDefinitionIndex();


	std::string weaponstr;
	switch (nWeaponIndex)
	{
	case KNIFE_BAYONET:
		weaponstr.assign("WEAPON_BAYONET");
		break;
	case KNIFE_M9_BAYONET:
		weaponstr.assign("WEAPON_KNIFE_M9_BAYONET");
		break;
	case KNIFE_FLIP:
		weaponstr.assign("WEAPON_KNIFE_FLIP");
		break;
	case KNIFE_FALCHION:
		weaponstr.assign("WEAPON_KNIFE_FALCHION");
		break;
	case KNIFE_KARAMBIT:
		weaponstr.assign("WEAPON_KNIFE_KARAMBIT");
		break;
	case KNIFE_GUT:
		weaponstr.assign("WEAPON_KNIFE_GUT");
		break;
	case KNIFE_TACTICAL:
		weaponstr.assign("WEAPON_KNIFE_TACTICAL");
		break;
	case KNIFE_BOWIE:
		weaponstr.assign("WEAPON_KNIFE_SURVIVAL_BOWIE");
		break;
	case KNIFE_BUTTERFLY:
		weaponstr.assign("WEAPON_KNIFE_BUTTERFLY");
		break;
	case REVOLVER:
		weaponstr.assign("WEAPON_REVOLVER");
		break;
	case KNIFE_PUSH:
		weaponstr.assign("WEAPON_KNIFE_PUSH");
		break;
	case DEAGLE:
		weaponstr.assign("WEAPON_DEAGLE");
		break;
	case ELITE:
		weaponstr.assign("WEAPON_ELITE");
		break;
	case FIVESEVEN:
		weaponstr.assign("WEAPON_FIVESEVEN");
		break;
	case GLOCK:
		weaponstr.assign("WEAPON_GLOCK");
		break;
	case AK47:
		weaponstr.assign("WEAPON_AK47");
		break;
	case AUG:
		weaponstr.assign("WEAPON_AUG");
		break;
	case AWP:
		weaponstr.assign("WEAPON_AWP");
		break;
	case FAMAS:
		weaponstr.assign("WEAPON_FAMAS");
		break;
	case G3SG1:
		weaponstr.assign("WEAPON_G3SG1");
		break;
	case GALILAR:
		weaponstr.assign("WEAPON_GALILAR");
		break;
	case M249:
		weaponstr.assign("WEAPON_M249");
		break;
	case M4A1_SILENCER:
		weaponstr.assign("WEAPON_M4A1_SILENCER");
		break;
	case M4A1:
		weaponstr.assign("WEAPON_M4A1");
		break;
	case MAC10:
		weaponstr.assign("WEAPON_MAC10");
		break;
	case P90:
		weaponstr.assign("WEAPON_P90");
		break;
	case UMP45:
		weaponstr.assign("WEAPON_UMP");
		break;
	case XM1014:
		weaponstr.assign("WEAPON_XM1014");
		break;
	case BIZON:
		weaponstr.assign("WEAPON_BIZON");
		break;
	case MAG7:
		weaponstr.assign("WEAPON_MAG7");
		break;
	case NEGEV:
		weaponstr.assign("WEAPON_NEGEV");
		break;
	case SAWEDOFF:
		weaponstr.assign("WEAPON_SAWEDOFF");
		break;
	case TEC9:
		weaponstr.assign("WEAPON_TEC9");
		break;
	case HKP2000:
		weaponstr.assign("WEAPON_HKP2000");
		break;
	case MP7:
		weaponstr.assign("WEAPON_MP7");
		break;
	case MP9:
		weaponstr.assign("WEAPON_MP9");
		break;
	case NOVA:
		weaponstr.assign("WEAPON_NOVA");
		break;
	case P250:
		weaponstr.assign("WEAPON_P250");
		break;
	case SCAR20:
		weaponstr.assign("WEAPON_SCAR20");
		break;
	case SG556:
		weaponstr.assign("WEAPON_SG556");
		break;
	case SSG08:
		weaponstr.assign("WEAPON_SSG08");
		break;
	case USP_SILENCER:
		weaponstr.assign("WEAPON_USP_SILENCER");
		break;
	case KNIFE_T:
		//weaponstr.assign("WEAPON_hkp2000");
		break;
	case KNIFE:
		//weaponstr.assign("WEAPON_hkp2000");
		break;
/*	case 5027:
		weaponstr.assign("STUDDED_BLOODHOUND_GLOVES");
		break;
	case 5030:
		weaponstr.assign("SPORTY_GLOVES");
		break;
	case 5031:
		weaponstr.assign("SLICK_GLOVES");
		break;
	case 5032:
		weaponstr.assign("LEATHER_HANDWRAPS");
		break;
	case 5033:
		weaponstr.assign("MOTORCYCLE_GLOVES");
		break;
	case 5034:
		weaponstr.assign("SPECIALIST_GLOVES");
		break;*/
	}

	std::transform(weaponstr.begin(), weaponstr.end(), weaponstr.begin(), easytolower);

	g_SkinChangerCfg[weaponstr].nFallbackPaintKit = SkinsUtil::data.find(weaponstr)->second;


	*attrib_item->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;//SkinsUtil::data.find(weaponstr)->second;//

	*attrib_item->GetFallbackSeed() = (int)GlobalSkinchanger->Skinchanger_Seed->value;//g_SkinChangerCfg[weaponstr].nFallbackSeed;

	if (((CBaseCombatWeapon*)attrib_item)->IsKnife())
		if (GlobalSkinchanger->Skinchanger_Knife->SelectedIndex > 0)
			*attrib_item->GetEntityQuality() = 3;
		else
			*attrib_item->GetEntityQuality() = 1;
	else
		*attrib_item->GetEntityQuality() = 0;

	/*if (bStatTrack)
		*attrib_item->GetFallbackStatTrak() = (int)GlobalSkinchanger->Skinchanger_Stattrack_Kills->value;//g_SkinChangerCfg[weaponstr].nFallbackStatTrak;
	else*/
		*attrib_item->GetFallbackStatTrak() = -1;

	*attrib_item->GetFallbackWear() = GlobalSkinchanger->Skinchanger_Wear->value;//g_SkinChangerCfg[weaponstr].flFallbackWear;


	
	//*attrib_item->GetAccountID() = pinfo.m_nXuidLow;
	*attrib_item->GetItemIDHigh() = -1; //-1
	//*attrib_item->GetItemIDLow() = 0;

	attrib_item->OnDataUpdate(5);
//	ApplyCustomGloveModel();


	CBaseAttributableItem* pGlove = (CBaseAttributableItem*)g_pEntitylist->GetClientEntity(G::LocalPlayer->GetWearables()[0] & 0xFFF);
	if (!pGlove)
	{
		for (ClientClass* pClass = g_pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID == (int)CSGOClassID::CEconWearable)
			{
				int iEntry = g_pEntitylist->GetHighestEntityIndex() + 1;
				int iSerial = RandomInt(0x0, 0xFFF);
				pClass->m_pCreateFn(iEntry, iSerial);
				G::LocalPlayer->GetWearables()[0] = iEntry | (iSerial << 16);
				pGlove = (CBaseAttributableItem*)g_pEntitylist->GetClientEntity(G::LocalPlayer->GetWearables()[0] & 0xFFF);
				break;
			}
		}
	}

	if (pGlove)
	{

		*reinterpret_cast<int*>(uintptr_t(pGlove) + 0x64) = -1;

		int modelIndex = 0;
		int paintkit = 0;
		int itemdef;

		switch (GlobalSkinchanger->Skinchanger_Glove->SelectedIndex)
		{
		case 1:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl");
			itemdef = 5027;
			break;
		case 2:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl");
			itemdef = 5032;
			break;
		case 3:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl");
			itemdef = 5031;
			break;
		case 4:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl");
			itemdef = 5030;
			break;
		case 5:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl");
			itemdef = 5033;
			break;
		case 6:
			modelIndex = g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl");
			itemdef = 5034;
			break;
		default:
			break;
		}


		/**pGlove->GetItemDefinitionIndex() = itemdef;

		*pGlove->GetItemIDHigh() = -1;
		*pGlove->GetFallbackWear() = 0.000001f;
		*pGlove->GetFallbackSeed() = 0;
		*pGlove->GetFallbackStatTrak() = -1;
		*pGlove->GetEntityQuality() = 4;
		*pGlove->GetFallbackPaintKit() = g_SkinChangerCfg[weaponstr].nFallbackPaintKit;
		pGlove->SetModelIndex(modelIndex);
		pGlove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);*/
	}

	

	return true;
}