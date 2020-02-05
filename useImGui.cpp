#include "Windows.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "useImGui.h"

void CuseImGui::Create(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
#pragma region ImGui‚Ì‰Šú‰»ˆ—

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, context);

	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	// Window‚ÌF‚Æ‚©•ÏX‚Å‚«‚é
	colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);

#pragma endregion
}

void CuseImGui::Destroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void CuseImGui::SetFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void CuseImGui::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}