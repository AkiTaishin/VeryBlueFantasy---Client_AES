#include "scene.h"
#include "manager.h"
#include <string>
#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "gameObject.h"
#include "mouse.h"
#include "input.h"
#include "gatya.h"

void CGatya::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackground>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
}

void CGatya::Uninit()
{
	CScene::Uninit();
}

void CGatya::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CGatya::Draw()
{
	CScene::Draw();
}