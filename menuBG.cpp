#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "menuBG.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "ClientManager.h"

void CMenuBG::Init()
{
	m_ImgW = 100.0f;
	m_ImgH = 313.0f;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/sidemenu/menuBG.png", m_ImgW, m_ImgH, 0.4);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(-151.0f, -178.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.2f, 1.1f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CMenuBG::Uninit()
{
	m_Poly->Uninit();
}

void CMenuBG::Update()
{
#pragma region “ü—Í

#pragma endregion
}

void CMenuBG::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}