#include "pch.h"
#include "CEventMgr.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

CEventMgr* CEventMgr::GetInst()
{
	static CEventMgr instance;
	return &instance;
}