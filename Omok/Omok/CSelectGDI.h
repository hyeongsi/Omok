#pragma once

class CSelectGDI
{
private:
	HDC		m_hdc;
	HPEN	m_defaulthPen;
	HPEN	m_defaulthBrush;

public:
	CSelectGDI(HDC _dc, HPEN _hpen);
	CSelectGDI(HDC _dc, HBRUSH _hbrush);
	~CSelectGDI();
};

