#include "pch.h"
#include "CGameMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"

#include "CStone.h"
#include "CBoard.h"
#include "CDotUI.h"


CGameMgr::CGameMgr()
	: m_eGameState(GAME_STATE::NONE)
	, m_eTurn(STONE_INFO::BLACK)
	, m_bDebugMode(false)
	, m_pBoard(nullptr)
	, m_pDotUI(nullptr)
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

void CGameMgr::SkipTurn()
{
	if (STONE_INFO::BLACK == m_eTurn)
		m_eTurn = STONE_INFO::WHITE;
	else if (STONE_INFO::WHITE == m_eTurn)
		m_eTurn = STONE_INFO::BLACK;
}

void CGameMgr::PlacementStone(int index)
{
	CStone* pStone = m_pBoard->m_vBoardInfo[index];
	// 돌 색상 변경
	pStone->SetInfo(m_eTurn);

	// ui 위치 활성화, 위치 조정
	m_pDotUI->SetEnable(true);
	m_pDotUI->SetPos(pStone->GetPos());

	// 턴 넘기기
	SkipTurn();
}

void CGameMgr::Init(CBoard* pBoard)
{
	// 매개변수 초기화
	m_eGameState = GAME_STATE::PLAY;
	m_eTurn = STONE_INFO::BLACK;
	m_bDebugMode = false;
	m_pBoard = pBoard;

	CDotUI* pDotUI = new CDotUI();
	pDotUI->SetScale(Vec2(5.f, 5.f));
	CSceneMgr::GetInst()->GetCurScene()->AddObject(pDotUI, GROUP_TYPE::UI);
	m_pDotUI = pDotUI;
}

void CGameMgr::Update()
{
	if (GAME_STATE::NONE == m_eGameState)
		return;
	if (!GetFocus())
		return;

	if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::F1))
	{
		m_bDebugMode = !m_bDebugMode;
	}
}

void CGameMgr::Render(HDC _dc)
{
	if (GAME_STATE::NONE == m_eGameState)
		return;
	if (!GetFocus())
		return;

	assert(m_pBoard);
	assert(m_pDotUI);

	if (m_bDebugMode)
		m_pBoard->DrawDebugModeBoard(_dc);
}
