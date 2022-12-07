#include "pch.h"
#include "CSelectGDI.h"

CSelectGDI::CSelectGDI(HDC _dc, HPEN _hpen)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
{
	m_defaulthPen = (HPEN)SelectObject(m_hdc, _hpen);
}

CSelectGDI::CSelectGDI(HDC _dc, HBRUSH _hbrush)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
{
	m_defaulthBrush = (HPEN)SelectObject(m_hdc, _hbrush);
}

CSelectGDI::~CSelectGDI()
{
	if (nullptr != m_defaulthPen)
		SelectObject(m_hdc, m_defaulthPen);
	if (nullptr != m_defaulthBrush)
		SelectObject(m_hdc, m_defaulthBrush);
}
