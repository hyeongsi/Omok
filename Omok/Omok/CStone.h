#pragma once
#include "CObject.h"

class CTexture;

class CStone :
    public CObject
{
private:
    bool isBlack;

public:
    void SetBlack(bool _b) { isBlack = _b; }
    bool IsBlack() { return isBlack; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CStone();
    virtual ~CStone();
};

