#pragma once

#include <ISmmPlugin.h>
#include <sourcehook/sourcehook.h>
#include "MonoManager.h"

class MonoModPlugin : public ISmmPlugin
{

public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();

public:
	const char *GetAuthor() 
		{ return "Jake Heidt <evolved>"; }
	const char *GetName() 
		{ return "monomod"; }
	const char *GetDescription() 
		{ return "Allows server plugin development in CLI/.net languages"; }
	const char *GetURL() 
		{ return "http://monomod.jheidt.com/"; }
	const char *GetLicense() 
		{ return "GPL"; }
	const char *GetVersion() 
		{ return "0.001A"; }
	const char *GetDate() 
		{ return __DATE__; }
	const char *GetLogTag() 
		{ return "MONOM"; }

public:
	void ClientPutInServer(edict_t *pEntity, char const *playername);
	void ClientDisconnect(edict_t *pEntity);
	void GameFrame(bool simulating);

private:
	IServerGameDLL *m_ServerDll;
	IServerGameDLL *m_ServerDll_CC;
	IVEngineServer *m_Engine;
	IServerGameClients *m_ServerClients;
	IServerGameEnts *m_ServerEnts;

	MonoManager *m_MonoManager;
};

extern MonoModPlugin g_MonoModPlugin;

PLUGIN_GLOBALVARS();

//Called on ServerActivate.  Same definition as server plugins
void ServerActivate_handler(edict_t *pEdictList, int edictCount, int clientMax);