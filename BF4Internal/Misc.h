#pragma once
#include <Windows.h>
#include <iostream>
#include "Settings.h"

class Misc
{

private:
	uint8_t breathBackUpBytes[5];
	bool noBreathActive = false;
	MenuSettings* menuSettings;
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
public:
	Misc(MenuSettings* menuSettings);
	void SniperInfiniteBreath();
	/*cambiare 0x101044f in jmp    /x76/x04
	* nop 0x101041e
	*/
};

