#pragma once
#include "GameMath.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <random>
class AimBot
{
private:
	float maxFov = 5.f;
	bool active = TRUE;
	ClientPlayer* aimTarget = nullptr;
	std::default_random_engine generator;
private:
	MenuSettings* menuSettings;
	ClientPlayer* GetBestPlayer();
	void AimAt(ClientPlayer* target);

public:
	AimBot(MenuSettings* settings);
	void Run();
};

