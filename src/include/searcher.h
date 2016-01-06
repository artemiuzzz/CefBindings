#pragma once

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

	void search( const std::wstring& keyword, bool inFileName, bool inFolderName );

private:
	bool searchInFolder( const std::wstring& keyword );

	std::wstring m_keyword;
	bool m_inFileName;
	bool m_inFolderName;

	std::list<SearchItem> m_results;
};

