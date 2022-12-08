#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

class CEventMgr
{
private:
	vector<tEvent> m_vEvemt;


private:
	void Excute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vEvemt.emplace_back(_eve); }
	static CEventMgr* GetInst();

	void Update();

private:
	CEventMgr();
	~CEventMgr();

};

