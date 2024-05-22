#include <Windows.h>
#include "graphics.h"
#include <iostream>
#include "Hooking_x64.h"
#include "Drawing.h"
#include "DebugConsole.h"
#include "SecurityHelper.h"
#include "AimBot.h"
#include "Utils.h"
#include "Misc.h"



uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);


//real present function
typedef HRESULT(__fastcall* _Present)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);

typedef __m128(__fastcall* _CalcDamage)(__m128* bulletEntity, float* bulletData, __int64 materialGrid,
    Vector3* hitPosition, float* penetrationMult, float bonusDamageMultiplier);

_Present Present = nullptr;
uintptr_t presentSrcHk = NULL;


_CalcDamage CalcDamage = nullptr;
uintptr_t calcDamageHk = NULL;

//globals
bool ShowMenu = TRUE;
HWND Window;
WNDPROC OriginalWndProcHandler;
MenuSettings* menuSettings = new MenuSettings();
RenderHelper* render = new RenderHelper(menuSettings);
DebugConsole* console = new DebugConsole();
SecurityHelper* security = new SecurityHelper();

HRESULT __fastcall hkPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags) {
    render->UpdateValues(pThis, SyncInterval, Flags);
    render->Render();
    return Present(pThis, SyncInterval, Flags);
}


__m128 __fastcall hkcalcDamage(__m128* bulletEntity, float* bulletData, __int64 materialGrid,
    Vector3* hitPosition, float* penetrationMult, float bonusDamageMultiplier) {

    if (_Utils::IsValidPointer((uintptr_t*)bulletEntity)) {
        if (_Utils::IsValidPointer((uintptr_t*)((uintptr_t)bulletEntity + 0x8))) {
            Vector3* origin = (Vector3*)((uintptr_t)bulletEntity + 0x8);
        }   
    }
    if (_Utils::IsValidPointer((uintptr_t*)penetrationMult)){
        *penetrationMult = 10.f;
    }
    bonusDamageMultiplier = 10.f;
    return CalcDamage(bulletEntity,bulletData,materialGrid,
        hitPosition, penetrationMult, bonusDamageMultiplier);
}


DWORD WINAPI MainThread(HMODULE hModule) {
    
    presentSrcHk = (uintptr_t)((uintptr_t)GetModuleHandle("igo64.dll") + 0x36A30);
    calcDamageHk = (uintptr_t)(moduleBase + 0x993410);
    Hooking_x64* presentHook = new Hooking_x64((LPVOID)presentSrcHk, hkPresent, 0x13);
    Hooking_x64* calcDamageHook = new Hooking_x64((LPVOID)calcDamageHk, hkcalcDamage, 0x15);
    presentHook->Hook();
    calcDamageHook->Hook();
    Present = (_Present)presentHook->getGateway();
    CalcDamage = (_CalcDamage)calcDamageHook->getGateway();
    console->LOG("\n[+] : Injected");
    if (security->BypassDetection()) {
        console->LOG("\n[+] : DetectionBypass Active");
    }
    //Cheat Loop
    Sleep(1);
    AimBot* aimbot = new AimBot(menuSettings);
    Misc* misc = new Misc(menuSettings);
    while (!GetAsyncKeyState(VK_END)) {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
            console->Toggle();
        aimbot->Run();
        misc->SniperInfiniteBreath();
        
    }
    if (!console->getState())
        console->Toggle();
    console->LOG("\n[+] : Uninjected");
    Sleep(1000);
    delete presentHook;
    delete calcDamageHook;
    delete render;
    delete console;
    delete security;
    delete aimbot;
    delete menuSettings;
    Sleep(100);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        if (hThread) {
            CloseHandle(hThread);
        }
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

