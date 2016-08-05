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

#include "CstrikeDatas.h"
#include "CstrikeUtils.h"
#include "CstrikeHacks.h"
#include "CstrikeItemsInfos.h"

CDetour *GiveDefaultItemsDetour;

CreateNamedEntityFunc       CS_CreateNamedEntity;
UTIL_FindEntityByStringFunc CS_UTIL_FindEntityByString;
GetWeaponInfoFunc           GetWeaponInfo;
AddEntityHashValueFunc      AddEntityHashValue;
RemoveEntityHashValueFunc   RemoveEntityHashValue;

bool Active_cs_set_no_knives = false;
bool Active_cs_create_entity = false;
bool Active_cs_find_ent = false;
bool Active_cs_get_weapon_info = false;
bool Active_set_ent_class = false;

edict_s* OnCreateNamedEntity(int classname)
{
	if (NoKnivesMode)
	{
		if (!strcmp(STRING(classname), "weapon_knife"))
		{
			RETURN_META_VALUE(MRES_SUPERCEDE, nullptr);
		}
	}
	else
	{
		g_pengfuncsTable->pfnCreateNamedEntity = nullptr;
	}

	RETURN_META_VALUE(MRES_IGNORED, nullptr);
}

DETOUR_DECL_MEMBER0(GiveDefaultItems, void)  // void CBasePlayer::GiveDefaultItems(void)
{
	if (NoKnivesMode)
	{
		g_pengfuncsTable->pfnCreateNamedEntity = OnCreateNamedEntity;
	}

	DETOUR_MEMBER_CALL(GiveDefaultItems)();

	g_pengfuncsTable->pfnCreateNamedEntity = nullptr;
}

void CBasePlayer_GiveDefaultItems(IReGameHook_CBasePlayer_GiveDefaultItems *chain, CBasePlayer *pthis)
{
	if (NoKnivesMode)
	{
		g_pengfuncsTable->pfnCreateNamedEntity = OnCreateNamedEntity;
	}

	chain->callNext(pthis);

	g_pengfuncsTable->pfnCreateNamedEntity = nullptr;
}

void InitializeHacks()
{
	if (g_bReGame == true)
	{
		Active_cs_set_no_knives = true;
		Active_cs_create_entity = true;
		Active_cs_find_ent = true;
		Active_cs_get_weapon_info = true;
		Active_set_ent_class = true;
	}
	else
	{
		void *address = nullptr;

		if (MainConfig->GetMemSig("GiveDefaultItems", &address))
		{
			GiveDefaultItemsDetour = DETOUR_CREATE_MEMBER_FIXED(GiveDefaultItems, address);
		}

		if (MainConfig->GetMemSig("CreateNamedEntity", &address)) // cs_create_entity()
		{
			CS_CreateNamedEntity = reinterpret_cast<CreateNamedEntityFunc>(address);
		}

		if (MainConfig->GetMemSig("FindEntityByString", &address)) // cs_find_ent_by_class()
		{
			CS_UTIL_FindEntityByString = reinterpret_cast<UTIL_FindEntityByStringFunc>(address);
		}

		if (MainConfig->GetMemSig("GetWeaponInfo", &address)) // cs_get_weapon_info()
		{
			GetWeaponInfo = reinterpret_cast<GetWeaponInfoFunc>(address);
		}

		if (MainConfig->GetMemSig("AddEntityHashValue", &address)) // cs_set_ent_class()
		{
			AddEntityHashValue = reinterpret_cast<AddEntityHashValueFunc>(address);
		}

		if (MainConfig->GetMemSig("RemoveEntityHashValue", &address)) // cs_set_ent_class()
		{
			RemoveEntityHashValue = reinterpret_cast<RemoveEntityHashValueFunc>(address);
		}

		if (GiveDefaultItemsDetour)
		{
			Active_cs_set_no_knives = true;
		} else {
			MF_Log("GiveDefaultItems is not available - native cs_set_no_knives has been disabled");
		}

		if (CS_CreateNamedEntity)
		{
			Active_cs_create_entity = true;
		} else {
			MF_Log("CREATE_NAMED_ENITTY is not available - native cs_create_entity() has been disabled");
		}

		if (CS_UTIL_FindEntityByString)
		{
			Active_cs_find_ent = true;
		} else {
			MF_Log("UTIL_FindEntByString is not available - native cs_find_ent_by_class() has been disabled");
		}

		if (GetWeaponInfo)
		{
			Active_cs_get_weapon_info = true;
		} else {
			MF_Log("GetWeaponInfo is not available - native cs_get_weapon_info() have been disabled");
		}

		if (AddEntityHashValue && RemoveEntityHashValue)
		{
			Active_set_ent_class = true;
		} else {
			MF_Log("GetWeaponInfo is not available - native cs_set_ent_class() have been disabled");
		}
	}
}
