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

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <extdll.h>
#include "amxxmodule.h"

#include "hook.h"
#include "forward.h"
#include "hook_callbacks.h"
#include "call_funcs.h"
#include "hook_create.h"
#include "offsets.h"
#include "hooklist.h"
#include "ham_utils.h"
#include "hook_specialbot.h"
#include <amtl/am-vector.h>

OffsetManager Offsets;

bool gDoForwards=true;

ke::Vector<Hook *> hooks[HAM_LAST_ENTRY_DONT_USE_ME_LOL];
CHamSpecialBotHandler SpecialbotHandler;

#define V(__KEYNAME, __STUFF__) 0, 0, __KEYNAME, RT_##__STUFF__, RB_##__STUFF__, PC_##__STUFF__, reinterpret_cast<void *>(Hook_##__STUFF__), Create_##__STUFF__, Call_##__STUFF__

hook_t hooklist[] =
{
	{ V("spawn",					Void_Void) },
	{ V("precache",					Void_Void) },
	{ V("keyvalue",					Void_Int) },
	{ V("objectcaps",				Int_Void) },
	{ V("activate",					Void_Void) },
	{ V("setobjectcollisionbox",	Void_Void) },
	{ V("classify",					Int_Void) },
	{ V("deathnotice",				Void_Entvar) },
	{ V("traceattack",				Void_Entvar_Float_Vector_Trace_Int) },
	{ V("takedamage",				Int_Entvar_Entvar_Float_Int) },
	{ V("takehealth",				Int_Float_Int) },
	{ V("killed",					Void_Entvar_Int) },
	{ V("bloodcolor",				Int_Void) },
	{ V("tracebleed",				Void_Float_Vector_Trace_Int) },
	{ V("istriggered",				Int_Cbase) },
	{ V("mymonsterpointer",			Cbase_Void) },
	{ V("mysquadmonsterpointer",	Cbase_Void) },
	{ V("gettogglestate",			Int_Void) },
	{ V("addpoints",				Void_Int_Int) },
	{ V("addpointstoteam",			Void_Int_Int) },
	{ V("addplayeritem",			Int_Cbase) },
	{ V("removeplayeritem",			Int_Cbase) },
	{ V("giveammo",					Int_Int_Str_Int) },
	{ V("getdelay",					Float_Void) },
	{ V("ismoving",					Int_Void) },
	{ V("overridereset",			Void_Void) },
	{ V("damagedecal",				Int_Int) },
	{ V("settogglestate",			Void_Int) },
	{ V("startsneaking",			Void_Void) },
	{ V("stopsneaking",				Void_Void) },
	{ V("oncontrols",				Int_Entvar) },
	{ V("issneaking",				Int_Void) },
	{ V("isalive",					Int_Void) },
	{ V("isbspmodel",				Int_Void) },
	{ V("reflectgauss",				Int_Void) },
	{ V("hastarget",				Int_Int) },
	{ V("isinworld",				Int_Void) },
	{ V("isplayer",					Int_Void) },
	{ V("isnetclient",				Int_Void) },
	{ V("teamid",					Str_Void) },
	{ V("getnexttarget",			Cbase_Void) },
	{ V("think",					Void_Void) },
	{ V("touch",					Void_Cbase) },
	{ V("use",						Void_Cbase_Cbase_Int_Float) },
	{ V("blocked",					Void_Cbase) },
	{ V("respawn",					Cbase_Void) },
	{ V("updateowner",				Void_Void) },
	{ V("fbecomeprone",				Int_Void) },
	{ V("center",					Vector_Void) },
	{ V("eyeposition",				Vector_Void) },
	{ V("earposition",				Vector_Void) },
	{ V("bodytarget",				Vector_pVector) },
	{ V("illumination",				Int_Void) },
	{ V("fvisible",					Int_Cbase) },
	{ V("fvecvisible",				Int_pVector) },

	/** Entity specific hooks **/

	/* CBasePlayer */
	{ V("player_jump",				Void_Void) },
	{ V("player_duck",				Void_Void) },
	{ V("player_prethink",			Void_Void) },
	{ V("player_postthink",			Void_Void) },
	{ V("player_getgunposition",	Vector_Void) },
	{ V("player_shouldfadeondeath",	Int_Void) },
	{ V("player_impulsecommands",	Void_Void) },
	{ V("player_updateclientdata",	Void_Void) },

	/* CBasePlayerItem */
	{ V("item_addtoplayer",			Int_Cbase) },
	{ V("item_addduplicate",		Int_Cbase) },
	{ V("item_candeploy",			Int_Void) },
	{ V("item_deploy",				Int_Void) },
	{ V("item_canholster",			Int_Void) },
	{ V("item_holster",				Void_Int) },
	{ V("item_updateiteminfo",		Void_Void) },
	{ V("item_preframe",			Void_Void) },
	{ V("item_postframe",			Void_Void) },
	{ V("item_drop",				Void_Void) },
	{ V("item_kill",				Void_Void) },
	{ V("item_attachtoplayer",		Void_Cbase) },
	{ V("item_primaryammoindex",	Int_Void) },
	{ V("item_secondaryammoindex",	Int_Void) },
	{ V("item_updateclientdata",	Int_Cbase) },
	{ V("item_getweaponptr",		Cbase_Void) },
	{ V("item_itemslot",			Int_Void) },

	/* CBasePlayerWeapon */
	{ V("weapon_extractammo",		Int_Cbase) },
	{ V("weapon_extractclipammo",	Int_Cbase) },
	{ V("weapon_addweapon",			Int_Void) },
	{ V("weapon_playemptysound",	Int_Void) },
	{ V("weapon_resetemptysound",	Void_Void) },
	{ V("weapon_sendweaponanim",	Void_Int_Int_Int) },
	{ V("weapon_isusable",			Int_Void) },
	{ V("weapon_primaryattack",		Void_Void) },
	{ V("weapon_secondaryattack",	Void_Void) },
	{ V("weapon_reload",			Void_Void) },
	{ V("weapon_weaponidle",		Void_Void) },
	{ V("weapon_retireweapon",		Void_Void) },
	{ V("weapon_shouldweaponidle",	Int_Void) },
	{ V("weapon_usedecrement",		Int_Void) },

	/* fix old compile*/
	{ V("null_1", Void_Void) },
	{ V("null_1", Void_Void) },
	{ V("null_1", Void_Void) },

	/* Counter-Strike */
	{ V("cstrike_restart",			Void_Void) },
	{ V("cstrike_roundrespawn",		Void_Void) },
	{ V("cstrike_item_candrop",		Int_Void) },
	{ V("cstrike_item_getmaxspeed",	Float_Void) },

	/** New Additions (2011) **/

	{ V("changeyaw",				Float_Int) },
	{ V("hashumangibs",				Int_Void) },
	{ V("hasaliengibs",				Int_Void) },
	{ V("fademonster",				Void_Void) },
	{ V("gibmonster",				Void_Void) },
	{ V("becomedead",				Void_Void) },
	{ V("irelationship",			Int_Cbase) },
	{ V("painsound",				Void_Void) },
	{ V("reportaistate",			Void_Void) },
	{ V("monsterinitdead",			Void_Void) },
	{ V("look",						Void_Int) },
	{ V("bestvisibleenemy",			Cbase_Void) },
	{ V("finviewcone",				Int_Cbase) },
	{ V("fvecinviewcone",			Int_pVector) },
	{ V("getdeathactivity",			Int_Void) },

	/* Counter-Strike */
	{ V("cstrike_weapon_sendweaponanim",Void_Int_Int) },
	{ V("cstrike_player_resetmaxspeed",	Void_Void) },
	{ V("cstrike_player_isbot",		Int_Void) },
	{ V("cstrike_player_getautoaimvector",		Vector_Float) },
	{ V("cstrike_player_blind",		Void_Float_Float_Float_Int) },
	{ V("cstrike_player_ontouchingweapon",Void_Cbase) },
	{ V("cstrike_item_isweapon", Int_Void) },

	{ V("item_getiteminfo", Void_ItemInfo) }
};


void FailPlugin(AMX *amx, int id, int err, const char *reason)
{
	int fwd = MF_RegisterSPForwardByName(amx, "__fatal_ham_error", FP_CELL, FP_CELL, FP_STRING, FP_DONE);

	MF_ExecuteForward(fwd, id, err, reason);

	MF_UnregisterSPForward(fwd);
}

int checkTable(int NumFunc)
{
	if (NumFunc == 130) {
		NumFunc = 101;
		//MF_Log("--- fix ChangeYaw");
	} else if (NumFunc == 131) {
		NumFunc = 102;
		//MF_Log("--- fix HasHumanGibs");
	} else if (NumFunc == 132) {
		NumFunc = 103;
		//MF_Log("--- fix HasAlienGibs");
	} else if (NumFunc == 133) {
		NumFunc = 104;
		//MF_Log("--- fix FadeMonster");
	} else if (NumFunc == 134) {
		NumFunc = 105;
		//MF_Log("--- fix GibMonster");
	} else if (NumFunc == 135) {
		NumFunc = 106;
		//MF_Log("--- fix BecomeDead");
	} else if (NumFunc == 136) {
		NumFunc = 107;
		//MF_Log("--- fix IRelationship");
	} else if (NumFunc == 137) {
		NumFunc = 108;
		//MF_Log("--- fix PainSound");
	} else if (NumFunc == 138) {
		NumFunc = 109;
		//MF_Log("--- fix ReportAIState");
	} else if (NumFunc == 139) {
		NumFunc = 110;
		//MF_Log("--- fix MonsterInitDead");
	} else if (NumFunc == 140) {
		NumFunc = 111;
		//MF_Log("--- fix Look");
	} else if (NumFunc == 141) {
		NumFunc = 112;
		//MF_Log("--- fix BestVisibleEnemy");
	} else if (NumFunc == 142) {
		NumFunc = 113;
		//MF_Log("--- fix FInViewCone");
	} else if (NumFunc == 143) {
		NumFunc = 114;
		//MF_Log("--- fix FVecInViewCone");
	} else if (NumFunc == 144) {
		NumFunc = 115;
		//MF_Log("--- fix GetDeathActivity");
	} else if (NumFunc == 186) {
		NumFunc = 116;
		//MF_Log("--- fix Weapon_SendWeaponAnim");
	} else if (NumFunc == 187) {
		NumFunc = 117;
		//MF_Log("--- fix Player_ResetMaxSpeed");
	} else if (NumFunc == 188) {
		NumFunc = 118;
		//MF_Log("--- fix Player_IsBot");
	} else if (NumFunc == 189) {
		NumFunc = 119;
		//MF_Log("--- fix Player_GetAutoaimVector");
	} else if (NumFunc == 190) {
		NumFunc = 120;
		//MF_Log("--- fix Player_Blind");
	} else if (NumFunc == 191) {
		NumFunc = 121;
		//MF_Log("--- fix Player_OnTouchingWeapon");
	} else if (NumFunc == 415) {
		NumFunc = 122;
		//MF_Log("--- fix Item_IsWeapon");
	}
	return NumFunc;
}

static cell AMX_NATIVE_CALL RegisterHam(AMX *amx, cell *params)
{
	// Make sure the function we're requesting is within bounds
	int func = params[1];
	int post = params[4];

	/// check table fix old compile

	if (func > 129 && func < 145
		|| func > 185 && func < 192
		|| func == 415)
	{
		func = checkTable(func);
	}

	///

	CHECK_FUNCTION(func);

	char *function = MF_GetAmxString(amx, params[3], 0, NULL);
	char *classname = MF_GetAmxString(amx, params[2], 1, NULL);

	// Check the entity

	// create an entity, assign it the gamedll's class, hook it and destroy it
	edict_t *Entity = CREATE_ENTITY();

	CALL_GAME_ENTITY(PLID,classname,&Entity->v);

	if (Entity->pvPrivateData == NULL)
	{
		REMOVE_ENTITY(Entity);

		MF_LogError(amx, AMX_ERR_NATIVE,"Failed to retrieve classtype for \"%s\", hook for \"%s\" not active.",classname,function);

		return 0;
	}

	void **vtable=GetVTable(Entity->pvPrivateData, Offsets.GetBase());

	REMOVE_ENTITY(Entity);

	if (vtable == NULL)
	{
		MF_LogError(amx, AMX_ERR_NATIVE,"Failed to retrieve vtable for \"%s\", hook for \"%s\" not active.",classname,function);

		return 0;
	}

	// Verify that the function is valid
	// Don't fail the plugin if this fails, just emit a normal error
	int fwd = hooklist[func].makefunc(amx, function);

	if (fwd == -1)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function %s not found.", function);

		return 0;
	}

	bool enableSpecialBot = false;

	// Old plugin doesn't have this param.
	if (*params / sizeof(cell) == 5)
	{
		enableSpecialBot = params[5] > 0;
	}

	Forward *pfwd = new Forward(fwd);
	pfwd->AddRef();

	// We've passed all tests...
	if (enableSpecialBot && strcmp(classname, "player") == 0)
	{
		SpecialbotHandler.RegisterHamSpecialBot(amx, func, function, post, pfwd);
	}

	int **ivtable = (int **)vtable;

	void *vfunction = (void *)ivtable[hooklist[func].vtid];

	// Check the list of this function's hooks, see if the function we have is a hook

	for (size_t i = 0; i < hooks[func].length(); ++i)
	{
		if (hooks[func].at(i)->tramp == vfunction)
		{
			// Yes, this function is hooked
			if (post)
			{
				hooks[func].at(i)->post.append(pfwd);
			}
			else
			{
				hooks[func].at(i)->pre.append(pfwd);
			}
			return reinterpret_cast<cell>(pfwd);
		}
	}

	// If we got here, the function is not hooked
	Hook *hook = new Hook(vtable, hooklist[func].vtid, hooklist[func].targetfunc, hooklist[func].isvoid, hooklist[func].needsretbuf, hooklist[func].paramcount, classname);
	hooks[func].append(hook);

	if (post)
	{
		hook->post.append(pfwd);
	}
	else
	{
		hook->pre.append(pfwd);
	}

	return reinterpret_cast<cell>(pfwd);
}

// RegisterHamFromEntity(Ham:function, EntityId, const Callback[], Post=0);
static cell AMX_NATIVE_CALL RegisterHamFromEntity(AMX *amx, cell *params)
{
	// Make sure the function we're requesting is within bounds
	int func = params[1];
	int post = params[4];

	CHECK_FUNCTION(func);

	char *function = MF_GetAmxString(amx, params[3], 0, NULL);
	int entid = params[2];
	char classname[64];

	// Check the entity

	edict_t *Entity = TypeConversion.id_to_edict(entid);

	if (!Entity || Entity->pvPrivateData == NULL)
	{
		MF_LogError(amx, AMX_ERR_NATIVE,"Failed to retrieve classtype for entity id \"%d\", hook for \"%s\" not active.",entid,function);

		return 0;
	}

	void **vtable = GetVTable(Entity->pvPrivateData, Offsets.GetBase());

	if (vtable == NULL)
	{
		MF_LogError(amx, AMX_ERR_NATIVE,"Failed to retrieve vtable for entity id \"%d\", hook for \"%s\" not active.",entid,function);

		return 0;
	}

	// Verify that the function is valid
	// Don't fail the plugin if this fails, just emit a normal error
	int fwd = hooklist[func].makefunc(amx, function);

	if (fwd == -1)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function %s not found.", function);

		return 0;
	}

	// We've passed all tests...

	Forward *pfwd = new Forward(fwd);
	pfwd->AddRef();

	int **ivtable = (int **)vtable;

	void *vfunction = (void *)ivtable[hooklist[func].vtid];

	// Check the list of this function's hooks, see if the function we have is a hook

	for (size_t i = 0; i < hooks[func].length(); ++i)
	{
		if (hooks[func].at(i)->tramp == vfunction)
		{
			// Yes, this function is hooked
			if (post)
			{
				hooks[func].at(i)->post.append(pfwd);
			}
			else
			{
				hooks[func].at(i)->pre.append(pfwd);
			}
			return reinterpret_cast<cell>(pfwd);
		}
	}

	// Note down the classname for the given class
	// It may very well be wrong (such as lots of TS weapons have the same classname)
	// but it's the best we can do, and better than nothing.
	// (only used for display)
	ke::SafeSprintf(classname, sizeof(classname), "%s", STRING(Entity->v.classname));

	// If we got here, the function is not hooked
	Hook *hook = new Hook(vtable, hooklist[func].vtid, hooklist[func].targetfunc, hooklist[func].isvoid, hooklist[func].needsretbuf, hooklist[func].paramcount, classname);
	hooks[func].append(hook);

	if (post)
	{
		hook->post.append(pfwd);
	}
	else
	{
		hook->pre.append(pfwd);
	}

	return reinterpret_cast<cell>(pfwd);
}

static cell AMX_NATIVE_CALL ExecuteHam(AMX *amx, cell *params)
{
	int func = params[1];

	CHECK_FUNCTION(func);

	gDoForwards = false;

	return hooklist[func].call(amx, params);
}

static cell AMX_NATIVE_CALL ExecuteHamB(AMX *amx, cell *params)
{
	int func=params[1];

	CHECK_FUNCTION(func);

	gDoForwards = true;

	return hooklist[func].call(amx, params);
}

static cell AMX_NATIVE_CALL IsHamValid(AMX *amx, cell *params)
{
	int func = params[1];

	if (func >= 0 && 
		func < HAM_LAST_ENTRY_DONT_USE_ME_LOL &&
		hooklist[func].isset!=0)
	{
		return 1;
	}

	return 0;
}

static cell AMX_NATIVE_CALL DisableHamForward(AMX *amx, cell *params)
{
	Forward *fwd = reinterpret_cast<Forward *>(params[1]);

	if (fwd == 0)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid HamHook handle.");
		return -1;
	}

	fwd->state = FSTATE_STOP;

	return 0;
}
static cell AMX_NATIVE_CALL EnableHamForward(AMX *amx, cell *params)
{
	Forward *fwd = reinterpret_cast<Forward *>(params[1]);

	if (fwd == 0)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid HamHook handle.");
		return -1;
	}

	fwd->state = FSTATE_OK;

	return 0;
}
AMX_NATIVE_INFO RegisterNatives[] =
{
	{ "RegisterHam",			RegisterHam },
	{ "RegisterHamFromEntity",	RegisterHamFromEntity },
	{ "ExecuteHam",				ExecuteHam },
	{ "ExecuteHamB",			ExecuteHamB },
	{ "IsHamValid",				IsHamValid },
	{ "DisableHamForward",		DisableHamForward },
	{ "EnableHamForward",		EnableHamForward },

	{ NULL,						NULL }
};
