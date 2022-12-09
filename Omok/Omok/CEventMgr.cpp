#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"

#include "CStone.h"
#include "CBoard.h"
#include "CDotUI.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vEvemt.size(); i++)
	{
		Excute(m_vEvemt[i]);
	}

	m_vEvemt.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Obejct Address
		// wParam : Object Group
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::CHANGE_GAME_STATE:
	{
		// lParam : GAME_STATE
		GAME_STATE eState = (GAME_STATE)_eve.lParam;
		CGameMgr::GetInst()->SetGameState(eState);
	}
		break;
	case EVENT_TYPE::ENABLE_DOT_UI:
	{
		// lParam : pos x
		// wParam : pos y
		float xPos = (float)_eve.lParam;
		float yPos = (float)_eve.wParam;
		CDotUI* pDotUI = CGameMgr::GetInst()->GetDotUI();
		pDotUI->SetPos(Vec2(xPos, yPos));
		pDotUI->SetEnable(true);
	}
	break;
	case EVENT_TYPE::SKIP_TURN:
		CGameMgr::GetInst()->SkipTurn();
		break;
	}
}

CEventMgr* CEventMgr::GetInst()
{
	static CEventMgr instance;
	return &instance;
}