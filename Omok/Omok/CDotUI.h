#pragma once
#include "CObject.h"
class CDotUI :
    public CObject
{
private:
    bool m_bEnable;

public:
    void SetEnable(bool _b) { m_bEnable = _b; }
    bool GetEnable() { return m_bEnable; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CDotUI();
    virtual ~CDotUI();
};

