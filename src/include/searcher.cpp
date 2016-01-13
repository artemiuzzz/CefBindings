#include "stdafx.h"
#include "searcher.h"


Searcher::Searcher()
{
}


Searcher::~Searcher()
{
}


void Searcher::Search( const std::wstring& keyword, bool inFileName, bool inFolderName )
{
	m_keyword = keyword;
	m_inFileName = inFileName;
	m_inFolderName = inFolderName;

	PWSTR pathToDocs;
	HRESULT hr = ::SHGetKnownFolderPath( FOLDERID_Documents, 0, NULL, &pathToDocs );
	if( hr == S_OK )
	{
		SearchInFolderRecursive( pathToDocs );
		CoTaskMemFree( pathToDocs );
	}
}


bool Searcher::SearchInFolderRecursive( const std::wstring& folder )
{
	std::wstring searchPath( folder );
	searchPath.append( _T( "\\*" ) );

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFile( searchPath.c_str(), &ffd );

	if( INVALID_HANDLE_VALUE == hFind )
	{
		std::wstring error( _T( "Could not access " ) );
		error.append( searchPath );
		CefStringUTF16 w( error );
		LOG( ERROR ) << w.ToString().c_str();
		return false;
	}

	SearchMatches( folder );

	// cycle for recursive searching in ALL nested folders
	do
	{
		// skip current directory
		if( !lstrcmp( ffd.cFileName, _T(".") ) || !lstrcmp( ffd.cFileName, _T("..") ) )
			continue;		
		
		if( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			// go deeper			
			std::wstring subDir( folder + _T( "\\" ) + ffd.cFileName );
			SearchInFolderRecursive( subDir );			
		}
		
	} while( FindNextFile( hFind, &ffd ) != 0 );

	DWORD dwError = GetLastError();
	FindClose( hFind );
	if( dwError != ERROR_NO_MORE_FILES )
	{
		LOG( ERROR ) << "Error in FindNextFile: " << dwError;
		return false;
	}

	return true;
}


bool Searcher::SearchMatches( const std::wstring& folder )
{
	std::wstring searchPath( folder + _T( "\\" ) + m_keyword );

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFile( searchPath.c_str(), &ffd );

	if( INVALID_HANDLE_VALUE == hFind )
	{
		return false;
	}

	do
	{
		// skip current directory
		if( !lstrcmp( ffd.cFileName, _T( "." ) ) || !lstrcmp( ffd.cFileName, _T( ".." ) ) )
			continue;

		bool isFolder = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != NULL;

		if( (isFolder && m_inFolderName) || (!isFolder && m_inFileName) )
		{
			SearchItem itemInfo;
			itemInfo.name = ffd.cFileName;
			itemInfo.path = folder;

			SYSTEMTIME sysTime;
			if( FileTimeToSystemTime( &ffd.ftCreationTime, &sysTime ) )
			{
				TCHAR timeStr[256];
				GetTimeFormat( LOCALE_USER_DEFAULT, 0, &sysTime, NULL, timeStr,
					sizeof( timeStr ) / sizeof( TCHAR ) );
				TCHAR dateStr[256];
				GetDateFormat( LOCALE_USER_DEFAULT, 0, &sysTime, NULL, dateStr,
					sizeof( dateStr ) / sizeof( TCHAR ) );

				itemInfo.date.append( dateStr );
				itemInfo.date.append( _T( " " ) );
				itemInfo.date.append( timeStr );
			}

			if( !isFolder )
			{
				LARGE_INTEGER filesize;
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;

				std::wstringstream ss;
				ss << filesize.QuadPart;
				ss << _T( " bytes" );
				itemInfo.size = ss.str();

				SHFILEINFO fileInfo = { 0 };
				std::wstring fullFileNamel;
				fullFileNamel.append( folder );
				fullFileNamel.append( _T( "\\" ) );
				fullFileNamel.append( ffd.cFileName );

				if( SHGetFileInfo( fullFileNamel.c_str(), FILE_ATTRIBUTE_NORMAL, &fileInfo, sizeof( fileInfo ), SHGFI_TYPENAME ) )
					itemInfo.type = fileInfo.szTypeName;
			}

			OnItemfound( itemInfo );
		}
	} while( FindNextFile( hFind, &ffd ) != 0 );

	DWORD dwError = GetLastError();
	FindClose( hFind );
	if( dwError != ERROR_NO_MORE_FILES )
	{
		LOG( ERROR ) << "Error in FindNextFile: " << dwError;
		return false;
	}

	return true;
}