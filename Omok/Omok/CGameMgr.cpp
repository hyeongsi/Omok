#include "pch.h"
#include "CGameMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CEventMgr.h"
#include "CSelectGDI.h"

#include "CStone.h"
#include "CDotUI.h"

#include "CCore.h"


CGameMgr::CGameMgr()
	: m_eGameState(GAME_STATE::NONE)
	, m_eTurn(STONE_INFO::BLACK)
	, m_bDebugMode(false)
	, m_pDotUI(nullptr)
	, m_uiId(0)
{
}

CGameMgr::~CGameMgr()
{
}

CGameMgr* CGameMgr::GetInst()
{
	static CGameMgr instance;
	return &instance;
}

bool CGameMgr::IsEnd()
{
	if (KEY_STATE::HOLD == CKeyMgr::GetInst()->GetKeyState(KEY::C))
	{
		return true;
	}

	return false;
}

void CGameMgr::SkipTurn()
{
	if (STONE_INFO::BLACK == m_eTurn)
		m_eTurn = STONE_INFO::WHITE;
	else if (STONE_INFO::WHITE == m_eTurn)
		m_eTurn = STONE_INFO::BLACK;
}

void CGameMgr::PlacementStone(CStone* stone)
{
	stone->SetInfo(m_eTurn);
	stone->SetSequence(++m_uiId);

	// ui 위치 활성화, 위치 조정
	m_pDotUI->SetEnable(true);
	m_pDotUI->SetPos(stone->GetPos());

	if (!IsEnd())
		SkipTurn();
	else
		m_eGameState = GAME_STATE::VICTORY;
}

void CGameMgr::Victory(STONE_INFO _e)
{
	switch (_e)
	{
	case STONE_INFO::NONE:
		assert(nullptr);
		break;
	case STONE_INFO::BLACK:
	{
		wstring victoryMessage = L"Black Win";
		MessageBox(CCore::GetInst()->GetMainHwnd(), victoryMessage.c_str(), L"Victory", MB_OK);
		m_eGameState = GAME_STATE::END;
	}
		break;
	case STONE_INFO::WHITE:
	{
		wstring victoryMessage = L"White Win";
		MessageBox(CCore::GetInst()->GetMainHwnd(), victoryMessage.c_str(), L"Victory", MB_OK);
		m_eGameState = GAME_STATE::END;
	}
		break;
	}
}

void CGameMgr::Init()
{
	// 매개변수 초기화
	m_eGameState = GAME_STATE::PLAY;
	m_eTurn = STONE_INFO::BLACK;
	m_bDebugMode = false;

	CDotUI* pDotUI = new CDotUI();
	pDotUI->SetScale(Vec2(5.f, 5.f));
	CSceneMgr::GetInst()->GetCurScene()->AddObject(pDotUI, GROUP_TYPE::UI);
	m_pDotUI = pDotUI;

	m_uiId = 0;
}

void CGameMgr::Update()
{
	if (GAME_STATE::NONE == m_eGameState)
		return;
	if (!GetFocus())
		return;

	if (GAME_STATE::VICTORY == m_eGameState)
	{
		Victory(m_eTurn);
	}
	else if (GAME_STATE::END == m_eGameState)
	{
		tEvent endGameEvent;
		endGameEvent.eEven = EVENT_TYPE::RESTART_GAME;
		CEventMgr::GetInst()->AddEvent(endGameEvent);
	}
	else
	{
		if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::F1))
		{
			m_bDebugMode = !m_bDebugMode;
		}
	}
}

void CGameMgr::Render(HDC _dc)
{
	if (GAME_STATE::PLAY == m_eGameState)
	{
		const int margin = 15;
		const int size = 10;

		Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
		mousePos += margin;

		CSelectGDI gdi(_dc);
		if (STONE_INFO::BLACK == m_eTurn)
		{
			gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));
		}
		else if (STONE_INFO::WHITE == m_eTurn)
		{
			gdi.SetBrush(CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));
		}

		Ellipse(_dc
			, (int)(mousePos.x - size)
			, (int)(mousePos.y - size)
			, (int)(mousePos.x + size)
			, (int)(mousePos.y + size));
	}
}
