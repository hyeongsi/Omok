#pragma once

class CScene;

class CSceneMgr
{
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurScene;

public:
	CScene* GetCurScene() { return m_pCurScene; }

	static CSceneMgr* GetInst();
	
public:
	void Init();
	void Update();
	void Render(HDC _dc);

private:
	CSceneMgr();
	~CSceneMgr();
};

