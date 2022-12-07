#include "pch.h"
#include "COmokBoard.h"

#include "CCore.h"
#include "CSelectGDI.h"

COmokBoard::COmokBoard()
{
	float xScale = float(GO_BOARD_SIZE_X * GO_BOARD_COUNT);
	float yScale = float(GO_BOARD_SIZE_Y * GO_BOARD_COUNT);

	// �翷�� ���μ��� ũ���� ���� ���� �߰�
	int marginX = GO_BOARD_SIZE_X * 2;
	int marginY = GO_BOARD_SIZE_Y * 2;
	xScale += marginX;
	yScale += marginY;

	SetScale(Vec2(xScale, yScale));

	// ȭ�� �߾����� ����
	POINT resolution = CCore::GetInst()->GetResolution();
	SetPos(Vec2(resolution.x / 2.f, resolution.y / 2.f));
}

COmokBoard::~COmokBoard()
{
}


void COmokBoard::Update()
{
}

void COmokBoard::Render(HDC _dc)
{
	DrawBoardRect(_dc); // �ٵ��� �׸���
	DrawBoardLine(_dc);	// �ٵ��� ���� �� �׸���
	DrawBoardDot(_dc);	// �ٵ��� ���� �� �׸���
}
Vec2 COmokBoard::GetLT()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = GO_BOARD_SIZE_X;
	int marginY = GO_BOARD_SIZE_Y;

	// �������� �����ϰ� ���� �׸� LeftTop, RightBottom ��ġ ���
	Vec2 vLt = Vec2(pos.x - scale.x / 2.f + marginX, pos.y - scale.y / 2.f + marginY);

	return vLt;
}
Vec2 COmokBoard::GetRB()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	int marginX = GO_BOARD_SIZE_X;
	int marginY = GO_BOARD_SIZE_Y;

	// �������� �����ϰ� ���� �׸� LeftTop, RightBottom ��ġ ���
	Vec2 vRb = Vec2(pos.x + scale.x / 2.f - marginX, pos.y + scale.y / 2.f - marginY);

	return vRb;
}
void COmokBoard::DrawBoardRect(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetWoodBrush());
	Rectangle(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

void COmokBoard::DrawBoardLine(HDC _dc)
{
	Vec2 vLt = GetLT();
	Vec2 vRb = GetRB();

	int bCount = GO_BOARD_COUNT;
	// ���� ��
	for (int i = 0; i <= GO_BOARD_COUNT; i++)
	{
		int y = (int)vLt.y + (i * GO_BOARD_SIZE_Y);
		MoveToEx(_dc, (int)vLt.x, y, NULL);
		LineTo(_dc, (int)vRb.x, y);
	}
	// ���� ��
	for (int i = 0; i <= GO_BOARD_COUNT; i++)
	{
		int x = (int)vLt.x + (i * GO_BOARD_SIZE_X);
		MoveToEx(_dc, x, (int)vLt.y, NULL);
		LineTo(_dc, x, (int)vRb.y);
	}
}

void COmokBoard::DrawBoardDot(HDC _dc)
{
	const int radius = 3;
	Vec2 vLt = GetLT();

	CSelectGDI gdi(_dc, CCore::GetInst()->GetBlackBrush());

	for (int i = 0; i <= GO_BOARD_COUNT; i++)
	{
		for (int j = 0; j <= GO_BOARD_COUNT; j++)
		{
			// 3, 9, 15
			if ((2 == i || 9 == i || 15 == i) &&
				(2 == j || 9 == j || 15 == j) )
			{
				int x = j * GO_BOARD_SIZE_X;
				int y = i * GO_BOARD_SIZE_Y;

				Ellipse(_dc
					, int(vLt.x) + x - radius
					, int(vLt.y) + y - radius
					, int(vLt.x) + x + radius
					, int(vLt.y) + y + radius);
			}
		}
	}
}