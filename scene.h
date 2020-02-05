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

			// remove_if �̓��X�g�̃��\�b�h
			// �����Ŋ֐����́A�֐��|�C���^��n��
			// �����ł͊֐��|�C���^�ł͂Ȃ��A�����Ŋ֐��𒼐ړn���Ă���
			// []��"���O�̂Ȃ��֐�"�����Ƃ�������

			m_GameObject[i].remove_if([](CGameObject* object) { return object->Destroy(); });
		}

		/// <summary>
		/// �V�[���؂芷���t���O�������Ă�����
		/// ���̃V�[����Uninit���Ăяo���Ă��̃V�[�����폜����
		/// �t���O��false�ɖ߂�
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

#pragma region Template�̂��ꂱ��

	/// <summary>
	/// CGameObject���p�����Ă���N���X��m_GameObject���X�g�ɒǉ�����
	/// Init�������Ă���̂ŁA�����͂��̃N���X��Init�Ŏw�肷��B
	/// </summary>
	template < typename T >
	T* AddGameObject(int layer) {
		T* object = new T();
		//object->Init();
		m_GameObject[layer].push_back(object);

		return object;
	}

	/// <summary>
	/// m_GameObject���X�g�Ɋi�[����Ă���GameObject�̎擾�B
	/// �������w�肷�邱�Ƃɂ��A�������o���̂�����ł���B
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
	/// �����`
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