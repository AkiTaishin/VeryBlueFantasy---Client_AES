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
#include "detailPoly.h"
#include "ClientManager.h"

void CDetailPoly::Init(std::string fileName, float width, float height, float posX, float posY)
{
	m_ImgW = width * ASPECT;
	m_ImgH = height * ASPECT;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init(fileName, m_ImgW, m_ImgH, 1.0);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(posX, posY, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CDetailPoly::Uninit()
{
	m_Poly->Uninit();
}

void CDetailPoly::Update()
{
	m_Poly->SetPosition(m_Position);
}

void CDetailPoly::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}