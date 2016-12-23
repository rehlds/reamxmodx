#include <extdll.h>
#include <meta_api.h>

#include "cbase.h"

#include "gamerules.h"
#include "regamedll_api.h"

IReGameApi *g_ReGameApi;
const ReGameFuncs_t *g_ReGameFuncs;
IReGameHookchains *g_ReGameHookchains;
CGameRules *g_pGameRules = nullptr;

void REGAMEDLL_PRINT(const char *fmt, ...)
{
	va_list ap;
	uint32 len;
	char buf[1048];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	len = strlen(buf);

	if (len < sizeof(buf) - 2) {
		strcat(buf, "\n");
	} else {
		buf[len - 1] = '\n';
	}

	SERVER_PRINT(buf);
}

bool RegamedllApi_Init()
{
	const char *szGameDLLModule = GET_GAME_INFO(PLID, GINFO_DLL_FULLPATH);

	if (szGameDLLModule == NULL) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL szGameDLLModule NULL.", Plugin_info.logtag);
		return false;
	}

	CSysModule *gameModule = Sys_LoadModule(szGameDLLModule);

	if (!gameModule) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL gameModule NULL.", Plugin_info.logtag);
		return false;
	}

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(gameModule);

	if (!ifaceFactory) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL ifaceFactory NULL.", Plugin_info.logtag);
		return false;
	}

	int retCode = 0;

	g_ReGameApi = (IReGameApi *)ifaceFactory(VRE_GAMEDLL_API_VERSION, &retCode);

	if (!g_ReGameApi) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL error load Api.", Plugin_info.logtag);
		return false;
	}

	int majorVersion = g_ReGameApi->GetMajorVersion();
	int minorVersion = g_ReGameApi->GetMinorVersion();

	if (majorVersion != REGAMEDLL_API_VERSION_MAJOR) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL Api major version mismatch; expected %d, real %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR, majorVersion);
		return false;
	}

	if (minorVersion < REGAMEDLL_API_VERSION_MINOR) {
		REGAMEDLL_PRINT("[%s]: ReGameDLL Api minor version mismatch; expected at least %d, real %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR, minorVersion);
		return false;
	}

	g_ReGameFuncs = g_ReGameApi->GetFuncs();
	g_ReGameHookchains = g_ReGameApi->GetHookchains();

	return true;
}
