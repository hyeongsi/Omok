#include "pch.h"
#include "CSelectGDI.h"

CSelectGDI::CSelectGDI(HDC _dc)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(RGB(255,255,255))
	, m_defaultTextColor(RGB(0, 0, 0))
	, m_bIsTransparentMode(false)
{}

CSelectGDI::CSelectGDI(HDC _dc, HPEN _hpen)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(RGB(255, 255, 255))
	, m_defaultTextColor(RGB(0, 0, 0))
	, m_bIsTransparentMode(false)
{
	m_defaulthPen = (HPEN)SelectObject(m_hdc, _hpen);
}

CSelectGDI::CSelectGDI(HDC _dc, HBRUSH _hbrush)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(RGB(255, 255, 255))
	, m_defaultTextColor(RGB(0, 0, 0))
	, m_bIsTransparentMode(false)
{
	m_defaulthBrush = (HPEN)SelectObject(m_hdc, _hbrush);
}

CSelectGDI::CSelectGDI(HDC _dc, COLORREF _colorRef, COLORREF_TYPE _eType)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(RGB(255, 255, 255))
	, m_defaultTextColor(RGB(0, 0, 0))
	, m_bIsTransparentMode(false)
{
	switch (_eType)
	{
	case COLORREF_TYPE::BACKGROUND:
		SetBkColor(_dc, _colorRef);
		break;
	case COLORREF_TYPE::TEXT:
		SetTextColor(_dc, _colorRef);
		break;
	}
}

CSelectGDI::~CSelectGDI()
{
	if (nullptr != m_defaulthPen)
		SelectObject(m_hdc, m_defaulthPen);
	if (nullptr != m_defaulthBrush)
		SelectObject(m_hdc, m_defaulthBrush);

	SetBkColor(m_hdc, m_defaultBkColor);
	SetTextColor(m_hdc, m_defaultTextColor);

	if(m_bIsTransparentMode)
		SetBkMode(m_hdc, OPAQUE);
}

void CSelectGDI::SetPen(HPEN _hpen)
{
	if (nullptr == m_defaulthPen)
	{
		m_defaulthPen = (HPEN)SelectObject(m_hdc, _hpen);
	}
}

void CSelectGDI::SetBrush(HBRUSH _hbrush)
{
	if (nullptr == m_defaulthBrush)
	{
		m_defaulthBrush = (HPEN)SelectObject(m_hdc, _hbrush);
	}
}

void CSelectGDI::SetColorRef(COLORREF _colorRef, COLORREF_TYPE _eType)
{
	switch(_eType)
	{
	case COLORREF_TYPE::BACKGROUND:
		SetBkColor(m_hdc, _colorRef);
		break;
	case COLORREF_TYPE::TEXT:
		SetTextColor(m_hdc, _colorRef);
		break;
	}
}

void CSelectGDI::SetTransparentBkMode()
{
	SetBkMode(m_hdc, TRANSPARENT);
	m_bIsTransparentMode = true;
}
