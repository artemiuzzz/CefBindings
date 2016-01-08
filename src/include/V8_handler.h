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

	std::function<void( CefString )> onSearchButton;

private:

	IMPLEMENT_REFCOUNTING( V8Handler );
};

