#pragma once
#include "Undocumented.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include <windows.h>
#include <ShlObj.h>
#include <ctime>
#include <sstream>
#include "Hooking_x64.h"
/*	This class covers all things needed to protect the cheat from detection
* 
* DebugBypass: Credit to ImNotEvenSparta
*/

class SecurityHelper
{
private:
	PEB* peb;
	bool isRunning = FALSE; //refers to securityHelper
	bool debugThreadActive = FALSE;

private:
	void DisableDebugger();
public:
	SecurityHelper();
	bool BypassDetection();
	~SecurityHelper();
};

