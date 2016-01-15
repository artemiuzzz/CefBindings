#pragma once
#include "include/cef_v8.h"
#include <functional>


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

	// callback when search button is clicked
	std::function<void( CefString )> onSearchButton;

	// js callbacks
	CefRefPtr<CefV8Value> m_addItemMethod;
	CefRefPtr<CefV8Context> m_callbackContext;

private:

	IMPLEMENT_REFCOUNTING( V8Handler );
};

