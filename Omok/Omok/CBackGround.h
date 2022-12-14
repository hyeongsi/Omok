#pragma once

#include "CObject.h"
class CBackGround :
    public CObject
{
private:
    HDC         m_hMemDC;
    HBITMAP     m_hBitmap;


public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CBackGround();
    virtual ~CBackGround();
    
};

