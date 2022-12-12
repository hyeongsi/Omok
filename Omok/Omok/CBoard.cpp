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
	int marginX = OMOK_BOARD_SIZE_X * 4;
	int marginY = OMOK_BOARD_SIZE_Y * 4;
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
	RenderBoardBody(_dc);	// 바둑판 그리기
	RenderBoardLine(_dc);	// 바둑판 내부 선 그리기
	RenderBoardDot(_dc);	// 바둑판 내부 점 그리기
	RenderBoardText(_dc);	// 바둑 외각 텍스트 그리기
}

Vec2 CBoard::GetLT()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = OMOK_BOARD_SIZE_X * 2;
	int marginY = OMOK_BOARD_SIZE_Y * 2;

	// 마진공간 제외하고 선을 그릴 LeftTop, RightBottom 위치 계산
	Vec2 vLt = Vec2(pos.x - scale.x / 2.f + marginX, pos.y - scale.y / 2.f + marginY);

	return vLt;
}

Vec2 CBoard::GetRB()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = OMOK_BOARD_SIZE_X * 2;
	int marginY = OMOK_BOARD_SIZE_Y * 2;

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
			if ((3 == i || 11 == i) &&
				(3 == j || 11 == j) ||
				(7 == i && 7 == j))
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

void CBoard::RenderBoardText(HDC _dc)
{
	Vec2 lt = GetLT();
	lt.x -= OMOK_BOARD_SIZE_X / 2.f;

	for (int i = 1; i <= 15; i++)
	{
		wstring sequenceStr = to_wstring(i);

		RECT rt = { (LONG)(lt.x - OMOK_BOARD_SIZE_X / 2.f)
					,(LONG)(lt.y - OMOK_BOARD_SIZE_Y / 2.f + ((i - 1) * OMOK_BOARD_SIZE_Y))
					,(LONG)(lt.x + OMOK_BOARD_SIZE_X / 2.f)
					,(LONG)(lt.y + OMOK_BOARD_SIZE_Y / 2.f + ((i - 1) * OMOK_BOARD_SIZE_Y)) };

		CSelectGDI background(_dc);

		background.SetColorRef(RGB(244, 176, 77), COLORREF_TYPE::BACKGROUND);
		DrawText(_dc, sequenceStr.c_str(), (int)sequenceStr.length(), &rt, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}

	lt = GetLT();
	lt.y -= OMOK_BOARD_SIZE_Y / 2.f;

	for (int i = 1; i <= 15; i++)
	{
		wstring sequenceStr;
		sequenceStr += 'A' + i - 1;

		RECT rt = { (LONG)(lt.x - OMOK_BOARD_SIZE_X / 2.f + ((i - 1) * OMOK_BOARD_SIZE_X))
					,(LONG)(lt.y - OMOK_BOARD_SIZE_Y / 2.f)
					,(LONG)(lt.x + OMOK_BOARD_SIZE_X / 2.f + ((i - 1) * OMOK_BOARD_SIZE_X))
					,(LONG)(lt.y + OMOK_BOARD_SIZE_Y / 2.f) };

		CSelectGDI background(_dc);

		background.SetColorRef(RGB(244, 176, 77), COLORREF_TYPE::BACKGROUND);
		DrawText(_dc, sequenceStr.c_str(), (int)sequenceStr.length(), &rt, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
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