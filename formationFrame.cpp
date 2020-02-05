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
#include "formationFrame.h"
#include "ClientManager.h"

void CFormationFrame::Init()
{
	m_ScreenImg = ASPECT;
	m_ImgW = 320.0f * m_ScreenImg;
	m_ImgH = 46.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/formation/formationFrame.png", m_ImgW, m_ImgH, 1.0f);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, -303.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CFormationFrame::Uninit()
{
	m_Poly->Uninit();
}

void CFormationFrame::Update()
{
	//#pragma region “ü—Í
	//
	//	if (CInput::GetKeyPress(VK_LEFT)) {
	//		m_Position.x -= m_MoveSpeed;
	//		m_Poly->SetPosition(m_Position);
	//	}
	//
	//	if (CInput::GetKeyPress(VK_RIGHT)) {
	//		m_Position.x += m_MoveSpeed;
	//		m_Poly->SetPosition(m_Position);
	//	}
	//
	//	if (CInput::GetKeyPress(VK_UP)) {
	//		m_Position.y -= m_MoveSpeed;
	//		m_Poly->SetPosition(m_Position);
	//	}
	//
	//	if (CInput::GetKeyPress(VK_DOWN)) {
	//		m_Position.y += m_MoveSpeed;
	//		m_Poly->SetPosition(m_Position);
	//	}
	//
	//	m_Poly->SetPosition(m_Position);
	//#pragma endregion
}

void CFormationFrame::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}