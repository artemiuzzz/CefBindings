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

	CefRefPtr<CefV8Value> object = context->GetGlobal();
	CefRefPtr<CefV8Handler> v8handler = new V8Handler();

	// cpp method from js
	CefRefPtr<CefV8Value> method = CefV8Value::CreateFunction( "cppmethod", v8handler );
	object->SetValue( "cppmethod", method, V8_PROPERTY_ATTRIBUTE_NONE );
   
	// JS method from cpp
	object->SetValue( "register",
	CefV8Value::CreateFunction( "register", v8handler ),
	V8_PROPERTY_ATTRIBUTE_NONE );
}