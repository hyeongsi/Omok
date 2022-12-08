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

	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	static CCore* GetInst();
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetBDC() { return m_hBDC; }

	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPEN(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

public:
	void CreateBrushPen();

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

