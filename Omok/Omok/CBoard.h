#pragma once

#include "CObject.h"

class CBoard :
    public CObject
{
private:

public:
    Vec2 GetLT();
    Vec2 GetRB();

private:
    void RenderBoardBody(HDC _dc);
    void RenderBoardLine(HDC _dc);
    void RenderBoardDot(HDC _dc);

    void DrawRect(HDC _dc, Vec2 pos, Vec2 scale);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CBoard();
    virtual ~CBoard();

    friend class CGameMgr;
};

