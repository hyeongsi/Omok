﻿#include "pch.h"
#include "CStone.h"

#include "CCore.h"
#include "CSelectGDI.h"
#include "CGameMgr.h"
#include "CKeyMgr.h"
#include "CEventMgr.h"

CStone::CStone()
	: m_eStoneInfo(STONE_INFO::NONE)
	, m_uiSequence(0)
	, m_iIndex(-1)
	, m_bIsVictoryStone(false)
{
}

CStone::~CStone()
{
}

void CStone::Update()
{
	if (GAME_STATE::READY == CGameMgr::GetInst()->GetGameState()
		|| GAME_STATE::PLAY == CGameMgr::GetInst()->GetGameState())
	{
		if (STONE_INFO::NONE == m_eStoneInfo
			&& IsCollision())
		{
			if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN))
			{
				STONE_INFO turn = CGameMgr::GetInst()->GetTurn();

				tEvent stoneInfoEvent;
				stoneInfoEvent.eEven = EVENT_TYPE::PLACEMENT_STONE;
				stoneInfoEvent.lParam = (DWORD_PTR)this;
				CEventMgr::GetInst()->AddEvent(stoneInfoEvent);
			}
		}
	}
}

void CStone::Render(HDC _dc)
{
	RenderBody(_dc);
	RenderPlaceText(_dc, m_eStoneInfo);
	RenderVictoryStone(_dc);
}

bool CStone::IsCollision()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();

	return CKeyMgr::GetInst()->IsCollision(pos, scale, mousePos, Vec2(1, 1));
}

void CStone::RenderBody(HDC _dc)
{
	if (STONE_INFO::NONE == m_eStoneInfo)
		return;

	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI brush(_dc);
	CSelectGDI pen(_dc);

	if (STONE_INFO::BLACK == m_eStoneInfo)
	{
		pen.SetPen(CCore::GetInst()->GetPEN(PEN_TYPE::WHITE));
		brush.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
	}
	else if (STONE_INFO::WHITE == m_eStoneInfo)
	{
		brush.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));
	}

	RenderEllipse(_dc);
}

void CStone::RenderPlaceText(HDC _dc, STONE_INFO _eType)
{
	if (!CGameMgr::GetInst()->IsDebugMode())
		return;
	if (0 == m_uiSequence)
		return;

	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	wstring sequenceStr = to_wstring(m_uiSequence);

	RECT rt = { (LONG)(pos.x - scale.x / 2.f),
					(LONG)(pos.y - scale.y / 2.f),
					(LONG)(pos.x + scale.x / 2.f),
					(LONG)(pos.y + scale.y / 2.f) };

	CSelectGDI gdi(_dc);

	if (this == CGameMgr::GetInst()->GetCurStone())
	{
		gdi.SetColorRef(RGB(255, 127, 0), COLORREF_TYPE::BACKGROUND);
		gdi.SetColorRef(RGB(0, 0, 0), COLORREF_TYPE::TEXT);
	}
	else
	{
		if (STONE_INFO::BLACK == _eType)
		{
			gdi.SetColorRef(RGB(0, 0, 0), COLORREF_TYPE::BACKGROUND);
			gdi.SetColorRef(RGB(255, 255, 255), COLORREF_TYPE::TEXT);
		}
		else
		{
			gdi.SetColorRef(RGB(255, 255, 255), COLORREF_TYPE::BACKGROUND);
			gdi.SetColorRef(RGB(0, 0, 0), COLORREF_TYPE::TEXT);
		}
	}

	DrawText(_dc, sequenceStr.c_str(), (int)sequenceStr.length(), &rt, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

void CStone::RenderVictoryStone(HDC _dc)
{
	if (m_bIsVictoryStone)
	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::RED));
		gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));
		RenderRect(_dc);
	}
}

void CStone::RenderEllipse(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Ellipse(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

bool CStone::RenderGuideLine(HDC _dc)
{
	if (STONE_INFO::NONE == m_eStoneInfo
		&& IsCollision())
	{
		CSelectGDI gdi(_dc);
		gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));
		gdi.SetPen(CCore::GetInst()->GetPEN(PEN_TYPE::GREEN));

		RenderRect(_dc);

		return true;
	}

	return false;
}

void CStone::RenderRect(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Rectangle(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

