#include "offsets.h"
#include <array>
class IClientRenderable;
class IClientNetworkable;
class IClientUnknown;
class IClientThinkable;
struct model_t;
class CBaseCombatWeapon;
#define ACTIVITY_NOT_AVAILABLE		-1



typedef enum
{
	ACT_INVALID = -1,			// So we have something more succint to check for than '-1'
	ACT_RESET = 0,				// Set m_Activity to this invalid value to force a reset to m_IdealActivity
	ACT_IDLE,
	ACT_TRANSITION,
	ACT_COVER,					// FIXME: obsolete? redundant with ACT_COVER_LOW?
	ACT_COVER_MED,				// FIXME: unsupported?
	ACT_COVER_LOW,				// FIXME: rename ACT_IDLE_CROUCH?
	ACT_WALK,
	ACT_WALK_AIM,
	ACT_WALK_CROUCH,
	ACT_WALK_CROUCH_AIM,
	ACT_RUN,
	ACT_RUN_AIM,
	ACT_RUN_CROUCH,
	ACT_RUN_CROUCH_AIM,
	ACT_RUN_PROTECTED,
	ACT_SCRIPT_CUSTOM_MOVE,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_RANGE_ATTACK1_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_RANGE_ATTACK2_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_DIERAGDOLL,
	ACT_FLY,				// Fly (and flap if appropriate)
	ACT_HOVER,
	ACT_GLIDE,
	ACT_SWIM,
	ACT_JUMP,
	ACT_HOP,				// vertical jump
	ACT_LEAP,				// long forward jump
	ACT_LAND,
	ACT_CLIMB_UP,
	ACT_CLIMB_DOWN,
	ACT_CLIMB_DISMOUNT,
	ACT_SHIPLADDER_UP,
	ACT_SHIPLADDER_DOWN,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,			// tuck and roll, left
	ACT_ROLL_RIGHT,			// tuck and roll, right
	ACT_TURN_LEFT,			// turn quickly left (stationary)
	ACT_TURN_RIGHT,			// turn quickly right (stationary)
	ACT_CROUCH,				// FIXME: obsolete? only used be soldier (the act of crouching down from a standing position)
	ACT_CROUCHIDLE,			// FIXME: obsolete? only used be soldier (holding body in crouched position (loops))
	ACT_STAND,				// FIXME: obsolete? should be transition (the act of standing from a crouched position)
	ACT_USE,
	ACT_ALIEN_BURROW_IDLE,
	ACT_ALIEN_BURROW_OUT,

	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,

	ACT_SIGNAL_ADVANCE,		// Squad handsignals, specific.
	ACT_SIGNAL_FORWARD,
	ACT_SIGNAL_GROUP,
	ACT_SIGNAL_HALT,
	ACT_SIGNAL_LEFT,
	ACT_SIGNAL_RIGHT,
	ACT_SIGNAL_TAKECOVER,

	ACT_LOOKBACK_RIGHT,		// look back over shoulder without turning around.
	ACT_LOOKBACK_LEFT,
	ACT_COWER,				// FIXME: unused, should be more extreme version of crouching
	ACT_SMALL_FLINCH,		// FIXME: needed? shouldn't flinching be down with overlays?
	ACT_BIG_FLINCH,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_RELOAD_START,
	ACT_RELOAD_FINISH,
	ACT_RELOAD_LOW,
	ACT_ARM,				// pull out gun, for instance
	ACT_DISARM,				// reholster gun
	ACT_DROP_WEAPON,
	ACT_DROP_WEAPON_SHOTGUN,
	ACT_PICKUP_GROUND,		// pick up something in front of you on the ground
	ACT_PICKUP_RACK,		// pick up something from a rack or shelf in front of you.
	ACT_IDLE_ANGRY,			// FIXME: being used as an combat ready idle?  alternate idle animation in which the monster is clearly agitated. (loop)

	ACT_IDLE_RELAXED,
	ACT_IDLE_STIMULATED,
	ACT_IDLE_AGITATED,
	ACT_IDLE_STEALTH,
	ACT_IDLE_HURT,

	ACT_WALK_RELAXED,
	ACT_WALK_STIMULATED,
	ACT_WALK_AGITATED,
	ACT_WALK_STEALTH,

	ACT_RUN_RELAXED,
	ACT_RUN_STIMULATED,
	ACT_RUN_AGITATED,
	ACT_RUN_STEALTH,

	ACT_IDLE_AIM_RELAXED,
	ACT_IDLE_AIM_STIMULATED,
	ACT_IDLE_AIM_AGITATED,
	ACT_IDLE_AIM_STEALTH,

	ACT_WALK_AIM_RELAXED,
	ACT_WALK_AIM_STIMULATED,
	ACT_WALK_AIM_AGITATED,
	ACT_WALK_AIM_STEALTH,

	ACT_RUN_AIM_RELAXED,
	ACT_RUN_AIM_STIMULATED,
	ACT_RUN_AIM_AGITATED,
	ACT_RUN_AIM_STEALTH,

	ACT_CROUCHIDLE_STIMULATED,
	ACT_CROUCHIDLE_AIM_STIMULATED,
	ACT_CROUCHIDLE_AGITATED,

	ACT_WALK_HURT,			// limp  (loop)
	ACT_RUN_HURT,			// limp  (loop)
	ACT_SPECIAL_ATTACK1,	// very monster specific special attacks.
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,		// FIXME: unused?  agitated idle.
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,		// killed a player, do a victory dance.
	ACT_DIE_HEADSHOT,		// die, hit in head. 
	ACT_DIE_CHESTSHOT,		// die, hit in chest
	ACT_DIE_GUTSHOT,		// die, hit in gut
	ACT_DIE_BACKSHOT,		// die, hit in back
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH_PHYSICS,
	ACT_FLINCH_HEAD_BACK,
	ACT_FLINCH_CHEST_BACK,
	ACT_FLINCH_STOMACH_BACK,
	ACT_FLINCH_CROUCH_FRONT,
	ACT_FLINCH_CROUCH_BACK,
	ACT_FLINCH_CROUCH_LEFT,
	ACT_FLINCH_CROUCH_RIGHT,

	ACT_IDLE_ON_FIRE,		// ON FIRE animations
	ACT_WALK_ON_FIRE,
	ACT_RUN_ON_FIRE,

	ACT_RAPPEL_LOOP,		// Rappel down a rope!

	ACT_180_LEFT,			// 180 degree left turn
	ACT_180_RIGHT,

	ACT_90_LEFT,			// 90 degree turns
	ACT_90_RIGHT,

	ACT_STEP_LEFT,			// Single steps
	ACT_STEP_RIGHT,
	ACT_STEP_BACK,
	ACT_STEP_FORE,

	ACT_GESTURE_RANGE_ATTACK1,
	ACT_GESTURE_RANGE_ATTACK2,
	ACT_GESTURE_MELEE_ATTACK1,
	ACT_GESTURE_MELEE_ATTACK2,
	ACT_GESTURE_RANGE_ATTACK1_LOW,	// FIXME: not used yet, crouched versions of the range attack
	ACT_GESTURE_RANGE_ATTACK2_LOW,	// FIXME: not used yet, crouched versions of the range attack

	ACT_MELEE_ATTACK_SWING_GESTURE,

	ACT_GESTURE_SMALL_FLINCH,
	ACT_GESTURE_BIG_FLINCH,
	ACT_GESTURE_FLINCH_BLAST,			// Startled by an explosion
	ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
	ACT_GESTURE_FLINCH_BLAST_DAMAGED,	// Damaged by an explosion
	ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
	ACT_GESTURE_FLINCH_HEAD,
	ACT_GESTURE_FLINCH_CHEST,
	ACT_GESTURE_FLINCH_STOMACH,
	ACT_GESTURE_FLINCH_LEFTARM,
	ACT_GESTURE_FLINCH_RIGHTARM,
	ACT_GESTURE_FLINCH_LEFTLEG,
	ACT_GESTURE_FLINCH_RIGHTLEG,

	ACT_GESTURE_TURN_LEFT,
	ACT_GESTURE_TURN_RIGHT,
	ACT_GESTURE_TURN_LEFT45,
	ACT_GESTURE_TURN_RIGHT45,
	ACT_GESTURE_TURN_LEFT90,
	ACT_GESTURE_TURN_RIGHT90,
	ACT_GESTURE_TURN_LEFT45_FLAT,
	ACT_GESTURE_TURN_RIGHT45_FLAT,
	ACT_GESTURE_TURN_LEFT90_FLAT,
	ACT_GESTURE_TURN_RIGHT90_FLAT,

	// HALF-LIFE 1 compatability stuff goes here. Temporary!
	ACT_BARNACLE_HIT,		// barnacle tongue hits a monster
	ACT_BARNACLE_PULL,		// barnacle is lifting the monster ( loop )
	ACT_BARNACLE_CHOMP,		// barnacle latches on to the monster
	ACT_BARNACLE_CHEW,		// barnacle is holding the monster in its mouth ( loop )

							// Sometimes, you just want to set an NPC's sequence to a sequence that doesn't actually
							// have an activity. The AI will reset the NPC's sequence to whatever its IDEAL activity
							// is, though. So if you set ideal activity to DO_NOT_DISTURB, the AI will not interfere
							// with the NPC's current sequence. (SJB)
							ACT_DO_NOT_DISTURB,

							ACT_SPECIFIC_SEQUENCE,

							// viewmodel (weapon) activities
							// FIXME: move these to the specific viewmodels, no need to make global
							ACT_VM_DRAW,
							ACT_VM_HOLSTER,
							ACT_VM_IDLE,
							ACT_VM_FIDGET,
							ACT_VM_PULLBACK,
							ACT_VM_PULLBACK_HIGH,
							ACT_VM_PULLBACK_LOW,
							ACT_VM_THROW,
							ACT_VM_PULLPIN,
							ACT_VM_PRIMARYATTACK,		// fire
							ACT_VM_SECONDARYATTACK,		// alt. fire
							ACT_VM_RELOAD,
							ACT_VM_DRYFIRE,				// fire with no ammo loaded.
							ACT_VM_HITLEFT,				// bludgeon, swing to left - hit (primary attk)
							ACT_VM_HITLEFT2,			// bludgeon, swing to left - hit (secondary attk)
							ACT_VM_HITRIGHT,			// bludgeon, swing to right - hit (primary attk)
							ACT_VM_HITRIGHT2,			// bludgeon, swing to right - hit (secondary attk)
							ACT_VM_HITCENTER,			// bludgeon, swing center - hit (primary attk)
							ACT_VM_HITCENTER2,			// bludgeon, swing center - hit (secondary attk)
							ACT_VM_MISSLEFT,			// bludgeon, swing to left - miss (primary attk)
							ACT_VM_MISSLEFT2,			// bludgeon, swing to left - miss (secondary attk)
							ACT_VM_MISSRIGHT,			// bludgeon, swing to right - miss (primary attk)
							ACT_VM_MISSRIGHT2,			// bludgeon, swing to right - miss (secondary attk)
							ACT_VM_MISSCENTER,			// bludgeon, swing center - miss (primary attk)
							ACT_VM_MISSCENTER2,			// bludgeon, swing center - miss (secondary attk)
							ACT_VM_HAULBACK,			// bludgeon, haul the weapon back for a hard strike (secondary attk)
							ACT_VM_SWINGHARD,			// bludgeon, release the hard strike (secondary attk)
							ACT_VM_SWINGMISS,
							ACT_VM_SWINGHIT,
							ACT_VM_IDLE_TO_LOWERED,
							ACT_VM_IDLE_LOWERED,
							ACT_VM_LOWERED_TO_IDLE,
							ACT_VM_RECOIL1,
							ACT_VM_RECOIL2,
							ACT_VM_RECOIL3,
							ACT_VM_PICKUP,
							ACT_VM_RELEASE,

							ACT_VM_ATTACH_SILENCER,
							ACT_VM_DETACH_SILENCER,

							//===========================
							// HL2 Specific Activities
							//===========================
							// SLAM	Specialty Activities
							ACT_SLAM_STICKWALL_IDLE,
							ACT_SLAM_STICKWALL_ND_IDLE,
							ACT_SLAM_STICKWALL_ATTACH,
							ACT_SLAM_STICKWALL_ATTACH2,
							ACT_SLAM_STICKWALL_ND_ATTACH,
							ACT_SLAM_STICKWALL_ND_ATTACH2,
							ACT_SLAM_STICKWALL_DETONATE,
							ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
							ACT_SLAM_STICKWALL_DRAW,
							ACT_SLAM_STICKWALL_ND_DRAW,
							ACT_SLAM_STICKWALL_TO_THROW,
							ACT_SLAM_STICKWALL_TO_THROW_ND,
							ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
							ACT_SLAM_THROW_IDLE,
							ACT_SLAM_THROW_ND_IDLE,
							ACT_SLAM_THROW_THROW,
							ACT_SLAM_THROW_THROW2,
							ACT_SLAM_THROW_THROW_ND,
							ACT_SLAM_THROW_THROW_ND2,
							ACT_SLAM_THROW_DRAW,
							ACT_SLAM_THROW_ND_DRAW,
							ACT_SLAM_THROW_TO_STICKWALL,
							ACT_SLAM_THROW_TO_STICKWALL_ND,
							ACT_SLAM_THROW_DETONATE,
							ACT_SLAM_THROW_DETONATOR_HOLSTER,
							ACT_SLAM_THROW_TO_TRIPMINE_ND,
							ACT_SLAM_TRIPMINE_IDLE,
							ACT_SLAM_TRIPMINE_DRAW,
							ACT_SLAM_TRIPMINE_ATTACH,
							ACT_SLAM_TRIPMINE_ATTACH2,
							ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
							ACT_SLAM_TRIPMINE_TO_THROW_ND,
							ACT_SLAM_DETONATOR_IDLE,
							ACT_SLAM_DETONATOR_DRAW,
							ACT_SLAM_DETONATOR_DETONATE,
							ACT_SLAM_DETONATOR_HOLSTER,
							ACT_SLAM_DETONATOR_STICKWALL_DRAW,
							ACT_SLAM_DETONATOR_THROW_DRAW,

							// Shotgun Specialty Activities
							ACT_SHOTGUN_RELOAD_START,
							ACT_SHOTGUN_RELOAD_FINISH,
							ACT_SHOTGUN_PUMP,

							// SMG2 special activities
							ACT_SMG2_IDLE2,
							ACT_SMG2_FIRE2,
							ACT_SMG2_DRAW2,
							ACT_SMG2_RELOAD2,
							ACT_SMG2_DRYFIRE2,
							ACT_SMG2_TOAUTO,
							ACT_SMG2_TOBURST,

							// Physcannon special activities
							ACT_PHYSCANNON_UPGRADE,

							// weapon override activities
							ACT_RANGE_ATTACK_AR1,
							ACT_RANGE_ATTACK_AR2,
							ACT_RANGE_ATTACK_AR2_LOW,
							ACT_RANGE_ATTACK_AR2_GRENADE,
							ACT_RANGE_ATTACK_HMG1,
							ACT_RANGE_ATTACK_ML,
							ACT_RANGE_ATTACK_SMG1,
							ACT_RANGE_ATTACK_SMG1_LOW,
							ACT_RANGE_ATTACK_SMG2,
							ACT_RANGE_ATTACK_SHOTGUN,
							ACT_RANGE_ATTACK_SHOTGUN_LOW,
							ACT_RANGE_ATTACK_PISTOL,
							ACT_RANGE_ATTACK_PISTOL_LOW,
							ACT_RANGE_ATTACK_SLAM,
							ACT_RANGE_ATTACK_TRIPWIRE,
							ACT_RANGE_ATTACK_THROW,
							ACT_RANGE_ATTACK_SNIPER_RIFLE,
							ACT_RANGE_ATTACK_RPG,
							ACT_MELEE_ATTACK_SWING,

							ACT_RANGE_AIM_LOW,
							ACT_RANGE_AIM_SMG1_LOW,
							ACT_RANGE_AIM_PISTOL_LOW,
							ACT_RANGE_AIM_AR2_LOW,

							ACT_COVER_PISTOL_LOW,
							ACT_COVER_SMG1_LOW,

							// weapon override activities
							ACT_GESTURE_RANGE_ATTACK_AR1,
							ACT_GESTURE_RANGE_ATTACK_AR2,
							ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
							ACT_GESTURE_RANGE_ATTACK_HMG1,
							ACT_GESTURE_RANGE_ATTACK_ML,
							ACT_GESTURE_RANGE_ATTACK_SMG1,
							ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
							ACT_GESTURE_RANGE_ATTACK_SMG2,
							ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
							ACT_GESTURE_RANGE_ATTACK_PISTOL,
							ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
							ACT_GESTURE_RANGE_ATTACK_SLAM,
							ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
							ACT_GESTURE_RANGE_ATTACK_THROW,
							ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
							ACT_GESTURE_MELEE_ATTACK_SWING,

							ACT_IDLE_RIFLE,
							ACT_IDLE_SMG1,
							ACT_IDLE_ANGRY_SMG1,
							ACT_IDLE_PISTOL,
							ACT_IDLE_ANGRY_PISTOL,
							ACT_IDLE_ANGRY_SHOTGUN,
							ACT_IDLE_STEALTH_PISTOL,

							ACT_IDLE_PACKAGE,
							ACT_WALK_PACKAGE,
							ACT_IDLE_SUITCASE,
							ACT_WALK_SUITCASE,

							ACT_IDLE_SMG1_RELAXED,
							ACT_IDLE_SMG1_STIMULATED,
							ACT_WALK_RIFLE_RELAXED,
							ACT_RUN_RIFLE_RELAXED,
							ACT_WALK_RIFLE_STIMULATED,
							ACT_RUN_RIFLE_STIMULATED,

							ACT_IDLE_AIM_RIFLE_STIMULATED,
							ACT_WALK_AIM_RIFLE_STIMULATED,
							ACT_RUN_AIM_RIFLE_STIMULATED,

							ACT_IDLE_SHOTGUN_RELAXED,
							ACT_IDLE_SHOTGUN_STIMULATED,
							ACT_IDLE_SHOTGUN_AGITATED,

							// Policing activities
							ACT_WALK_ANGRY,
							ACT_POLICE_HARASS1,
							ACT_POLICE_HARASS2,

							// Manned guns
							ACT_IDLE_MANNEDGUN,

							// Melee weapon
							ACT_IDLE_MELEE,
							ACT_IDLE_ANGRY_MELEE,

							// RPG activities
							ACT_IDLE_RPG_RELAXED,
							ACT_IDLE_RPG,
							ACT_IDLE_ANGRY_RPG,
							ACT_COVER_LOW_RPG,
							ACT_WALK_RPG,
							ACT_RUN_RPG,
							ACT_WALK_CROUCH_RPG,
							ACT_RUN_CROUCH_RPG,
							ACT_WALK_RPG_RELAXED,
							ACT_RUN_RPG_RELAXED,

							ACT_WALK_RIFLE,
							ACT_WALK_AIM_RIFLE,
							ACT_WALK_CROUCH_RIFLE,
							ACT_WALK_CROUCH_AIM_RIFLE,
							ACT_RUN_RIFLE,
							ACT_RUN_AIM_RIFLE,
							ACT_RUN_CROUCH_RIFLE,
							ACT_RUN_CROUCH_AIM_RIFLE,
							ACT_RUN_STEALTH_PISTOL,

							ACT_WALK_AIM_SHOTGUN,
							ACT_RUN_AIM_SHOTGUN,

							ACT_WALK_PISTOL,
							ACT_RUN_PISTOL,
							ACT_WALK_AIM_PISTOL,
							ACT_RUN_AIM_PISTOL,
							ACT_WALK_STEALTH_PISTOL,
							ACT_WALK_AIM_STEALTH_PISTOL,
							ACT_RUN_AIM_STEALTH_PISTOL,

							// Reloads
							ACT_RELOAD_PISTOL,
							ACT_RELOAD_PISTOL_LOW,
							ACT_RELOAD_SMG1,
							ACT_RELOAD_SMG1_LOW,
							ACT_RELOAD_SHOTGUN,
							ACT_RELOAD_SHOTGUN_LOW,

							ACT_GESTURE_RELOAD,
							ACT_GESTURE_RELOAD_PISTOL,
							ACT_GESTURE_RELOAD_SMG1,
							ACT_GESTURE_RELOAD_SHOTGUN,

							// Busy animations
							ACT_BUSY_LEAN_LEFT,
							ACT_BUSY_LEAN_LEFT_ENTRY,
							ACT_BUSY_LEAN_LEFT_EXIT,
							ACT_BUSY_LEAN_BACK,
							ACT_BUSY_LEAN_BACK_ENTRY,
							ACT_BUSY_LEAN_BACK_EXIT,
							ACT_BUSY_SIT_GROUND,
							ACT_BUSY_SIT_GROUND_ENTRY,
							ACT_BUSY_SIT_GROUND_EXIT,
							ACT_BUSY_SIT_CHAIR,
							ACT_BUSY_SIT_CHAIR_ENTRY,
							ACT_BUSY_SIT_CHAIR_EXIT,
							ACT_BUSY_STAND,
							ACT_BUSY_QUEUE,

							// Dodge animations
							ACT_DUCK_DODGE,

							// For NPCs being lifted/eaten by barnacles:
							// being swallowed by a barnacle
							ACT_DIE_BARNACLE_SWALLOW,
							// being lifted by a barnacle
							ACT_GESTURE_BARNACLE_STRANGLE,

							ACT_PHYSCANNON_DETACH,	// An activity to be played if we're picking this up with the physcannon
							ACT_PHYSCANNON_ANIMATE, // An activity to be played by an object being picked up with the physcannon, but has different behavior to DETACH
							ACT_PHYSCANNON_ANIMATE_PRE,	// An activity to be played by an object being picked up with the physcannon, before playing the ACT_PHYSCANNON_ANIMATE
							ACT_PHYSCANNON_ANIMATE_POST,// An activity to be played by an object being picked up with the physcannon, after playing the ACT_PHYSCANNON_ANIMATE

							ACT_DIE_FRONTSIDE,
							ACT_DIE_RIGHTSIDE,
							ACT_DIE_BACKSIDE,
							ACT_DIE_LEFTSIDE,

							ACT_OPEN_DOOR,

							// Dynamic interactions
							ACT_DI_ALYX_ZOMBIE_MELEE,
							ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
							ACT_DI_ALYX_HEADCRAB_MELEE,
							ACT_DI_ALYX_ANTLION,

							ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
							ACT_DI_ALYX_ZOMBIE_SHOTGUN26,

							ACT_READINESS_RELAXED_TO_STIMULATED,
							ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
							ACT_READINESS_AGITATED_TO_STIMULATED,
							ACT_READINESS_STIMULATED_TO_RELAXED,

							ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
							ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
							ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
							ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,

							ACT_IDLE_CARRY,
							ACT_WALK_CARRY,

							//===========================
							// TF2 Specific Activities
							//===========================
							ACT_STARTDYING,
							ACT_DYINGLOOP,
							ACT_DYINGTODEAD,

							ACT_RIDE_MANNED_GUN,

							// All viewmodels
							ACT_VM_SPRINT_ENTER,
							ACT_VM_SPRINT_IDLE,
							ACT_VM_SPRINT_LEAVE,

							// Looping weapon firing
							ACT_FIRE_START,
							ACT_FIRE_LOOP,
							ACT_FIRE_END,

							ACT_CROUCHING_GRENADEIDLE,
							ACT_CROUCHING_GRENADEREADY,
							ACT_CROUCHING_PRIMARYATTACK,
							ACT_OVERLAY_GRENADEIDLE,
							ACT_OVERLAY_GRENADEREADY,
							ACT_OVERLAY_PRIMARYATTACK,
							ACT_OVERLAY_SHIELD_UP,
							ACT_OVERLAY_SHIELD_DOWN,
							ACT_OVERLAY_SHIELD_UP_IDLE,
							ACT_OVERLAY_SHIELD_ATTACK,
							ACT_OVERLAY_SHIELD_KNOCKBACK,
							ACT_SHIELD_UP,
							ACT_SHIELD_DOWN,
							ACT_SHIELD_UP_IDLE,
							ACT_SHIELD_ATTACK,
							ACT_SHIELD_KNOCKBACK,
							ACT_CROUCHING_SHIELD_UP,
							ACT_CROUCHING_SHIELD_DOWN,
							ACT_CROUCHING_SHIELD_UP_IDLE,
							ACT_CROUCHING_SHIELD_ATTACK,
							ACT_CROUCHING_SHIELD_KNOCKBACK,

							// turning in place
							ACT_TURNRIGHT45,
							ACT_TURNLEFT45,

							ACT_TURN,

							ACT_OBJ_ASSEMBLING,
							ACT_OBJ_DISMANTLING,
							ACT_OBJ_STARTUP,
							ACT_OBJ_RUNNING,
							ACT_OBJ_IDLE,
							ACT_OBJ_PLACING,
							ACT_OBJ_DETERIORATING,
							ACT_OBJ_UPGRADING,

							// Deploy
							ACT_DEPLOY,
							ACT_DEPLOY_IDLE,
							ACT_UNDEPLOY,

							// Crossbow
							ACT_CROSSBOW_DRAW_UNLOADED,

							// Gauss
							ACT_GAUSS_SPINUP,
							ACT_GAUSS_SPINCYCLE,

							//===========================
							// CSPort Specific Activities
							//===========================

							ACT_VM_PRIMARYATTACK_SILENCED,		// fire
							ACT_VM_RELOAD_SILENCED,
							ACT_VM_DRYFIRE_SILENCED,				// fire with no ammo loaded.
							ACT_VM_IDLE_SILENCED,
							ACT_VM_DRAW_SILENCED,
							ACT_VM_IDLE_EMPTY_LEFT,
							ACT_VM_DRYFIRE_LEFT,

							// new for CS2
							ACT_VM_IS_DRAW,
							ACT_VM_IS_HOLSTER,
							ACT_VM_IS_IDLE,
							ACT_VM_IS_PRIMARYATTACK,

							ACT_PLAYER_IDLE_FIRE,
							ACT_PLAYER_CROUCH_FIRE,
							ACT_PLAYER_CROUCH_WALK_FIRE,
							ACT_PLAYER_WALK_FIRE,
							ACT_PLAYER_RUN_FIRE,

							ACT_IDLETORUN,
							ACT_RUNTOIDLE,

							ACT_VM_DRAW_DEPLOYED,

							ACT_HL2MP_IDLE_MELEE,
							ACT_HL2MP_RUN_MELEE,
							ACT_HL2MP_IDLE_CROUCH_MELEE,
							ACT_HL2MP_WALK_CROUCH_MELEE,
							ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
							ACT_HL2MP_GESTURE_RELOAD_MELEE,
							ACT_HL2MP_JUMP_MELEE,

							// Portal!
							ACT_VM_FIZZLE,

							// Multiplayer
							ACT_MP_STAND_IDLE,
							ACT_MP_CROUCH_IDLE,
							ACT_MP_CROUCH_DEPLOYED_IDLE,
							ACT_MP_CROUCH_DEPLOYED,
							ACT_MP_DEPLOYED_IDLE,
							ACT_MP_RUN,
							ACT_MP_WALK,
							ACT_MP_AIRWALK,
							ACT_MP_CROUCHWALK,
							ACT_MP_SPRINT,
							ACT_MP_JUMP,
							ACT_MP_JUMP_START,
							ACT_MP_JUMP_FLOAT,
							ACT_MP_JUMP_LAND,
							ACT_MP_DOUBLEJUMP,
							ACT_MP_SWIM,
							ACT_MP_DEPLOYED,
							ACT_MP_SWIM_DEPLOYED,
							ACT_MP_VCD,

							ACT_MP_ATTACK_STAND_PRIMARYFIRE,
							ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
							ACT_MP_ATTACK_STAND_SECONDARYFIRE,
							ACT_MP_ATTACK_STAND_GRENADE,
							ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
							ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
							ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
							ACT_MP_ATTACK_CROUCH_GRENADE,
							ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
							ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
							ACT_MP_ATTACK_SWIM_GRENADE,
							ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
							ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
							ACT_MP_ATTACK_AIRWALK_GRENADE,
							ACT_MP_RELOAD_STAND,
							ACT_MP_RELOAD_STAND_LOOP,
							ACT_MP_RELOAD_STAND_END,
							ACT_MP_RELOAD_CROUCH,
							ACT_MP_RELOAD_CROUCH_LOOP,
							ACT_MP_RELOAD_CROUCH_END,
							ACT_MP_RELOAD_SWIM,
							ACT_MP_RELOAD_SWIM_LOOP,
							ACT_MP_RELOAD_SWIM_END,
							ACT_MP_RELOAD_AIRWALK,
							ACT_MP_RELOAD_AIRWALK_LOOP,
							ACT_MP_RELOAD_AIRWALK_END,
							ACT_MP_ATTACK_STAND_PREFIRE,
							ACT_MP_ATTACK_STAND_POSTFIRE,
							ACT_MP_ATTACK_STAND_STARTFIRE,
							ACT_MP_ATTACK_CROUCH_PREFIRE,
							ACT_MP_ATTACK_CROUCH_POSTFIRE,
							ACT_MP_ATTACK_SWIM_PREFIRE,
							ACT_MP_ATTACK_SWIM_POSTFIRE,

							// Multiplayer - Primary
							ACT_MP_STAND_PRIMARY,
							ACT_MP_CROUCH_PRIMARY,
							ACT_MP_RUN_PRIMARY,
							ACT_MP_WALK_PRIMARY,
							ACT_MP_AIRWALK_PRIMARY,
							ACT_MP_CROUCHWALK_PRIMARY,
							ACT_MP_JUMP_PRIMARY,
							ACT_MP_JUMP_START_PRIMARY,
							ACT_MP_JUMP_FLOAT_PRIMARY,
							ACT_MP_JUMP_LAND_PRIMARY,
							ACT_MP_SWIM_PRIMARY,
							ACT_MP_DEPLOYED_PRIMARY,
							ACT_MP_SWIM_DEPLOYED_PRIMARY,

							ACT_MP_ATTACK_STAND_PRIMARY,		// RUN, WALK
							ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
							ACT_MP_ATTACK_CROUCH_PRIMARY,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
							ACT_MP_ATTACK_SWIM_PRIMARY,
							ACT_MP_ATTACK_AIRWALK_PRIMARY,

							ACT_MP_RELOAD_STAND_PRIMARY,		// RUN, WALK
							ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
							ACT_MP_RELOAD_STAND_PRIMARY_END,
							ACT_MP_RELOAD_CROUCH_PRIMARY,		// CROUCHWALK
							ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
							ACT_MP_RELOAD_CROUCH_PRIMARY_END,
							ACT_MP_RELOAD_SWIM_PRIMARY,
							ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
							ACT_MP_RELOAD_SWIM_PRIMARY_END,
							ACT_MP_RELOAD_AIRWALK_PRIMARY,
							ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
							ACT_MP_RELOAD_AIRWALK_PRIMARY_END,

							ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
							ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,

							// Secondary
							ACT_MP_STAND_SECONDARY,
							ACT_MP_CROUCH_SECONDARY,
							ACT_MP_RUN_SECONDARY,
							ACT_MP_WALK_SECONDARY,
							ACT_MP_AIRWALK_SECONDARY,
							ACT_MP_CROUCHWALK_SECONDARY,
							ACT_MP_JUMP_SECONDARY,
							ACT_MP_JUMP_START_SECONDARY,
							ACT_MP_JUMP_FLOAT_SECONDARY,
							ACT_MP_JUMP_LAND_SECONDARY,
							ACT_MP_SWIM_SECONDARY,

							ACT_MP_ATTACK_STAND_SECONDARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_SECONDARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_SECONDARY,
							ACT_MP_ATTACK_AIRWALK_SECONDARY,

							ACT_MP_RELOAD_STAND_SECONDARY,		// RUN, WALK
							ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
							ACT_MP_RELOAD_STAND_SECONDARY_END,
							ACT_MP_RELOAD_CROUCH_SECONDARY,		// CROUCHWALK
							ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
							ACT_MP_RELOAD_CROUCH_SECONDARY_END,
							ACT_MP_RELOAD_SWIM_SECONDARY,
							ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
							ACT_MP_RELOAD_SWIM_SECONDARY_END,
							ACT_MP_RELOAD_AIRWALK_SECONDARY,
							ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
							ACT_MP_RELOAD_AIRWALK_SECONDARY_END,

							ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
							ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,

							// Melee
							ACT_MP_STAND_MELEE,
							ACT_MP_CROUCH_MELEE,
							ACT_MP_RUN_MELEE,
							ACT_MP_WALK_MELEE,
							ACT_MP_AIRWALK_MELEE,
							ACT_MP_CROUCHWALK_MELEE,
							ACT_MP_JUMP_MELEE,
							ACT_MP_JUMP_START_MELEE,
							ACT_MP_JUMP_FLOAT_MELEE,
							ACT_MP_JUMP_LAND_MELEE,
							ACT_MP_SWIM_MELEE,

							ACT_MP_ATTACK_STAND_MELEE,		// RUN, WALK
							ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
							ACT_MP_ATTACK_CROUCH_MELEE,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
							ACT_MP_ATTACK_SWIM_MELEE,
							ACT_MP_ATTACK_AIRWALK_MELEE,

							ACT_MP_ATTACK_STAND_GRENADE_MELEE,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
							ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,

							// Item1
							ACT_MP_STAND_ITEM1,
							ACT_MP_CROUCH_ITEM1,
							ACT_MP_RUN_ITEM1,
							ACT_MP_WALK_ITEM1,
							ACT_MP_AIRWALK_ITEM1,
							ACT_MP_CROUCHWALK_ITEM1,
							ACT_MP_JUMP_ITEM1,
							ACT_MP_JUMP_START_ITEM1,
							ACT_MP_JUMP_FLOAT_ITEM1,
							ACT_MP_JUMP_LAND_ITEM1,
							ACT_MP_SWIM_ITEM1,

							ACT_MP_ATTACK_STAND_ITEM1,		// RUN, WALK
							ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
							ACT_MP_ATTACK_CROUCH_ITEM1,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
							ACT_MP_ATTACK_SWIM_ITEM1,
							ACT_MP_ATTACK_AIRWALK_ITEM1,

							// Item2
							ACT_MP_STAND_ITEM2,
							ACT_MP_CROUCH_ITEM2,
							ACT_MP_RUN_ITEM2,
							ACT_MP_WALK_ITEM2,
							ACT_MP_AIRWALK_ITEM2,
							ACT_MP_CROUCHWALK_ITEM2,
							ACT_MP_JUMP_ITEM2,
							ACT_MP_JUMP_START_ITEM2,
							ACT_MP_JUMP_FLOAT_ITEM2,
							ACT_MP_JUMP_LAND_ITEM2,
							ACT_MP_SWIM_ITEM2,

							ACT_MP_ATTACK_STAND_ITEM2,		// RUN, WALK
							ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
							ACT_MP_ATTACK_CROUCH_ITEM2,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
							ACT_MP_ATTACK_SWIM_ITEM2,
							ACT_MP_ATTACK_AIRWALK_ITEM2,

							// Flinches
							ACT_MP_GESTURE_FLINCH,
							ACT_MP_GESTURE_FLINCH_PRIMARY,
							ACT_MP_GESTURE_FLINCH_SECONDARY,
							ACT_MP_GESTURE_FLINCH_MELEE,
							ACT_MP_GESTURE_FLINCH_ITEM1,
							ACT_MP_GESTURE_FLINCH_ITEM2,

							ACT_MP_GESTURE_FLINCH_HEAD,
							ACT_MP_GESTURE_FLINCH_CHEST,
							ACT_MP_GESTURE_FLINCH_STOMACH,
							ACT_MP_GESTURE_FLINCH_LEFTARM,
							ACT_MP_GESTURE_FLINCH_RIGHTARM,
							ACT_MP_GESTURE_FLINCH_LEFTLEG,
							ACT_MP_GESTURE_FLINCH_RIGHTLEG,

							// Team Fortress specific - medic heal, medic infect, etc.....
							ACT_MP_GRENADE1_DRAW,
							ACT_MP_GRENADE1_IDLE,
							ACT_MP_GRENADE1_ATTACK,
							ACT_MP_GRENADE2_DRAW,
							ACT_MP_GRENADE2_IDLE,
							ACT_MP_GRENADE2_ATTACK,

							ACT_MP_PRIMARY_GRENADE1_DRAW,
							ACT_MP_PRIMARY_GRENADE1_IDLE,
							ACT_MP_PRIMARY_GRENADE1_ATTACK,
							ACT_MP_PRIMARY_GRENADE2_DRAW,
							ACT_MP_PRIMARY_GRENADE2_IDLE,
							ACT_MP_PRIMARY_GRENADE2_ATTACK,

							ACT_MP_SECONDARY_GRENADE1_DRAW,
							ACT_MP_SECONDARY_GRENADE1_IDLE,
							ACT_MP_SECONDARY_GRENADE1_ATTACK,
							ACT_MP_SECONDARY_GRENADE2_DRAW,
							ACT_MP_SECONDARY_GRENADE2_IDLE,
							ACT_MP_SECONDARY_GRENADE2_ATTACK,

							ACT_MP_MELEE_GRENADE1_DRAW,
							ACT_MP_MELEE_GRENADE1_IDLE,
							ACT_MP_MELEE_GRENADE1_ATTACK,
							ACT_MP_MELEE_GRENADE2_DRAW,
							ACT_MP_MELEE_GRENADE2_IDLE,
							ACT_MP_MELEE_GRENADE2_ATTACK,

							ACT_MP_ITEM1_GRENADE1_DRAW,
							ACT_MP_ITEM1_GRENADE1_IDLE,
							ACT_MP_ITEM1_GRENADE1_ATTACK,
							ACT_MP_ITEM1_GRENADE2_DRAW,
							ACT_MP_ITEM1_GRENADE2_IDLE,
							ACT_MP_ITEM1_GRENADE2_ATTACK,

							ACT_MP_ITEM2_GRENADE1_DRAW,
							ACT_MP_ITEM2_GRENADE1_IDLE,
							ACT_MP_ITEM2_GRENADE1_ATTACK,
							ACT_MP_ITEM2_GRENADE2_DRAW,
							ACT_MP_ITEM2_GRENADE2_IDLE,
							ACT_MP_ITEM2_GRENADE2_ATTACK,

							// Building
							ACT_MP_STAND_BUILDING,
							ACT_MP_CROUCH_BUILDING,
							ACT_MP_RUN_BUILDING,
							ACT_MP_WALK_BUILDING,
							ACT_MP_AIRWALK_BUILDING,
							ACT_MP_CROUCHWALK_BUILDING,
							ACT_MP_JUMP_BUILDING,
							ACT_MP_JUMP_START_BUILDING,
							ACT_MP_JUMP_FLOAT_BUILDING,
							ACT_MP_JUMP_LAND_BUILDING,
							ACT_MP_SWIM_BUILDING,

							ACT_MP_ATTACK_STAND_BUILDING,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_BUILDING,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_BUILDING,
							ACT_MP_ATTACK_AIRWALK_BUILDING,

							ACT_MP_ATTACK_STAND_GRENADE_BUILDING,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
							ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,

							ACT_MP_STAND_PDA,
							ACT_MP_CROUCH_PDA,
							ACT_MP_RUN_PDA,
							ACT_MP_WALK_PDA,
							ACT_MP_AIRWALK_PDA,
							ACT_MP_CROUCHWALK_PDA,
							ACT_MP_JUMP_PDA,
							ACT_MP_JUMP_START_PDA,
							ACT_MP_JUMP_FLOAT_PDA,
							ACT_MP_JUMP_LAND_PDA,
							ACT_MP_SWIM_PDA,

							ACT_MP_ATTACK_STAND_PDA,
							ACT_MP_ATTACK_SWIM_PDA,

							ACT_MP_GESTURE_VC_HANDMOUTH,
							ACT_MP_GESTURE_VC_FINGERPOINT,
							ACT_MP_GESTURE_VC_FISTPUMP,
							ACT_MP_GESTURE_VC_THUMBSUP,
							ACT_MP_GESTURE_VC_NODYES,
							ACT_MP_GESTURE_VC_NODNO,

							ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
							ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
							ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
							ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
							ACT_MP_GESTURE_VC_NODYES_PRIMARY,
							ACT_MP_GESTURE_VC_NODNO_PRIMARY,

							ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
							ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
							ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
							ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
							ACT_MP_GESTURE_VC_NODYES_SECONDARY,
							ACT_MP_GESTURE_VC_NODNO_SECONDARY,

							ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
							ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
							ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
							ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
							ACT_MP_GESTURE_VC_NODYES_MELEE,
							ACT_MP_GESTURE_VC_NODNO_MELEE,

							ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
							ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
							ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
							ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
							ACT_MP_GESTURE_VC_NODYES_ITEM1,
							ACT_MP_GESTURE_VC_NODNO_ITEM1,

							ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
							ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
							ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
							ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
							ACT_MP_GESTURE_VC_NODYES_ITEM2,
							ACT_MP_GESTURE_VC_NODNO_ITEM2,

							ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
							ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
							ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
							ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
							ACT_MP_GESTURE_VC_NODYES_BUILDING,
							ACT_MP_GESTURE_VC_NODNO_BUILDING,

							ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
							ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
							ACT_MP_GESTURE_VC_FISTPUMP_PDA,
							ACT_MP_GESTURE_VC_THUMBSUP_PDA,
							ACT_MP_GESTURE_VC_NODYES_PDA,
							ACT_MP_GESTURE_VC_NODNO_PDA,


							ACT_VM_UNUSABLE,
							ACT_VM_UNUSABLE_TO_USABLE,
							ACT_VM_USABLE_TO_UNUSABLE,

							// Specific viewmodel activities for weapon roles
							ACT_PRIMARY_VM_DRAW,
							ACT_PRIMARY_VM_HOLSTER,
							ACT_PRIMARY_VM_IDLE,
							ACT_PRIMARY_VM_PULLBACK,
							ACT_PRIMARY_VM_PRIMARYATTACK,
							ACT_PRIMARY_VM_SECONDARYATTACK,
							ACT_PRIMARY_VM_RELOAD,
							ACT_PRIMARY_VM_DRYFIRE,
							ACT_PRIMARY_VM_IDLE_TO_LOWERED,
							ACT_PRIMARY_VM_IDLE_LOWERED,
							ACT_PRIMARY_VM_LOWERED_TO_IDLE,

							ACT_SECONDARY_VM_DRAW,
							ACT_SECONDARY_VM_HOLSTER,
							ACT_SECONDARY_VM_IDLE,
							ACT_SECONDARY_VM_PULLBACK,
							ACT_SECONDARY_VM_PRIMARYATTACK,
							ACT_SECONDARY_VM_SECONDARYATTACK,
							ACT_SECONDARY_VM_RELOAD,
							ACT_SECONDARY_VM_DRYFIRE,
							ACT_SECONDARY_VM_IDLE_TO_LOWERED,
							ACT_SECONDARY_VM_IDLE_LOWERED,
							ACT_SECONDARY_VM_LOWERED_TO_IDLE,

							ACT_MELEE_VM_DRAW,
							ACT_MELEE_VM_HOLSTER,
							ACT_MELEE_VM_IDLE,
							ACT_MELEE_VM_PULLBACK,
							ACT_MELEE_VM_PRIMARYATTACK,
							ACT_MELEE_VM_SECONDARYATTACK,
							ACT_MELEE_VM_RELOAD,
							ACT_MELEE_VM_DRYFIRE,
							ACT_MELEE_VM_IDLE_TO_LOWERED,
							ACT_MELEE_VM_IDLE_LOWERED,
							ACT_MELEE_VM_LOWERED_TO_IDLE,

							ACT_PDA_VM_DRAW,
							ACT_PDA_VM_HOLSTER,
							ACT_PDA_VM_IDLE,
							ACT_PDA_VM_PULLBACK,
							ACT_PDA_VM_PRIMARYATTACK,
							ACT_PDA_VM_SECONDARYATTACK,
							ACT_PDA_VM_RELOAD,
							ACT_PDA_VM_DRYFIRE,
							ACT_PDA_VM_IDLE_TO_LOWERED,
							ACT_PDA_VM_IDLE_LOWERED,
							ACT_PDA_VM_LOWERED_TO_IDLE,

							ACT_ITEM1_VM_DRAW,
							ACT_ITEM1_VM_HOLSTER,
							ACT_ITEM1_VM_IDLE,
							ACT_ITEM1_VM_PULLBACK,
							ACT_ITEM1_VM_PRIMARYATTACK,
							ACT_ITEM1_VM_SECONDARYATTACK,
							ACT_ITEM1_VM_RELOAD,
							ACT_ITEM1_VM_DRYFIRE,
							ACT_ITEM1_VM_IDLE_TO_LOWERED,
							ACT_ITEM1_VM_IDLE_LOWERED,
							ACT_ITEM1_VM_LOWERED_TO_IDLE,

							ACT_ITEM2_VM_DRAW,
							ACT_ITEM2_VM_HOLSTER,
							ACT_ITEM2_VM_IDLE,
							ACT_ITEM2_VM_PULLBACK,
							ACT_ITEM2_VM_PRIMARYATTACK,
							ACT_ITEM2_VM_SECONDARYATTACK,
							ACT_ITEM2_VM_RELOAD,
							ACT_ITEM2_VM_DRYFIRE,
							ACT_ITEM2_VM_IDLE_TO_LOWERED,
							ACT_ITEM2_VM_IDLE_LOWERED,
							ACT_ITEM2_VM_LOWERED_TO_IDLE,

							// Infested activities
							ACT_RELOAD_SUCCEED,
							ACT_RELOAD_FAIL,
							// Autogun
							ACT_WALK_AIM_AUTOGUN,
							ACT_RUN_AIM_AUTOGUN,
							ACT_IDLE_AUTOGUN,
							ACT_IDLE_AIM_AUTOGUN,
							ACT_RELOAD_AUTOGUN,
							ACT_CROUCH_IDLE_AUTOGUN,
							ACT_RANGE_ATTACK_AUTOGUN,
							ACT_JUMP_AUTOGUN,
							// Pistol
							ACT_IDLE_AIM_PISTOL,
							// PDW
							ACT_WALK_AIM_DUAL,
							ACT_RUN_AIM_DUAL,
							ACT_IDLE_DUAL,
							ACT_IDLE_AIM_DUAL,
							ACT_RELOAD_DUAL,
							ACT_CROUCH_IDLE_DUAL,
							ACT_RANGE_ATTACK_DUAL,
							ACT_JUMP_DUAL,
							// Shotgun
							ACT_IDLE_SHOTGUN,
							ACT_IDLE_AIM_SHOTGUN,
							ACT_CROUCH_IDLE_SHOTGUN,
							ACT_JUMP_SHOTGUN,
							// Rifle
							ACT_IDLE_AIM_RIFLE,
							ACT_RELOAD_RIFLE,
							ACT_CROUCH_IDLE_RIFLE,
							ACT_RANGE_ATTACK_RIFLE,
							ACT_JUMP_RIFLE,

							// Infested General AI
							ACT_SLEEP,
							ACT_WAKE,

							// Shield Bug
							ACT_FLICK_LEFT,
							ACT_FLICK_LEFT_MIDDLE,
							ACT_FLICK_RIGHT_MIDDLE,
							ACT_FLICK_RIGHT,
							ACT_SPINAROUND,

							// Mortar Bug
							ACT_PREP_TO_FIRE,
							ACT_FIRE,
							ACT_FIRE_RECOVER,

							// Shaman
							ACT_SPRAY,

							// Boomer
							ACT_PREP_EXPLODE,
							ACT_EXPLODE,

							// this is the end of the global activities, private per-monster activities start here.
							LAST_SHARED_ACTIVITY,
} Activity;
static const char *Ranks[] =
{
	"Unranked",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",

	"pWhite Nova I",
	"pWhite Nova II",
	"pWhite Nova III",
	"pWhite Nova Master",
	"Master Guardian I",
	"Master Guardian II",

	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite"
};
class CollisionProperty
{
public:
	Vector VecMins()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x8);
	}
	Vector VecMaxs()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x14);
	}
};


typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8;
class IClientRenderable
{
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual Vector const&              GetRenderOrigin(void) = 0;
	virtual QAngle const&              GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       Unused(void) const {}
	virtual ClientShadowHandle_t       GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&      RenderHandle() = 0;
	virtual const model_t*             GetModel() const = 0;
	virtual int                        DrawModel(int flags, const int /*RenderableInstance_t*/ &instance) = 0;
	virtual int                        GetBody() = 0;
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void* /*IPVSNotify*/       GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector &mins, Vector &maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool                       GetShadowCastDistance(float *pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector *pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int /*ShadowType_t*/       ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t      GetModelInstance() = 0;
	virtual const matrix3x4_t&         RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char *pAttachmentName) = 0;
	virtual   bool                     GetAttachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
	bool SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		typedef bool(__thiscall* oSetupBones)(PVOID, VMatrix *, int, int, float);
		return getvfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	const model_t* GetModel() //void*
	{
		typedef const model_t*(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 8)(this);
	}
};

struct bf_read;

class ClientClass;

class IClientNetworkable
{
public:
	virtual IClientUnknown*  GetIClientUnknown() = 0;
	virtual void             Release() = 0;
	virtual ClientClass*     GetClientClass() = 0;
	virtual void             NotifyShouldTransmit(int state) = 0;
	virtual void             OnPreDataChanged(int updateType) = 0;
	virtual void             OnDataChanged(int updateType) = 0;
	virtual void             PreDataUpdate(int updateType) = 0;
	virtual void             PostDataUpdate(int updateType) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             IsDormant(void) = 0;
	virtual int              Index(void) const = 0;
	virtual void             ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void*            GetDataTableBasePtr() = 0;
	virtual void             SetDestroyedOnRecreateEntities(void) = 0;

};
class IClientUnknown
{
public:
	virtual CollisionProperty*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual void*		GetIClientCBaseEntity() = 0;
	virtual void*		GetBaseCBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};
class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};

class VarMapEntry_t
{
public:
	unsigned short		type;
	unsigned short		m_bNeedsToInterpolate;	// Set to false when this var doesn't
												// need Interpolate() called on it anymore.
	void				*data;
	void	*watcher;
};

struct VarMapping_t
{
	CUtlVector<VarMapEntry_t>	m_Entries;
	int							m_nInterpolatedEntries;
	float						m_lastInterpolationTime;
};

class CBaseAnimating
{
public:

	enum
	{
		NUM_POSEPAREMETERS = 24,
		NUM_BONECTRLS = 4
	};



};

struct RecvProp;

class CAnimationLayer
{
public:
	char  pad_0000[20];
	uint32_t m_nOrder; //0x0014
	uint32_t m_nSequence; //0x0018
	float_t m_flPrevCycle; //0x001C
	float_t m_flWeight; //0x0020
	float_t m_flWeightDeltaRate; //0x0024
	float_t m_flPlaybackRate; //0x0028
	float_t m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038



class CBaseEntity
{
public:
	bool IsPlayer();
	UINT PhysicsSolidMaskForEntity()
	{
		typedef UINT(__thiscall* Fn)(void*);
		return getvfunc<Fn>(this, 148)(this);
	}
	int* GetWearables()
	{
		return reinterpret_cast<int*>((DWORD)this + offys.m_hMyWearables);
	}
	int GetChockedPackets();
	float GetOldSimulationTime();
	Vector& m_vecNetworkOrigin();
	bool IsTargettingLocal();
	/*CAnimationLayer& GetAnimOverlay(int Index)
	{
		return (*(CAnimationLayer**)((DWORD)this + 0x2970))[Index];
	}*/

	CUtlVector<CAnimationLayer> GetAnimOverlays();// {
	//	return *reinterpret_cast<CUtlVector<CAnimationLayer>*>(this + (DWORD)(Utilities::Memory::FindPatternIDA("client.dll", "55 8B EC 51 53 8B 5D 08 33 C0"))); // 55 8B EC 51 53 8B 5D 08 33 C0
	//}
	//virtual IClientUnknown*		GetIClientUnknown();
	//{
	//	return (IClientUnknown*)this; //index0
	//}
	int GetSequenceActivity(int sequence);
	int draw_model(int flags, uint8_t alpha) {
		using fn = int(__thiscall*)(void*, int, uint8_t);
		return getvfunc< fn >(GetRenderable(), 9)(GetRenderable(), flags, alpha);
	}
	void SetAngle2(Vector wantedang);
	CBaseAnimating*	GetBaseAnimating()
	{
		typedef CBaseAnimating*& (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 1)(this);
	} //vtable index 1
	float GetUpdateTime()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xA9FC + 0x8);
	}
	int GetSequence()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_nSequence);
	}
	
	float GetCycle()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_flCycle);
	}
	void UpdateClientSideAnimation()
	{
		typedef void(__thiscall* Fn)(void*);
		return getvfunc<Fn>(this, 218)(this);
	}
	float LowerBodyYaw()
	{
		return *reinterpret_cast<float*>((DWORD)this + offys.m_flLowerBodyYawTarget);
	}
	float GetMaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + offys.m_flMaxSpeed);
	}
	float GetAnimationTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + /*offys.m_flAnimTime*/0x3C);
	}
	float GetSimulationTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + offys.m_flSimulationTime);
	}
	int TickBase()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_nTickBase);
	}
	int GetHitboxSet()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x09FC);
	}
	Vector GetAngRotation()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0128);
	}
	Vector GetPredictedEyePosition(float interval_per_tick)
	{
		return GetEyePosition() + (GetVelocity() * interval_per_tick);
	}
	float Friction()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x0140);
	}
	int GetTeamNum()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xF0);
	}
	int GetArmor()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_ArmorValue);
	}
	int get_full_ammo() {
		return *(int*)((uintptr_t)this + offys.m_iPrimaryReserveAmmo);
	}
	bool HasHelmet()
	{
		return *reinterpret_cast<bool*>((DWORD)this + offys.m_bHasHelmet);
	}
	bool HasHeavyArmor()
	{
		return *reinterpret_cast<bool*>((DWORD)this + offys.m_bHasHeavyArmor);
	}
	Vector Velocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0110);
	}

	int GetHealth()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xFC);
	}

	int Index()
	{
		return GetNetworkable()->Index();
	}
	VarMapping_t* GetVarMap()
	{
		/*inline int C_BaseCBaseEntity::Interp_Interpolate( VarMapping_t *map, float currentTime )
{
	int bNoMoreChanges = 1;
	if ( currentTime < map->m_lastInterpolationTime )
	{
		for ( int i = 0; i < map->m_nInterpolatedEntries; i++ )
		{
			VarMapEntry_t *e = &map->m_Entries[ i ];

			e->m_bNeedsToInterpolate = true;
		}
	}
	map->m_lastInterpolationTime = currentTime;

	for ( int i = 0; i < map->m_nInterpolatedEntries; i++ )
	{
		VarMapEntry_t *e = &map->m_Entries[ i ];

		if ( !e->m_bNeedsToInterpolate )
			continue;
			
		IInterpolatedVar *watcher = e->watcher;
		Assert( !( watcher->GetType() & EXCLUDE_AUTO_INTERPOLATE ) );


		if ( watcher->Interpolate( currentTime ) )
			e->m_bNeedsToInterpolate = false;
		else
			bNoMoreChanges = 0;
	}

	return bNoMoreChanges;
}*/
		return reinterpret_cast<VarMapping_t*>((DWORD)this + 0x24);
	}
	int GetFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x0100);
	}
	float GetFriction()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + offys.m_flFriction));
	}
	float GetFallVelocity()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + offys.m_flFallVelocity));
	}
	int GetShotsFired()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_iShotsFired);
	}
	Vector GetEyePosition()
	{
		if (!this)
			return Vector(0, 0, 0);
	//	Vector vecViewOffset = *reinterpret_cast<Vector*>((DWORD)this + 0x0104);
		return GetOrigin() + GetViewOffset();
	}

	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_vecViewOffset);
	}


	Vector& GetAbsOrigin()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 10)(this);

	}
	Vector GetOrigin()
	{
		//if (!this)
		//	return Vector(0, 0, 0);


		//real abs origin

		//typedef Vector& (__thiscall* OriginalFn)(void*);
		//return getvfunc<OriginalFn>(this, 10)(this);
	
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_vecOrigin);
	}
	
	float GetStepSize()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + offys.m_flStepSize));
	}
	Vector SetOrigin(Vector Origin)
	{
		*(Vector*)((DWORD)this + offys.m_vecOrigin) = Origin;
	}


	Vector GetBaseVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_vecBaseVelocity);
	}
	void SetBaseVelocity(Vector Velocity)
	{
		*(Vector*)((DWORD)this + offys.m_vecBaseVelocity) = Velocity;
	}
	void SetVelocity(Vector Velocity)
	{
		*(Vector*)((DWORD)this + offys.m_vecVelocity) = Velocity;
	}
	void SetFallVelocity(float FallVelocity)
	{
		*(float*)((DWORD)this + offys.m_flFallVelocity) = FallVelocity;
	}
	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 11)(this);
		//return *reinterpret_cast<Vector*>((DWORD)this + 0x0128);
	}
	
	void* GetClientClass()
	{
		void* Networkable = (void*)(this + 0x8);
		typedef void* (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(Networkable, 2)(Networkable);
	}
	bool UnkAwCeck()
	{
		typedef bool* (__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 152)(this);
	}

	void SetAbsOrigin(Vector& origin);
	Vector GetVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_vecVelocity);
	}
	bool IsDormant()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0xE9);
	}

	float MaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x3240);
	}

	bool isAlive()
	{
		BYTE lifestate = *(BYTE*)((DWORD)this + 0x025B);
		return (lifestate == 0);
	}

	int GetIndex()
	{
	//	void* networkable = (void*)(this + 0x8);
		//typedef int(__thiscall* OriginalFn)(PVOID);
		//return getvfunc<OriginalFn>(this, 76)(this);
		return GetNetworkable()->Index();
	}
	IClientNetworkable* GetNetworkable()
	{
		return reinterpret_cast<IClientNetworkable*>((DWORD)this + 0x8);
	}

	bool SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);

	const model_t* GetModel() //void*
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef const model_t*(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(pRenderable, 8)(pRenderable);
	}
	float GetPoseParameter()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x2764);
	
	}
	int GetCollisionGroup()
	{
		return *reinterpret_cast<int*>((DWORD)this + offys.m_CollisionGroup); 
		//GetNetVar 
	}
	bool IsBroken()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x0A04);
	}
	CollisionProperty* GetCollision()
	{
		return reinterpret_cast<CollisionProperty*>((DWORD)this + 0x0318);
	}
	
	matrix3x4& GetCollisionBoundTrans()
	{
		return *reinterpret_cast<matrix3x4*>((DWORD)this + 0x0440);
	}
	IClientRenderable* GetRenderable()
	{
		return reinterpret_cast<IClientRenderable*>((DWORD)this + 0x4);
	}
	bool IsScoped()
	{
		return *reinterpret_cast<bool*>((DWORD)this + offys.m_bIsScoped);
	}
	bool GunGameImmunity()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x38A0);
	}
	QAngle GetPunchAngle()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x0000301C);
	}
	QAngle GetPunchAngleVelocity()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x3020);
	}
	QAngle* GetPunchAnglePtr()
	{
		return reinterpret_cast<QAngle*>((DWORD)this + 0x301C);
	}
	QAngle GetViewPunch()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x3010);
	}
	QAngle* GetViewPunchPtr()
	{
		return reinterpret_cast<QAngle*>((DWORD)this + 0x3010);
	}
	Vector* GetEyeAnglesPtr()
	{
		return reinterpret_cast<Vector*>((DWORD)this + offys.m_angEyeAngles);
	}
	Vector GetEyeAngles()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_angEyeAngles);
	}
	void SetEyeAngles(Vector Angles)
	{
		*(Vector*)((uintptr_t)this + 0xAA08) = Angles;
	}
	RecvProp* GetSequence3();
	CBaseCombatWeapon* GetWeapon();
	int GetGlowIndex()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x0000A320);
	}
	UINT* GetWeapons()
	{
		return (UINT*)((DWORD)this + 0x00002DE8);
	}
	int GetMoveType()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x258);
	}
	Vector GetNetworkOrigin()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + offys.m_flFriction - sizeof(Vector));
	}
	 int GetRank()
	{
	
		 return *(int*)((DWORD)offys.dw_CSPlayerResource + offys.m_iCompetetiveRanking+ this->Index() * 4);
	}
	const char* szRank()
	 {
		 return Ranks[GetRank()];
	 }
	int GetWins()
	{
		return *(int*)((DWORD)offys.dw_CSPlayerResource + offys.m_iCompetetiveWins + this->Index() * 4);
	}
	int GetPing()
	{
		int size = this->Index() * sizeof(int);
		return *(int*)(uintptr_t(offys.dw_CSPlayerResource + offys.m_iPing + size));
	}
	int GetMoney()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xA4A4);
	}
	std::array<float, 24> GetPoseParameters()
	{
		std::array<float, 24> flParam;
		float * flPose = (float*)((DWORD)this + offys.m_flPoseParameter);
		for (int i = 0; i < 23; i++)
		{
			flParam[i] = flPose[i];
		}
		return flParam;
	}
};
enum class CSClasses // Must specify CSClasses::Whatever in order to use smth from here
					 // Last updated -- 29 November 2016 (Glove Update)
{
	CAI_BaseNPC = 0,
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleCBaseEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempCBaseEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconCBaseEntity = 44,
	CEconWearable = 45,
	CEmbers = 46,
	CCBaseEntityDissolve = 47,
	CCBaseEntityFlame = 48,
	CCBaseEntityFreezing = 49,
	CCBaseEntityParticleTrail = 50,
	CEnvAmbientLight = 51,
	CEnvDetailController = 52,
	CEnvDOFController = 53,
	CEnvParticleScript = 54,
	CEnvProjectedTexture = 55,
	CEnvQuadraticBeam = 56,
	CEnvScreenEffect = 57,
	CEnvScreenOverlay = 58,
	CEnvTonemapController = 59,
	CEnvWind = 60,
	CFEPlayerDecal = 61,
	CFireCrackerBlast = 62,
	CFireSmoke = 63,
	CFireTrail = 64,
	CFish = 65,
	CFlashbang = 66,
	CFogController = 67,
	CFootstepControl = 68,
	CFunc_Dust = 69,
	CFunc_LOD = 70,
	CFuncAreaPortalWindow = 71,
	CFuncBrush = 72,
	CFuncConveyor = 73,
	CFuncLadder = 74,
	CFuncMonitor = 75,
	CFuncMoveLinear = 76,
	CFuncOccluder = 77,
	CFuncReflectiveGlass = 78,
	CFuncRotating = 79,
	CFuncSmokeVolume = 80,
	CFuncTrackTrain = 81,
	CGameRulesProxy = 82,
	CHandleTest = 83,
	CHEGrenade = 84,
	CHostage = 85,
	CHostageCarriableProp = 86,
	CIncendiaryGrenade = 87,
	CInferno = 88,
	CInfoLadderDismount = 89,
	CInfoOverlayAccessor = 90,
	CItem_Healthshot = 91,
	CKnife = 92,
	CKnifeGG = 93,
	CLightGlow = 94,
	CMaterialModifyControl = 95,
	CMolotovGrenade = 96,
	CMolotovProjectile = 97,
	CMovieDisplay = 98,
	CParticleFire = 99,
	CParticlePerformanceMonitor = 100,
	CParticleSystem = 101,
	CPhysBox = 102,
	CPhysBoxMultiplayer = 103,
	CPhysicsProp = 104,
	CPhysicsPropMultiplayer = 105,
	CPhysMagnet = 106,
	CPlantedC4 = 107,
	CPlasma = 108,
	CPlayerResource = 109,
	CPointCamera = 110,
	CPointCommentaryNode = 111,
	CPoseController = 112,
	CPostProcessController = 113,
	CPrecipitation = 114,
	CPrecipitationBlocker = 115,
	CPredictedViewModel = 116,
	CProp_Hallucination = 117,
	CPropDoorRotating = 118,
	CPropJeep = 119,
	CPropVehicleDriveable = 120,
	CRagdollManager = 121,
	CRagdollProp = 122,
	CRagdollPropAttached = 123,
	CRopeKeyframe = 124,
	CSCAR17 = 125,
	CSceneCBaseEntity = 126,
	CSensorGrenade = 127,
	CSensorGrenadeProjectile = 128,
	CShadowControl = 129,
	CSlideshowDisplay = 130,
	CSmokeGrenade = 131,
	CSmokeGrenadeProjectile = 132,
	CSmokeStack = 133,
	CSpatialCBaseEntity = 134,
	CSpotlightEnd = 135,
	CSprite = 136,
	CSpriteOriented = 137,
	CSpriteTrail = 138,
	CStatueProp = 139,
	CSteamJet = 140,
	CSun = 141,
	CSunlightShadowControl = 142,
	CTeam = 143,
	CTeamplayRoundBasedRulesProxy = 144,
	CTEArmorRicochet = 145,
	CTEBaseBeam = 146,
	CTEBeamEntPoint = 147,
	CTEBeamEnts = 148,
	CTEBeamFollow = 149,
	CTEBeamLaser = 150,
	CTEBeamPoints = 151,
	CTEBeamRing = 152,
	CTEBeamRingPoint = 153,
	CTEBeamSpline = 154,
	CTEBloodSprite = 155,
	CTEBloodStream = 156,
	CTEBreakModel = 157,
	CTEBSPDecal = 158,
	CTEBubbles = 159,
	CTEBubbleTrail = 160,
	CTEClientProjectile = 161,
	CTEDecal = 162,
	CTEDust = 163,
	CTEDynamicLight = 164,
	CTEEffectDispatch = 165,
	CTEEnergySplash = 166,
	CTEExplosion = 167,
	CTEFireBullets = 168,
	CTEFizz = 169,
	CTEFootprintDecal = 170,
	CTEFoundryHelpers = 171,
	CTEGaussExplosion = 172,
	CTEGlowSprite = 173,
	CTEImpact = 174,
	CTEKillPlayerAttachments = 175,
	CTELargeFunnel = 176,
	CTEMetalSparks = 177,
	CTEMuzzleFlash = 178,
	CTEParticleSystem = 179,
	CTEPhysicsProp = 180,
	CTEPlantBomb = 181,
	CTEPlayerAnimEvent = 182,
	CTEPlayerDecal = 183,
	CTEProjectedDecal = 184,
	CTERadioIcon = 185,
	CTEShatterSurface = 186,
	CTEShowLine = 187,
	CTesla = 188,
	CTESmoke = 189,
	CTESparks = 190,
	CTESprite = 191,
	CTESpriteSpray = 192,
	CTest_ProxyToggle_Networkable = 193,
	CTestTraceline = 194,
	CTEWorldDecal = 195,
	CTriggerPlayerMovement = 196,
	CTriggerSoundOperator = 197,
	CVGuiScreen = 198,
	CVoteController = 199,
	CWaterBullet = 200,
	CWaterLODControl = 201,
	CWeaponAug = 202,
	CWeaponAWP = 203,
	CWeaponBaseItem = 204,
	CWeaponBizon = 205,
	CWeaponCSBase = 206,
	CWeaponCSBaseGun = 207,
	CWeaponCycler = 208,
	CWeaponElite = 209,
	CWeaponFamas = 210,
	CWeaponFiveSeven = 211,
	CWeaponG3SG1 = 212,
	CWeaponGalil = 213,
	CWeaponGalilAR = 214,
	CWeaponGlock = 215,
	CWeaponHKP2000 = 216,
	CWeaponM249 = 217,
	CWeaponM3 = 218,
	CWeaponM4A1 = 219,
	CWeaponMAC10 = 220,
	CWeaponMag7 = 221,
	CWeaponMP5Navy = 222,
	CWeaponMP7 = 223,
	CWeaponMP9 = 224,
	CWeaponNegev = 225,
	CWeaponNOVA = 226,
	CWeaponP228 = 227,
	CWeaponP250 = 228,
	CWeaponP90 = 229,
	CWeaponSawedoff = 230,
	CWeaponSCAR20 = 231,
	CWeaponScout = 232,
	CWeaponSG550 = 233,
	CWeaponSG552 = 234,
	CWeaponSG556 = 235,
	CWeaponSSG08 = 236,
	CWeaponTaser = 237,
	CWeaponTec9 = 238,
	CWeaponTMP = 239,
	CWeaponUMP45 = 240,
	CWeaponUSP = 241,
	CWeaponXM1014 = 242,
	CWorld = 243,
	DustTrail = 244,
	MovieExplosion = 245,
	ParticleSmokeGrenade = 246,
	RocketTrail = 247,
	SmokeTrail = 248,
	SporeExplosion = 249,
	SporeTrail = 250
};
enum class CSGOClassID
{
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleCBaseEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempCBaseEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconCBaseEntity = 44,
	CEconWearable = 45,
	CEmbers = 46,
	CCBaseEntityDissolve = 47,
	CCBaseEntityFlame = 48,
	CCBaseEntityFreezing = 49,
	CCBaseEntityParticleTrail = 50,
	CEnvAmbientLight = 51,
	CEnvDetailController = 52,
	CEnvDOFController = 53,
	CEnvParticleScript = 54,
	CEnvProjectedTexture = 55,
	CEnvQuadraticBeam = 56,
	CEnvScreenEffect = 57,
	CEnvScreenOverlay = 58,
	CEnvTonemapController = 59,
	CEnvWind = 60,
	CFEPlayerDecal = 61,
	CFireCrackerBlast = 62,
	CFireSmoke = 63,
	CFireTrail = 64,
	CFish = 65,
	CFlashbang = 66,
	CFogController = 67,
	CFootstepControl = 68,
	CFunc_Dust = 69,
	CFunc_LOD = 70,
	CFuncAreaPortalWindow = 71,
	CFuncBrush = 72,
	CFuncConveyor = 73,
	CFuncLadder = 74,
	CFuncMonitor = 75,
	CFuncMoveLinear = 76,
	CFuncOccluder = 77,
	CFuncReflectiveGlass = 78,
	CFuncRotating = 79,
	CFuncSmokeVolume = 80,
	CFuncTrackTrain = 81,
	CGameRulesProxy = 82,
	CHandleTest = 83,
	CHEGrenade = 84,
	CHostage = 85,
	CHostageCarriableProp = 86,
	CIncendiaryGrenade = 87,
	CInferno = 88,
	CInfoLadderDismount = 89,
	CInfoOverlayAccessor = 90,
	CItem_Healthshot = 91,
	CItemDogtags = 92,
	CKnife = 93,
	CKnifeGG = 94,
	CLightGlow = 95,
	CMaterialModifyControl = 96,
	CMolotovGrenade = 97,
	CMolotovProjectile = 98,
	CMovieDisplay = 99,
	CParticleFire = 100,
	CParticlePerformanceMonitor = 101,
	CParticleSystem = 102,
	CPhysBox = 103,
	CPhysBoxMultiplayer = 104,
	CPhysicsProp = 105,
	CPhysicsPropMultiplayer = 106,
	CPhysMagnet = 107,
	CPlantedC4 = 108,
	CPlasma = 109,
	CPlayerResource = 110,
	CPointCamera = 111,
	CPointCommentaryNode = 112,
	CPointWorldText = 113,
	CPoseController = 114,
	CPostProcessController = 115,
	CPrecipitation = 116,
	CPrecipitationBlocker = 117,
	CPredictedViewModel = 118,
	CProp_Hallucination = 119,
	CPropDoorRotating = 120,
	CPropJeep = 121,
	CPropVehicleDriveable = 122,
	CRagdollManager = 123,
	CRagdollProp = 124,
	CRagdollPropAttached = 125,
	CRopeKeyframe = 126,
	CSCAR17 = 127,
	CSceneCBaseEntity = 128,
	CSensorGrenade = 129,
	CSensorGrenadeProjectile = 130,
	CShadowControl = 131,
	CSlideshowDisplay = 132,
	CSmokeGrenade = 133,
	CSmokeGrenadeProjectile = 134,
	CSmokeStack = 135,
	CSpatialCBaseEntity = 136,
	CSpotlightEnd = 137,
	CSprite = 138,
	CSpriteOriented = 139,
	CSpriteTrail = 140,
	CStatueProp = 141,
	CSteamJet = 142,
	CSun = 143,
	CSunlightShadowControl = 144,
	CTeam = 145,
	CTeamplayRoundBasedRulesProxy = 146,
	CTEArmorRicochet = 147,
	CTEBaseBeam = 148,
	CTEBeamEntPoint = 149,
	CTEBeamEnts = 150,
	CTEBeamFollow = 151,
	CTEBeamLaser = 152,
	CTEBeamPoints = 153,
	CTEBeamRing = 154,
	CTEBeamRingPoint = 155,
	CTEBeamSpline = 156,
	CTEBloodSprite = 157,
	CTEBloodStream = 158,
	CTEBreakModel = 159,
	CTEBSPDecal = 160,
	CTEBubbles = 161,
	CTEBubbleTrail = 162,
	CTEClientProjectile = 163,
	CTEDecal = 164,
	CTEDust = 165,
	CTEDynamicLight = 166,
	CTEEffectDispatch = 167,
	CTEEnergySplash = 168,
	CTEExplosion = 169,
	CTEFireBullets = 170,
	CTEFizz = 171,
	CTEFootprintDecal = 172,
	CTEFoundryHelpers = 173,
	CTEGaussExplosion = 174,
	CTEGlowSprite = 175,
	CTEImpact = 176,
	CTEKillPlayerAttachments = 177,
	CTELargeFunnel = 178,
	CTEMetalSparks = 179,
	CTEMuzzleFlash = 180,
	CTEParticleSystem = 181,
	CTEPhysicsProp = 182,
	CTEPlantBomb = 183,
	CTEPlayerAnimEvent = 184,
	CTEPlayerDecal = 185,
	CTEProjectedDecal = 186,
	CTERadioIcon = 187,
	CTEShatterSurface = 188,
	CTEShowLine = 189,
	CTesla = 190,
	CTESmoke = 191,
	CTESparks = 192,
	CTESprite = 193,
	CTESpriteSpray = 194,
	CTest_ProxyToggle_Networkable = 194,
	CTestTraceline = 196,
	CTEWorldDecal = 197,
	CTriggerPlayerMovement = 198,
	CTriggerSoundOperator = 199,
	CVGuiScreen = 200,
	CVoteController = 201,
	CWaterBullet = 202,
	CWaterLODControl = 203,
	CWeaponAug = 204,
	CWeaponAWP = 205,
	CWeaponBaseItem = 206,
	CWeaponBizon = 207,
	CWeaponCSBase = 208,
	CWeaponCSBaseGun = 209,
	CWeaponCycler = 210,
	CWeaponElite = 211,
	CWeaponFamas = 212,
	CWeaponFiveSeven = 213,
	CWeaponG3SG1 = 214,
	CWeaponGalil = 215,
	CWeaponGalilAR = 216,
	CWeaponGlock = 217,
	CWeaponHKP2000 = 218,
	CWeaponM249 = 219,
	CWeaponM3 = 220,
	CWeaponM4A1 = 221,
	CWeaponMAC10 = 222,
	CWeaponMag7 = 223,
	CWeaponMP5Navy = 224,
	CWeaponMP7 = 225,
	CWeaponMP9 = 226,
	CWeaponNegev = 227,
	CWeaponNOVA = 228,
	CWeaponP228 = 229,
	CWeaponP250 = 230,
	CWeaponP90 = 231,
	CWeaponSawedoff = 232,
	CWeaponSCAR20 = 233,
	CWeaponScout = 234,
	CWeaponSG550 = 235,
	CWeaponSG552 = 236,
	CWeaponSG556 = 237,
	CWeaponSSG08 = 238,
	CWeaponTaser = 239,
	CWeaponTec9 = 240,
	CWeaponTMP = 241,
	CWeaponUMP45 = 242,
	CWeaponUSP = 243,
	CWeaponXM1014 = 244,
	CWorld = 245,
	DustTrail = 246,
	MovieExplosion = 247,
	ParticleSmokeGrenade = 248,
	RocketTrail = 249,
	SmokeTrail = 250,
	SporeExplosion = 251,
	SporeTrail = 252
};


enum class CSGOHitboxID
{
	Head = 0,
	Neck,
	NeckLower,
	Pelvis,
	Stomach,
	LowerChest,
	Chest,
	UpperChest,
	RightThigh,
	LeftThigh,
	RightShin,
	LeftShin,
	RightFoot,
	LeftFoot,
	RightHand,
	LeftHand,
	RightUpperArm,
	RightLowerArm,
	LeftUpperArm,
	LeftLowerArm
};
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)