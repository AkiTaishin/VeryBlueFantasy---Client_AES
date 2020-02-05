#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "scene.h"
#include "manager.h"
#include "gameObject.h"
#include "polygon.h"
#include "header.h"
#include "headerPower.h"
#include "ClientManager.h"

void CHeaderPower::Init()
{
#pragma region ‰æ‘œƒTƒCƒY‚ğHeader‚É‡‚í‚¹‚é

	m_ScreenImg = ASPECT;
	m_ImgW = 160.0f * m_ScreenImg;
	m_ImgH = 31.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

#pragma endregion

	m_Poly = new CPolygon();
	m_Poly->Init("asset/header/power.png", m_ImgW, m_ImgH, 1.0f);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(-102.0f, -343.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CHeaderPower::Uninit()
{
	m_Poly->Uninit();
}

void CHeaderPower::Update()
{
}

void CHeaderPower::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}