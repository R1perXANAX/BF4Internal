#pragma once
#include <Windows.h>
#include "GameMath.h"
#include "FBClasses.h"
#include <iostream>
#include <chrono>
#include <thread>


using namespace _Math;
#define FOV_O          0x26611E0
#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)

constexpr bool IsValidPtr(PVOID p)
{
	return (p >= (PVOID)0x10000) && (p < _PTR_MAX_VALUE) && p != nullptr;
}

namespace _Utils {
	bool IsValidPointer(uintptr_t* ptr);
	bool WorldToScreen(Vector3 position, Vector2& screen, Matrix4x4 matrix, SIZE windowSize);
	float GetPixelFov(float fovConfig);
	float GetPitchAngle();
	float GetYawAngle();
	void SetPitch(float pitch);
	void SetYaw(float yaw);
	bool isInFov(Vector3 forwardVector, Vector3 pos, Vector3 enemyPos, float maxFov);
	Angles CalcAngle(Vector3 from, Vector3 to);
	Vector3 GetBonePosition(ClientPlayer* ent, int BoneID);
	Vector3 GetVehicleBonePosition(ClientVehicleEntity* ent, int ID);
	uintptr_t GetSessionVirtualTable();
	GameRender* GetGameRender();
	
	ClientPlayer* GetLocalPlayer();
	NetworkableEntity* GetEntityList();
}