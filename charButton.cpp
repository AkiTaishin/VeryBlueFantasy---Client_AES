#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "charButton.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "ClientManager.h"

void CCharButton::Init(float x, float y, float z, int number, bool flag)
{
	m_ScreenImg = ASPECT;
	m_ImgW = 95.0f * m_ScreenImg;
	m_ImgH = 34.0f * m_ScreenImg;
	m_IsAlive = flag;

	m_Poly = new CPolygon();

	m_Poly->Init("asset/button/charButton.png", "asset/button/charButtonNow.png", m_ImgW, m_ImgH);
	m_Poly->m_number = number;

	m_Position = XMFLOAT3(x, y, z);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CCharButton::Uninit()
{
	m_Poly->Uninit();
}

void CCharButton::Update()
{
#pragma region 入力

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region ポリゴンがクリックされたかデバッグ用

	/// <summary>
	/// 自分が選択されているときに押されても何も起きない(作りこみの時にスケールを小さくする)
	/// 自分以外が選択されているときに選択された時のみ、
	/// 自分をONにして自分以外をOFFにする
	/// </summary>

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 画像の切り替え
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON))
	{
		CManager::m_Mouse->m_IsSelect = false;

		// クリックが離されたときにボタンの上にマウスがあった場合
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// DestroyGameObjectを呼んで新たなポリゴンをAddする
			m_IsAlive = !m_IsAlive;
		}
	}

#pragma endregion
}

void CCharButton::Draw()
{
	if (m_IsAlive)
		m_Poly->Draw(m_Poly->m_number);
}

/// <summary>
/// フラグ情報によりDrawするかしないかを管理する。
/// つまり
/// ポリゴンは重ねて表示しておく
/// </summary>