#include "stdafx.h"
#include "client_handler.h"
#include "searcher.h"


ClientHandler::ClientHandler()
{
}


bool ClientHandler::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message )
{
	CEF_REQUIRE_UI_THREAD();

	if( message->GetName() == "js_search_button_pressed" )
	{
		auto args = message->GetArgumentList();
		if( args->GetSize() > 0 )
		{
			CefString keyword = args->GetString( 0 );

			auto searcher = std::make_shared<Searcher>();
			searcher->OnItemfound = [browser]( SearchItem searchItem )
				{
					// send message to renderer thread
					CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create( "item_found_msg" );
					CefRefPtr<CefListValue> args = msg->GetArgumentList();
					args->SetString( 0, searchItem.name );
					args->SetString( 1, searchItem.size );
					args->SetString( 2, searchItem.path );
				
					browser->SendProcessMessage( PID_RENDERER, msg );
				};
				
			searcher->Search( keyword, true, true );
		}

		return true;
	}

	return false;
}


void ClientHandler::OnBeforeClose( CefRefPtr<CefBrowser> browser )
{
	CEF_REQUIRE_UI_THREAD();

	CefQuitMessageLoop();
}
