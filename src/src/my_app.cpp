#include "stdafx.h"
#include "my_app.h"
#include "client_handler.h"


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

	// SimpleHandler implements browser-level callbacks.
	CefRefPtr<ClientHandler> handler( new ClientHandler() );

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
	CefBrowserHost::CreateBrowser( window_info, handler.get(), url,
		browser_settings, NULL );
}