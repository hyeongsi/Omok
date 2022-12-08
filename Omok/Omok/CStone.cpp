#include "pch.h"
#include "CStone.h"

#include "CCore.h"

CStone::CStone()
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

	Ellipse(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

