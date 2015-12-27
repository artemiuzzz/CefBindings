#include "stdafx.h"
#include "client_handler.h"


ClientHandler::ClientHandler()
{
}


void ClientHandler::OnBeforeClose( CefRefPtr<CefBrowser> browser )
{
	CEF_REQUIRE_UI_THREAD();

	CefQuitMessageLoop();
}


bool ClientHandler::OnKeyEvent( CefRefPtr<CefBrowser> browser,
	const CefKeyEvent& event,
	CefEventHandle os_event )
{
	if( event.character == 'J' )
	{
		if( m_callbackFunction.get() && m_callbackContext.get() )
		{
			CefV8ValueList args /*= { CefV8Value::CreateObject(NULL) }*/;
			if( m_callbackFunction.get()->ExecuteFunctionWithContext( m_callbackContext, NULL, args ) )
			//if( m_callbackFunction.get()->ExecuteFunction( NULL, args ) )
			{
				MessageBox(NULL, L"Success", L"Caption", 0);
			}
		}
	}
	return false;
}