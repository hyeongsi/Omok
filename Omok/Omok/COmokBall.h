#pragma once
#include "CObject.h"

class CTexture;

class COmokBall :
    public CObject
{
private:


private:


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    COmokBall();
    virtual ~COmokBall();
};

