#include "pch.h"
#include "CCore.h"

#include "CSceneMgr.h"

CCore::CCore()
	: m_hInst()
	, m_hWnd()
	, m_ptResolution{1280, 768}
	, m_hDC(nullptr)
	, m_hBDC(nullptr)
	, m_hBitmap()
	, m_bitmapInfo()
	, m_bMenu(true)
	, m_woodBrush(nullptr)
	, m_blackBrush(nullptr)
{}

CCore::~CCore()
{
	DeleteObject(m_woodBrush);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hBDC);
	ReleaseDC(m_hWnd, m_hDC);
}

CCore* CCore::GetInst()
{
	static CCore instnace;
	return &instnace;
}

void CCore::Init(HINSTANCE _hInst, HWND _hWnd)
{
	m_hInst = _hInst;
	m_hWnd = _hWnd;

	// 클라이언트 사이즈 설정
	m_ptResolution = POINT{ 1280, 768 };
	ChangeWindowSize(m_ptResolution, m_bMenu);
	// 백버퍼 생성
	CreateHDC();
	// brush 생성
	m_woodBrush = CreateSolidBrush(COLORREF(RGB(244, 176, 77)));
	m_blackBrush = CreateSolidBrush(COLORREF(RGB(0, 0, 0)));

	// Mgr Init
	CSceneMgr::GetInst()->Init();
}

void CCore::Progress()
{
	Update();
	Render();
}

void CCore::Update()
{
	CSceneMgr::GetInst()->Update();

}

void CCore::Render()
{
	// 화면 Clear
	Rectangle(m_hBDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Mgr Render
	CSceneMgr::GetInst()->Render(m_hBDC);
	


	// Render
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBDC, 0, 0, SRCCOPY);
}

void CCore::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (LONG)_ptResolution.x, (LONG)_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 50, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CCore::CreateHDC()
{
	m_hDC = GetDC(m_hWnd);

	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hBDC, m_hBitmap);
	DeleteObject(hOldBit);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmapInfo);
	assert(m_hBitmap);
}