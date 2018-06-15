#include "sdk.h"

#include "Menu.h"
#include "tinyxml2.h"

CMenu* m_pMenu;
CMiniWindows MiniWindowElements;
CRagebotElements RagebotElements;
CSaveElements SaveElements;
CColorElements ColorElements;
CVisualElements VisualElements;
CMiscElements MiscElements;
CLegitElements LegitElements;

void SetupLegitCat(MWindow* MainWindow)
{
	LegitElements.LegitCat = new MCategory(XorStr("legit"), MainWindow, 0, sizeof(0), 512, 512);
}

void SetupMiscCat(MWindow* MainWindow)
{
	MiscElements.MiscCat = new MCategory(XorStr("misc"), MainWindow, 0, sizeof(0), 512, 512);
	MiscElements.Misc_General = new MGroupbox2(MiscElements.MiscCat, XorStr("main"), 1, 1, 1, 1, false, 180, 305, -5, -10);
	MiscElements.Misc_General_Restriction = new MCheckbox(MiscElements.Misc_General, XorStr("anti-untrusted"), XorStr("Prevents you from getting untrusted banned"), MiscElements.MiscCat, XorStr("misc_general_restriction"));
	MiscElements.Misc_General_RevealRanks = new MCheckbox(MiscElements.Misc_General, XorStr("reveal ranks"), XorStr("Reveals the ranks of the enemies"), MiscElements.MiscCat, XorStr("misc_general_revealranks"));
	MiscElements.Misc_General_FOV = new MSlider(MiscElements.Misc_General, XorStr("world model fov"), XorStr("Change your view world fov"), 90, 120, true, MiscElements.MiscCat, XorStr("misc_general_wfov"), false, true);
	MiscElements.Misc_General_VFOV = new MSlider(MiscElements.Misc_General, XorStr("view model fov"), XorStr("Change your view view fov"), 68, 120, true, MiscElements.MiscCat, XorStr("misc_general_vfov"), false, true);
	MiscElements.Misc_General_Crosshair = new MDropdown(MiscElements.Misc_General, XorStr("crosshair"), XorStr("Draws a crosshair"), MiscElements.MiscCat, XorStr("misc_general_crosshair"), std::vector<std::string>{"Off", "normal", "recoil", "recoil and spread"});
	MiscElements.Misc_General_Thirdperson = new MCheckbox(MiscElements.Misc_General, XorStr("thirdperson"), XorStr("Moves you to thirdperson view"), MiscElements.MiscCat, XorStr("misc_general_thirdperson"));
	MiscElements.Misc_General_Thirdperson_Key_Bind = new MKeybind(MiscElements.Misc_General, XorStr("thirdperson key"), XorStr("Etp key"), MiscElements.MiscCat, XorStr("misc_general_thirdperson_key"));
	MiscElements.Misc_General_Thirdperson_Angles = new MDropdown(MiscElements.Misc_General, XorStr("thirdperson angles"), XorStr("Shows real or fake angles or lowerbody angles"), MiscElements.MiscCat, XorStr("misc_general_thirdperson_angles"), std::vector<std::string>{"fake", "real", "lby"});
	MiscElements.Misc_Chat_ClanTagChanger = new MDropdown(MiscElements.Misc_General, XorStr("clan tag changer"), XorStr("Changes your clantag"), MiscElements.MiscCat, XorStr("misc_general_clantagchanger"), std::vector<string>{"off", "supreme"});
	MiscElements.Misc_Windows_Skinchanger = new MCheckbox(MiscElements.Misc_General, XorStr("skin changer"), XorStr("Enable Skin Changer"), MiscElements.MiscCat, XorStr("misc_general_skin_changer"));


	MiscElements.Misc_General_FOV->value = 90.f;
	MiscElements.Misc_General_VFOV->value = 68.f;


	MiscElements.Misc_Movement = new MGroupbox2(MiscElements.MiscCat, XorStr("movement"), 1, 2, 1, 1, false, 175, 100, 190, -10);
	MiscElements.Misc_Movement_Bunnyhop = new MCheckbox(MiscElements.Misc_Movement, XorStr("automic hop"), XorStr("Makes you jump automatically"), MiscElements.MiscCat, XorStr("misc_movement_bunnyhop"));
	MiscElements.Misc_Movement_Autostrafe = new MCheckbox(MiscElements.Misc_Movement, XorStr("automatic strafe"), XorStr("Makes you strafe automatically"), MiscElements.MiscCat, XorStr("misc_movement_autostrafe"));
	//MiscElements.Misc_Movement_Strafe_Retrack = new MSlider(MiscElements.Misc_Movement, XorStr("retrack speed"), XorStr("Defines the retracking speed of the strafings"), 1, 8, true, MiscElements.MiscCat, XorStr("misc_movement_retrack"));
	
	MiscElements.Misc_Fakelag = new MGroupbox2(MiscElements.MiscCat, XorStr("fake lag"), 1, 2, 1, 1, false, 175, 195, 190, 100);
	MiscElements.Misc_Movement_FakelagType = new MDropdown(MiscElements.Misc_Fakelag, XorStr("fakelag mode"), XorStr("Mode of the fakelag"), MiscElements.MiscCat, XorStr("misc_movement_fakelag"), std::vector<string>{ XorStr("Off"), XorStr("Factor"), XorStr("Lightning"), XorStr("Adaptive"), "Switch", "Beat", "Whatever"});
	MiscElements.Misc_Movement_Fakelag_Choke = new MSlider(MiscElements.Misc_Fakelag, XorStr("fakelag amount"), XorStr("Amount of the fakelag"), 0, 14, true, MiscElements.MiscCat, XorStr("misc_movement_fakelag_choke"));
	MiscElements.Misc_Movement_Fakelag_OnShoot = new MCheckbox(MiscElements.Misc_Fakelag, XorStr("fakelag while shooting"), XorStr("Fakelag while shooting"), MiscElements.MiscCat, XorStr("misc_movement_fakelag_onshoot"));
	MiscElements.Misc_Movement_Fakelag_OnGround = new MCheckbox(MiscElements.Misc_Fakelag, XorStr("fakelag on ground"), XorStr("Fakelag on ground"), MiscElements.MiscCat, XorStr("misc_movement_fakelag_onground"));


	ColorElements.Colorcol = new MGroupbox2(MiscElements.MiscCat, "Colors", 1, 1, 1, 1, false, 180, 305, 375, -10);
	ColorElements.Color_CT = new MGroupbox(ColorElements.Colorcol, "counter terrorists", 1, 1, 1, 1, true);
	ColorElements.Color_CT_Visible = new MColorPicker(ColorElements.Color_CT, "visible", "", MiscElements.MiscCat, "color_ct_vis");
	ColorElements.Color_CT_Invisible = new MColorPicker(ColorElements.Color_CT, "invisible", "", MiscElements.MiscCat, "color_ct_invis");
	ColorElements.Color_CT_Visible_Cham = new MColorPicker(ColorElements.Color_CT, "chams visible", "", MiscElements.MiscCat, "color_ct_vis_cham");
	ColorElements.Color_CT_Invisible_Cham = new MColorPicker(ColorElements.Color_CT, "chams invisible", "", MiscElements.MiscCat, "color_ct_invis_cham");

	ColorElements.Color_T = new MGroupbox(ColorElements.Colorcol, "terrorists", 1, 2, 1, 1, true);
	ColorElements.Color_T_Visible = new MColorPicker(ColorElements.Color_T, "visible", "", MiscElements.MiscCat, "color_t_vis");
	ColorElements.Color_T_Invisible = new MColorPicker(ColorElements.Color_T, "invisible", "", MiscElements.MiscCat, "color_t_invis");
	ColorElements.Color_T_Visible_Cham = new MColorPicker(ColorElements.Color_T, "chams visible", "", MiscElements.MiscCat, "color_t_vis_cham");
	ColorElements.Color_T_Invisible_Cham = new MColorPicker(ColorElements.Color_T, "chams invisible", "", MiscElements.MiscCat, "color_t_invis_cham");

	ColorElements.Color_Weapon = new MColorPicker(ColorElements.Colorcol, "world", "", MiscElements.MiscCat, "color_world");


}

void SetupRagebotCat(MWindow* MainWindow)
{
	/*Addchildcontrol for everything is in the init*/

	RagebotElements.RagebotCat = new MCategory(XorStr("rage"), MainWindow, 0, sizeof(0), 400, 382);
	RagebotElements.Ragebot_Main = new MGroupbox2(RagebotElements.RagebotCat, XorStr("main"), 1, 1, 1, 1, false, 260, 90, 0, -10);
	RagebotElements.Ragebot_Active = new MCheckbox(RagebotElements.Ragebot_Main, XorStr("enable"), XorStr("Activates ragebot"), RagebotElements.RagebotCat, XorStr("rb_active"));
	RagebotElements.Ragebot_Type = new MCheckbox(RagebotElements.Ragebot_Main, XorStr("silent aim"), XorStr("Select the type of ragebot"), RagebotElements.RagebotCat, XorStr("rb_silent"));
	RagebotElements.Ragebot_BodyAWP = new MCheckbox(RagebotElements.Ragebot_Main, XorStr("automatic awp body aim"), XorStr("Aims always at the body with an awp"), RagebotElements.RagebotCat, XorStr("rb_bodyawp"));
	RagebotElements.Ragebot_AutoShoot = new MCheckbox(RagebotElements.Ragebot_Main, XorStr("automatic fire"), XorStr("Automatically shoots"), RagebotElements.RagebotCat, XorStr("rb_autoshoot"));


	RagebotElements.Ragebot_Selection = new MGroupbox2(RagebotElements.RagebotCat, XorStr("target"), 1, 2, 1, 1, false, 260, 200, 0, 90);
	RagebotElements.Ragebot_SelectBy = new MDropdown(RagebotElements.Ragebot_Selection, XorStr("target selection"), XorStr("Change the algorithm targets get selected"), RagebotElements.RagebotCat, XorStr("rb_select"), std::vector<string>{XorStr("field of view"), XorStr("distance"), XorStr("cycle"), XorStr("velocity"), "health"});
	RagebotElements.Ragebot_FOV = new MSlider(RagebotElements.Ragebot_Selection, XorStr("maximum aim angle"), XorStr("Select the fov to aim at"), 0, 180, true, RagebotElements.RagebotCat, XorStr("fb_fov"), false, true);
	RagebotElements.Ragebot_AtFriendly = new MCheckbox(RagebotElements.Ragebot_Selection, XorStr("friendly fire"), XorStr("Aims at allies"), RagebotElements.RagebotCat, XorStr("rb_atfriendly"));
	RagebotElements.Ragebot_Hitbox = new MDropdown(RagebotElements.Ragebot_Selection, XorStr("hitbox"), XorStr("Select the hitbox to aim at"), RagebotElements.RagebotCat, XorStr("rb_hitbox"), std::vector<string>{XorStr("head"), XorStr("neck"), XorStr("chest"), XorStr("pelvis"), XorStr("stomach"), XorStr("smart")});
	RagebotElements.Ragebot_Hitscan = new MDropdown(RagebotElements.Ragebot_Selection, XorStr("hitscan"), XorStr("Intsensity of the hitscan"), RagebotElements.RagebotCat, XorStr("rb_hitscan"), std::vector<string>{XorStr("off"), XorStr("basic"), XorStr("medium"), XorStr("full")});



	RagebotElements.Ragebot_Accuracy = new MGroupbox2(RagebotElements.RagebotCat, XorStr("accuracy"), 1, 1, 1, 1, false, 260, 300, 280, -10);
//	RagebotElements.Ragebot_SecondaryRevolver = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("resolver secondary fire"), XorStr("Automatically shoots"), RagebotElements.RagebotCat, XorStr("rb_autoshoot"));
	RagebotElements.Ragebot_NoRecoil = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("no recoil"), XorStr("Compensate for recoil"), RagebotElements.RagebotCat, XorStr("rb_norecoil"));
	RagebotElements.Ragebot_NoSpread = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("no spread"), XorStr("Compensate for spread"), RagebotElements.RagebotCat, XorStr("rb_nospread"));
	RagebotElements.Ragebot_AutoScope = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("automatic scope"), XorStr("Automatically scope"), RagebotElements.RagebotCat, XorStr("rb_autoscope"));
	RagebotElements.Ragebot_AutoStop = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("automatic stop"), XorStr("Automatically stop"), RagebotElements.RagebotCat, XorStr("rb_autostop"));
	RagebotElements.Ragebot_Autowall = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("autowall"), XorStr("Shoots through walls"), RagebotElements.RagebotCat, XorStr("rb_autowall"));
//	RagebotElements.Ragebot_Autowall_Hitscan = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("autowall hitscan"), XorStr("Hitscan walls"), RagebotElements.RagebotCat, XorStr("rb_autowall_hitscan"));
	RagebotElements.Ragebot_Multipoint = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("multipoint"), XorStr("Adds more aimpoints to a hitbox"), RagebotElements.RagebotCat, XorStr("rb_multipoint"));
	RagebotElements.Ragebot_Multipoint_Scale = new MSlider(RagebotElements.Ragebot_Accuracy, XorStr("multipoint scale"), XorStr("Scale of the extended hitbox"), 0, 100, true, RagebotElements.RagebotCat, XorStr("rb_multipoint_scale"), true);
	//RagebotElements.Ragebot_Corrections_HeightAdjustment = new MDropdown(RagebotElements.Ragebot_Accuracy, XorStr("aimpoint adjustment"), XorStr("Adjusts the aimpoint"), RagebotElements.RagebotCat, XorStr("rb_heightadjustment"), std::vector<std::string>{XorStr("Off"), XorStr("MM"), XorStr("Nospread")});
	RagebotElements.Ragebot_Corrections_PositionAdjustment = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("position adjustment"), XorStr("Fixes fakelag and other things"), RagebotElements.RagebotCat, XorStr("rb_positionadjustment"));// , std::vector<string>{"Off"), XorStr("Adjust for Target"), XorStr("Floessen Fix"), XorStr("Wait"), XorStr("Manual"), XorStr("Backtrack"});
	RagebotElements.Ragebot_Corrections_Resolver = new MCheckbox(RagebotElements.Ragebot_Accuracy, XorStr("anti-aim correction"), XorStr("Fixes antiaim"), RagebotElements.RagebotCat, XorStr("rb_resolver"));// , std::vector<string>{"Off"), XorStr("Adjust for Target"), XorStr("Floessen Fix"), XorStr("Wait"), XorStr("Manual"), XorStr("Backtrack"});
	RagebotElements.Ragebot_MinDamage = new MSlider(RagebotElements.Ragebot_Accuracy, XorStr("minimum damage"), XorStr("Minimum damage to shoot at a part of the body (NOT AUTOWALL RELATED)"), 0, 100, true, RagebotElements.RagebotCat, XorStr("rb_mindamage"), true);
	//	RagebotElements.Ragebot_Hitchance = new MCheckbox(RagebotElements.Ragebot_Selection, XorStr("enable hitchance"), XorStr("Enable hitchance"), RagebotElements.RagebotCat, XorStr("rb_hitchance"));
	RagebotElements.Ragebot_Hitchance_Slider = new MSlider(RagebotElements.Ragebot_Accuracy, XorStr("hitchance"), XorStr("Hitchance percentage"), 0, 100, true, RagebotElements.RagebotCat, XorStr("rb_hitchance_value"), true);

}

void SetupVisualTab(MWindow* MainWindow)
{
	VisualElements.VisualCat = new MCategory(XorStr("visual"), MainWindow, 0, sizeof(0), 200, 200);
	VisualElements.Visual_Player = new MGroupbox2(VisualElements.VisualCat, XorStr("players"), 1, 1, 1, 2, false, 180, 300, 0, -10);
	VisualElements.Visual_Player_Active = new MCheckbox(VisualElements.Visual_Player, XorStr("active"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_active"));
	VisualElements.Visual_Player_EnemyOnly = new MCheckbox(VisualElements.Visual_Player, XorStr("enemy only"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_enemy_only"));
	VisualElements.Visual_Misc_Beams = new MCheckbox(VisualElements.Visual_Player, XorStr("bullet beams"), XorStr("Draws a beam to the place hit"), VisualElements.VisualCat, XorStr("vis_player_beams"));
	VisualElements.Visual_Player_Box = new MCheckbox(VisualElements.Visual_Player, XorStr("bounding box"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_box"));
	VisualElements.Visual_Player_Bones = new MCheckbox(VisualElements.Visual_Player, XorStr("skeleton"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_bones"));
	VisualElements.Visual_Player_Health = new MCheckbox(VisualElements.Visual_Player, XorStr("health"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_health"));
	VisualElements.Visual_Player_Armor = new MCheckbox(VisualElements.Visual_Player, XorStr("armor"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_armor"));
	VisualElements.Visual_Player_DLight = new MCheckbox(VisualElements.Visual_Player, XorStr("d-lights"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_dlight"));
	VisualElements.Visual_Player_Name = new MCheckbox(VisualElements.Visual_Player, XorStr("name"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_name"));
	VisualElements.Visual_Player_Weapon = new MCheckbox(VisualElements.Visual_Player, XorStr("weapon"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_weapon"));
	VisualElements.Visual_Player_Weapon_Ammo = new MCheckbox(VisualElements.Visual_Player, XorStr("ammo"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_ammo"));
	//VisualElements.Visual_Player_Weapon_All = new MCheckbox(VisualElements.Visual_Player, XorStr("All equipment"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_weapon_all"));
	//VisualElements.Visual_Player_Rank = new MCheckbox(VisualElements.Visual_Player, XorStr("rank"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_rank"));
	//VisualElements.Visual_Player_Wins = new MCheckbox(VisualElements.Visual_Player, XorStr("wins"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_wins"));
	VisualElements.Visual_Player_Glow = new MCheckbox(VisualElements.Visual_Player, XorStr("glow"), XorStr("Activates player visuals"), VisualElements.VisualCat, XorStr("vis_player_glow"));
	VisualElements.Visual_Player_Snaplines = new MCheckbox(VisualElements.Visual_Player, XorStr("tracers"), XorStr("Draws lines to the enemy"), VisualElements.VisualCat, XorStr("vis_player_snaplines"));



	VisualElements.Visual_Other = new MGroupbox2(VisualElements.VisualCat, XorStr("other"), 2, 1, 1, 1, false, 180, 300, 190, -10);
	VisualElements.Visual_Chams = new MGroupbox(VisualElements.Visual_Other, XorStr("chams"), 2, 1, 1, 1, true);
	VisualElements.Visual_Chams_Active = new MCheckbox(VisualElements.Visual_Chams, XorStr("active"), XorStr("Activate Chams"), VisualElements.VisualCat, XorStr("vis_chams_active"));
	VisualElements.Visual_Chams_Style = new MDropdown(VisualElements.Visual_Chams, XorStr("style"), XorStr("Select the style of the chams"), VisualElements.VisualCat, XorStr("vis_chams_style"), std::vector<string>{XorStr("Flat"), XorStr("Material"), "Glass"});
	VisualElements.Visual_Chams_EnemyOnly = new MCheckbox(VisualElements.Visual_Chams, XorStr("enemy only"), XorStr("Cham only enemies"), VisualElements.VisualCat, XorStr("vis_chams_enemyonly"));
	VisualElements.Visual_Chams_VisibleOnly = new MCheckbox(VisualElements.Visual_Chams, XorStr("visible only"), XorStr("Cham only visible"), VisualElements.VisualCat, XorStr("vis_chams_visibleonlu"));
	VisualElements.Visual_Misc_FChams = new MCheckbox(VisualElements.Visual_Chams, XorStr("fake angle ghost"), XorStr("Draws lines to the enemy"), VisualElements.VisualCat, XorStr("vis_chams_fake_angle_ghost"));

	VisualElements.Visual_CBaseEntity = new MGroupbox(VisualElements.Visual_Other, XorStr("world"), 2, 2, 1, 1, true);
	//VisualElements.Visual_CBaseEntity_Active = new MCheckbox(VisualElements.Visual_CBaseEntity, XorStr("active"), XorStr("Activates entity visuals"), VisualElements.VisualCat, XorStr("vis_entity_active"));
	VisualElements.Visual_CBaseEntity_Box = new MCheckbox(VisualElements.Visual_CBaseEntity, XorStr("bounding box"), XorStr("Draws a box around the entity"), VisualElements.VisualCat, XorStr("vis_entity_box"));
	VisualElements.Visual_CBaseEntity_Name = new MCheckbox(VisualElements.Visual_CBaseEntity, XorStr("name"), XorStr("Draws the name of the entity"), VisualElements.VisualCat, XorStr("vis_entity_name"));
	VisualElements.Visual_CBaseEntity_Glow = new MCheckbox(VisualElements.Visual_CBaseEntity, XorStr("glow"), XorStr("The entity glows"), VisualElements.VisualCat, XorStr("vis_entity_glow"));
	VisualElements.Visual_CBaseEntity_Filter = new MGroupbox(VisualElements.Visual_CBaseEntity, XorStr("filter"), 0, 0, 0, 0, true);
	VisualElements.Visual_CBaseEntity_C4 = new MCheckbox(VisualElements.Visual_CBaseEntity_Filter, XorStr("bomb"), XorStr("Draw the bombs"), VisualElements.VisualCat, XorStr("vis_entity_filter_bomb"));
	VisualElements.Visual_CBaseEntity_Weapons = new MCheckbox(VisualElements.Visual_CBaseEntity_Filter, XorStr("weapons"), XorStr("Draw the weapons"), VisualElements.VisualCat, XorStr("vis_entity_filter_weapons"));
	VisualElements.Visual_CBaseEntity_Hostages = new MCheckbox(VisualElements.Visual_CBaseEntity_Filter, XorStr("hostages"), XorStr("Draw the hostages"), VisualElements.VisualCat, XorStr("vis_entity_filter_hostages"));
	VisualElements.Visual_CBaseEntity_Grenades = new MCheckbox(VisualElements.Visual_CBaseEntity_Filter, XorStr("grenades"), XorStr("Draw the grenades"), VisualElements.VisualCat, XorStr("vis_entity_filter_grenades"));


	VisualElements.Visual_Misc = new MGroupbox2(VisualElements.VisualCat, XorStr("misc"), 3, 1, 1, 2, false, 180, 300, 375, -10);
	VisualElements.Visual_Misc_SelfESP = new MCheckbox(VisualElements.Visual_Misc, XorStr("self visuals"), XorStr("Draws visuals on the localplayer"), VisualElements.VisualCat, XorStr("vis_misc_self"));
	VisualElements.Visual_Misc_Hands = new MDropdown(VisualElements.Visual_Misc, XorStr("hands"), XorStr("Change the model of your hands"), VisualElements.VisualCat, XorStr("vis_misc_hands"), std::vector<string>{XorStr("Off"), XorStr("Colored"), XorStr("No Hands"), XorStr("Wireframe")});
	VisualElements.Visual_Misc_Weapon = new MDropdown(VisualElements.Visual_Misc, XorStr("weapon"), XorStr("Change the model of your weapon"), VisualElements.VisualCat, XorStr("vis_misc_weapon"), std::vector<string>{XorStr("Off"), XorStr("Colored"), XorStr("No Weapon"), XorStr("Wireframe")});
	VisualElements.Visual_Misc_Nightmode = new MCheckbox(VisualElements.Visual_Misc, XorStr("night mode"), XorStr("Enables nightmode"), VisualElements.VisualCat, XorStr("vis_misc_nightmode"));
	VisualElements.Visual_Misc_Skybox = new MDropdown(VisualElements.Visual_Misc, XorStr("custom skybox"), XorStr("Enables a custom skybox"), VisualElements.VisualCat, XorStr("vis_misc_skybox"), std::vector<std::string>{"Off", "Dawn", "Himalaya", "Mountains", "Jungle", "City", "Daylight", "Night", "Storm"});
	VisualElements.Visual_Misc_NoFlash = new MCheckbox(VisualElements.Visual_Misc, XorStr("no flash"), XorStr("Removes the flash effect"), VisualElements.VisualCat, XorStr("vis_misc_noflash"));
	VisualElements.Visual_Misc_NoSmoke = new MCheckbox(VisualElements.Visual_Misc, XorStr("no smoke"), XorStr("Removes the smoke"), VisualElements.VisualCat, XorStr("vis_misc_nosmoke"));
	VisualElements.Visual_Misc_NoScope = new MCheckbox(VisualElements.Visual_Misc, XorStr("no scope"), XorStr("Removes the black during scoping"), VisualElements.VisualCat, XorStr("vis_misc_noscope"));
	//VisualElements.Visual_Misc_NoParticles = new MCheckbox(VisualElements.Visual_Misc, XorStr("no particles"), XorStr("Removes the particles"), VisualElements.VisualCat, XorStr("vis_misc_noparticles"));
	VisualElements.Visual_Misc_NoRecoil = new MCheckbox(VisualElements.Visual_Misc, XorStr("no visual recoil"), XorStr("Removes the visual recoil"), VisualElements.VisualCat, XorStr("vis_misc_norecoil"));
	VisualElements.Visual_Misc_Hitmaker = new MDropdown(VisualElements.Visual_Misc, "hitmarker", "Enable Hitmarker", VisualElements.VisualCat, "vis_misc_hitmarker", std::vector<std::string>{"Off", "visual", "visual + sound"});
	VisualElements.Visual_Misc_GrenadePrediction = new MCheckbox(VisualElements.Visual_Misc, XorStr("grenade prediction"), XorStr("fucks niggers"), VisualElements.VisualCat, XorStr("vis_misc_grenadepred"));

}


void SetupSaveCat(MWindow* MainWindow)
{
	SaveElements.SavePanelCat = new MCategory(XorStr("config"), MainWindow, 0, sizeof(0), 512, 512);
	SaveElements.Save_Box = new MGroupbox2(SaveElements.SavePanelCat, "", 1, 1, 1.5f, 2, false, 500, 300, 0, -10);
	SaveElements.SavePanel = new MSavePanel(SaveElements.Save_Box);
//	SaveElements.SaveList = new MListBox(SaveElements.Save_Box, "List", "This is a list", SaveElements.SavePanelCat, "config_list_curconfig", Vector(100, 100), Vector(200, -10));
//	SaveElements.SaveList->AddChild("nigger");
}
/*
void SetupConfigCat(MWindow* MainWindow)
{
	MiscElements.MiscCat = new MCategory("colors", MainWindow, brush, sizeof(brush), 200, 200);
	ColorElements.Color_CT = new MGroupbox2(MiscElements.MiscCat, "counter terrorists", 1, 1, 1, 1, false, 180, 150, -5, -10);
	ColorElements.Color_CT_Visible = new MColorPicker(ColorElements.Color_CT, "visible", "", MiscElements.MiscCat, "color_ct_vis");
	ColorElements.Color_CT_Invisible = new MColorPicker(ColorElements.Color_CT, "invisible", "", MiscElements.MiscCat, "color_ct_invis");
	ColorElements.Color_CT_Visible_Cham = new MColorPicker(ColorElements.Color_CT, "chams visible", "", MiscElements.MiscCat, "color_ct_vis_cham");
	ColorElements.Color_CT_Invisible_Cham = new MColorPicker(ColorElements.Color_CT, "chams invisible", "", MiscElements.MiscCat, "color_ct_invis_cham");

	ColorElements.Color_T = new MGroupbox2(MiscElements.MiscCat, "terrorists", 1, 2, 1, 1, false, 180, 150, -5, 150);
	ColorElements.Color_T_Visible = new MColorPicker(ColorElements.Color_T, "visible", "", MiscElements.MiscCat, "color_t_vis");
	ColorElements.Color_T_Invisible = new MColorPicker(ColorElements.Color_T, "invisible", "", MiscElements.MiscCat, "color_t_invis");
	ColorElements.Color_T_Visible_Cham = new MColorPicker(ColorElements.Color_T, "chams visible", "", MiscElements.MiscCat, "color_t_vis_cham");
	ColorElements.Color_T_Invisible_Cham = new MColorPicker(ColorElements.Color_T, "chams invisible", "", MiscElements.MiscCat, "color_t_invis_cham");

	ColorElements.Color_Entities = new MGroupbox2(MiscElements.MiscCat, "world", 2, 1, 1, 1, false, 180, 300, 185, -10);
	ColorElements.Color_Weapon = new MColorPicker(ColorElements.Color_Entities, "weapon", "", MiscElements.MiscCat, "color_e_weapon");
	ColorElements.Color_Bomb = new MColorPicker(ColorElements.Color_Entities, "bomb", "", MiscElements.MiscCat, "color_e_bomb");
	ColorElements.Color_Planted_Bomb = new MColorPicker(ColorElements.Color_Entities, "planted bomb", "", MiscElements.MiscCat, "color_e_planted_bomb");
	ColorElements.Color_Hostage = new MColorPicker(ColorElements.Color_Entities, "hostage", "", MiscElements.MiscCat, "color_e_hostage");

	/*
	ColorElements.Color_Misc = new MGroupbox2(MiscElements.MiscCat, "misc", 2, 2, 1, 1, false, 180, 300, 375, -10);
	ColorElements.Color_Me_Visible = new MColorPicker(ColorElements.Color_Misc, "Local Visible", "", MiscElements.MiscCat, "color_misc_local_vis");
	ColorElements.Color_Me_Invisible = new MColorPicker(ColorElements.Color_Misc, "Local Invisible", "", MiscElements.MiscCat, "color_misc_local_invis");
	ColorElements.Color_Me_Visible_Cham = new MColorPicker(ColorElements.Color_Misc, "Chams Local Visible", "", MiscElements.MiscCat, "color_misc_local_vis_cham");
	ColorElements.Color_Me_Invisible_Cham = new MColorPicker(ColorElements.Color_Misc, "Chams Local Invisible", "", MiscElements.MiscCat, "color_misc_local_invis_cham");
	ColorElements.Color_Misc_Hands = new MColorPicker(ColorElements.Color_Misc, "Chams Hands", "", MiscElements.MiscCat, "color_misc_weapon");
	ColorElements.Color_Misc_Weapon = new MColorPicker(ColorElements.Color_Misc, "Chams Weapon", "", MiscElements.MiscCat, "color_misc_hands");
	
}*/

void SetupAntiAimCat(MWindow* MainWindow)
{
	auto aacat = new MCategory(XorStr("anti-aim"), MainWindow, 0, sizeof(0), 400, 382);
	RagebotElements.Ragebot_AntiAim = new MGroupbox2(aacat, XorStr("anti-aims"), 3, 1, 1, 1, false, 260, 300, 0, -10);
	RagebotElements.Ragebot_AntiAim_Active = new MCheckbox(RagebotElements.Ragebot_AntiAim, XorStr("active"), XorStr("Enables antiaim"), aacat, XorStr("rb_aa_active"));
	RagebotElements.Ragebot_AntiAim_Pitch = new MDropdown(RagebotElements.Ragebot_AntiAim, XorStr("pitch"), XorStr("Enables pitch antiaim"), aacat, XorStr("rb_aa_pitch"), std::vector<string>{XorStr("Off"), XorStr("emotion"), XorStr("down"), XorStr("up"), XorStr("fake-down"), XorStr("random"), XorStr("fake up"), "fake down", "fake zero down", "fake zero up"});
	RagebotElements.Ragebot_AntiAim_Yaw_Fake = new MDropdown(RagebotElements.Ragebot_AntiAim, XorStr("fake yaw"), XorStr("Enables fake yaw antiaim"), aacat, XorStr("rb_aa_yaw_fake"), std::vector<string>{XorStr("off"), "rotation", "spin", "backwards jitter", "lowerbody", "backwards spin", "static 2", "random lby", "sideways head", "lby update", "adpative 1", "custom"});
	RagebotElements.Ragebot_AntiAim_Yaw_Real = new MDropdown(RagebotElements.Ragebot_AntiAim, XorStr("real yaw"), XorStr("Enables real yaw antiaim"), aacat, XorStr("rb_aa_yaw_real"), std::vector<string>{XorStr("Off"), "rotation", "spin", "backwards jitter", "backwards", "fake lowerbody", "backwards spin", "static 2", "random lby", "sideways head", "lby update", "adpative 1", "custom"});
	RagebotElements.Ragebot_AntiAim_AtTargets = new MDropdown(RagebotElements.Ragebot_AntiAim, XorStr("at targets"), XorStr("Adjusts the antiaim to the targets"), aacat, XorStr("rb_aa_attarget"), std::vector<string>{XorStr("Off"), XorStr("nearest"), XorStr("everyone")});
	RagebotElements.Ragebot_AntiAim_FreeStand = new MDropdown(RagebotElements.Ragebot_AntiAim, XorStr("free standing"), XorStr("Enables edge antiaim"), aacat, XorStr("rb_aa_freestand"), std::vector<string>{XorStr("off"), XorStr("real"), XorStr("fake"), "fake 2"});

	RagebotElements.Ragebot_AntiAim_Disable_NoPlayers = new MCheckbox(RagebotElements.Ragebot_AntiAim, XorStr("disable aa with no enemies"), XorStr("Disable the antiaim if there are no enemy players"), aacat, XorStr("rb_aa_disable_noplayers"));

	RagebotElements.Ragebot_AntiAim_Custom = new MGroupbox2(aacat, XorStr("anti-aim builder"), 3, 2, 1, 1, false, 260, 300, 280, -10);
	RagebotElements.Ragebot_AntiAim_Custom_Fake_Yaw = new MSlider(RagebotElements.Ragebot_AntiAim_Custom, "fake", "Set your custom fake yaw", -180, 180, true, aacat, "rb_aa_c_fake_yaw", false);
	RagebotElements.Ragebot_AntiAim_Custom_Real_Yaw = new MSlider(RagebotElements.Ragebot_AntiAim_Custom, "real", "Set your custom real yaw", -180, 180, true, aacat, "rb_aa_c_real_yaw", false);
	//RagebotElements.Ragebot_AntiAim_Custom_Jitter_Range = new MSlider(RagebotElements.Ragebot_AntiAim_Custom, "jitter range", "Set your custom jitter range", 0, 180, true, aacat, "rb_aa_c_jitter_range", false);
	//RagebotElements.Ragebot_AntiAim_Custom_Rand_Jitter = new MCheckbox(RagebotElements.Ragebot_AntiAim_Custom, "randomise jitter range", "Selects a random float between 0 and your jitterrange to jitter", aacat, "rb_aa_c_jitter_range_randomise");
	RagebotElements.Ragebot_AntiAim_Custom_Mode = new MDropdown(RagebotElements.Ragebot_AntiAim_Custom, "mode", "Set your aa mode", aacat, "rb_aa_c_mode", std::vector<string>{"static", "changing"});
	RagebotElements.Ragebot_AntiAim_Custom_Dynamic = new MCheckbox(RagebotElements.Ragebot_AntiAim_Custom, "at targets", "Your yaw is dynamic according to At Targets", aacat, "rb_aa_c_dynamic");

}

CMenu::CMenu()
{

	MainWindow = new MWindow(XorStr("S U P R E M E"), Vector(500, 500), Vector(600, 400), true);

	//SkinChanger = new MMiniWindow(XorStr("Skinchanger"), Vector(1, 1), Vector(400, 500), MainWindow);
	//GlobalSkinchanger = new MSkinchanger(SkinChanger);
	//Sleep(200);

	SetupRagebotCat(MainWindow);
	SetupAntiAimCat(MainWindow);
//	SetupLegitCat(MainWindow);
	SetupVisualTab(MainWindow);
	SetupMiscCat(MainWindow);
	//SetupConfigCat(MainWindow);
	SetupSaveCat(MainWindow);

	

	this->initialized = true;

	MiniWindowElements.Playerlist = new MMiniWindow("Playerlist", Vector(200, 200), Vector(300, 400), nullptr, false);
	MiniWindowElements.Damagelist = new MMiniWindow("Damagelist", Vector(500, 300), Vector(250, 300), nullptr, true);
	global_damagelist = new MDamagelist(MiniWindowElements.Damagelist);
	MiniWindowElements.Skinchanger = new MMiniWindow("skin changer", Vector(800, 200), Vector(500, 550), nullptr, false);
	GlobalSkinchanger = new MSkinchanger(MiniWindowElements.Skinchanger);
}


void CMenu::SaveWindowState(std::string Filename)
{
	tinyxml2::XMLDocument Doc;

	// Root Element is called "ayy"
	tinyxml2::XMLElement *Root = Doc.NewElement(XorStr("Config"));
	Doc.LinkEndChild(Root);

	// If the window has some tabs..
	if (Root && MainWindow->Children.size() > 0)
	{
		for (auto Cat : MainWindow->Children)
		{
			MCategory* Category = (MCategory*)Cat;
			// Add a new section for this tab
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Category->name.c_str());
			Root->LinkEndChild(TabElement);

			// Now we itterate the controls this tab contains
			if (TabElement && Category->SaveChildren.size() > 0)
			{
				for (auto Control : Category->SaveChildren)
				{
					// If the control is ok to be saved
					if (Control &&  Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						// Create an element for the control
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						Utilities::Log(XorStr("Saving control %s"), Control->FileIdentifier.c_str());

						if (!ControlElement)
						{
							Utilities::Log(XorStr("Errorino :(XorStr("));
							return;
						}

						MCheckbox* cbx = nullptr;
						MDropdown* cbo = nullptr;
						MKeybind* key = nullptr;
						MSlider* sld = nullptr;
						MColorPicker* cpr = nullptr;
						MListBox* lst = nullptr;

						// Figure out what kind of control and data this is
						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (MCheckbox*)Control;
							ControlElement->SetText(cbx->Checked);
							break;
						case UIControlTypes::UIC_DropDown:
							cbo = (MDropdown*)Control;
							ControlElement->SetText(cbo->SelectedIndex);
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (MKeybind*)Control;
							ControlElement->SetText(key->Key);
							break;
						case UIControlTypes::UIC_Slider:
							sld = (MSlider*)Control;
							ControlElement->SetText(sld->value);
							break;
						case UIControlTypes::UIC_ColorPicker:
							cpr = (MColorPicker*)Control;

							char buf[256];
							sprintf_s(buf, "%d", cpr->color);

						//	std::string buffer = buf;

							ControlElement->SetText(buf);
							break;
						case UIControlTypes::UIC_Listbox:
							lst = (MListBox*)Control;

							char buf2[256];
							sprintf_s(buf2, "%d", lst->Selected);

							ControlElement->SetText(buf2);
							break;
						}
					}
				}
			}
		}
	}
	Filename.append(XorStr(".xml"));
	//Save the file
	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		MessageBox(NULL, XorStr("Failed To Save Config File!"), XorStr("ethereal"), MB_OK);
	}
}

void CMenu::LoadWindowState(std::string Filename)
{
	// Lets load our meme
	Filename.append(XorStr(".xml"));
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		// The root "ayy" element
		if (Root)
		{
			// If the window has some tabs..
			if (Root && MainWindow->Children.size() > 0)
			{
				for (auto Cat : MainWindow->Children)
				{
					MCategory* Category = (MCategory*)Cat;

					// We find the corresponding element for this tab
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Category->name.c_str());
					if (TabElement)
					{
						// Now we itterate the controls this tab contains
						if (TabElement && Category->SaveChildren.size() > 0)
						{
							for (auto Control : Category->SaveChildren)
							{
								// If the control is ok to be saved
								if (Control && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									// Get the controls element
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										//Utilities::Log(XorStr("We tryin to load fam"));
										MCheckbox* cbx = nullptr;
										MDropdown* cbo = nullptr;
										MKeybind* key = nullptr;
										MSlider* sld = nullptr;
										MColorPicker* cpr = nullptr;
										MListBox* lst = nullptr;

										// Figure out what kind of control and data this is
										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (MCheckbox*)Control;
											cbx->Checked = (ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_DropDown:
											cbo = (MDropdown*)Control;
											//cbo->SelectIndex(atoi(ControlElement->GetText()));
											cbo->SelectedIndex = (atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (MKeybind*)Control;
											key->Key = (atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (MSlider*)Control;
											sld->value = (atof(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_ColorPicker:
											DWORD doubleWord;

											cpr = (MColorPicker*)Control;

											cpr->color = (DWORD)(atoll(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Listbox:
											lst = (MListBox*)Control;
											lst->Selected = (stoi(ControlElement->GetText()));
											break;
										}
						
									}
								}
							}
						}
					}
				}
			}
		}
	}
}