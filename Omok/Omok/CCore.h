#pragma once

class CCore
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	POINT		m_ptResolution;

	HDC			m_hDC;
	HDC			m_hBDC;
	HBITMAP		m_hBitmap;
	BITMAP		m_bitmapInfo;
	
	bool		m_bMenu;

	HBRUSH		m_woodBrush;
	HBRUSH		m_blackBrush;

public:
	static CCore* GetInst();
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetBDC() { return m_hBDC; }

	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetWoodBrush() { return m_woodBrush; }
	HBRUSH GetBlackBrush() { return m_blackBrush; }
public:
	void Init(HINSTANCE _hInst, HWND _hWnd);
	void Progress();

	void Update();
	void Render();

	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);
	void CreateHDC();

private:
	CCore();
	~CCore();
};

