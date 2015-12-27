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


	CefRefPtr<CefV8Value>& getCallbackFunction()
	{
		return m_callbackFunction;
	}

	CefRefPtr<CefV8Context>& getCallbackContext()
	{
		return m_callbackContext;
	}

private:

	CefRefPtr<CefV8Value> m_callbackFunction;
	CefRefPtr<CefV8Context> m_callbackContext;

	IMPLEMENT_REFCOUNTING( ClientHandler );
};

