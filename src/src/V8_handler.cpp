#include "stdafx.h"
#include "V8_handler.h"


V8Handler::V8Handler()
{
}


V8Handler::~V8Handler()
{
}


bool V8Handler::Execute( const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception )
{
	if( name == "cppmethod" )
	{
		retval = CefV8Value::CreateString( "My Value!" );
		return true;
	}
	return false;
}