#include "pch.h"
#include "CSelectGDI.h"

CSelectGDI::CSelectGDI(HDC _dc)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(NULL)
	, m_defaultTextColor(NULL)
{}

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
}

CSelectGDI::CSelectGDI(HDC _dc, COLORREF _colorRef, COLORREF_TYPE _eType)
	: m_hdc(_dc)
	, m_defaulthPen(nullptr)
	, m_defaulthBrush(nullptr)
	, m_defaultBkColor(NULL)
	, m_defaultTextColor(NULL)
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
	if (NULL != m_defaultBkColor)
		SetBkColor(m_hdc, m_defaultBkColor);
	if (NULL != m_defaultTextColor)
		SetTextColor(m_hdc, m_defaultTextColor);
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
		if(NULL == m_defaultBkColor)
			m_defaultBkColor = SetBkColor(m_hdc, _colorRef);
		break;
	case COLORREF_TYPE::TEXT:
		if (NULL == m_defaultTextColor)
			m_defaultTextColor = SetTextColor(m_hdc, _colorRef);
		break;
	}
}
