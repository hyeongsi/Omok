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
	, m_vStone()
	, m_pCurStone(nullptr)
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

bool CGameMgr::VictoryCheckWidth()
{
	UINT sameColorCount = 1;

	int index = m_pCurStone->GetIndex();
	STONE_INFO color = m_pCurStone->GetStoneInfo();

	sameColorCount += CheckSameStoneWidth(index, color, true);
	sameColorCount += CheckSameStoneWidth(index, color, false);

	if (5 <= sameColorCount)
		return true;

	return false;
}

int CGameMgr::CheckSameStoneWidth(int index, STONE_INFO color, bool isRight)
{
	int count = 0;
	int stoneIndex;

	// index 0부터 시작, %, / 결과값을 맞추기 위해 + 1하여 1부터 시작하게끔 만듦
	int compenIndex = index + 1;
	int compenWidth = OMOK_BOARD_STONE_COUNT + 1;
	int y = compenIndex / compenWidth;

	// 좌우 이동 검사
	for (int i = 1; i <= 4; i++)
	{
		if(isRight)
			stoneIndex = index + i;
		else
			stoneIndex = index - i;

		// 범위 밖 검사
		if (0 > stoneIndex || OMOK_BOARD_STONE_COUNT * OMOK_BOARD_STONE_COUNT < stoneIndex)
			break;

		// y 증가 여부 검사
		if ((stoneIndex + 1) / compenWidth != y)
			break;

		// 다른색상 돌 검사
		if (color != m_vStone[stoneIndex]->GetStoneInfo())
			break;

		count++;
	}

	return count;
}

bool CGameMgr::IsEnd()
{
	if (VictoryCheckWidth())
		return true;

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

	m_pCurStone = stone;

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

	vector<CObject*> v = CSceneMgr::GetInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::STONE);
	m_vStone.clear();
	for (int i = 0; i < v.size(); i++)
	{
		m_vStone.emplace_back((CStone*)v[i]);
	}
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
