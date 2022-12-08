#pragma once

enum class KEY_STATE
{
	NONE,	// X
	TAP,	// down
	HOLD,	// press
	AWAY,	// up
};

struct tKeyInfo
{
	KEY_STATE eState;
	bool bPrevPush;
};

enum class KEY
{
	C,
	LBTN,
	F1,

	LAST,
};

class CKeyMgr
{
private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;

public:
	void FindMousePos();
	bool IsCollision(const Vec2& pos1, const Vec2& scale1, const Vec2& pos2, const Vec2& scale2);

public:
	Vec2 GetMousePos() { return m_vCurMousePos; }
	KEY_STATE GetKeyState(KEY _ekey) { return m_vecKey[(UINT)_ekey].eState; }

	static CKeyMgr* GetInst();

public:
	void Init();
	void Update();

private:
	CKeyMgr();
	~CKeyMgr();
};

