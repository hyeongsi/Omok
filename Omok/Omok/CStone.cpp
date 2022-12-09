#include "pch.h"
#include "CStone.h"

#include "CCore.h"
#include "CSelectGDI.h"

CStone::CStone()
	: m_eStoneInfo(STONE_INFO::NONE)
{
}

CStone::~CStone()
{
}

void CStone::Update()
{
}

void CStone::Render(HDC _dc)
{
	if (STONE_INFO::NONE == m_eStoneInfo)
		return;

	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	if (STONE_INFO::BLACK == m_eStoneInfo)
	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));
	}
	else if(STONE_INFO::WHITE == m_eStoneInfo)
	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));
	}
	
}

