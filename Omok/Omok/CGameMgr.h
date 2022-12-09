#pragma once

class CDotUI;

class CGameMgr
{
private:
	GAME_STATE		m_eGameState;
	bool			m_bBlackTurn;
	bool			m_bDebugMode;

public:
	void SetGameState(GAME_STATE _e) { m_eGameState = _e; }
	GAME_STATE GetGameState() { return m_eGameState; }

	bool GetIsBlackTurn() { return m_bBlackTurn; }
	bool GetIsDebugMode() { return m_bDebugMode; }

	void SkipTurn() { m_bBlackTurn = !m_bBlackTurn; }

	static CGameMgr* GetInst();

public:
	void Update();

private:
	CGameMgr();
	~CGameMgr();
};

