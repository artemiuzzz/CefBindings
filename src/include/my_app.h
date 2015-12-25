#pragma once
#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"


class MyApp :
	public CefApp,
	public CefBrowserProcessHandler,
	public CefRenderProcessHandler
{
public:
	MyApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE
	{
		return this;
	}

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

	virtual void OnContextCreated( CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context ) OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING( MyApp );
};

