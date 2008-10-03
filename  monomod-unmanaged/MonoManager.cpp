#include "MonoManager.h"
#include "MonoModPlugin.h"

MonoManager::MonoManager(void)
{
	m_AppDomain = 0;
}

MonoManager::~MonoManager(void)
{
	ShutdownRuntime();
}

void MonoManager::StartRuntime()
{
	const char* file = "C:\\SRCDS\\ZPS\\addons\\monomod\\plugins\\bin\\debug\\test_delete.dll";	
	char* av[] = {"program"};	
	MonoClass *klass;

	if(!m_AppDomain) {

		mono_set_dirs("C:\\Program Files\\Mono-1.9.1\\lib", "C:\\Program Files\\Mono-1.9.1\\etc");		
		
		if(!(m_AppDomain = mono_jit_init(file))) {
			// todo
			return;
		}

		mono_thread_attach(m_AppDomain);		
		mono_add_internal_call("JHeidt.MonoMod.Server::_Log", MonoManager::LogEntry);
		mono_add_internal_call("JHeidt.MonoMod.Server::_Print", MonoManager::ServerPrint);
				
		if (!(m_CoreAssembly = mono_domain_assembly_open(m_AppDomain, file))) {
			// todo
			return;
		}

		if (!(klass = mono_class_from_name(mono_assembly_get_image(m_CoreAssembly), "JHeidt.MonoMod", "Mod"))) {
			// todo
			return;
		}

		if(!(m_CoreMod = mono_object_new(m_AppDomain, klass))) {
			// todo
			return;
		}
		mono_runtime_object_init(m_CoreMod);
		
		m_CoreModStart.target = m_CoreMod;
		m_CoreModStart.klass = klass;
		m_CoreModStart.methdesc = mono_method_desc_new(":OnStart()", FALSE);
		m_CoreModStart.method = mono_method_desc_search_in_class(m_CoreModStart.methdesc, klass);

		m_CoreModShutdown.target = m_CoreMod;
		m_CoreModShutdown.klass = klass;
		m_CoreModShutdown.methdesc = mono_method_desc_new(":OnShutdown()", FALSE);
		m_CoreModShutdown.method = mono_method_desc_search_in_class(m_CoreModShutdown.methdesc, klass);

		mono_runtime_invoke(m_CoreModStart.method, m_CoreModStart.target, NULL, NULL);

		/*
		m_CoreModStart.target = m_CoreMod;
		m_CoreModStart.klass = klass;
		m_CoreModStart.methdesc = mono_method_desc_new(":OnStart()", FALSE);
		m_CoreModStart.method = mono_method_desc_search_in_class(m_CoreModStart.methdesc, klass);

		m_CoreModStart.target = m_CoreMod;
		m_CoreModStart.klass = klass;
		m_CoreModStart.methdesc = mono_method_desc_new(":OnStart()", FALSE);
		m_CoreModStart.method = mono_method_desc_search_in_class(m_CoreModStart.methdesc, klass);

		m_CoreModStart.target = m_CoreMod;
		m_CoreModStart.klass = klass;
		m_CoreModStart.methdesc = mono_method_desc_new(":OnStart()", FALSE);
		m_CoreModStart.method = mono_method_desc_search_in_class(m_CoreModStart.methdesc, klass);
		*/		
	}	
}

MonoDomain *MonoManager::GetAppDomain() const
{
	return m_AppDomain;
}

MonoAssembly *MonoManager::GetCoreAssembly() const
{
	return m_CoreAssembly;
}

MonoObject *MonoManager::GetCoreMod() const
{
	return m_CoreMod;
}

void MonoManager::ShutdownRuntime()
{
	if(m_AppDomain) {
		if(m_CoreModShutdown.method && m_CoreModShutdown.target) {
			mono_runtime_invoke(m_CoreModShutdown.method, m_CoreModShutdown.target, NULL, NULL);			
			m_CoreModShutdown.klass = 0;
			m_CoreModShutdown.methdesc = 0;
			m_CoreModShutdown.method = 0;			
			m_CoreModShutdown.target = 0;			
		}		
		mono_jit_cleanup(m_AppDomain);
		m_CoreAssembly = 0;
		m_CoreMod = 0;
		m_AppDomain = 0;
	}
}

void MonoManager::LogEntry(MonoString* logEntry)
{
	if(logEntry) {
		META_CONPRINT(mono_string_to_utf8(logEntry));
	}	
}

void MonoManager::ServerPrint(MonoString* printEntry)
{	
	if(printEntry) {
		META_CONPRINT(mono_string_to_utf8(printEntry));
	}	
}

void MonoManager::NotifyClientDisconnect()
{

}

void MonoManager::NotifyClientPutInServer()
{
}

void MonoManager::NotifyGameFrame()
{
}