#include "pch.h"
#include "CSoundMgr.h"

#include "CCore.h"

CSoundMgr::CSoundMgr()
{
}

CSoundMgr::~CSoundMgr()
{
}

CSoundMgr* CSoundMgr::GetInst()
{
	static CSoundMgr instance;
	return &instance;
}

void CSoundMgr::RegistPath(wstring _key, wstring _path)
{
	m_mWavPath.insert(make_pair(_key, _path));
}

void CSoundMgr::Init()
{
	RegistPath(L"replacement", L"Resource\\sound\\replacement.wav");
}

void CSoundMgr::Play(wstring _key)
{
	PlaySound(m_mWavPath[_key].c_str(), 0, SND_FILENAME | SND_ASYNC);
}