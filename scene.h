#pragma once

#include <list>
#include "manager.h"
#include <vector>
#include <typeinfo>
#include "main.h"
#include "gameObject.h"
#include "imgui.h"
#include "useImGui.h"
#include "Camera.h"
#include "cube.h"
#include "polygon.h"
#include "background.h"
#include "backSpace.h"
#include "detailBG.h"
#include "characterPoly.h"
#include "header.h"
#include "headerMenu.h"
#include "headerTop.h"
#include "headerMypage.h"
#include "headerPower.h"
#include "headerSound.h"
#include "headerTown.h"
#include "menuBG.h"
#include "formationFrame.h"
#include "formationGuran.h"
#include "selectBG.h"
#include "mainMenberPoly.h"
#include "templateCharacter.h"
#include "characterSelectButton.h"
#include "detailButton.h"
#include "loginButton.h"
#include "firstCharacter.h"
#include "secondCharacter.h"
#include "thirdCharacter.h"
#include "selectCharPoly.h"
#include "detailCharPoly.h"
#include "detailPoly.h"
#include "charButton.h"
#include "weaponButton.h"
#include "summonButton.h"
#include "party.h"
#include "slot.h"
#include "weapon.h"
#include "quest.h"

class CScene
{
protected:
#define LISTMAX		(30)
	std::list<CGameObject*> m_GameObject[LISTMAX];		// STL(Standerd Template Library)

public:
	CScene() {}
	virtual ~CScene() {}

	virtual void Init()
	{
	}

	virtual void Uninit()
	{
		for (int i = 0; i < LISTMAX; i++) {
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}

			m_GameObject[i].clear();
		}
	}

	virtual void Update() {
		for (int i = 0; i < LISTMAX; i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Update();
			}

			// remove_if はリストのメソッド
			// 引数で関数又は、関数ポインタを渡す
			// ここでは関数ポインタではなく、引数で関数を直接渡している
			// []は"名前のない関数"を作るというもの

			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });
		}

		/// <summary>
		/// シーン切り換えフラグが立っていたら
		/// そのシーンのUninitを呼び出してそのシーンを削除する
		/// フラグはfalseに戻す
		/// </summary>
		if (CManager::GetSceneChangeFlag())
		{
			CManager::ChangeScene();
			CManager::SetSceneChangeFlag(false);
		}
	}

	virtual void Draw() {
		for (int i = 0; i < LISTMAX; i++) {
			for (CGameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

	void DestroyGameObject(CGameObject* GameObject) {
		GameObject->SetDestroy();
	}

#pragma region Templateのあれこれ

	/// <summary>
	/// CGameObjectを継承しているクラスをm_GameObjectリストに追加する
	/// Initを消しているので、引数はこのクラスのInitで指定する。
	/// </summary>
	template < typename T >
	T* AddGameObject(int layer) {
		T* object = new T();
		//object->Init();
		m_GameObject[layer].push_back(object);

		return object;
	}

	/// <summary>
	/// m_GameObjectリストに格納されているGameObjectの取得。
	/// 引数を指定することにより、何を取り出すのか決定できる。
	/// </summary>
	template< typename T >
	T* GetGameObject(int layer) {
		for (CGameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T)) {
				return (T*)object;
			}
		}

		return nullptr;
	}

	/// <summary>
	/// 複数形
	/// </summary>
	template < typename T >
	std::vector<T*>GetGameObjects(int layer) {
		std::vector<T*> objects;

		for (CGameObject* object : m_GameObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}

		return objects;
	}

#pragma endregion
};