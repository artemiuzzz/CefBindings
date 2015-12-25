#pragma once
#include "include/cef_app.h"


class MyApp :
	public CefApp,
	public CefBrowserProcessHandler
{
public:
	MyApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE{ return this; }

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING( MyApp );

};

