#pragma once
#include "CScene.h"

class CInGameScene :
    public CScene
{
private:

public:
    virtual void Update();

    virtual void Enter();
    virtual void Exit();

public:
    CInGameScene();
    ~CInGameScene();
};

