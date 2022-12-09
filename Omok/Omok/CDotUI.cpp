#include "pch.h"
#include "CDotUI.h"

#include "CCore.h"
#include "CSelectGDI.h"

#include "CGameMgr.h"

CDotUI::CDotUI()
	: m_bEnable(false)
{
}

CDotUI::~CDotUI()
{
}

void CDotUI::Update()
{
	
}

void CDotUI::Render(HDC _dc)
{
	if (m_bEnable)
	{
		if (CGameMgr::GetInst()->IsDebugMode())
			return;

		Vec2 pos = GetPos();
		Vec2 scale = GetScale();

		CSelectGDI rPen(_dc, CCore::GetInst()->GetPEN(PEN_TYPE::RED));
		CSelectGDI rBrush(_dc, CCore::GetInst()->GetBrush(BRUSH_TYPE::RED));

		Ellipse(_dc
			, int(pos.x - scale.x / 2.f)
			, int(pos.y - scale.y / 2.f)
			, int(pos.x + scale.x / 2.f)
			, int(pos.y + scale.y / 2.f));
	}
}