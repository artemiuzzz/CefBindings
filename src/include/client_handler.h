#pragma once
#include "include/cef_client.h"


class ClientHandler :
	public CefClient,
	public CefLifeSpanHandler,
	public CefKeyboardHandler
{
public:
	ClientHandler();
	
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}

	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE
	{
		return this;
	}

	virtual void OnBeforeClose( CefRefPtr<CefBrowser> browser ) OVERRIDE;
	virtual bool OnKeyEvent( CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event ) OVERRIDE;


private:
	IMPLEMENT_REFCOUNTING( ClientHandler );
};

