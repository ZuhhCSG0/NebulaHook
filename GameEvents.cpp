#include "hooks.h"
#include <time.h>
#include "Mmsystem.h"
#include <thread>
#include "Hitmarker.h"
#include "Resolver.h"
#include "global.h"
#include "Aimbot.h"
#include "controls.h"
#include "Menu.h"


#pragma comment(lib, "winmm.lib") 
#define EVENT_HOOK( x )
#define TICK_INTERVAL			(Globals->interval_per_tick)


#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
cGameEvent g_Event;

std::vector<trace_info> trace_logs;

float logged_hits[64];

int KillsPerRound;
int GetServerSideID(int CBaseEntityIndex)
{
	player_info_t pInfo;
	g_pEngine->GetPlayerInfo(CBaseEntityIndex, &pInfo);
	return pInfo.m_nUserID;
}
std::map<int, ResolveData> PlayerData;
void cGameEvent::FireGameEvent(IGameEvent *event)
{
	/*short   m_nUserID		user ID who was hurt
	short	attacker	user ID who attacked
	byte	health		remaining health points
	byte	armor		remaining armor points
	string	weapon		weapon name attacker used, if not the world
	short	dmg_health	damage done to health
	byte	dmg_armor	damage done to armor
	byte	hitgroup	hitgroup that was damaged*/
	const char* szEventName = event->GetName();
	if (!szEventName)	
		return;

	
	if (strcmp(szEventName, "round_end") == 0)
	{
		if (global_damagelist->damage_infos.size() > 0)
			global_damagelist->damage_infos.clear();
	}
	

	if (strcmp(szEventName, "player_connect") == 0)
	{		
		memset(&G::Shots, 0, sizeof(G::Shots)); // reset shotsfired	
	}

	if (strcmp(szEventName, "weapon_fire") == 0)
	{
		CBaseEntity *player = g_pEntitylist->GetClientEntity(g_pEngine->GetPlayerForUserID(event->GetInt("userID")));
		if (player == G::LocalPlayer)
		{
			if (G::Target != NULL)
				G::Shots[G::Target->GetIndex()]++;
		}
	}

	if (strcmp(szEventName, "player_hurt") == 0)
	{
		CBaseEntity * hurt = g_pEntitylist->GetClientEntity(g_pEngine->GetPlayerForUserID(event->GetInt(XorStr("userID"))));
		CBaseEntity * attacker = g_pEntitylist->GetClientEntity(g_pEngine->GetPlayerForUserID(event->GetInt(XorStr("attacker"))));

		if (attacker == G::LocalPlayer)
		{
			if (hurt == G::Target)
			{
				if (G::Target != NULL)
				{					
					G::Shots[G::Target->GetIndex()] -= 1;				
				}
			}
		}



		bool IsHeadshot = (event->GetInt(XorStr("hitgroup")) == 1);

		int damage = event->GetInt("dmg_health");

		int CBaseEntityServerID =event->GetInt(XorStr("userID"));
		int AttackerServerID = event->GetInt(XorStr("attacker"));
		int AttackerIndex = g_pEngine->GetPlayerForUserID(AttackerServerID);
		if (AttackerIndex != g_pEngine->GetLocalPlayer())
			return;
		int CBaseEntityIndex = g_pEngine->GetPlayerForUserID(CBaseEntityServerID);
		if (CBaseEntityIndex == g_pEngine->GetLocalPlayer())
			return;

		auto* entity = g_pEntitylist->GetClientEntity(CBaseEntityIndex);
	

		if (!entity)
			return;

		g_Hitmarker->update_end_time();
		g_Hitmarker->play_sound();
		
		player_info_s pl_info;
		g_pEngine->GetPlayerInfo(CBaseEntityIndex, &pl_info);

		if (global_damagelist->damage_infos.size() > 21)
			global_damagelist->damage_infos.erase(global_damagelist->damage_infos.begin());

		std::string dmg_info = ""; dmg_info.append(pl_info.m_szPlayerName); dmg_info.append(" was damaged "); dmg_info.append(std::to_string(damage)); dmg_info.append(" HP!");
			global_damagelist->damage_infos.push_back(dmg_info);
		
		{
		
			int hitgroup = event->GetInt("hitgroup");
			if (hitgroup == HITGROUP_HEAD)
			{
				logged_hits[CBaseEntityServerID] = entity->GetEyeAngles().y;

			}


			if (hitgroup == 4)
			{
				PlayerData[CBaseEntityServerID].LastAttemptedAngles.y -= 45;
				//PlayerData[CBaseEntityServerID].LastAnglesHit.y = PlayerData[CBaseEntityServerID].LastAttemptedAngles.y;
				PlayerData[CBaseEntityServerID].MissedShots = 0;
			}
			else if (hitgroup == 5)
			{
				PlayerData[CBaseEntityServerID].LastAttemptedAngles.y += 45;
				//PlayerData[CBaseEntityServerID].LastAnglesHit.y = PlayerData[CBaseEntityServerID].LastAttemptedAngles.y;
				PlayerData[CBaseEntityServerID].MissedShots = 0;
			}
			else if (hitgroup == 2)
			{
				PlayerData[CBaseEntityServerID].MissedShots = 0;
			}


			
			Msg("[Hit registered %i]\n", hitgroup);
		}
	}

	if (strcmp(szEventName, "bullet_impact") == 0)
	{
		auto* index = g_pEntitylist->GetClientEntity(g_pEngine->GetPlayerForUserID(event->GetInt("userid")));

		//return if the userid is not valid or we werent the entity who was firing
		//if (G::LocalPlayer)
		//{
			//get the bullet impact's position
			Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

		//	if (VisualElements.Visual_Player_EnemyOnly->Checked && index->GetTeamNum() == G::LocalPlayer->GetTeamNum())
		//		return;

		//	Msg("pos = %f, %f, %f", event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));
			if (index)
				trace_logs.push_back(trace_info(index->GetEyePosition(), position, g_pGlobals->curtime, event->GetInt("userid")));
	//	}
	}

	if (strcmp(szEventName, "player_death") == 0)
	{

		
		int CBaseEntityServerID = event->GetInt(XorStr("userID"));
		int AttackerServerID = event->GetInt(XorStr("attacker"));
		int AttackerIndex = g_pEngine->GetPlayerForUserID(AttackerServerID);
		if (AttackerIndex != g_pEngine->GetLocalPlayer())
			return;
		int CBaseEntityIndex = g_pEngine->GetPlayerForUserID(CBaseEntityServerID);
		if (CBaseEntityIndex == g_pEngine->GetLocalPlayer())
			return;
			
		G::resolver_ticks[CBaseEntityIndex] = 0;

			if (std::string(event->GetString("weapon")).find("knife_") != std::string::npos)
			{
				std::string knifebuffer;
				auto KnifeType = GlobalSkinchanger->Skinchanger_Knife->SelectedIndex;
				if (KnifeType > 0)
				{
					if (KnifeType == 1)
						knifebuffer = "knife_karambit";
					if (KnifeType == 2)
						knifebuffer = "bayonet";
					if (KnifeType == 3)
						knifebuffer = "knife_m9_bayonet";
					if (KnifeType == 4)
						knifebuffer = "knife_tactical";
					if (KnifeType == 5)
						knifebuffer = "knife_gut";
					if (KnifeType == 6)
						knifebuffer = "knife_falchion";
					if (KnifeType == 7)
						knifebuffer = "knife_push";
					if (KnifeType == 8)
						knifebuffer = "knife_butterfly";
					if (KnifeType == 9)
						knifebuffer = "knife_flip";
					if (KnifeType == 10)
						knifebuffer = "knife_bowie";
					event->SetString("weapon", knifebuffer.c_str());
				}
			}
	}
}

int cGameEvent::GetEventDebugID()
{
	return 42;
}

void cGameEvent::RegisterSelf()
{
	g_pGameEventManager->AddListener(this, "player_connect", false);
	g_pGameEventManager->AddListener(this, "player_hurt", false);
	g_pGameEventManager->AddListener(this, "round_start", false);
	g_pGameEventManager->AddListener(this, "round_end", false);
	g_pGameEventManager->AddListener(this, "player_death", false);
	g_pGameEventManager->AddListener(this, "weapon_fire", false);
	g_pGameEventManager->AddListener(this, "bullet_impact", false);
}

void cGameEvent::Register()
{
	EVENT_HOOK(FireEvent);
}