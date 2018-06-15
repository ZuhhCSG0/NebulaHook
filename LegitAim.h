#pragma once
#include "sdk.h"

class legitbot
{
public:
	legitbot();

	void weapon_settings(CBaseCombatWeapon* weapon);

	void on_create_move(CUserCmd* cmd, CBaseEntity* local, CBaseCombatWeapon* weapon);
	bool hit_chance(CBaseEntity* local, CUserCmd* cmd, CBaseCombatWeapon* weapon, CBaseEntity* target);

	void do_aimbot(CBaseEntity *local, CBaseCombatWeapon *weapon, CUserCmd *cmd);
	QAngle get_randomized_recoil(CBaseEntity* local);
	QAngle get_randomized_angles(CBaseEntity* local);
	void triggerbot(CUserCmd* cmd, CBaseEntity* local, CBaseCombatWeapon* weapon);

private:
	bool get_hitbox(CBaseEntity *local, CBaseEntity *entity, Vector &destination);
	int get_target(CBaseEntity *local, CBaseCombatWeapon *weapon, CUserCmd *cmd, Vector &destination);

private:
	int best_target;

	QAngle view_angle;
	QAngle aim_angle;
	QAngle delta_angle;
	QAngle final_angle;

	Vector hitbox_position;

	int aim_key;
	float aim_smooth;
	float aim_fov;
	float randomized_smooth;
	float recoil_min;
	float recoil_max;
	float randomized_angle;
	bool shoot;
};

extern legitbot* c_legitbot;