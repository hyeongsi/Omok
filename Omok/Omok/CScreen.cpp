#include "pch.h"
#include "CScreen.h"

#include "CCore.h"
#include "CTimeMgr.h"

constexpr double FADE_TIME = 1.0;

CScreen::CScreen()
	: m_hDc(nullptr)
	, m_hBitmap(nullptr)
	, m_dCurrentTime(0.)
{
	POINT resolution = CCore::GetInst()->GetResolution();

	HDC hdc = CCore::GetInst()->GetMainDC();

	m_hDc = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, resolution.x, resolution.y);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hDc, m_hBitmap);
	DeleteObject(hOldBit);
}

CScreen::~CScreen()
{
}

void CScreen::Update()
{
	if (m_dCurrentTime < FADE_TIME)
	{
		m_dCurrentTime += CTimeMgr::GetInst()->GetDT();

		if (m_dCurrentTime > FADE_TIME)
		{
			m_dCurrentTime = FADE_TIME;
		}
	}
}

void CScreen::Render(HDC _dc)
{
	POINT resolution = CCore::GetInst()->GetResolution();

	double ratio = m_dCurrentTime / FADE_TIME;
	int alpha = 255 * (1 - ratio);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(_dc, 0, 0
		, resolution.x
		, resolution.y
		, m_hDc
		, 0
		, 0
		, resolution.x
		, resolution.y
		, bf);
}
