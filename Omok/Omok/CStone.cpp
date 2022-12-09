#include "pch.h"
#include "CStone.h"

#include "CCore.h"
#include "CSelectGDI.h"
#include "CGameMgr.h"

CStone::CStone()
	: m_eStoneInfo(STONE_INFO::NONE)
	, m_uiSequence(0)
{
}

CStone::~CStone()
{
}

void CStone::Update()
{
}

void CStone::Render(HDC _dc)
{
	if (STONE_INFO::NONE == m_eStoneInfo)
		return;

	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	if (STONE_INFO::BLACK == m_eStoneInfo)
	{
		CSelectGDI blackBrush(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));

		if (CGameMgr::GetInst()->IsDebugMode() && 0 != m_uiSequence)
		{
			CSelectGDI blackBk(_dc, RGB(0,0,0), COLORREF_TYPE::BACKGROUND);
			CSelectGDI whiteText(_dc, RGB(255, 255, 255), COLORREF_TYPE::TEXT);

			wstring sequenceStr = to_wstring(m_uiSequence);
			RECT rt = { (LONG)(pos.x - scale.x / 2.f),
						(LONG)(pos.y - scale.y / 2.f),
						(LONG)(pos.x + scale.x / 2.f),
						(LONG)(pos.y + scale.y / 2.f) };
			DrawText(_dc, sequenceStr.c_str(), (int)sequenceStr.length(), &rt, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
	else if(STONE_INFO::WHITE == m_eStoneInfo)
	{
		CSelectGDI whiteBrush(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));
		
		if (CGameMgr::GetInst()->IsDebugMode() && 0 != m_uiSequence)
		{
			CSelectGDI whiteBk(_dc, RGB(255, 255, 255), COLORREF_TYPE::BACKGROUND);
			CSelectGDI blackText(_dc, RGB(0, 0, 0), COLORREF_TYPE::TEXT);

			wstring sequenceStr = to_wstring(m_uiSequence);
			RECT rt = { (LONG)(pos.x - scale.x / 2.f),
						(LONG)(pos.y - scale.y / 2.f),
						(LONG)(pos.x + scale.x / 2.f),
						(LONG)(pos.y + scale.y / 2.f) };
			DrawText(_dc, sequenceStr.c_str(), (int)sequenceStr.length(), &rt, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
	}
	
}

