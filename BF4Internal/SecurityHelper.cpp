#include "SecurityHelper.h"

SecurityHelper::SecurityHelper() {
	peb = (PEB*)__readgsqword(0x60);
	isRunning = TRUE;
}


void SecurityHelper::DisableDebugger() {
	debugThreadActive = TRUE;
	while (isRunning) {
		if (peb == nullptr) {
			peb = (PEB*)__readgsqword(0x60);
		}
		else {
			peb->BeingDebugged = 0;
		}
		Sleep(1);
	}
	debugThreadActive = FALSE;
}

bool SecurityHelper::BypassDetection() {
	std::thread debugT(&SecurityHelper::DisableDebugger, this);
	debugT.detach();
	Sleep(100);
	return debugThreadActive;
}



SecurityHelper::~SecurityHelper() {
	isRunning = FALSE;
	Sleep(100);
}



