#pragma once
#include <Windows.h>
#include <cstdint>
#include <iostream>

#define ACTIVE 1
#define INACTIVE -1
#define FAILED 0
class Hooking_x64
{
private:

	LPVOID src;
	LPVOID dst;
	LPVOID gateway = NULL;
	uintptr_t jumpBackAddr;
	size_t len;
	INT8 status = INACTIVE;
public:
	Hooking_x64(LPVOID src, LPVOID dst, size_t len);
	void Hook();
	void UnHook();
	~Hooking_x64();
	inline LPVOID getGateway() { if (gateway != nullptr)return gateway; else return nullptr; }
};

