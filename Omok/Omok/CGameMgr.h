﻿#pragma once

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
