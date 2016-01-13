#pragma once
#include <functional>


struct SearchItem
{
	std::wstring		name;
	std::wstring		size;
	std::wstring		type;
	std::wstring		date;
	std::wstring		path;
};


class Searcher
{
public:
	Searcher();
	~Searcher();

	void Search( const std::wstring& keyword, bool inFileName, bool inFolderName );
	std::function<void( SearchItem )> OnItemfound;

private:
	bool SearchInFolderRecursive( const std::wstring& folder );
	bool SearchMatches( const std::wstring& folder );

	std::wstring m_keyword;
	bool m_inFileName;
	bool m_inFolderName;

	//std::list<SearchItem> m_results;
};

