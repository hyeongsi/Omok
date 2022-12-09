#pragma once

class CSelectGDI
{
private:
	HDC			m_hdc;
	HPEN		m_defaulthPen;
	HPEN		m_defaulthBrush;
	COLORREF	m_defaultBkColor;
	COLORREF	m_defaultTextColor;

public:
	CSelectGDI(HDC _dc, HPEN _hpen);
	CSelectGDI(HDC _dc, HBRUSH _hbrush);
	CSelectGDI(HDC _dc, COLORREF _ref, COLORREF_TYPE _eType);
	~CSelectGDI();
};

