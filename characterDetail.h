#include <vector>
#include "getCharacterInfo.h"

class CCharacterDetail : public CScene {
private:

	/// <summary>
	/// Init�ŏ���character�̏������o���ĕۊǂ��Ă������߂̃����o�ϐ����쐬����
	/// </summary>
	std::vector<GETINFO> m_GetCharData;
	int m_HaveCharacterNumber;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DebugRender();

#pragma region ImGuI�ł̃f�o�b�N

	void DebugImGui() {
		for (int i = 0; i < LISTMAX; i++) {
			for (auto object : m_GameObject[i])
			{
				// @todo �����_����
				// �e��GameObject�̍��W�\��
				switch (i)
				{
				case 0:
					if (ImGui::TreeNode("Camera")) {
						XMFLOAT3 position = object->GetPosition();
						XMFLOAT3 rotation = object->GetRotation();
						ImGui::InputFloat3("position", &position.x);
						ImGui::InputFloat3("rotaion", &rotation.x);
						ImGui::TreePop();
					}
					break;

				case 1:
					if (ImGui::TreeNode("Cube")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 2:
					if (ImGui::TreeNode("Background")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						ImGui::TreePop();
					}
					break;

				case 3:
					if (ImGui::TreeNode("Header")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						ImGui::TreePop();
					}
					break;

				case 4:
					if (ImGui::TreeNode("HeaderMenu")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						ImGui::TreePop();
					}
					break;

				case 5:
					if (ImGui::TreeNode("HeaderMypage")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						ImGui::TreePop();
					}
					break;

				case 6:
					if (ImGui::TreeNode("CDetailBG")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 7:
					if (ImGui::TreeNode("box")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 8:
					if (ImGui::TreeNode("char")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 9:
					if (ImGui::TreeNode("ribbon")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 10:
					if (ImGui::TreeNode("Apply")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 11:
					if (ImGui::TreeNode("Cancel")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

					//case 11:
					//	if (ImGui::TreeNode("yuriusu")) {
					//		XMFLOAT3 position = object->GetPosition();
					//		ImGui::InputFloat3("position", &position.x);
					//		XMFLOAT3 newPosition = position;
					//		object->SetPosition(newPosition);
					//		ImGui::TreePop();
					//	}
					//	break;

						//case 15:
						//	if (ImGui::TreeNode("Template1")) {
						//		XMFLOAT3 position = object->GetPosition();
						//		ImGui::InputFloat3("position", &position.x);
						//		XMFLOAT3 newPosition = position;
						//		object->SetPosition(newPosition);
						//		ImGui::TreePop();
						//	}
						//	break;

						//case 16:
						//	if (ImGui::TreeNode("Template2")) {
						//		XMFLOAT3 position = object->GetPosition();
						//		ImGui::InputFloat3("position", &position.x);
						//		XMFLOAT3 newPosition = position;
						//		object->SetPosition(newPosition);
						//		ImGui::TreePop();
						//	}
						//	break;

						//case 17:
						//	if (ImGui::TreeNode("Template3")) {
						//		XMFLOAT3 position = object->GetPosition();
						//		ImGui::InputFloat3("position", &position.x);
						//		XMFLOAT3 newPosition = position;
						//		object->SetPosition(newPosition);
						//		ImGui::TreePop();
						//	}
						//	break;

						//case 18:
						//	if (ImGui::TreeNode("CharacterSelectButton")) {
						//		XMFLOAT3 position = object->GetPosition();
						//		ImGui::InputFloat3("position", &position.x);
						//		XMFLOAT3 newPosition = position;
						//		object->SetPosition(newPosition);
						//		ImGui::TreePop();
						//	}
						//	break;
						//	/*
						//					case 11:
						//						if (ImGui::TreeNode("Weapon")) {
						//							XMFLOAT3 position = object->GetPosition();
						//							ImGui::InputFloat3("position", &position.x);
						//							ImGui::TreePop();
						//						}
						//						break;

						//					case 12:
						//						if (ImGui::TreeNode("HeaderPower")) {
						//							XMFLOAT3 position = object->GetPosition();
						//							ImGui::InputFloat3("position", &position.x);
						//							ImGui::TreePop();
						//						}
						//						break;

						//					case 13:
						//						if (ImGui::TreeNode("HeaderSound")) {
						//							XMFLOAT3 position = object->GetPosition();
						//							ImGui::InputFloat3("position", &position.x);
						//							ImGui::TreePop();
						//						}
						//						break;

						//					case 14:
						//						if (ImGui::TreeNode("HeaderTown")) {
						//							XMFLOAT3 position = object->GetPosition();
						//							ImGui::InputFloat3("position", &position.x);
						//							ImGui::TreePop();
						//						}
						//						break;
						//						*/
				}
			}
		}
	}

#pragma endregion
};