#include "pch.h"
#include "CStone.h"

#include "CCore.h"
#include "CSelectGDI.h"

CStone::CStone()
	: isBlack(true)
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
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	if (isBlack)
	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));
	}
	else
	{
		CSelectGDI gdi(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE));

		Ellipse(_dc
			, (int)(pos.x - scale.x / 2.f)
			, (int)(pos.y - scale.y / 2.f)
			, (int)(pos.x + scale.x / 2.f)
			, (int)(pos.y + scale.y / 2.f));
	}
	
}

