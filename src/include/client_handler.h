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

	virtual bool OnProcessMessageReceived( CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message ) OVERRIDE;

	virtual void OnBeforeClose( CefRefPtr<CefBrowser> browser ) OVERRIDE;


private:
	IMPLEMENT_REFCOUNTING( ClientHandler );
};

