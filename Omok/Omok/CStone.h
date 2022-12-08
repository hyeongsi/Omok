#pragma once
#include "CObject.h"

class CTexture;

class CStone :
    public CObject
{
private:


private:


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CStone();
    virtual ~CStone();
};

