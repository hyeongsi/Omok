#pragma once

class CTimeMgr
{
private:
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	double			m_dDt;

public:
	static CTimeMgr* GetInst();

	double GetDT() { return m_dDt; }

public:
	void Init();
	void Update();

private:
	CTimeMgr();
	~CTimeMgr();

};
