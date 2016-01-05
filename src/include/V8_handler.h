#pragma once
#include "include/cef_v8.h"


class V8Handler : public CefV8Handler
{
public:
	V8Handler();
	~V8Handler();

	bool Execute( const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception );

	CefRefPtr<CefV8Value> m_callbackFunction;
	CefRefPtr<CefV8Context> m_callbackContext;

private:
	IMPLEMENT_REFCOUNTING( V8Handler );
};

