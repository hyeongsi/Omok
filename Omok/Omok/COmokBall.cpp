#include "pch.h"
#include "COmokBall.h"

#include "CCore.h"

COmokBall::COmokBall()
{
}

COmokBall::~COmokBall()
{
}

void COmokBall::Update()
{
}

void COmokBall::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	Ellipse(_dc
		, (int)(pos.x - scale.x / 2.f)
		, (int)(pos.y - scale.y / 2.f)
		, (int)(pos.x + scale.x / 2.f)
		, (int)(pos.y + scale.y / 2.f));
}

