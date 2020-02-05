#pragma once

class CScene;
class CMouse;
class CuseImGui;
class CManager
{
private:
	static CScene*	  m_NextScene;
	static bool       m_SceneChangeFlag;

public:
	static CScene*	  m_Scene;
	static CMouse*    m_Mouse;
	static CuseImGui* m_Gui;
	CManager(bool m_SceneChangeFlag) { m_SceneChangeFlag = false; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static bool GetSceneChangeFlag();
	static void SetSceneChangeFlag(bool wannaChange);
	static void ChangeScene();

	static CScene* GetScene() { return m_Scene; }

	template < typename T >
	static void SetScene() {
		T* scene = new T();
		m_NextScene = scene;
		if (m_Scene == nullptr)
		{
			m_Scene = m_NextScene;
			m_Scene->Init();
		}
	}
};