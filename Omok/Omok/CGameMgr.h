#pragma once

class CDotUI;
class CTurnUI;
class CScreen;
class CStone;

constexpr double TURN_LIMIT_SECOND = 10.;

class CGameMgr
{
private:
	GAME_STATE			m_eGameState;
	STONE_INFO			m_eTurn;
	bool				m_bDebugMode;

	CDotUI*				m_pDotUI;
	UINT				m_uiId;
	CTurnUI*			m_pTurnUI;

	CScreen*			m_pScreen;

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
	void CheckSameStoneWidth(UINT& sameColorCount, int curIndex, STONE_INFO color, int gap, int deep = 0);
	void CheckSameStoneHeight(UINT& sameColorCount, int curIndex, STONE_INFO color, int gap, int deep = 0);
	void CheckSameStoneRCross(UINT& sameColorCount, int curIndex, STONE_INFO color, int gap, int deep = 0);
	void CheckSameStoneLCross(UINT& sameColorCount, int curIndex, STONE_INFO color, int gap, int deep = 0);

	void SetVictoryStoneWidth(int curIndex, STONE_INFO color);
	void SetVictoryStoneHeight(int curIndex, STONE_INFO color);
	void SetVictoryStoneRCross(int curIndex, STONE_INFO color);
	void SetVictoryStoneLCross(int curIndex, STONE_INFO color);

public:
	bool IsEnd();
	void SkipTurn();
	void PlacementStone(CStone* stone);
	void Victory(STONE_INFO _e);

public:
	void Init();
	void FinalUpdate();
	void Render(HDC _dc);

private:
	CGameMgr();
	~CGameMgr();
};

