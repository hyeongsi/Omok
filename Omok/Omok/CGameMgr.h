#pragma once

class CDotUI;
class CStone;

class CGameMgr
{
private:
	GAME_STATE			m_eGameState;
	STONE_INFO			m_eTurn;
	bool				m_bDebugMode;

	CDotUI*				m_pDotUI;
	UINT				m_uiId;

	vector<CStone*>		m_vStone;
	CStone*				m_pCurStone;

public:
	void SetGameState(GAME_STATE _e) { m_eGameState = _e; }
	GAME_STATE GetGameState() { return m_eGameState; }

	STONE_INFO GetTurn() { return m_eTurn; }
	bool IsDebugMode() { return m_bDebugMode; }

	CDotUI* GetDotUI() { return m_pDotUI; }
	CStone* GetCurStone() { return m_pCurStone; }

	static CGameMgr* GetInst();

private:
	bool VictoryCheckWidth();
	int CheckSameStoneWidth(int index, STONE_INFO color, bool isRight);


public:
	bool IsEnd();
	void SkipTurn();
	void PlacementStone(CStone* stone);
	void Victory(STONE_INFO _e);

public:
	void Init();
	void Update();
	void Render(HDC _dc);

private:
	CGameMgr();
	~CGameMgr();
};

