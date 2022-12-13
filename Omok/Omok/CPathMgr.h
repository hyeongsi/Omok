#pragma once

class CPathMgr
{
private:
	wchar_t m_wcPath[256];

public:
	const wchar_t* GetRealPath() { return m_wcPath; }
	
	static CPathMgr* GetInst();

public:
	void Init();

private:
	CPathMgr();
	~CPathMgr();
};

