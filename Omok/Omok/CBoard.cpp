#include "pch.h"
#include "CBoard.h"

#include "CCore.h"
#include "CSelectGDI.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"
#include "CEventMgr.h"

#include "CScene.h"
#include "CStone.h"

CBoard::CBoard()
{
	float xScale = float(OMOK_BOARD_SIZE_X * OMOK_BOARD_COUNT);
	float yScale = float(OMOK_BOARD_SIZE_Y * OMOK_BOARD_COUNT);

	// 양옆에 가로세로 크기의 여유 공간 추가
	int marginX = OMOK_BOARD_SIZE_X * 2;
	int marginY = OMOK_BOARD_SIZE_Y * 2;
	xScale += marginX;
	yScale += marginY;

	// 크기 지정
	SetScale(Vec2(xScale, yScale));

	// 위치 지정, (화면 중앙)
	POINT resolution = CCore::GetInst()->GetResolution();
	SetPos(Vec2(resolution.x / 2.f, resolution.y / 2.f));
}

CBoard::~CBoard()
{
}


void CBoard::Update()
{
}

void CBoard::Render(HDC _dc)
{
	RenderBoardBody(_dc); // 바둑판 그리기
	RenderBoardLine(_dc);	// 바둑판 내부 선 그리기
	RenderBoardDot(_dc);	// 바둑판 내부 점 그리기
}

Vec2 CBoard::GetLT()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = OMOK_BOARD_SIZE_X;
	int marginY = OMOK_BOARD_SIZE_Y;

	// 마진공간 제외하고 선을 그릴 LeftTop, RightBottom 위치 계산
	Vec2 vLt = Vec2(pos.x - scale.x / 2.f + marginX, pos.y - scale.y / 2.f + marginY);

	return vLt;
}

Vec2 CBoard::GetRB()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = OMOK_BOARD_SIZE_X;
	int marginY = OMOK_BOARD_SIZE_Y;

	// 마진공간 제외하고 선을 그릴 LeftTop, RightBottom 위치 계산
	Vec2 vRb = Vec2(pos.x + scale.x / 2.f - marginX, pos.y + scale.y / 2.f - marginY);

	return vRb;
}

void CBoard::RenderBoardBody(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WOOD));
	DrawRect(_dc, pos, scale);
}

void CBoard::RenderBoardLine(HDC _dc)
{
	Vec2 vLt = GetLT();
	Vec2 vRb = GetRB();

	int bCount = OMOK_BOARD_COUNT;
	// 가로 선
	for (int i = 0; i <= OMOK_BOARD_COUNT; i++)
	{
		int y = (int)vLt.y + (i * OMOK_BOARD_SIZE_Y);
		MoveToEx(_dc, (int)vLt.x, y, NULL);
		LineTo(_dc, (int)vRb.x, y);
	}
	// 세로 선
	for (int i = 0; i <= OMOK_BOARD_COUNT; i++)
	{
		int x = (int)vLt.x + (i * OMOK_BOARD_SIZE_X);
		MoveToEx(_dc, x, (int)vLt.y, NULL);
		LineTo(_dc, x, (int)vRb.y);
	}
}

void CBoard::RenderBoardDot(HDC _dc)
{
	const int radius = 3;
	Vec2 vLt = GetLT();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));

	for (int i = 0; i <= OMOK_BOARD_COUNT; i++)
	{
		for (int j = 0; j <= OMOK_BOARD_COUNT; j++)
		{
			// 3, 9, 15
			if ((2 == i || 9 == i || 15 == i) &&
				(2 == j || 9 == j || 15 == j) )
			{
				int x = j * OMOK_BOARD_SIZE_X;
				int y = i * OMOK_BOARD_SIZE_Y;

				Ellipse(_dc
					, int(vLt.x) + x - radius
					, int(vLt.y) + y - radius
					, int(vLt.x) + x + radius
					, int(vLt.y) + y + radius);
			}
		}
	}
}

void CBoard::DrawRect(HDC _dc, Vec2 pos, Vec2 scale)
{
	Rectangle(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}