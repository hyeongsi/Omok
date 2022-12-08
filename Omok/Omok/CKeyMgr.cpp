#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

// KEY와 매칭되는 VK 세팅
int g_arrVK[(int)KEY::LAST] =
{
	'C',
	VK_LBUTTON,
	VK_F1,

	// LAST
};

CKeyMgr::CKeyMgr()
	: m_vecKey()
	, m_vCurMousePos(Vec2(0.f, 0.f))
{
}

CKeyMgr::~CKeyMgr()
{
}

CKeyMgr* CKeyMgr::GetInst()
{
	static CKeyMgr instance;
	return &instance;
}

void CKeyMgr::Init()
{
	// 모든 입력 키 초기화
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.emplace_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		FindMousePos();
	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if(KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

void CKeyMgr::FindMousePos()
{
	POINT ptMousePos;
	GetCursorPos(&ptMousePos);
	ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptMousePos);

	m_vCurMousePos = Vec2((float)ptMousePos.x, (float)ptMousePos.y);
}

bool CKeyMgr::IsCollision(const Vec2& pos1, const Vec2& scale1, const Vec2& pos2, const Vec2& scale2)
{
	if (abs(pos1.x - pos2.x) <= ((scale1.x + scale2.x) / 2.f)
		&&  abs(pos1.y - pos2.y) <= ((scale1.y + scale2.y) / 2.f))
	{
		return true;
	}

	return false;
}
