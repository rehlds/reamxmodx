// vim: set ts=4 sw=4 tw=99 noet:
//
// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license

//
// Ham Sandwich Module
//

#ifndef HAM_CONST_H
#define HAM_CONST_H


enum 
{
	HAM_UNSET = 0,
	HAM_IGNORED,
	HAM_HANDLED,
	HAM_OVERRIDE,
	HAM_SUPERCEDE
};

enum
{
	Ham_Spawn = 0,
	Ham_Precache,
	Ham_Keyvalue,
	Ham_ObjectCaps,
	Ham_Activate,
	Ham_SetObjectCollisionBox,
	Ham_Classify,
	Ham_DeathNotice,
	Ham_TraceAttack,
	Ham_TakeDamage,
	Ham_TakeHealth,
	Ham_Killed,
	Ham_BloodColor,
	Ham_TraceBleed,
	Ham_IsTriggered,
	Ham_MyMonsterPointer,
	Ham_MySquadMonsterPointer,
	Ham_GetToggleState,
	Ham_AddPoints,
	Ham_AddPointsToTeam,
	Ham_AddPlayerItem,
	Ham_RemovePlayerItem,
	Ham_GiveAmmo,
	Ham_GetDelay,
	Ham_IsMoving,
	Ham_OverrideReset,
	Ham_DamageDecal,
	Ham_SetToggleState,
	Ham_StartSneaking,
	Ham_StopSneaking,
	Ham_OnControls,
	Ham_IsSneaking,
	Ham_IsAlive,
	Ham_IsBSPModel,
	Ham_ReflectGauss,
	Ham_HasTarget,
	Ham_IsInWorld,
	Ham_IsPlayer,
	Ham_IsNetClient,
	Ham_TeamId,
	Ham_GetNextTarget,
	Ham_Think,
	Ham_Touch,
	Ham_Use,
	Ham_Blocked,
	Ham_Respawn,
	Ham_UpdateOwner,
	Ham_FBecomeProne,
	Ham_Center,
	Ham_EyePosition,
	Ham_EarPosition,
	Ham_BodyTarget,
	Ham_Illumination,
	Ham_FVisible,
	Ham_FVecVisible,

	Ham_Player_Jump,
	Ham_Player_Duck,
	Ham_Player_PreThink,
	Ham_Player_PostThink,
	Ham_Player_GetGunPosition,
	Ham_Player_ShouldFadeOnDeath,
	Ham_Player_ImpulseCommands,
	Ham_Player_UpdateClientData,
	
	Ham_Item_AddToPlayer,
	Ham_Item_AddDuplicate,
	Ham_Item_CanDeploy,
	Ham_Item_Deploy,
	Ham_Item_CanHolster,
	Ham_Item_Holster,
	Ham_Item_UpdateItemInfo,
	Ham_Item_PreFrame,
	Ham_Item_PostFrame,
	Ham_Item_Drop,
	Ham_Item_Kill,
	Ham_Item_AttachToPlayer,
	Ham_Item_PrimaryAmmoIndex,
	Ham_Item_SecondaryAmmoIndex,
	Ham_Item_UpdateClientData,
	Ham_Item_GetWeaponPtr,
	Ham_Item_ItemSlot,

	Ham_Weapon_ExtractAmmo,
	Ham_Weapon_ExtractClipAmmo,
	Ham_Weapon_AddWeapon,
	Ham_Weapon_PlayEmptySound,
	Ham_Weapon_ResetEmptySound,
	Ham_Weapon_SendWeaponAnim,
	Ham_Weapon_IsUsable,
	Ham_Weapon_PrimaryAttack,
	Ham_Weapon_SecondaryAttack,
	Ham_Weapon_Reload,
	Ham_Weapon_WeaponIdle,
	Ham_Weapon_RetireWeapon,
	Ham_Weapon_ShouldWeaponIdle,
	Ham_Weapon_UseDecrement,

	Ham_CS_Restart,
	Ham_CS_RoundRespawn,
	Ham_CS_Item_CanDrop,
	Ham_CS_Item_GetMaxSpeed,

	Ham_ChangeYaw,
	Ham_HasHumanGibs,
	Ham_HasAlienGibs, 
	Ham_FadeMonster,
	Ham_GibMonster,
	Ham_BecomeDead,
	Ham_IRelationship, 
	Ham_PainSound,
	Ham_ReportAIState,
	Ham_MonsterInitDead,
	Ham_Look, 
	Ham_BestVisibleEnemy, 
	Ham_FInViewCone,
	Ham_FVecInViewCone,
	Ham_GetDeathActivity,

	Ham_CS_Weapon_SendWeaponAnim,
	Ham_CS_Player_ResetMaxSpeed,
	Ham_CS_Player_IsBot,
	Ham_CS_Player_GetAutoaimVector,
	Ham_CS_Player_Blind,
	Ham_CS_Player_OnTouchingWeapon,
	Ham_CS_Item_IsWeapon,

	Ham_Item_GetItemInfo,

	HAM_LAST_ENTRY_DONT_USE_ME_LOL
};

enum 
{
	HAM_OK = 0,
	
	HAM_INVALID_FUNC,			// The function is not valid
	HAM_FUNC_NOT_CONFIGURED,	// This function is not configured in hamdata.ini
	
	HAM_ERR_END
};

#endif
