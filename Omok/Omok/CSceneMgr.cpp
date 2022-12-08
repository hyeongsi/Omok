#include "pch.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CInGameScene.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

CSceneMgr* CSceneMgr::GetInst()
{
	static CSceneMgr inst;
	return &inst;
}

void CSceneMgr::Init()
{
	// Create Scene & init
	CScene* ingameScene = new CInGameScene();
	m_arrScene[(UINT)SCENE_TYPE::INGAME] = ingameScene;

	m_pCurScene = ingameScene;
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}