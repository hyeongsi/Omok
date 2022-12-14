#pragma once
#include "CObject.h"

class CStone :
    public CObject
{
private:
    STONE_INFO      m_eStoneInfo;
    UINT            m_uiSequence;

    int             m_iIndex;
    bool            m_bIsVictoryStone;

public:
    void SetInfo(STONE_INFO _eType) { m_eStoneInfo = _eType; }
    STONE_INFO GetStoneInfo() { return m_eStoneInfo; }

    void SetSequence(UINT i) { m_uiSequence = i; }
    UINT GetSequence() { return m_uiSequence; }
    
    void SetIndex(int i) { m_iIndex = i; }
    int GetIndex() { return m_iIndex; }

    void SetVictory(bool isVictory) { m_bIsVictoryStone = isVictory; }

    bool IsCollision();

public:
    void RenderBody(HDC _dc);
    void RenderPlaceText(HDC _dc, STONE_INFO _eType);
    void RenderVictoryStone(HDC _dc);
    void RenderEllipse(HDC _dc);
    bool RenderGuideLine(HDC _dc);
    void RenderRect(HDC _dc);

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CStone();
    virtual ~CStone();
};

