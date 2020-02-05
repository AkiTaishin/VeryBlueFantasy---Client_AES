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
#include "selectBG.h"
#include "ClientManager.h"

void CSelectBG::Init()
{
	m_ScreenImg = ASPECT;
	m_ImgW = 315.0f * m_ScreenImg;
	m_ImgH = 491.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/characterSelect/selectBG2.png", m_ImgW, m_ImgH, 1.0f);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, -25.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CSelectBG::Uninit()
{
	m_Poly->Uninit();
}

void CSelectBG::Update()
{
	m_Poly->SetPosition(m_Position);
}

void CSelectBG::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}