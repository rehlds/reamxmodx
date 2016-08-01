#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "net.h"
#include "delta_packet.h"
#include "server_static.h"
#include "userid_rehlds.h"
#include "progs.h"

#define MAX_INFO_STRING 256
#define MAX_DATAGRAM	4000
#define MAX_CONSISTENCY_LIST 512
#define NUM_BASELINES 64

#define HL_MODEL_MAX 512
#define HL_GENERIC_MAX 512
#define HL_EVENT_MAX 256
#define HL_SOUND_MAX 512
#define HL_SOUND_HASHLOOKUP_SIZE (HL_SOUND_MAX * 2 - 1)

typedef struct client_frame_s
{
	double senttime;
	float ping_time;
	clientdata_t clientdata;
	weapon_data_t weapondata[64];
	packet_entities_t entities;
} client_frame_t;

struct client_t
{
	qboolean active;
	qboolean spawned;
	qboolean fully_connected;
	qboolean connected;
	qboolean uploading;
	qboolean hasusrmsgs;
	qboolean has_force_unmodified;
	netchan_t netchan;
	int chokecount;
	int delta_sequence;
	qboolean fakeclient;
	qboolean proxy;
	usercmd_t lastcmd;
	double connecttime;
	double cmdtime;
	double ignorecmdtime;
	float latency;
	float packet_loss;
	double localtime;
	double nextping;
	double svtimebase;
	sizebuf_t datagram;
	byte datagram_buf[4000];
	double connection_started;
	double next_messagetime;
	double next_messageinterval;
	qboolean send_message;
	qboolean skip_message;
	client_frame_t *frames;
	event_state_t events;
	edict_t *pEdict;
	const edict_t *pViewEntity;
	int userid;
	USERID_t network_userid;
	char userinfo[MAX_INFO_STRING];
	qboolean sendinfo;
	float sendinfo_time;
	char hashedcdkey[64];
	char name[32];
	int topcolor;
	int bottomcolor;
	int entityId;
	resource_t resourcesonhand;
	resource_t resourcesneeded;
	FILE *upload;
	qboolean uploaddoneregistering;
	customization_t customdata;
	int crcValue;
	int lw;
	int lc;
	char physinfo[256];
	qboolean m_bLoopback;
	uint32_t m_VoiceStreams[2];
	double m_lastvoicetime;
	int m_sendrescount;
};

typedef struct event_s
{
	unsigned short	index;
	const char		*filename;
	int				filesize;
	const char		*pszScript;
} event_t;

typedef struct consistency_s
{
	char * filename;
	int issound;
	int orig_index;
	int value;
	int check_type;
	float mins[3];
	float maxs[3];
} consistency_t;

typedef enum server_state_e
{
	ss_dead = 0,
	ss_loading = 1,
	ss_active = 2,
} server_state_t;

typedef struct extra_baselines_s
{
	int number;
	int classname[NUM_BASELINES];
	entity_state_t baseline[NUM_BASELINES];
} extra_baselines_t;

typedef struct server_s
{
	qboolean active;
	qboolean paused;
	qboolean loadgame;
	double time;
	double oldtime;
	int lastcheck;
	double lastchecktime;
	char name[64];
	char oldname[64];
	char startspot[64];
	char modelname[64];
	struct model_s *worldmodel;
	CRC32_t worldmapCRC;
	unsigned char clientdllmd5[16];
	resource_t resourcelist[MAX_RESOURCE_LIST];
	int num_resources;
	consistency_t consistency_list[MAX_CONSISTENCY_LIST];
	int num_consistency;
	const char *model_precache[HL_MODEL_MAX];
	struct model_s *models[HL_MODEL_MAX];
	unsigned char model_precache_flags[HL_MODEL_MAX];
	struct event_s event_precache[HL_EVENT_MAX];
	const char *sound_precache[HL_SOUND_MAX];
	short int sound_precache_hashedlookup[HL_SOUND_HASHLOOKUP_SIZE];
	qboolean sound_precache_hashedlookup_built;
	const char *generic_precache[HL_GENERIC_MAX];
	char generic_precache_names[HL_GENERIC_MAX][64];
	int num_generic_names;
	char *lightstyles[MAX_LIGHTSTYLES];
	int num_edicts;
	int max_edicts;
	edict_t *edicts;
	struct entity_state_s *baselines;
	extra_baselines_t *instance_baselines;
	server_state_t state;
	sizebuf_t datagram;
	unsigned char datagram_buf[MAX_DATAGRAM];
	sizebuf_t reliable_datagram;
	unsigned char reliable_datagram_buf[MAX_DATAGRAM];
	sizebuf_t multicast;
	unsigned char multicast_buf[1024];
	sizebuf_t spectator;
	unsigned char spectator_buf[1024];
	sizebuf_t signon;
	unsigned char signon_data[32768];
} server_t;

#endif //_STRUCT_H_
