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

#include "amxxmodule.h"
#include "CstrikeUtils.h"
#include "CstrikeHacks.h"
#include "CstrikeItemsInfos.h"
#include "CstrikeUserMessages.h"
#include <IGameConfigs.h>

bool g_bReHLDS = false;
bool g_bReGame = false;

IGameConfig *MainConfig;
IGameConfig *CommonConfig;
IGameConfigManager *ConfigManager;

HLTypeConversion TypeConversion;

int AmxxCheckGame(const char *game)
{
	if (strcasecmp(game, "cstrike") == 0 || strcasecmp(game, "czero") == 0) {
		return AMXX_GAME_OK;
	}
	return AMXX_GAME_BAD;
}

void OnAmxxAttach()
{
	g_bReHLDS = RehldsApi_Init();

	if (g_bReHLDS == false) {
		MF_Log("Error load ReHLDS.");
		return;
	}
	
	g_bReGame = RegamedllApi_Init();

	MF_AddNatives(CstrikeNatives);

	ConfigManager = MF_GetConfigManager();

	char error[256] = "";
	ConfigManager->AddUserConfigHook("ItemInfos", &ItemsManager);

	if (!ConfigManager->LoadGameConfigFile("modules.games", &MainConfig, error, sizeof(error)) && *error) {
		MF_Log("Could not read module.games gamedata: %s", error);
		return;
	}

	*error = '\0';

	if (!ConfigManager->LoadGameConfigFile("common.games", &CommonConfig, error, sizeof(error)) && *error) {
		MF_Log("Could not read common.games gamedata: %s", error);
		return;
	}

	InitializeHacks();
}

void OnPluginsLoaded()
{
	if (g_bReHLDS == false) {
		return;
	}

	TypeConversion.init();
}

void OnServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	if (g_bReHLDS == false) {
		return;
	}

	// Used to catch WeaponList message at map change.
	EnableMessageHooks();
	
	RETURN_META(MRES_IGNORED);
}

void OnServerActivate_Post(edict_t *pEdictList, int edictCount, int clientMax)
{
	DisableMessageHooks();

	RETURN_META(MRES_IGNORED);
}

void OnPluginsUnloaded()
{
	// Used with model natives, enabled on demand.
	g_pengfuncsTable->pfnSetClientKeyValue     = nullptr;
	g_pFunctionTable->pfnClientUserInfoChanged = nullptr;

	// Force to disable all event hooks at map change.
	DisableMessageHooks(true);

	if (g_bReGame && NoKnivesMode) {
		g_ReGameHookchains->CBasePlayer_GiveDefaultItems()->unregisterHook(&CBasePlayer_GiveDefaultItems);
	}
}

void OnAmxxDetach()
{
	ConfigManager->RemoveUserConfigHook("ItemInfos", &ItemsManager);

	ConfigManager->CloseGameConfigFile(MainConfig);
	ConfigManager->CloseGameConfigFile(CommonConfig);
}
