#include "pch.h"
#include "CBackGround.h"

#include "CCore.h"
#include "CPathMgr.h"

CBackGround::CBackGround()
{
	m_hMemDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	POINT resolution = CCore::GetInst()->GetResolution();

	wstring path = CPathMgr::GetInst()->GetRealPath();
	path += L"\\content\\texture\\background.bmp";
	m_hBitmap = (HBITMAP)LoadImage(CCore::GetInst()->GetHInstance()
		, path.c_str()
		, IMAGE_BITMAP
		, resolution.x
		, resolution.y
		, LR_LOADFROMFILE);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	DeleteObject(oldBitmap);
}

CBackGround::~CBackGround()
{
	DeleteObject(m_hMemDC);
}

void CBackGround::Update()
{
}

void CBackGround::Render(HDC _dc)
{
	POINT resolution = CCore::GetInst()->GetResolution();

	BitBlt(_dc, 0, 0, resolution.x, resolution.y, m_hMemDC, 0, 0, SRCCOPY);
}