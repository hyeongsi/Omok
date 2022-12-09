#include "pch.h"
#include "CSelectGDI.h"

CSelectGDI::CSelectGDI(HDC _dc, HPEN _hpen)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(NULL)
	, m_defaultTextColor(NULL)
{
	m_defaulthPen = (HPEN)SelectObject(m_hdc, _hpen);
}

CSelectGDI::CSelectGDI(HDC _dc, HBRUSH _hbrush)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(NULL)
	, m_defaultTextColor(NULL)
{
	m_defaulthBrush = (HPEN)SelectObject(m_hdc, _hbrush);
	SetBkColor(_dc, m_defaultBkColor);
	SetTextColor(_dc, m_defaultTextColor);
}

CSelectGDI::CSelectGDI(HDC _dc, COLORREF _colorRef, COLORREF_TYPE _eType)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
{
	switch (_eType)
	{
	case COLORREF_TYPE::BACKGROUND:
		m_defaultBkColor = SetBkColor(_dc, _colorRef);
		break;
	case COLORREF_TYPE::TEXT:
		m_defaultTextColor = SetTextColor(_dc, _colorRef);
		break;
	}
}

CSelectGDI::~CSelectGDI()
{
	if (nullptr != m_defaulthPen)
		SelectObject(m_hdc, m_defaulthPen);
	if (nullptr != m_defaulthBrush)
		SelectObject(m_hdc, m_defaulthBrush);
}
