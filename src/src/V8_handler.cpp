#include "stdafx.h"
#include "V8_handler.h"
#include "client_handler.h"


extern CefRefPtr<ClientHandler> g_handler;


V8Handler::V8Handler()
{
}


V8Handler::~V8Handler()
{
}


bool V8Handler::Execute( const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception )
{
	CEF_REQUIRE_RENDERER_THREAD();

	// realization of cppmethod
	if( name == "cppmethod" )
	{
		LOG( INFO ) << "cppmethod";
		retval = CefV8Value::CreateString( "Hello from C++ !" );
		return true;
	}

	// realization of register method
	if( name == "register" )
	{
		LOG( INFO ) << "register";
		if( arguments.size() == 1 && arguments[0]->IsFunction() )
		{
			auto clientHandler = g_handler.get();
			if( clientHandler )
			{
				clientHandler->getCallbackFunction() = arguments[0];
				clientHandler->getCallbackContext() = CefV8Context::GetCurrentContext();
				return true;
			}
		}
	}

	return false;
}