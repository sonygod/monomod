#pragma once
#pragma comment (lib,"mono.lib")

#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/debug-helpers.h>
#include <ISmmPlugin.h>

struct MethodCallCache {
	MonoObject *target;
	MonoClass *klass;
	MonoMethodDesc *methdesc;
	MonoMethod *method;
};

class MonoManager
{
public:
	MonoManager(void);
	~MonoManager(void);

public:
	void StartRuntime();
	void ShutdownRuntime();
	bool IsLoaded() const { return (m_AppDomain != 0); }

	MonoDomain *GetAppDomain() const;
	MonoAssembly *GetCoreAssembly() const;
	MonoObject *GetCoreMod() const;

public:
	void NotifyClientPutInServer();
	void NotifyClientDisconnect();
	void NotifyGameFrame();

private:
	MonoDomain *m_AppDomain;
	MonoAssembly *m_CoreAssembly;
	MonoObject *m_CoreMod;
	
	MethodCallCache m_CoreModStart;
	MethodCallCache m_CoreModShutdown;
	MethodCallCache m_CoreModClientPutInServer;
	MethodCallCache m_CoreModClientDisconnect;
	MethodCallCache m_CoreModGameFrame;

public:
	static void LogEntry(MonoString* logEntry);
	static void ServerPrint(MonoString* printEntry);	
};
