#pragma once

#include "CObject.h"

class CScreen :
    public CObject
{
private:
	HDC			m_hDc;
	HBITMAP		m_hBitmap;

	double		m_dCurrentTime;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	CScreen();
	virtual ~CScreen();
};

