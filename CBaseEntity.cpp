#include "sdk.h"
#include "Math.h"
#include "global.h"
#include "GameUtils.h"
#include "xor.h"

RecvProp* CBaseEntity::GetSequence3()
{
	static auto pProp = netvars.get_prop("DT_BaseAnimating", "m_nSequence");
	return pProp;
}

CUtlVector<CAnimationLayer> CBaseEntity::GetAnimOverlays() {
	return *reinterpret_cast<CUtlVector<CAnimationLayer>*>(this + 0x2970); // 55 8B EC 51 53 8B 5D 08 33 C0
}

int CBaseEntity::GetSequenceActivity(int sequence)
{
	auto hdr = g_pModelInfo->GetStudioModel(this->GetModel());

	if (!hdr)
		return -1;

	// c_csplayer vfunc 242, follow calls to find the function.

	// (DWORD)Utils::PatternScan(client, "55 8B EC 83 7D 08 FF 56 8B F1 74 3D")
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>((DWORD)Utilities::Memory::FindPatternIDA("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D"));

	return GetSequenceActivity(this, hdr, sequence);
}

CBaseCombatWeapon* CBaseEntity::GetWeapon()
{
	//index: 262
	//ref: [%s]->Weapon_GetActiveSlot()
	typedef CBaseCombatWeapon* (__thiscall* OriginalFn)(void*);
	return getvfunc<OriginalFn>(this, 262)(this);
}
DWORD GetCSWpnDataAddr;
CSWeaponInfo* CBaseCombatWeapon::GetCSWpnData()
{
	typedef CSWeaponInfo*(__thiscall* OriginalFn)(void*);
	return  getvfunc<OriginalFn>(this, 446)(this);
}
#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / g_pGlobals->interval_per_tick ) )
int CBaseEntity::GetChockedPackets()
{
	if (GetSimulationTime() > GetOldSimulationTime())
		return TIME_TO_TICKS(fabs(GetSimulationTime() - GetOldSimulationTime()));
	return 0;
}


void CBaseEntity::SetAbsOrigin(QAngle& Origin)
{
	typedef void(__thiscall* SetAbsOrigin_t)(void*, Vector&);
	static auto SetAbsOriginF = (SetAbsOrigin_t)Utilities::Memory::FindPatternIDA("client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	SetAbsOriginF(this, Origin);
}

void CBaseEntity::SetAngle2(Vector wantedang)
{
	typedef void(__thiscall* SetAngleFn)(void*, const Vector &);
	static SetAngleFn SetAngle = (SetAngleFn)((DWORD)Utilities::Memory::FindPatternIDA("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
	SetAngle(this, wantedang);
}

Vector& CBaseEntity::m_vecNetworkOrigin() 
{
	
	static int offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flFriction") - sizeof(Vector);
	return *(Vector*)((DWORD)this + offset);
}

float CBaseEntity::GetOldSimulationTime()
{

		static uintptr_t offset = g_pNetVars->GetOffset("DT_CSPlayer", "m_flSimulationTime") +0x4;
	return *(float*)((DWORD)this + offset);
}
bool CBaseEntity::SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	//void *pRenderable = (void*)(this + 0x4);
	//typedef bool(__thiscall* OriginalFn)(PVOID, VMatrix*, int, int, float);
	//return getvfunc<OriginalFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);

	__asm
	{
		mov edi, this
		lea ecx, dword ptr ds : [edi + 0x4]
		mov edx, dword ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call dword ptr ds : [edx + 0x34]
	}
}

bool CBaseEntity::IsTargettingLocal()
{

	Vector src, dst, forward;
	trace_t tr;

	if (!this || !G::LocalPlayer || G::LocalPlayer->GetHealth() < 0)
		return false;

	Vector viewangle = this->GetEyeAngles();

	Math::AngleVectors(viewangle, &forward);
	forward *= 8142.f;
	src = this->GetEyePosition();
	dst = src + forward;

	Ray_t ray;
	ray.Init(src, dst);
	CTraceCBaseEntity filter;
	filter.pHit = G::LocalPlayer;

	g_pEngineTrace->TraceRay_NEW(ray, MASK_SHOT, &filter, &tr);
	

	if (tr.m_pEnt && tr.m_pEnt->GetTeamNum() != this->GetTeamNum()/*== G::LocalPlayer*/)
		return true;

	return false;
}


bool CBaseEntity::IsPlayer()
{
	ClientClass* pClass = (ClientClass*)this->GetClientClass();
	return pClass->m_ClassID == 35;
}