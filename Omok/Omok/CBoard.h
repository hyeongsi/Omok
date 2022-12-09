#pragma once

#include "CObject.h"

struct tBoardInfo
{
    STONE_INFO  eStoneInfo;
    Vec2        vPos;
    Vec2        vScale;
};

class CBoard :
    public CObject
{
private:
    vector<tBoardInfo> m_vBoard;  

public:
    Vec2 GetLT();
    Vec2 GetRB();

private:
    void LandStone();
    void CreateStone(const Vec2& pos, const Vec2& scale, int index);

    void DrawBoardRect(HDC _dc);
    void DrawBoardLine(HDC _dc);
    void DrawBoardDot(HDC _dc);
    void DrawBoardInfo(HDC _dc);

public:


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CBoard();
    virtual ~CBoard();

};

