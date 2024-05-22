#include "Hooking_x64.h"

Hooking_x64::Hooking_x64(LPVOID src, LPVOID dst, size_t len) {
	this->src = src;
	this->dst = dst;
	this->len = len;
}


void Hooking_x64::Hook() {

	//initialize the gateway
	if (gateway == nullptr) {
		gateway = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (gateway == NULL)//virtual alloc failed
		{
			status = FAILED;
			return;
		}
		memcpy(gateway, src, len);

		uint8_t JumpBackBytes[] = {
		0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov r10
		0x41, 0xFF, 0xE2, // jmp r10
		};

		jumpBackAddr = (uintptr_t)src + len;

		//create jumpback opcodes for gateway and store it
		memcpy(&JumpBackBytes[2], &jumpBackAddr, 0x8);
		memcpy((LPVOID)((uintptr_t)gateway + len), &JumpBackBytes, sizeof(JumpBackBytes));
	}

	//create jump to our function and place detour
	uint8_t JumpToOurFunc[] = {
	0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov r10
	0x41, 0xFF, 0xE2, // jmp r10
	};

	memcpy(&JumpToOurFunc[2], &dst, 0x8);

	//write the jump to original function
	DWORD oldProtect;
	VirtualProtect((LPVOID)src, 0x13, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(src, 0x90, 0x13);
	memcpy(src, (void*)JumpToOurFunc, sizeof(JumpToOurFunc));
	VirtualProtect((LPVOID)src, 0x13, oldProtect, &oldProtect);
	status = ACTIVE;
}


void Hooking_x64::UnHook() {
	if (status = ACTIVE && gateway != nullptr) {
		DWORD oldProtect;
		VirtualProtect((LPVOID)src, 0x13, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)src, (void*)gateway, 0x13);
		VirtualProtect((LPVOID)src, 0x13, oldProtect, &oldProtect);
		status = INACTIVE;
	}
}

Hooking_x64::~Hooking_x64() {
	if (status = ACTIVE)
		UnHook();
	if (gateway != nullptr)
		VirtualFree(gateway, 0, MEM_RELEASE);
}