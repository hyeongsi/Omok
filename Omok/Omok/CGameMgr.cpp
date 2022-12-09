#include "pch.h"
#include "CGameMgr.h"

#include "CKeyMgr.h"

CGameMgr::CGameMgr()
	: m_eGameState(GAME_STATE::BEFORE_PLAY)
	, m_bBlackTurn(true)
	, m_bDebugMode(false)
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

void CGameMgr::Update()
{
	if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::F1))
	{
		m_bDebugMode = !m_bDebugMode;
	}
}