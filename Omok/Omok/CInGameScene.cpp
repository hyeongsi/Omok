#include "pch.h"
#include "CInGameScene.h"

#include "CBoard.h"
#include "CStone.h"

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

	Vec2 vLT = pBoard->GetLT();
	int id = 0;

	for (int y = 0; y < OMOK_BOARD_COUNT + 1; y++)
	{
		for (int x = 0; x < OMOK_BOARD_COUNT + 1; x++)
		{
			Vec2 vpos;
			vpos.x = vLT.x + OMOK_BOARD_SIZE_X * x;
			vpos.y = vLT.y + OMOK_BOARD_SIZE_Y * y;

			CStone* pStone = new CStone();
			pStone->SetPos(vpos);
			pStone->SetScale(Vec2(OMOK_BOARD_SIZE_X, OMOK_BOARD_SIZE_Y));
			pStone->SetIndex(id++);

			AddObject(pStone, GROUP_TYPE::STONE);
		}
	}

	CGameMgr::GetInst()->Init();
}

void CInGameScene::Exit()
{
	// delete object
	DeleteObjAll();
}