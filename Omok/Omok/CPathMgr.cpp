#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_wcPath{}
{
}

CPathMgr::~CPathMgr()
{
}

CPathMgr* CPathMgr::GetInst()
{
	static CPathMgr instance;
	return &instance;
}

void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_wcPath);
}