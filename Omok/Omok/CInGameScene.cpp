#include "pch.h"
#include "CInGameScene.h"

#include "COmokBoard.h"
#include "COmokBall.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

void CInGameScene::Enter()
{
	// create object
	COmokBoard* omokBoard = new COmokBoard();
	AddObject(omokBoard, GROUP_TYPE::OMOK_BOARD);
}

void CInGameScene::Exit()
{
	// delete object
	DeleteObjAll();
}