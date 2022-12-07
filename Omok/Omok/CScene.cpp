#include "pch.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
	: m_arrObj{}
{}

CScene::~CScene()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (nullptr != m_arrObj[i][j])
				delete m_arrObj[i][j];
		}
	}
}

void CScene::DeleteObjAll()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (nullptr != m_arrObj[i][j])
				delete m_arrObj[i][j];
		}
	}
}

void CScene::Update()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (nullptr != m_arrObj[i][j])
				m_arrObj[i][j]->Update();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (nullptr != m_arrObj[i][j])
				m_arrObj[i][j]->Render(_dc);
		}
	}
}