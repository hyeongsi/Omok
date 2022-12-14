#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount()
	, m_llCurCount()
	, m_llFrequency()
	, m_dDt()
{
}

CTimeMgr::~CTimeMgr()
{
}

CTimeMgr* CTimeMgr::GetInst()
{
	static CTimeMgr instance;
	return &instance;
}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;

	// dt값 1/60 제한
	if (m_dDt > (1. / 60.))
		m_dDt = 1. / 60.;
}
