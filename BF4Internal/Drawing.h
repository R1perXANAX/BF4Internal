#pragma once
#include "graphics.h"
#include "Settings.h"
#include "FBClasses.h"
#include "Utils.h"
#include <vector>

/* The only call that have to be instanciated is RenderHelper. It calls Render method of Menu and Esp. Modify the logic of render in the menu and esp classes
* but dont intanciate them, insthed use RenderHelper::Render() after call RenderHelper::Update() in a drawing method(hkPresent)
*/
struct RGBA
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
};


extern HWND Window;
extern WNDPROC OriginalWndProcHandler;
extern bool ShowMenu;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//graphics interface
class Graphics{

protected:

	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* mainRenderTargetView = nullptr;
	UINT SyncInterval;
	UINT Flags;
	SIZE windowSize;
	MenuSettings* menuSettings;
protected:

	//COLORS
	RGBA* PURPLE = new RGBA{ 105,27,222,255 };
	RGBA* GOLD = new RGBA{ 237,191,8,255 };
	RGBA* RED = new RGBA{ 209,7,60,255 };
	RGBA* GREEN = new RGBA{ 7,209,22,255 };
	RGBA* WHITE = new RGBA{ 255,255,255,255 };
	//--------
protected:

	Graphics();
	virtual void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness);
	virtual void DrawCircle(int x, int y, int radius, RGBA* color, int segments);
	virtual void DrawFilledRect(int x, int y, int w, int h, RGBA* color);
	virtual void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color);
	virtual void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness);
	virtual void DrawLine(Vector2 from, Vector2 to, RGBA* color, int thickness);
	virtual void DrawHealthCircle(Vector2 position, int health, int max_health, float radius);
	virtual void DrawString(std::string string, int x, int y, RGBA* color);
	virtual void DrawAABB(SpatialBoundsInfo& info, Matrix4x4& viewProjectionMatrix, SIZE windowSize, RGBA* color);
	virtual void Render() = 0;
	virtual void CleanUp() = 0;
	~Graphics();
};


class Menu : protected Graphics{

private:
	DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | 
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
	void ApplyStyle();
	int current_tab;

public:
	Menu();
	virtual void Render()override;
	inline MenuSettings* getMenuSettings() { return menuSettings; };
	~Menu();
};



class ESP : protected Menu{

private:
	uintptr_t* VisualUpdateInstruction;
	uint8_t OriginalInstruction[7];
	Matrix4x4 viewMatrix;
	uintptr_t gameHandle = (uintptr_t)GetModuleHandle("bf4.exe");
private:
	GameContext* gameContext = (GameContext*)((uintptr_t)GetModuleHandle("bf4.exe") + GAMECONTEXT_O);
	
public:
	ESP();
	virtual void Render() override;
	virtual void CleanUp()override;
	~ESP();
};



#define RENDERING 200
#define	RENDER_PAUSED 300
#define RENDER_STOPPED 400
class RenderHelper: ESP{
private:
	bool bInitialized = FALSE;
	bool UpdateCalled = FALSE;
private:
	HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext);
	void InitGraphics();
	void CleanUp() override;
public:
	int statusFlags;
public:
	RenderHelper(MenuSettings* menuSettings);
	//call inside hkPresent
	void UpdateValues(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
	//call after UpdateValues
	void Render() override;
	//pause render
	void Pause();
	//continue render if it is paused
	void Continue();


	inline MenuSettings* getMenuSettings() { return menuSettings; };
	~RenderHelper();
};

