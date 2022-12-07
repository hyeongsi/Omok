#pragma once

#include "CObject.h"

class COmokBoard :
    public CObject
{
private:


public:
    Vec2 GetLT();
    Vec2 GetRB();

private:
    void DrawBoardRect(HDC _dc);
    void DrawBoardLine(HDC _dc);
    void DrawBoardDot(HDC _dc);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    COmokBoard();
    virtual ~COmokBoard();

};

