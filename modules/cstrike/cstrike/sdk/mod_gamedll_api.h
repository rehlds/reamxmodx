#ifndef _AMX_REGAMEDLL_INCLUDE_H_
#define _AMX_REGAMEDLL_INCLUDE_H_

#pragma once

#include "regamedll_api.h"

extern IReGameApi *g_ReGameApi;
extern const ReGameFuncs_t *g_ReGameFuncs;
extern IReGameHookchains *g_ReGameHookchains;
extern CBasePlayer *(*UTIL_PlayerByIndex)(int playerIndex);
extern CGameRules *g_pGameRules;

extern bool RegamedllApi_Init();

extern bool g_bReGame;

extern CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain);

extern void CBasePlayer_GiveDefaultItems(IReGameHook_CBasePlayer_GiveDefaultItems *chain, CBasePlayer *pthis);

#endif //_AMX_REGAMEDLL_INCLUDE_H_
