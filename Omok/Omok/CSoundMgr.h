#pragma once

#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

class CSoundMgr
{
private:
	map<wstring, wstring> m_mWavPath;

public:
	void Play(wstring _key);

public:
	static CSoundMgr* GetInst();

public:
	void RegistPath(wstring _key, wstring _path);
	void Init();

private:
	CSoundMgr();
	~CSoundMgr();
};

