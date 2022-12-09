#include "pch.h"
#include "CInGameScene.h"

#include "CBoard.h"
#include "CStone.h"

#include "CDotUI.h"
#include "CGameMgr.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}


void CInGameScene::Update()
{
	CScene::Update();
}

void CInGameScene::Enter()
{
	// create object
	CBoard* pBoard = new CBoard();
	AddObject(pBoard, GROUP_TYPE::BOARD);

	CDotUI* pDotUI = new CDotUI();
	pDotUI->SetScale(Vec2(5.f, 5.f));
	AddObject(pDotUI, GROUP_TYPE::UI);
	CGameMgr::GetInst()->SetDotUI(pDotUI);
}

void CInGameScene::Exit()
{
	// delete object
	DeleteObjAll();
}