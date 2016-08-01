#ifndef _AMX_REHLDS_INCLUDE_H_
#define _AMX_REHLDS_INCLUDE_H_

#include "rehlds_api.h"

#pragma once

extern IRehldsApi* g_RehldsApi;
extern const RehldsFuncs_t* g_RehldsFuncs;
extern IRehldsServerData* g_RehldsData;
extern IRehldsHookchains* g_RehldsHookchains;
extern IRehldsServerStatic* g_RehldsSvs;
extern IRehldsServerData* g_RehldsSv;

extern bool RehldsApi_Init();

extern bool m_api_rehlds;

#endif //_AMX_REHLDS_INCLUDE_H_
