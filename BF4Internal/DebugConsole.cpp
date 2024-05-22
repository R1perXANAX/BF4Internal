#include "DebugConsole.h"

DebugConsole::DebugConsole() {
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	LOG("OUTPUT: ");
}

void DebugConsole::Toggle() {
	if (!bActive) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		bActive = true;
	}
	else {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		bActive = false;
	}
}
DebugConsole::~DebugConsole() {
	if (bActive = true) {
		if (f != NULL) {
			fclose(f);
		}
		FreeConsole();
	}
}