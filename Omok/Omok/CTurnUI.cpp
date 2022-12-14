#include "pch.h"
#include "CTurnUI.h"

#include "CSelectGDI.h"
#include "CCore.h"

#include "CGameMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"

CTurnUI::CTurnUI()
	: m_dCurTimeAcc(0)
{
	SetPos(Vec2(85.f, 140.f));
	SetScale(Vec2(150.f, 200.f));
}

CTurnUI::~CTurnUI()
{
}


void CTurnUI::Update()
{
	m_dCurTimeAcc += CTimeMgr::GetInst()->GetDT();

	if (m_dCurTimeAcc >= TURN_LIMIT_SECOND)
	{
		m_dCurTimeAcc = TURN_LIMIT_SECOND;

		tEvent skipTurnEvent;
		skipTurnEvent.eEven = EVENT_TYPE::SKIP_TURN;

		CEventMgr::GetInst()->AddEvent(skipTurnEvent);
	}
}

void CTurnUI::Render(HDC _dc)
{
	RenderBackground(_dc);

	RenderBorder(_dc, -50, STONE_INFO::BLACK);
	RenderEllipse(_dc, {30.f, 30.f}, true);
	RenderText(_dc, {50.f, 20.f}, L"Black");
	RenderTimerBar(_dc, { -20.f, -45.f }, STONE_INFO::BLACK);

	RenderBorder(_dc, 45, STONE_INFO::WHITE);
	RenderEllipse(_dc, { 30.f, 125.f }, false);
	RenderText(_dc, { 50.f, 115.f }, L"White");
	RenderTimerBar(_dc, { -20.f, 50.f }, STONE_INFO::WHITE);
}

void CTurnUI::RenderBackground(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI gdi(_dc);
	gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::WOOD));

	Rectangle(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

void CTurnUI::RenderEllipse(HDC _dc, Vec2 _margin, bool isBlack)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Vec2 renderPos;
	renderPos.x = pos.x - scale.x / 2.f;
	renderPos.y = pos.y - scale.y / 2.f;

	CSelectGDI gdi(_dc);
	if (isBlack)
	{
		gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
		gdi.SetPen(CCore::GetInst()->GetPEN(PEN_TYPE::WHITE));
	}
	else
	{
		gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));
	}

	Ellipse(_dc
		, (int)(renderPos.x - OMOK_STONE_SMALL_SIZE + _margin.x)
		, (int)(renderPos.y - OMOK_STONE_SMALL_SIZE + _margin.y)
		, (int)(renderPos.x + OMOK_STONE_SMALL_SIZE + _margin.x)
		, (int)(renderPos.y + OMOK_STONE_SMALL_SIZE + _margin.y));
}

void CTurnUI::RenderText(HDC _dc, Vec2 _margin, wstring _str)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	RECT rt = { (LONG)(pos.x - scale.x / 2.f + _margin.x)
				,(LONG)(pos.y - scale.y / 2.f + _margin.y)
				,(LONG)(pos.x + scale.x / 2.f + _margin.x)
				,(LONG)(pos.y + scale.y / 2.f + _margin.y) };

	CSelectGDI gdi(_dc);
	gdi.SetTransparentBkMode();

	DrawText(_dc, _str.c_str(), (int)_str.length(), &rt, DT_SINGLELINE);
	
}

void CTurnUI::RenderBorder(HDC _dc, int _margin, STONE_INFO info)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Vec2 rectangleScale(130.f, 80.f);

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));

	if (info == CGameMgr::GetInst()->GetTurn())
	{
		gdi.SetPen(CCore::GetInst()->GetPEN(PEN_TYPE::GREEN));
	}

	Rectangle(_dc
		, (int)(pos.x - rectangleScale.x / 2.f)
		, (int)(pos.y - rectangleScale.y / 2.f + _margin)
		, (int)(pos.x + rectangleScale.x / 2.f)
		, (int)(pos.y + rectangleScale.y / 2.f + _margin));
}

void CTurnUI::RenderTimerBar(HDC _dc, Vec2 _margin, STONE_INFO info)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Vec2 lt(pos.x - scale.x / 2.f - _margin.x, pos.y + _margin.y);
	Vec2 rt(pos.x + scale.x / 2.f + _margin.x, pos.y + _margin.y + 20);

	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));

		Rectangle(_dc
			, (int)lt.x
			, (int)lt.y
			, (int)rt.x
			, (int)rt.y);
	}

	CSelectGDI brush(_dc);
	if(CGameMgr::GetInst()->GetTurn() == info)
	{
		brush.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::GREEN));

		double ratio = 1 - ((TURN_LIMIT_SECOND - m_dCurTimeAcc) / TURN_LIMIT_SECOND);
		int percent = (int)(((rt.x + 1) - (lt.x - 1)) * ratio);

		Rectangle(_dc
			, (int)lt.x - 1
			, (int)lt.y + 1
			, (int)rt.x + 1 - percent
			, (int)rt.y - 1);
	}
	else
	{
		brush.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));

		Rectangle(_dc
			, (int)lt.x - 1
			, (int)lt.y + 1
			, (int)rt.x + 1
			, (int)rt.y - 1);
	}
}
