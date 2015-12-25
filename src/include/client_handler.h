#pragma once
#include "include/cef_client.h"


class ClientHandler :
	public CefClient,
	public CefLifeSpanHandler
{
public:
	ClientHandler();
	
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}

	virtual void OnBeforeClose( CefRefPtr<CefBrowser> browser ) OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING( ClientHandler );
};

