#pragma once

#include "CObject.h"
class CStone;

class CBoard :
    public CObject
{
private:
    vector<CStone*> m_vBoardInfo;

public:
    Vec2 GetLT();
    Vec2 GetRB();

private:
    void Placement();
    void PlaceStone(int index);

    void DrawBoardBody(HDC _dc);
    void DrawBoardLine(HDC _dc);
    void DrawBoardDot(HDC _dc);

    void DrawRect(HDC _dc, Vec2 pos, Vec2 scale);

public:
    void AddStone(CStone* _pStone) { m_vBoardInfo.emplace_back(_pStone); }
    void DrawDebugModeBoard(HDC _dc);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CBoard();
    virtual ~CBoard();

    friend class CGameMgr;
};

