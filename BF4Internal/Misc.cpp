#include "Misc.h"


Misc::Misc(MenuSettings* menuSettings) {
	this->menuSettings = menuSettings;
}

void Misc::SniperInfiniteBreath() {
	if (menuSettings->noSniperBreath && !noBreathActive) {
		DWORD oldProtect;
		VirtualProtect((LPVOID)(moduleBase + 0x101044f), 0x2, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((LPVOID)(moduleBase + 0x101044f), "\xEB\x04", 2);
		VirtualProtect((LPVOID)(moduleBase + 0x101044f), 0x2, oldProtect, &oldProtect);
		
		VirtualProtect((LPVOID)(moduleBase + 0x101041e), 0x5, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(breathBackUpBytes, (LPVOID)(moduleBase + 0x101041e), 5);
		memset((LPVOID)(moduleBase + 0x101041e), 0x90, 5);
		VirtualProtect((LPVOID)(moduleBase + 0x101041e), 0x5, oldProtect, &oldProtect);
		noBreathActive = TRUE;
	}
	if (!menuSettings->noSniperBreath && noBreathActive) {
		DWORD oldProtect;
		VirtualProtect((LPVOID)(moduleBase + 0x101044f), 0x2, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((LPVOID)(moduleBase + 0x101044f), "\x76\x04", 2);
		VirtualProtect((LPVOID)(moduleBase + 0x101044f), 0x2, oldProtect, &oldProtect);

		VirtualProtect((LPVOID)(moduleBase + 0x101041e), 0x5, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((LPVOID)(moduleBase + 0x101041e),breathBackUpBytes, 5);
		VirtualProtect((LPVOID)(moduleBase + 0x101041e), 0x5, oldProtect, &oldProtect);
		noBreathActive = FALSE;
	}
}