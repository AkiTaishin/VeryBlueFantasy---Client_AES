#include "mouse.h"
#include <Windows.h>
#include "main.h"

void CMouse::Init()
{
	GetCursorPos(&m_pt);
	m_Position = XMFLOAT3(m_pt.x, m_pt.y, 0.0f);
	m_IsSelect = false;
}

void CMouse::Update()
{
	GetCursorPos(&m_pt);
	int n = ScreenToClient(GetWindow(), &m_pt);
	m_Position = XMFLOAT3(m_pt.x - SCREEN_WIDTH * 0.5f, m_pt.y - SCREEN_HEIGHT * 0.5f, 0.0f);
}

/// <summary>
/// マウスにセレクト情報を持たせて
/// 選択しているオブジェクトをひとつに絞り込む
/// bool m_selectを使う
/// </summary>