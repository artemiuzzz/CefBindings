// CefBindings.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "cef_bindings.h"
#include "my_app.h"


//int _tmain( int argc, _TCHAR *argv[] )
int APIENTRY _tWinMain( _In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow )
{
	CefMainArgs main_args( hInstance );

	// Optional implementation of the CefApp interface.
	CefRefPtr<MyApp> app( new MyApp );

	// Execute the sub-process logic, if any. This will either return immediately for the browser
	// process or block until the sub-process should exit.
	int exit_code = CefExecuteProcess( main_args, app.get(), nullptr );
	if( exit_code >= 0 )
	{
		// The sub-process terminated, exit now.
		return exit_code;
	}

	// Populate this structure to customize CEF behavior.
	CefSettings settings;
	settings.single_process = true;

	// Initialize CEF in the main process.
	CefInitialize( main_args, settings, app.get(), nullptr );

	// Run the CEF message loop. This will block until CefQuitMessageLoop() is called.
	CefRunMessageLoop();

	// Shut down CEF.
	CefShutdown();

	return 0;
}
