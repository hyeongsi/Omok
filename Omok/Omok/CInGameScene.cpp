#include "pch.h"
#include "CInGameScene.h"

#include "CBoard.h"
#include "CStone.h"

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
	CBoard* board = new CBoard();
	AddObject(board, GROUP_TYPE::BOARD);
}

void CInGameScene::Exit()
{
	// delete object
	DeleteObjAll();
}