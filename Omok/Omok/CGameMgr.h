#pragma once

class CBoard;
class CDotUI;

class CGameMgr
{
private:
	GAME_STATE		m_eGameState;
	STONE_INFO		m_eTurn;
	bool			m_bDebugMode;

	CBoard*			m_pBoard;
	CDotUI*			m_pDotUI;

	UINT			m_uiId;

public:
	void SetGameState(GAME_STATE _e) { m_eGameState = _e; }
	GAME_STATE GetGameState() { return m_eGameState; }

	STONE_INFO GetTurn() { return m_eTurn; }
	bool IsDebugMode() { return m_bDebugMode; }

	CDotUI* GetDotUI() { return m_pDotUI; }

	static CGameMgr* GetInst();

public:
	bool IsEnd();
	void SkipTurn();
	void PlacementStone(int index);
	void Victory(STONE_INFO _e);

public:
	void Init(CBoard* pBoard);
	void Update();
	void Render(HDC _dc);

private:
	CGameMgr();
	~CGameMgr();
};

