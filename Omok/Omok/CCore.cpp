#include "pch.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CGameMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: m_hInst()
	, m_hWnd()
	, m_ptResolution{1280, 768}
	, m_hDC(nullptr)
	, m_hBDC(nullptr)
	, m_hBitmap()
	, m_bitmapInfo()
	, m_bMenu(true)
	, m_arrBrush{}
	, m_arrPen{}
{}

CCore::~CCore()
{
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
		DeleteObject(m_arrPen[i]);

	for (int i = 0; i < (UINT)BRUSH_TYPE::END; i++)
	{
		if((UINT)BRUSH_TYPE::HOLLOW != i)
			DeleteObject(m_arrBrush[i]);
	}
		

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
	// brush, pen 생성
	CreateBrushPen();

	// Mgr Init
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
}

void CCore::Progress()
{
	Update();
	Render();
}

void CCore::Update()
{
	CKeyMgr::GetInst()->Update();
	CSceneMgr::GetInst()->Update();
	CGameMgr::GetInst()->Update();
	CEventMgr::GetInst()->Update();
}

void CCore::Render()
{
	// 화면 Clear
	Rectangle(m_hBDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Mgr Render
	CSceneMgr::GetInst()->Render(m_hBDC);
	CGameMgr::GetInst()->Render(m_hBDC);
	
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

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::WOOD] = CreateSolidBrush(COLORREF(RGB(244, 176, 77)));
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(COLORREF(RGB(0, 0, 0)));
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = CreateSolidBrush(COLORREF(RGB(255, 255, 255)));
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(COLORREF(RGB(255, 0, 0)));
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, COLORREF(RGB(255, 0, 0)));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, COLORREF(RGB(0, 255, 0)));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, COLORREF(RGB(0, 0, 255)));
}
