#include "Utils.h"
extern uintptr_t moduleBase;
//ImNotEvenSparta Credit
bool _Utils::WorldToScreen(Vector3 position, Vector2& screen, Matrix4x4 matrix, SIZE windowSize) {


    float mX = windowSize.cx / 2;
    float mY = windowSize.cy / 2;

    float w =
        matrix[0][3] * position.x +
        matrix[1][3] * position.y +
        matrix[2][3] * position.z +
        matrix[3][3];

    if (w < 0.65f)
        return false;

    float x =
        matrix[0][0] * position.x +
        matrix[1][0] * position.y +
        matrix[2][0] * position.z +
        matrix[3][0];

    float y =
        matrix[0][1] * position.x +
        matrix[1][1] * position.y +
        matrix[2][1] * position.z +
        matrix[3][1];

    screen.x = (mX + mX * x / w);
    screen.y = (mY - mY * y / w);

    return true;
}

//ImNotEvenSparta Credit
Angles _Utils::CalcAngle(Vector3 from, Vector3 to) {
    Angles out(0, 0, 0);
    Vector3 originPosition = to - from;
    float terminal = originPosition.Magnitude(); // Solving for the terminal

    float Pitch = atan2f(originPosition.y, terminal);
    float Yaw = -atan2f(originPosition.x, originPosition.z);
    float YawMath = ((Yaw / 3.14f) * 180.0f) + (Yaw > 0 ? 0 : 360.0f); // 0 , 360 
    // That statement takes care of atan returning - 180, 180
    out.pitch = Pitch;
    out.yaw = ToRadians(YawMath);
    out.roll = 0;

    return out;
}

//ImNotEvenSparta Credit
void _Utils::SetPitch(float pitch) {
    uintptr_t PointerToPitchAngle = (*(uintptr_t*)(*(uintptr_t*)(moduleBase + 0x23B2EC0) + 0x4988) + 0x10);
    float* PitchAngle = (float*)(*(uintptr_t*)PointerToPitchAngle + 0x18);
    *PitchAngle = pitch;
}

//ImNotEvenSparta Credit
void _Utils::SetYaw(float yaw) {
    uintptr_t PointerToPitchAngle = (*(uintptr_t*)(*(uintptr_t*)(moduleBase + 0x23B2EC0) + 0x4988) + 0x10);
    float* YawAngle = (float*)(*(uintptr_t*)PointerToPitchAngle + 0x14);
    *YawAngle = yaw;
}


//ImNotEvenSparta Credit
uintptr_t _Utils::GetSessionVirtualTable()
{
    ClientPlayer* localPlayer = *(ClientPlayer**)(moduleBase + 0x23B2EA0);
    if (localPlayer != nullptr && IsValidPointer((uintptr_t*)localPlayer)) {
        uintptr_t VirtualTable = *(uintptr_t*)localPlayer;
        return VirtualTable;
    }
    return 0;
}

GameRender* _Utils::GetGameRender() {
    GameRender* gameRender = *(GameRender**)(moduleBase + GAMERENDER_O);
    if (IsValidPtr(gameRender))
        return gameRender;
    return nullptr;
}

//ImNotEvenSparta Credit
Vector3 _Utils::GetBonePosition(ClientPlayer* ent, int BoneID) {

    uintptr_t CurrentEntityPointer = (uintptr_t)ent;

    if ((uintptr_t*)CurrentEntityPointer != nullptr && IsValidPointer((uintptr_t*)CurrentEntityPointer)) {
        uintptr_t CurrentEntity = CurrentEntityPointer;
        if ((uintptr_t*)CurrentEntity != nullptr && IsValidPointer((uintptr_t*)CurrentEntity)) {
            uintptr_t VirtualTable = *((uintptr_t*)CurrentEntity);
            if (VirtualTable == GetSessionVirtualTable()) {
                uintptr_t CurrentEntityControllable = (CurrentEntity + _Offsets::ClientControllable);
                if ((uintptr_t*)CurrentEntityControllable != nullptr && IsValidPointer((uintptr_t*)CurrentEntityControllable)) {
                    uintptr_t* CurrentEntityHealthComponent = (uintptr_t*)(*(uintptr_t*)CurrentEntityControllable + _Offsets::HealthComponent);
                    if (CurrentEntityHealthComponent != nullptr && IsValidPointer(CurrentEntityHealthComponent)) {
                        float* CurrentEntityHealth = (float*)(*CurrentEntityHealthComponent + _Offsets::m_Health);
                        if (CurrentEntityHealth != nullptr && IsValidPointer((uintptr_t*)CurrentEntityHealth) && *CurrentEntityHealth > 0) {
                            uintptr_t* CurrentEntityRagdollComponent = (uintptr_t*)(*(uintptr_t*)CurrentEntityControllable + _Offsets::ClientRagdollComponent);
                            if (CurrentEntityRagdollComponent != nullptr && IsValidPointer(CurrentEntityRagdollComponent)) {
                                uintptr_t* BonesPointerChain = (uintptr_t*)((uintptr_t)(*CurrentEntityRagdollComponent) + 0xB0);
                                if (BonesPointerChain != nullptr && IsValidPointer(BonesPointerChain)) {
                                    uintptr_t BaseOfPositionAddress = ((uintptr_t)(*BonesPointerChain) + (uintptr_t)0x20 * (uintptr_t)BoneID);
                                    float* BoneX = (float*)((uintptr_t)BaseOfPositionAddress);
                                    float* BoneY = (float*)((uintptr_t)BaseOfPositionAddress + 0x4);
                                    float* BoneZ = (float*)((uintptr_t)BaseOfPositionAddress + 0x8);
                                    if (BoneX != nullptr && BoneY != nullptr && BoneZ != nullptr && IsValidPointer((uintptr_t*)BoneX) && IsValidPointer((uintptr_t*)BoneY) && IsValidPointer((uintptr_t*)BoneZ)) {
                                        Vector3 BonePosition{};
                                        BonePosition.x = *BoneX;
                                        BonePosition.y = *BoneY;
                                        BonePosition.z = *BoneZ;
                                        return BonePosition;
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }


    Vector3 BadPos{};
    return BadPos;
}

Vector3 _Utils::GetVehicleBonePosition(ClientVehicleEntity* ent, int ID) {
    Vector3 out(0, 0, 0);
    if (IsValidPtr(ent)) {
        DynamicPhysicsEntity* dynamicPhysics =ent->dynamicPhysicsEntity;
        if (IsValidPtr(dynamicPhysics)) {
            VehicleBones* bones = dynamicPhysics->bones;
            if (IsValidPtr(bones)) {
                Matrix4x4 transform;
                memcpy(transform, bones->boneArray[ID], sizeof(Matrix4x4));
                out.x = transform[3][0];
                out.y = transform[3][1];
                out.z = transform[3][2];
            }
        }
    }
    return out;
}

NetworkableEntity* _Utils::GetEntityList()
{
    GameContext* gamecontext = *(GameContext**)(moduleBase + _Offsets::GameContext);
    if (!gamecontext)
        return nullptr;
    PlayerManger* playerManager = gamecontext->playerManager;
    if (!IsValidPtr(playerManager) || !playerManager)
        return nullptr;
    NetworkableEntity* networkables = playerManager->networkable;
    if (!IsValidPtr(networkables))
        return nullptr;
    return networkables;
}

ClientPlayer* _Utils::GetLocalPlayer()
{
    GameContext* gamecontext = *(GameContext**)(moduleBase + _Offsets::GameContext);
    if (!gamecontext)
        return nullptr;
    PlayerManger* playerManager = gamecontext->playerManager;
    if (!IsValidPtr(playerManager) || !playerManager)
        return nullptr;
    ClientPlayer* localPlayer = playerManager->localPlayer;
    if (!IsValidPtr(localPlayer) || !localPlayer)
        return nullptr;
    return localPlayer;
}

float _Utils::GetPitchAngle()
{
    uintptr_t PointerToPitchAngle = (*(uintptr_t*)(*(uintptr_t*)(moduleBase + _Offsets::ViewAngles) + 0x4988) + 0x10);
    float* PitchAngle = (float*)(*(uintptr_t*)PointerToPitchAngle + _Offsets::m_ViewAnglesPitch);
    return *PitchAngle;
}
float _Utils::GetYawAngle()
{
    uintptr_t PointerToYawAngle = (*(uintptr_t*)(*(uintptr_t*)(moduleBase + _Offsets::ViewAngles) + 0x4988) + 0x10);
    float* YawAngle = (float*)(*(uintptr_t*)PointerToYawAngle + _Offsets::m_ViewAnglesYaw);
    return *YawAngle;
}

bool _Utils::IsValidPointer(uintptr_t* ptr)
{
    __try
    {
        volatile auto result = *ptr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
    return true;
}

//kix func
float _Utils::GetPixelFov(float fovConfig)
{
    float realFov;
    realFov = ((tanf((fovConfig / 2) * 3.14159265f / 180)) / tanf((70 / 2) * 3.14159265f / 180) * 800 / 2) + 20;
    return realFov;
}

bool _Utils::isInFov(Vector3 forwardVector, Vector3 pos, Vector3 enemyPos, float maxFov) {
    Vector3 angleNorm, distNorm;
    Normalize(forwardVector, angleNorm);
    Normalize((enemyPos - pos), distNorm);
    float angle = ToDegrees(acosf(DotProduct(angleNorm, distNorm)));
    if (angle > (maxFov / 2))
        return false;
    return true;
}
