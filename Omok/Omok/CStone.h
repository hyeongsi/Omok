#pragma once
#include "CObject.h"

class CStone :
    public CObject
{
private:
    STONE_INFO      m_eStoneInfo;
    UINT            m_uiSequence;

public:
    void SetInfo(STONE_INFO _eType) { m_eStoneInfo = _eType; }
    STONE_INFO GetStoneInfo() { return m_eStoneInfo; }

    void SetSequence(UINT i) { m_uiSequence = i; }
    UINT GetSequence() { return m_uiSequence; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CStone();
    virtual ~CStone();
};

