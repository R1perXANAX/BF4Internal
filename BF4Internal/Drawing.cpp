#include "Drawing.h"

Graphics::Graphics() {
	Window = nullptr;
	OriginalWndProcHandler = nullptr;
}

void Graphics::DrawRect(int x, int y, int w, int h, RGBA* color, int thickness) {
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}
void Graphics::DrawCircle(int x, int y, int radius, RGBA* color, int segments) {
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}
void Graphics::DrawFilledRect(int x, int y, int w, int h, RGBA* color) {
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}
void Graphics::DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color) {
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x, y, borderPx, h / 3, color);
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
}
void Graphics::DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness) {
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}
void Graphics::DrawLine(Vector2 from, Vector2 to, RGBA* color, int thickness) {
	DrawLine(from.x, from.y, to.x, to.y, color, thickness);
}

//credit to CedPlay from unknowncheats
void Graphics::DrawHealthCircle(Vector2 position, int health, int max_health, float radius) {
	float PI = 3.14159265359f;
	std::stringstream healthStr ;
	healthStr << health;
	float aMax = (PI * 2.f);
	ImVec4 color;
	if (health > 65)
		color = { 0,1,0,1 };
	else if (health > 25)
		color = { 1,1,0,1 };
	else
		color = { 1,0,0,1 };
	ImGui::GetForegroundDrawList()->PathArcTo({ position.x, position.y }, radius, (-(aMax / 4.0f)) + (aMax / max_health) * (max_health - health), aMax - (aMax / 4.0f), 200 - 1);
	ImGui::GetForegroundDrawList()->PathStroke(ImGui::ColorConvertFloat4ToU32(color), ImDrawFlags_None, 2.0f);
	DrawString(healthStr.str().c_str(), (position.x - ImGui::CalcTextSize(healthStr.str().c_str()).x / 2.0f), (position.y + ImGui::CalcTextSize(healthStr.str().c_str()).y / 2.0f) ,WHITE);
}

void Graphics::DrawString(std::string string, int x, int y, RGBA* color) {
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(),
		ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), string.c_str());
}

using namespace _Utils;

void Graphics::DrawAABB(SpatialBoundsInfo& info, Matrix4x4& viewProjectionMatrix, SIZE windowSize, RGBA* color) {
	Vector3 min_, max_, origin;
	float width, lenght, height;
	
	memcpy(&min_, &info.aabb.min, 3 * sizeof(float));
	memcpy(&max_, &info.aabb.max, 3 * sizeof(float));
	width = abs(max_.x - min_.x);
	height = abs(max_.y - max_.y);
	lenght = abs(max_.z - min_.z);
	origin.x = info.transform[3][0];
	origin.y = info.transform[3][1];
	origin.z = info.transform[3][2];
	Vector3 min{ min_.x + origin.x,min_.y + origin.y, min_.z + origin.z };
	Vector3 max{ max_.x + origin.x, max_.y + origin.y, max_.z + origin.z };
	Vector3 corner[8];
	Vector2 screenCorner[8];
	corner[0] = min;
	corner[1] = Vector3(min.x + width, min.y, min.z);
	corner[2] = Vector3(min.x + width, min.y, min.z + lenght);
	corner[3] = Vector3(min.x, min.y, min.z + lenght);
	corner[4] = Vector3(max.x - width, max.y, max.z - lenght);
	corner[5] = Vector3(max.x, max.y, max.z - lenght);
	corner[6] = max;
	corner[7] = Vector3(max.x - width, max.y, max.z);
	
	
	if (WorldToScreen(corner[0], screenCorner[0], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[1], screenCorner[1], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[2], screenCorner[2], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[3], screenCorner[3], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[4], screenCorner[4], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[5], screenCorner[5], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[6], screenCorner[6], viewProjectionMatrix, windowSize) &&
		WorldToScreen(corner[7], screenCorner[7], viewProjectionMatrix, windowSize))
	{
		for (int i = 0; i < 8; i++) {
			std::stringstream d;
			d << i;
			DrawString(d.str(), screenCorner[i].x, screenCorner[i].y, GREEN);
		}
		DrawLine(screenCorner[0], screenCorner[1], color,2.f);
		DrawLine(screenCorner[1], screenCorner[2], color, 2.f);
		DrawLine(screenCorner[2], screenCorner[3], color, 2.f);
		DrawLine(screenCorner[3], screenCorner[0], color, 2.f);

		DrawLine(screenCorner[7], screenCorner[4], color, 2.f);
		DrawLine(screenCorner[7], screenCorner[6], color, 2.f);
		DrawLine(screenCorner[6], screenCorner[5], color, 2.f);
		DrawLine(screenCorner[5], screenCorner[4], color, 2.f);

		DrawLine(screenCorner[4], screenCorner[0], color, 2.f);
		DrawLine(screenCorner[5], screenCorner[1], color, 2.f);
		DrawLine(screenCorner[6], screenCorner[2], color, 2.f);
		DrawLine(screenCorner[7], screenCorner[3], color, 2.f);
	}
}
Graphics::~Graphics() {
	delete PURPLE, GOLD, RED, GREEN, WHITE;
}


void Menu::ApplyStyle()
{

	auto& style = ImGui::GetStyle();

	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameBorderSize = 1;
	style.ChildBorderSize = 1;
	style.WindowBorderSize = 1;
	style.WindowRounding = 0;
	style.FrameRounding = 0;
	style.ChildRounding = 0;
	style.Colors[ImGuiCol_Text] = ImColor(192, 2, 175);
	style.Colors[ImGuiCol_TitleBg] = ImColor(70, 70, 70);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(10, 255, 161);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(10, 255, 161);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(70, 70, 70);
	style.Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25, 240);
	style.Colors[ImGuiCol_CheckMark] = ImColor(70, 70, 70);
	style.Colors[ImGuiCol_Border] = ImColor(70, 70, 70);
	style.Colors[ImGuiCol_Button] = ImColor(32, 32, 32);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_ChildBg] = ImColor(45, 45, 45);
	style.Colors[ImGuiCol_FrameBg] = ImColor(32, 32, 32);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
	style.Colors[ImGuiCol_Header] = ImColor(25, 25, 25, 240);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(25, 25, 25, 240);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(90, 90, 90);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(150, 150, 150);
}

Menu::Menu() {
	Menu::current_tab = 0;
}

LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_KEYUP)
	{
		if (wParam == VK_INSERT)
		{
			ShowMenu = !ShowMenu;
		}

	}

	if (ShowMenu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

void Menu::Render() {
	if (ShowMenu)
	{
		ApplyStyle();
		ImGui::SetNextWindowSize(ImVec2{ 500,400 });
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("BATTLEFIELD INTERNAL", 0, window_flags);
		{
			if (ImGui::BeginChild(
				1,
				{ ImGui::GetContentRegionAvail().x * 0.35f, ImGui::GetContentRegionAvail().y },
				true)) {
				constexpr auto button_height = 48;
				if (ImGui::Button("Aimbot", { ImGui::GetContentRegionAvail().x, button_height })) { current_tab = 0; }
				if (ImGui::Button("Visuals", { ImGui::GetContentRegionAvail().x, button_height })) { current_tab = 1; }
				if (ImGui::Button("Misc", { ImGui::GetContentRegionAvail().x, button_height })) { current_tab = 2; }
				if (ImGui::Button("Player", { ImGui::GetContentRegionAvail().x, button_height })) { current_tab = 3; }
				if (ImGui::Button("Info", { ImGui::GetContentRegionAvail().x, button_height })) { current_tab = 4; }
				
				ImGui::EndChild();

				ImGui::SameLine();

				if (ImGui::BeginChild(
					2,
					ImGui::GetContentRegionAvail(),
					true)) {

					switch (current_tab) {

					case 0:

						break;
					case 1:

						break;
					case 2:

						break;
					case 3:
						break;

					case 4:
						ImGui::Text("Build Version: 1.0\n\n");
						ImGui::Text("Credits:\n\n-> ImNotEvenSparta.\n\-> R1perXNX\n\n\n\n");
						ImGui::Text("Usage:\n[+] INS -> Open/Hide Menu\n[+] END -> Uninject\n[+] VK_F8 -> Open debugger console");
						break;
					}
				}
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}

	
}

Menu::~Menu() {
	ShowMenu = FALSE;
}


RenderHelper::RenderHelper(MenuSettings* menuSettings) {
	this->menuSettings = menuSettings;
}

void RenderHelper::UpdateValues(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags) {
	pSwapChain = pThis;
	SyncInterval = SyncInterval;
	Flags = Flags;
	UpdateCalled = TRUE;
}

HRESULT RenderHelper::GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext) {
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}


void RenderHelper::InitGraphics() {
	
	if (GetDeviceAndCtxFromSwapchain(pSwapChain, &pDevice, &pContext))
		return;
	if (pDevice != nullptr && pContext != nullptr) {
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Window = sd.OutputWindow;
		windowSize.cx = sd.BufferDesc.Width;
		windowSize.cy = sd.BufferDesc.Height;
		OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(Window, GWLP_WNDPROC, (LONG_PTR)hWndProc);
		ImGui_ImplWin32_Init(Window);
		ImGui_ImplDX11_Init(pDevice, pContext);
		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
		pBackBuffer->Release();
		bInitialized = TRUE;
		return;
	}
	bInitialized = FALSE;
}

void RenderHelper::Render() {
	if (!UpdateCalled)
		return;
	UpdateCalled = FALSE;
	if (!bInitialized) {
		InitGraphics();
	}
	if (!(statusFlags & RENDER_PAUSED) || !(statusFlags & RENDER_STOPPED)) {
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
		ImGui::NewFrame();
		Menu::Render();
		ESP::Render();
		ImGui::EndFrame();
		ImGui::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}

void RenderHelper::Pause() {
	if (statusFlags & RENDERING)
		statusFlags |= RENDER_PAUSED;
}

void RenderHelper::Continue() {
	if (statusFlags & RENDER_PAUSED)
		statusFlags |= RENDERING;
}

void RenderHelper::CleanUp() {
	statusFlags |= RENDER_STOPPED;
	(WNDPROC)SetWindowLongPtr(Window, GWLP_WNDPROC, (LONG_PTR)OriginalWndProcHandler);
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	pSwapChain->Release();
	pDevice->Release();
	pContext->Release();
	mainRenderTargetView->Release();
}

RenderHelper::~RenderHelper() {
	CleanUp();
}