#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];

public:
	void AddObject(CObject* _obj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].emplace_back(_obj); }
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteObjAll();

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	CScene();
	~CScene();

};

