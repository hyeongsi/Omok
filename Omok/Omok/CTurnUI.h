#pragma once
#include "CObject.h"

class CTurnUI :
    public CObject
{
private:
    double m_dCurTimeAcc;

public:
    void InitCurTimeAcc() { m_dCurTimeAcc = 0.; }

private:
    void RenderBackground(HDC _dc);
    void RenderEllipse(HDC _dc, Vec2 _margin, bool isBlack);
    void RenderText(HDC _dc, Vec2 _margin, wstring _str);
    void RenderBorder(HDC _dc, int _margin, STONE_INFO info);
    void RenderTimerBar(HDC _dc, Vec2 _margin, STONE_INFO info);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CTurnUI();
    virtual ~CTurnUI();

};

