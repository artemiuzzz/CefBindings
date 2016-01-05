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
	CEF_REQUIRE_UI_THREAD();

	if( event.character == 'J' )
	{
		// send message to renderer thread
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create( "execute_js" );
		CefRefPtr<CefListValue> args = msg->GetArgumentList();

		browser->SendProcessMessage( PID_RENDERER, msg );
	}
	return false;
}