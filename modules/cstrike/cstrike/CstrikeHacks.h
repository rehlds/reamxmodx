// vim: set ts=4 sw=4 tw=99 noet:
//
// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license

//
// Counter-Strike Module
//

#ifndef CSTRIKE_HACKS_H
#define CSTRIKE_HACKS_H

#include <amxxmodule.h>
#include <IGameConfigs.h>
#include <CDetour/detours.h>
#include "CstrikeDatas.h"

#include "entity_state.h"
#include "usercmd.h"
#include "struct.h"

void InitializeHacks();
void InitGlobalVars();

extern AMX_NATIVE_INFO CstrikeNatives[];

extern IGameConfig *MainConfig;
extern IGameConfig *CommonConfig;

enum class HashType
{
	Classname
};

typedef edict_t* (*CreateNamedEntityFunc)(string_t iszClassname);
typedef CBaseEntity* (*UTIL_FindEntityByStringFunc)(CBaseEntity* pStartEntity, const char *szKeyword, const char *szValue);
typedef WeaponInfoStruct* (*GetWeaponInfoFunc)(int id);
typedef void (*AddEntityHashValueFunc)(struct entvars_s *pev, const char *value, HashType fieldType);
typedef void (*RemoveEntityHashValueFunc)(struct entvars_s *pev, const char *value, HashType fieldType);

extern CreateNamedEntityFunc       CS_CreateNamedEntity;
extern UTIL_FindEntityByStringFunc CS_UTIL_FindEntityByString;
extern GetWeaponInfoFunc           GetWeaponInfo;
extern AddEntityHashValueFunc      AddEntityHashValue;
extern RemoveEntityHashValueFunc   RemoveEntityHashValue;

extern bool Active_cs_set_no_knives;
extern bool Active_cs_create_entity;
extern bool Active_cs_find_ent;
extern bool Active_cs_get_weapon_info;
extern bool Active_set_ent_class;

extern CDetour *GiveDefaultItemsDetour;

extern bool NoKnivesMode;

extern enginefuncs_t *g_pengfuncsTable;
extern DLL_FUNCTIONS *g_pFunctionTable;

#endif // CSTRIKE_HACKS_H
