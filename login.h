#pragma once

class CLogin : public CScene {
private:

public:
	static std::string m_UserID;
	static std::string m_LoginID;
	static std::string m_Pass;
	static int         m_RegisterNumber; // 登録者数

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void DebugRender();

#pragma region ImGuIでのデバック

	void DebugImGui() {
		for (int i = 0; i < LISTMAX; i++) {
			for (auto object : m_GameObject[i])
			{
				// @todo ラムダ式に
				// 各種GameObjectの座標表示
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
					if (ImGui::TreeNode("FormationFrame")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 7:
					if (ImGui::TreeNode("Guran")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 8:
					if (ImGui::TreeNode("CharButton")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 9:
					if (ImGui::TreeNode("WeaponButton")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 10:
					if (ImGui::TreeNode("SummonButton")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 14:
					if (ImGui::TreeNode("MainMenberPoly")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 15:
					if (ImGui::TreeNode("Template1")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 16:
					if (ImGui::TreeNode("Template2")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 17:
					if (ImGui::TreeNode("Template3")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;

				case 18:
					if (ImGui::TreeNode("CharacterSelectButton")) {
						XMFLOAT3 position = object->GetPosition();
						ImGui::InputFloat3("position", &position.x);
						XMFLOAT3 newPosition = position;
						object->SetPosition(newPosition);
						ImGui::TreePop();
					}
					break;
				}
			}
		}
	}

#pragma endregion
};