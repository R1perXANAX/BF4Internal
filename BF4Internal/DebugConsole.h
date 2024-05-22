#pragma once
#include <iostream>
#include <Windows.h>




/* Simple class that handles console msg
*/


class DebugConsole
{
private:
	FILE* f;
	bool bActive = false;
public:
	DebugConsole();
	template<typename T>
	void LOG(T msg, bool endL = true) {
		if (bActive) {
			if (endL)
				std::cout << msg << std::endl;
			else
				std::cout << msg;
		}
	}
	inline bool getState() { return bActive; };
	void Toggle();
	~DebugConsole();
};

