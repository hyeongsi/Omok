#pragma once

class CGameMgr
{
private:
	GAME_STATE		m_eGameState;
	bool			m_bBlackTurn;
	bool			m_bDebugMode;

public:
	GAME_STATE GetGameState() { return m_eGameState; }

	bool GetIsBlackTurn() { return m_bBlackTurn; }
	bool GetIsDebugMode() { return m_bDebugMode; }

	static CGameMgr* GetInst();

public:
	void Update();

private:
	CGameMgr();
	~CGameMgr();
};

