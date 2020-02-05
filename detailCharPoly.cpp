#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "getCharacterInfo.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "polygon.h"
#include "detailCharPoly.h"
#include "toScene.h"
#include "characterDetail.h"

void CDetailCharPoly::Init(std::string fileName)
{
	m_ImgW = 292.0f * ASPECT;
	m_ImgH = 114.0f * ASPECT;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init(fileName, m_ImgW, m_ImgH, 1.0);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(0.0f, -215.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CDetailCharPoly::Uninit()
{
	m_Poly->Uninit();
}

void CDetailCharPoly::Update()
{
	m_Poly->SetPosition(m_Position);
}

void CDetailCharPoly::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}