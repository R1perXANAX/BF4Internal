#include "AimBot.h"
#include "Utils.h"
using namespace _Utils;
void AimBot::Run() {
    
    if (GetAsyncKeyState(VK_F3) & 1) {
        aimTarget = GetBestPlayer();
        if (GetAsyncKeyState(VK_F3)) {
            if (IsValidPtr(aimTarget))
                AimAt(aimTarget);
        }
    }
    aimTarget = nullptr;
    
}

ClientPlayer* AimBot::GetBestPlayer() {
    float minDistance = 9999.f;
    ClientPlayer* out = nullptr;
    NetworkableEntity* networkables = GetEntityList();
    ClientPlayer* localPlayer = GetLocalPlayer();
    if (!networkables || !localPlayer)
        return nullptr;
    for (int i = 0; i < 60; i++) {
       ClientPlayer* currentEnt= networkables->EntityArray[i];
        if (IsValidPtr(currentEnt) && IsValidPtr(localPlayer)) {
            uintptr_t VMT = *(uintptr_t*)currentEnt;
            if (VMT == GetSessionVirtualTable()) {
                ClientSoldierEntity* currControllable = currentEnt->attachedControllable;
                ClientSoldierEntity* LPlayerControllable = localPlayer->attachedControllable;
                if ((IsValidPtr(currControllable) || IsValidPtr(LPlayerControllable)) && localPlayer) {
                    HealthComponent* healthCmp = currControllable->healthComponent;
                    if (IsValidPtr(healthCmp) && healthCmp->health > 0) {
                        if (localPlayer->teamID != currentEnt->teamID) {
                            if (!currControllable->isOccluded) {
                                GameRender* gameRender = GetGameRender();
                                if (gameRender) {
                                    RenderView* renderView = gameRender->renderView;
                                    if (IsValidPtr(renderView)) {
                                        Matrix4x4 viewMatrixInverse;
                                        memcpy(viewMatrixInverse, renderView->m_viewMatrixInverse, sizeof(Matrix4x4));
                                        Vector3 cameraForward(-viewMatrixInverse[2][0], -viewMatrixInverse[2][1], -viewMatrixInverse[2][2]);
                                        Vector3 cameraPosition(viewMatrixInverse[3][0], viewMatrixInverse[3][1], viewMatrixInverse[3][2]);
                                        Vector3 bonePosition = GetBonePosition(currentEnt, 55);
                                        if (isInFov(cameraForward, cameraPosition, bonePosition, 10.f)) {
                                            float dst = Get3DDistance(cameraPosition, bonePosition);
                                            if (dst * 1.5f < minDistance) {
                                                minDistance = dst;
                                                out = currentEnt;
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }
    return out;
}


void AimBot::AimAt(ClientPlayer* ent) {
    ClientPlayer* localPlayer = GetLocalPlayer();
    if (IsValidPointer((uintptr_t*)localPlayer) && (uintptr_t*)localPlayer != nullptr) {
        uintptr_t LPControllable = ((uintptr_t)localPlayer + _Offsets::ClientControllable);
        if ((uintptr_t*)LPControllable != nullptr && IsValidPointer((uintptr_t*)LPControllable)) {
            uintptr_t* LocalPlayerClientWeaponsComponent = (uintptr_t*)(*(uintptr_t*)LPControllable + _Offsets::ClientWeaponsComponent);
            if (LocalPlayerClientWeaponsComponent != nullptr && IsValidPointer(LocalPlayerClientWeaponsComponent)) {
                float* LocalPlayerPosX = (float*)(*LocalPlayerClientWeaponsComponent + _Offsets::m_WeaponOriginPos);
                float* LocalPlayerPosY = (float*)(*LocalPlayerClientWeaponsComponent + _Offsets::m_WeaponOriginPos + 0x4);
                float* LocalPlayerPosZ = (float*)(*LocalPlayerClientWeaponsComponent + _Offsets::m_WeaponOriginPos + 0x8);
                if (LocalPlayerPosX != nullptr && IsValidPointer((uintptr_t*)LocalPlayerPosX) && LocalPlayerPosY != nullptr
                    && IsValidPointer((uintptr_t*)LocalPlayerPosY) && LocalPlayerPosZ != nullptr && IsValidPointer((uintptr_t*)LocalPlayerPosZ)) {
                    Vector3 LocalPlayerPosition{
                                            *LocalPlayerPosX,
                                            *LocalPlayerPosY,
                                            *LocalPlayerPosZ
                    };
                    Vector3 TPos = GetBonePosition(ent, 55);
                    if (TPos.x != 0) {
                        
                        Angles newViewAngles = CalcAngle(LocalPlayerPosition, TPos);
                        Vector2 startAng(GetPitchAngle(), GetYawAngle());
                        Vector2 endAng(newViewAngles.pitch, newViewAngles.yaw);
                        startAng.x = ToDegrees(startAng.x);
                        startAng.y = ToDegrees(startAng.y);
                        endAng.x = ToDegrees(endAng.x);
                        endAng.y = ToDegrees(endAng.y);
                        if (startAng.y < 180.f && endAng.y > 180.f) {
                            startAng.y += 360.f;
                        }
                        Vector2 setAngles;
                        std::uniform_int_distribution<int> distribution(1, 3);
                        std::uniform_int_distribution<int> distribution1(1, 2);
                        int offset = distribution1(generator);
                        for (int i = 0; i <= 80; i++) {
                            float t = 0.0125 * i;
                            setAngles = _Math::QuadraticBezier(startAng, endAng, { startAng.x + (endAng.x - startAng.x) / offset , endAng.y }, t);
                            SetPitch(ToRadians(setAngles.x));
                            SetYaw(ToRadians(setAngles.y));
                            std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
                        }
                    }

                }
            }
        }

    }
}

AimBot::AimBot(MenuSettings* settings) {
	menuSettings = settings;
}