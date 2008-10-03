#include <oslink.h>
#include <sourcehook/sourcehook.h>
#include "MonoModPlugin.h"
#include "eiface.h"

#define snprintf _snprintf

SH_DECL_HOOK1_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool);
SH_DECL_HOOK3_void(IServerGameDLL, ServerActivate, SH_NOATTRIB, 0, edict_t *, int, int);
SH_DECL_HOOK2_void(IServerGameClients, ClientPutInServer, SH_NOATTRIB, 0, edict_t *, char const *);

#ifdef WIN32
	#define VTABLE_OFFSET 0
#else
	#define VTABLE_OFFSET 1
#endif


MonoModPlugin g_MonoModPlugin;

PLUGIN_EXPOSE(SamplePlugin, g_MonoModPlugin);

void ServerActivate_handler(edict_t *pEdictList, int edictCount, int clientMax)
{
	RETURN_META(MRES_IGNORED);
}

bool MonoModPlugin::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_ANY(serverFactory, m_ServerDll, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
	GET_V_IFACE_CURRENT(engineFactory, m_Engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
	GET_V_IFACE_ANY(serverFactory, m_ServerClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
	GET_V_IFACE_CURRENT(serverFactory, m_ServerEnts, IServerGameEnts, INTERFACEVERSION_SERVERGAMEENTS);
		
	if(!m_MonoManager) {
		m_MonoManager = new MonoManager();
		m_MonoManager->StartRuntime();
	}

	SH_ADD_HOOK_STATICFUNC(IServerGameDLL, ServerActivate, m_ServerDll, ServerActivate_handler, true);
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, m_ServerClients, &g_MonoModPlugin, &MonoModPlugin::ClientPutInServer, true);
	SH_ADD_HOOK_MEMFUNC(IServerGameDLL, GameFrame, m_ServerDll, &g_MonoModPlugin, &MonoModPlugin::GameFrame, true);

	return true;
}

bool MonoModPlugin::Unload(char *error, size_t maxlen) {

	if(m_MonoManager && m_MonoManager->IsLoaded()) {		
		m_MonoManager->ShutdownRuntime();
		delete m_MonoManager;
		m_MonoManager = 0;
	}

	SH_REMOVE_HOOK_MEMFUNC(IServerGameDLL, GameFrame, m_ServerDll, &g_MonoModPlugin, &MonoModPlugin::GameFrame, true);
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, m_ServerClients, &g_MonoModPlugin, &MonoModPlugin::ClientPutInServer, true);
	SH_REMOVE_HOOK_STATICFUNC(IServerGameDLL, ServerActivate, m_ServerDll, ServerActivate_handler, true);

	return true;
}

bool MonoModPlugin::Pause(char *error, size_t maxlen)
{
	return true;
}

bool MonoModPlugin::Unpause(char *error, size_t maxlen)
{
	return true;
}

void MonoModPlugin::AllPluginsLoaded()
{
}

void MonoModPlugin::ClientPutInServer(edict_t *pEntity, char const *playername)
{
	// SH_ADD_MANUALHOOK_MEMFUNC(WeaponCanUse_hook, (CBaseEntity*)pEntity->GetUnknown()->GetBaseEntity(), &g_Restrict2Plugin, &Restrict2Plugin::WeaponCanUse_handler, false);
	RETURN_META(MRES_IGNORED);
}

void MonoModPlugin::ClientDisconnect(edict_t *pEntity)
{
	// SH_REMOVE_MANUALHOOK_MEMFUNC(WeaponCanUse_hook, (CBaseEntity*)pEntity->GetUnknown()->GetBaseEntity(), &g_Restrict2Plugin, &Restrict2Plugin::WeaponCanUse_handler, false);
	RETURN_META(MRES_IGNORED);
}

void MonoModPlugin::GameFrame(bool simulating)
{
	MonoModPlugin(MRES_IGNORED);
}