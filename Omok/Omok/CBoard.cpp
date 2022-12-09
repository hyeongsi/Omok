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
	HWND hwnd = GetFocus();
	if (nullptr == hwnd)
		return;

	// 착점
	Placement();
}

void CBoard::Render(HDC _dc)
{
	DrawBoardBody(_dc); // 바둑판 그리기
	DrawBoardLine(_dc);	// 바둑판 내부 선 그리기
	DrawBoardDot(_dc);	// 바둑판 내부 점 그리기
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

void CBoard::Placement()
{
	Vec2 vPos;
	Vec2 vScale;

	for (size_t i = 0; i < m_vBoardInfo.size(); i++)
	{
		vPos = m_vBoardInfo[i]->GetPos();
		vScale = m_vBoardInfo[i]->GetScale();

		Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
		if (STONE_INFO::NONE == m_vBoardInfo[i]->GetStoneInfo()
			&& CKeyMgr::GetInst()->IsCollision(vPos, vScale, mousePos, Vec2(1, 1)))
		{
			if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN))
			{
				PlaceStone((int)i);
				break;
			}
		}
	}
}

void CBoard::PlaceStone(int index)
{
	STONE_INFO turn = CGameMgr::GetInst()->GetTurn();

	m_vBoardInfo[index]->SetInfo(turn);

	tEvent stoneInfoEvent;
	stoneInfoEvent.eEven = EVENT_TYPE::PLACEMENT_STONE;
	stoneInfoEvent.lParam = (DWORD_PTR)index;
	CEventMgr::GetInst()->AddEvent(stoneInfoEvent);
}

void CBoard::DrawBoardBody(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WOOD));
	DrawRect(_dc, pos, scale);
}

void CBoard::DrawBoardLine(HDC _dc)
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

void CBoard::DrawBoardDot(HDC _dc)
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

void CBoard::DrawDebugModeBoard(HDC _dc)
{
	Vec2 vPos;
	Vec2 vScale;

	for (size_t i = 0; i < m_vBoardInfo.size(); i++)
	{
		vPos = m_vBoardInfo[i]->GetPos();
		vScale = m_vBoardInfo[i]->GetScale();

		{
			CSelectGDI hollowBrush(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));

			// 마우스와 충돌 확인
			Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
			if (CKeyMgr::GetInst()->IsCollision(vPos, vScale, mousePos, Vec2(1, 1)))
			{
				if (KEY_STATE::HOLD == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN))
				{
					CSelectGDI bluePen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::BLUE));
					DrawRect(_dc, vPos, vScale);
				}
				else
				{
					CSelectGDI bluePen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::RED));
					DrawRect(_dc, vPos, vScale);
				}
			}
			else
			{
				CSelectGDI greenPen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::GREEN));
				DrawRect(_dc, vPos, vScale);

			}
		}
	}
}