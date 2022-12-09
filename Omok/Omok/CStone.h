#pragma once
#include "CObject.h"

class CStone :
    public CObject
{
private:
    STONE_INFO m_eStoneInfo;

public:
    void SetInfo(STONE_INFO _eType) { m_eStoneInfo = _eType; }
    STONE_INFO GetStoneInfo() { return m_eStoneInfo; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CStone();
    virtual ~CStone();
};

