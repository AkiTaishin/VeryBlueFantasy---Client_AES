#include "scene.h"
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
#include "backSpace.h"
#include "ClientManager.h"

void CBackSpace::Init()
{
	m_ScreenImg = SCREEN_WIDTH / 320.0f;
	m_ImgW = 320.0f * m_ScreenImg;
	m_ImgH = 800.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/background/backspace.png", (float)m_ImgW, (float)m_ImgH, (float)0.3);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, 100.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CBackSpace::Uninit()
{
	m_Poly->Uninit();
}

void CBackSpace::Update()
{
}

void CBackSpace::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}