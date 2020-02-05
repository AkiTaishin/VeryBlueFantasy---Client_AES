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
#include "detailBG.h"
#include "ClientManager.h"

void CDetailBG::Init()
{
	m_ImgW = 320 * ASPECT;
	m_ImgH = SCREEN_HEIGHT;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/background/bg_detail2.png", m_ImgW, m_ImgH, 1.0);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, 80.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CDetailBG::Uninit()
{
	m_Poly->Uninit();
}

void CDetailBG::Update()
{
	m_Poly->SetPosition(m_Position);
}

void CDetailBG::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}