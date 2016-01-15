#include "stdafx.h"
#include "my_app.h"
#include "client_handler.h"
#include "V8_handler.h"


CefRefPtr<ClientHandler> g_handler;


MyApp::MyApp()
{
}


void MyApp::OnContextInitialized()
{
	CEF_REQUIRE_UI_THREAD();

	// Information used when creating the native window.
	CefWindowInfo window_info;

#if defined(OS_WIN)
	// On Windows we need to specify certain flags that will be passed to
	// CreateWindowEx().
	window_info.SetAsPopup( NULL, "CefBindings" );
#endif

	// implements browser-level callbacks.
	g_handler = new ClientHandler();

	// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;

	std::string url;

	// Check if a "--url=" value was provided via the command-line. If so, use
	// that instead of the default URL.
	CefRefPtr<CefCommandLine> command_line =
		CefCommandLine::GetGlobalCommandLine();
	url = command_line->GetSwitchValue( "url" );
	if( url.empty() )
		url = "http://www.google.com";

	// Create the first browser window.
	CefBrowserHost::CreateBrowser( window_info, g_handler.get(), url,
		browser_settings, NULL );
}


void MyApp::OnContextCreated( CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context )
{
	CEF_REQUIRE_RENDERER_THREAD();

	//m_browser = browser;

	CefRefPtr<CefV8Value> object = context->GetGlobal();
	m_v8handler = new V8Handler();
	m_v8handler->onSearchButton = [browser]( CefString keyword )
	{
		
		// send message to browser thread
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create( "js_search_button_pressed" );
		CefRefPtr<CefListValue> args = msg->GetArgumentList();
		args->SetString( 0, keyword );

		browser->SendProcessMessage( PID_BROWSER, msg );
	};

	// cpp method from js
	CefRefPtr<CefV8Value> method = CefV8Value::CreateFunction( "searchInDocs", m_v8handler );
	object->SetValue( "searchInDocs", method, V8_PROPERTY_ATTRIBUTE_READONLY );
   
	// create JS methods for register methods to call from cpp
	object->SetValue( "registerAddMethod",
		CefV8Value::CreateFunction( "registerAddMethod", m_v8handler ),
		V8_PROPERTY_ATTRIBUTE_NONE );
}


bool MyApp::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message )
{
	CEF_REQUIRE_RENDERER_THREAD();

	// recieved message that item was found
	if( message->GetName() == "item_found_msg" )
	{
		auto args = message->GetArgumentList();
		if( args && ( args->GetSize() >= 3 ) )
		{
			CefString itemName = args->GetString( 0 );
			CefString itemSize = args->GetString( 1 );
			CefString itemPath = args->GetString( 2 );

			auto addMethod = m_v8handler->m_addItemMethod;
			if( addMethod )
			{
				CefV8ValueList methodArgs;
				methodArgs.push_back( CefV8Value::CreateString( itemName ) );
				methodArgs.push_back( CefV8Value::CreateString( itemSize ) );
				methodArgs.push_back( CefV8Value::CreateString( itemPath ) );
				if( !addMethod->ExecuteFunctionWithContext( m_v8handler->m_callbackContext, nullptr, methodArgs ) )
				{
					LOG( ERROR ) << "Error occurred when executing js function";
				}
			}
		}
		return true;
	}

	return false;
}