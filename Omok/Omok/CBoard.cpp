#include "pch.h"
#include "CBoard.h"

#include "CCore.h"
#include "CSelectGDI.h"

#include "CKeyMgr.h"
#include "CGameMgr.h"
#include "CEventMgr.h"

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

	SetScale(Vec2(xScale, yScale));

	// 화면 중앙으로 세팅
	POINT resolution = CCore::GetInst()->GetResolution();
	SetPos(Vec2(resolution.x / 2.f, resolution.y / 2.f));

	Vec2 vLT = GetLT(); 
	for (int y = 0; y < OMOK_BOARD_COUNT + 1; y++)
	{
		for (int x = 0; x < OMOK_BOARD_COUNT + 1; x++)
		{
			Vec2 vpos;
			vpos.x = vLT.x + OMOK_BOARD_SIZE_X * x;
			vpos.y = vLT.y + OMOK_BOARD_SIZE_Y * y;

			tBoardInfo tboardInfo{ STONE_INFO::NONE
			, vpos
			, Vec2(OMOK_BOARD_SIZE_X,OMOK_BOARD_SIZE_Y) };
			m_vBoard.emplace_back(tboardInfo);
		}
	}
}

CBoard::~CBoard()
{
}


void CBoard::Update()
{
	HWND hwnd = GetFocus();
	if (nullptr == hwnd)
		return;

	LandStone();
}

void CBoard::Render(HDC _dc)
{
	DrawBoardRect(_dc); // 바둑판 그리기
	DrawBoardLine(_dc);	// 바둑판 내부 선 그리기
	DrawBoardDot(_dc);	// 바둑판 내부 점 그리기

	if(CGameMgr::GetInst()->GetIsDebugMode())
		DrawBoardInfo(_dc);	// 바둑판 정보 그리기
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

void CBoard::LandStone()
{
	Vec2 vPos;
	Vec2 vScale;

	for (size_t i = 0; i < m_vBoard.size(); i++)
	{
		vPos = m_vBoard[i].vPos;
		vScale = m_vBoard[i].vScale;

		Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
		if (STONE_INFO::NONE == m_vBoard[i].eStoneInfo
			&& CKeyMgr::GetInst()->IsCollision(vPos, vScale, mousePos, Vec2(1, 1)))
		{
			if (KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN))
			{
				CreateStone(vPos, vScale, (int)i);
				break;
			}
		}
	}
}

void CBoard::CreateStone(const Vec2& pos, const Vec2& scale, int index)
{
	// play 상태로 변경
	if (GAME_STATE::PLAY != CGameMgr::GetInst()->GetGameState())
	{
		tEvent tevent;
		tevent.eEven = EVENT_TYPE::CHANGE_GAME_STATE;
		tevent.lParam = (DWORD_PTR)GAME_STATE::PLAY;
		CEventMgr::GetInst()->AddEvent(tevent);
	}

	bool isBlack = CGameMgr::GetInst()->GetIsBlackTurn();

	CStone* pStone = new CStone();
	pStone->SetPos(pos);
	pStone->SetScale(scale);
	pStone->SetBlack(isBlack);

	// 돌 생성
	tEvent tevent2;
	tevent2.eEven = EVENT_TYPE::CREATE_OBJECT;
	tevent2.lParam = (DWORD_PTR)pStone;
	tevent2.wParam = (DWORD_PTR)GROUP_TYPE::STONE;
	CEventMgr::GetInst()->AddEvent(tevent2);

	// 순서 넘기기
	tEvent tevent3;
	tevent3.eEven = EVENT_TYPE::SKIP_TURN;
	CEventMgr::GetInst()->AddEvent(tevent3);

	if(isBlack)
		m_vBoard[index].eStoneInfo = STONE_INFO::BLACK;
	else
		m_vBoard[index].eStoneInfo = STONE_INFO::WHITE;
}

void CBoard::DrawBoardRect(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WOOD));
	Rectangle(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
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

void CBoard::DrawBoardInfo(HDC _dc)
{
	Vec2 vPos;
	Vec2 vScale;

	for (size_t i = 0; i < m_vBoard.size(); i++)
	{
		vPos = m_vBoard[i].vPos;
		vScale = m_vBoard[i].vScale;

		{
			CSelectGDI hollowBrush(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW));

			Vec2 mousePos = CKeyMgr::GetInst()->GetMousePos();
			if (STONE_INFO::NONE != m_vBoard[i].eStoneInfo
				|| CKeyMgr::GetInst()->IsCollision(vPos, vScale, mousePos, Vec2(1,1)))
			{
				if (KEY_STATE::HOLD == CKeyMgr::GetInst()->GetKeyState(KEY::LBTN))
				{
					CSelectGDI bluePen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::BLUE));
					Rectangle(_dc
						, (int)(vPos.x - vScale.x / 2.f)
						, (int)(vPos.y - vScale.y / 2.f)
						, (int)(vPos.x + vScale.x / 2.f)
						, (int)(vPos.y + vScale.y / 2.f));
				}
				else
				{
					CSelectGDI rednPen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::RED));
					Rectangle(_dc
						, (int)(vPos.x - vScale.x / 2.f)
						, (int)(vPos.y - vScale.y / 2.f)
						, (int)(vPos.x + vScale.x / 2.f)
						, (int)(vPos.y + vScale.y / 2.f));
				}		
			}
			else
			{
				CSelectGDI greenPen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::GREEN));
				Rectangle(_dc
					, (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));
			}
		}
	}
}
