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