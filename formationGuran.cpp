#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "formationGuran.h"
#include "ClientManager.h"

void CFormationGuran::Init()
{
	m_ScreenImg = ASPECT;
	m_ImgW = 317.0f * m_ScreenImg;
	m_ImgH = 145.0f * m_ScreenImg;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/formation/formationGuran.png", m_ImgW, m_ImgH, 1.0f);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, -198.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CFormationGuran::Uninit()
{
	m_Poly->Uninit();
}

void CFormationGuran::Update()
{
#pragma region デバッグ入力

	m_Poly->SetPosition(m_Position);

#pragma endregion
}

void CFormationGuran::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}