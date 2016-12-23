#include <extdll.h>
#include <meta_api.h>

#include "rehlds_api.h"

IRehldsApi* g_RehldsApi;
const RehldsFuncs_t* g_RehldsFuncs;
IRehldsServerData* g_RehldsData;
IRehldsHookchains* g_RehldsHookchains;
IRehldsServerStatic* g_RehldsSvs;

void REHLDS_PRINT(const char *fmt, ...)
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

bool RehldsApi_Init()
{
#ifdef WIN32
	CSysModule* engineModule = Sys_LoadModule("swds.dll");
#else
	CSysModule* engineModule = Sys_LoadModule("engine_i486.so");
#endif

	if (!engineModule) {
		REHLDS_PRINT("[%s] Failed to locate engine module.", Plugin_info.logtag);
		return false;
	}

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(engineModule);

	if (!ifaceFactory) {
		REHLDS_PRINT("[%s] Failed to locate interface factory in engine module.", Plugin_info.logtag);
		return false;
	}

	int retCode = 0;

	g_RehldsApi = (IRehldsApi*)ifaceFactory(VREHLDS_HLDS_API_VERSION, &retCode);

	if (!g_RehldsApi) {
		REHLDS_PRINT("[%s] Failed to locate retrieve rehlds api interface from engine module, return code is %d.", Plugin_info.logtag, retCode);
		return false;
	}

	int majorVersion = g_RehldsApi->GetMajorVersion();
	int minorVersion = g_RehldsApi->GetMinorVersion();

	if (majorVersion != REHLDS_API_VERSION_MAJOR) {
		REHLDS_PRINT("[%s]: ReHLDS Api major version mismatch; expected %d, real %d", Plugin_info.logtag, REHLDS_API_VERSION_MAJOR, majorVersion);
		return false;
	}

	if (minorVersion < REHLDS_API_VERSION_MINOR) {
		REHLDS_PRINT("[%s]: ReHLDS Api minor version mismatch; expected at least %d, real %d", Plugin_info.logtag, REHLDS_API_VERSION_MINOR, minorVersion);
		return false;
	}

	g_RehldsFuncs = g_RehldsApi->GetFuncs();
	g_RehldsData = g_RehldsApi->GetServerData();
	g_RehldsHookchains = g_RehldsApi->GetHookchains();
	g_RehldsSvs = g_RehldsApi->GetServerStatic();

	return true;
}
