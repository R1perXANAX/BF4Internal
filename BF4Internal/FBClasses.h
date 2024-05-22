#pragma once
#include <iostream>
#include "GameMath.h"
using namespace _Math;
// Created with ReClass.NET 1.2 by KN4CK3R

#define GAMECONTEXT_O  0x2670D80
#define GAMERENDER_O   0x2672378


#define FOV_O          0x26611E0

namespace _Offsets {
	// Internal Linkage so no problems with this being used in multiple files...
	// Pointers
	static uintptr_t GameContext = 0x2670D80;
	static uintptr_t GameRender = 0x2672378;
	static uintptr_t LocalPlayer = 0x23B2EA0;
	static uintptr_t ViewAngles = 0x23B2EC0;
	// Classes
	static int ClientControllable = 0x14D0;
	static int AntAnimatableComponent = 0x1F0;
	static int HealthComponent = 0x140;
	static int ClientSolider = 0x490;
	static int ClientWeaponsComponent = 0x570;
	static int ClientRagdollComponent = 0x580;
	// Members
	static int m_PlayerManager = 0x60;
	static int m_EntityList = 0x548;
	static int m_Team = 0x13CC;
	static int m_Health = 0x20;
	static int m_NotVisible = 0x5B1;
	static int m_OriginPos = 0x30;
	static int m_WeaponOriginPos = 0x100;
	static int m_ViewAnglesPitch = 0x18;
	static int m_ViewAnglesYaw = 0x14;
	static int m_RenderView = 0x60;
	static int m_ViewProjectionMatrix = 0x420;
	static int m_ViewProjectionMatrixTranspose = 0x460;
	static int m_GameAnimatable = 0x68;
	static int m_VisualUpdate = 0xD4;
	// Chains
	static int m_ViewAnglesChain1 = 0x4988;
	static int m_ViewAnglesChain2 = 0x10;
};


struct AxisAlignedBox {
	float min[4];
	float max[4];
};

struct SpatialBoundsInfo
{
	Matrix4x4 transform;  /// Must not be the same as the transform of the entity. Should be used together with aabb
	AxisAlignedBox aabb;
	float visualCullScreenArea; /// Cull screen area used for visual culling, needs to be in 0-1 range.
};

class Fov {
	char pad_0000[90];
	float fov;
};

class GameRender
{
public:
	char pad_0000[96]; //0x0000
	class RenderView* renderView; //0x0060
	char pad_0068[24]; //0x0068
}; //Size: 0x0080


class RenderView
{
public:
	char pad_0000[176]; //0x0000
	float N00000093; //0x00B0
	float N0000010F; //0x00B4
	float N00000094; //0x00B8
	float Near; //0x00BC
	float Far; //0x00C0
	char pad_00C4[412]; //0x00C4
	Matrix4x4 m_viewMatrix; //0x0260
	Matrix4x4 m_viewMatrixTranspose; //0x02A0
	Matrix4x4 m_viewMatrixInverse; //0x02E0
	Matrix4x4 m_projectionMatrix; //0x0320
	Matrix4x4 m_viewMatrixAtOrigin; //0x0360
	Matrix4x4 m_projectionMatrixTranspose; //0x03A0
	Matrix4x4 m_projectionMatrixInverse; //0x03E0
	Matrix4x4 m_viewProjectionMatrix; //0x0420
	Matrix4x4 m_viewProjectionMatrixTranspose; //0x0460
	Matrix4x4 m_viewProjectionMatrixInverse; //0x04A0
}; //Size: 0x06F0

// Created with ReClass.NET 1.2 by KN4CK3R

class GameContext
{
public:
	char pad_0000[96]; //0x0000
	class PlayerManger* playerManager; //0x0060
	class OnlineManager* onlineManager; //0x0068
	char pad_0070[280]; //0x0070
}; //Size: 0x0188
static_assert(sizeof(GameContext) == 0x188);

class PlayerManger
{
public:
	char pad_0000[1344]; //0x0000
	class ClientPlayer* localPlayer; //0x0540
	class NetworkableEntity* networkable; //0x0548
	char pad_0550[264]; //0x0550
}; //Size: 0x0658
static_assert(sizeof(PlayerManger) == 0x658);

class ClientPlayer
{
public:
	char pad_0008[16]; //0x0008
	char* Name; //0x0018
	char pad_0020[5036]; //0x0020
	int32_t teamID; //0x13CC
	char pad_13D0[224]; //0x13D0
	class ClientSoldierEntity* clientSoldierEnt; //0x14B0
	char pad_14B8[24]; //0x14B8
	class ClientSoldierEntity* attachedControllable; //0x14D0
	char pad_14D8[121]; //0x14D8
	bool isInVehicle; //0x1551
	char pad_1552[142]; //0x1552

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual bool IsInVehicle();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x15E0
static_assert(sizeof(ClientPlayer) == 0x15E0);

class NetworkableEntity
{
public:
	class ClientPlayer* EntityArray[64]; //0x0000
}; //Size: 0x0200
static_assert(sizeof(NetworkableEntity) == 0x200);

class ClientSoldierEntity
{
public:
	char pad_0008[48]; //0x0008
	class Components* components; //0x0038
	char pad_0040[256]; //0x0040
	class HealthComponent* healthComponent; //0x0140
	class PhysicsComponent* physicsComponent; //0x0148
	char pad_0150[56]; //0x0150
	class SoldierFuncArray* funcPtr; //0x0188
	char pad_0190[96]; //0x0190
	class AntAnimatable* aintAnimatable; //0x01F0
	char pad_01F8[664]; //0x01F8
	class Position* origin; //0x0490
	char pad_0498[64]; //0x0498
	float pitch; //0x04D8
	float yaw; //0x04DC
	char pad_04E0[16]; //0x04E0
	uint32_t poseType; //0x04F0
	uint32_t renderFlags; //0x04F4
	char pad_04F8[120]; //0x04F8
	class WeaponComponent* clientSoldierWeapon; //0x0570
	char pad_0578[8]; //0x0578
	class ClientRagdollComponent* ragdollComponent; //0x0580
	class BreathingComponent* breathComponent; //0x0588
	char pad_0590[32]; //0x0590
	bool wasSprinting; //0x05B0
	bool isOccluded; //0x05B1
	char pad_05B2[69]; //0x05B2
	bool isJumping; //0x05F7
	char pad_05F8[568]; //0x05F8

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void computeBoundInfo(SpatialBoundsInfo& info);

}; //Size: 0x0830
static_assert(sizeof(ClientSoldierEntity) == 0x830);

class HealthComponent
{
public:
	char pad_0008[24]; //0x0008
	float health; //0x0020
	float maxHealth; //0x0024
	char pad_0028[16]; //0x0028
	float health2; //0x0038
	char pad_003C[76]; //0x003C

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
}; //Size: 0x0088
static_assert(sizeof(HealthComponent) == 0x88);

class Position
{
public:
	char pad_0000[48]; //0x0000
	Vector4 Origin; //0x0030
	char pad_0040[128]; //0x0040
}; //Size: 0x00C0
static_assert(sizeof(Position) == 0xC0);

class PhysicsComponent
{
public:
	char pad_0008[384]; //0x0008

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
}; //Size: 0x0188
static_assert(sizeof(PhysicsComponent) == 0x188);

class ClientRagdollComponent
{
public:
	char pad_0000[176]; //0x0000
	class Vector* bonesVec; //0x00B0
	char pad_00B8[8]; //0x00B8
	int32_t updatedFlag; //0x00C0
	char pad_00C4[324]; //0x00C4
}; //Size: 0x0208
static_assert(sizeof(ClientRagdollComponent) == 0x208);

class quatransf
{
public:
	Vector4 transAndScale; //0x0000
	Vector4 rotation; //0x0010
}; //Size: 0x0020
static_assert(sizeof(quatransf) == 0x20);

class Vector
{
public:
	char pad_0000[128]; //0x0000
	class quatransf bones[216]; //0x0080
}; //Size: 0x1B80
static_assert(sizeof(Vector) == 0x1B80);

class AntAnimatable
{
public:
	char pad_0000[296]; //0x0000
	class Animatable* animatable; //0x0128
	char pad_0130[1104]; //0x0130
}; //Size: 0x0580
static_assert(sizeof(AntAnimatable) == 0x580);

class Animatable
{
public:
	char pad_0000[160]; //0x0000
}; //Size: 0x00A0
static_assert(sizeof(Animatable) == 0xA0);

class WeaponComponent
{
public:
	char pad_0008[32]; //0x0008
	uint8_t renderFlag; //0x0028
	char pad_0029[2215]; //0x0029
	class ClientSoldierWeaponHandler* weaponHandler; //0x08D0
	char pad_08D8[32]; //0x08D8
	class ClientSoldierAimingSimulation* aimingSimulation; //0x08F8
	char pad_0900[720]; //0x0900

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0BD0
static_assert(sizeof(WeaponComponent) == 0xBD0);

class BreathingComponent
{
public:
	char pad_0000[56]; //0x0000
	float stabilizationTimeLeft; //0x0038
	char pad_003C[40]; //0x003C
	int32_t N00000B42; //0x0064
	char pad_0068[8]; //0x0068
}; //Size: 0x0070
static_assert(sizeof(BreathingComponent) == 0x70);

class ClientSoldierAimingSimulation
{
public:
	char pad_0000[16]; //0x0000
	class AimAssist* aimAssist; //0x0010
	float yaw; //0x0018
	float pitch; //0x001C
	char pad_0020[168]; //0x0020
}; //Size: 0x00C8
static_assert(sizeof(ClientSoldierAimingSimulation) == 0xC8);

class AimAssist
{
public:
	char pad_0000[16]; //0x0000
	float m_lastZoomLevel; //0x0010
	float m_yaw; //0x0014
	float m_pitch; //0x0018
}; //Size: 0x001C
static_assert(sizeof(AimAssist) == 0x1C);

class ClientSoldierWeaponHandler
{
public:
	char pad_0000[56]; //0x0000
	class ClientWeapon* currentWeapon; //0x0038
	int32_t weaponIndex; //0x0040
	char pad_0044[4]; //0x0044
	class ClientWeapon* nextWeapon; //0x0048
	char pad_0050[56]; //0x0050
}; //Size: 0x0088
static_assert(sizeof(ClientSoldierWeaponHandler) == 0x88);

class ClientWeapon
{
public:
	char pad_0000[48]; //0x0000
	class SoldierWeaponData* SWeaponData; //0x0030
	char pad_0038[18768]; //0x0038
	class ClientSoldierAimingSimulation* m_authorativeAiming; //0x4988
	char pad_4990[24]; //0x4990
	class ClientZeroingWeapon* zeroingWeapon; //0x49A8
	char pad_49B0[3544]; //0x49B0
}; //Size: 0x5788
static_assert(sizeof(ClientWeapon) == 0x5788);

class SoldierWeaponData
{
public:
	char pad_0000[144]; //0x0000
	class WeaponFiringData* weaponFiringData; //0x0090
	char pad_0098[152]; //0x0098
	char* name; //0x0130
	char pad_0138[848]; //0x0138
}; //Size: 0x0488
static_assert(sizeof(SoldierWeaponData) == 0x488);

class WeaponFiringData
{
public:
	char pad_0000[16]; //0x0000
	class FiringFunctionData* firingData; //0x0010
	char pad_0018[24]; //0x0018
	class GunSway* gunSway; //0x0030
	char pad_0038[224]; //0x0038
}; //Size: 0x0118
static_assert(sizeof(WeaponFiringData) == 0x118);

class ShotConfigData
{
public:
	Vector4 positionOffset; //0x0000
	Vector4 direction; //0x0010
	Vector4 speed; //0x0020
	char pad_0030[32]; //0x0030
	class BulletEntityData* bulletEntityData; //0x0050
	char pad_0058[24]; //0x0058
	float spawnDelay; //0x0070
	uint32_t bulletsPerShell; //0x0074
	uint32_t bulletsPerShot; //0x0078
	uint32_t bulletsPerBusts; //0x007C
	uint8_t felativeTargetAiming; //0x0080
	uint8_t forceSpawnToCamera; //0x0081
	uint8_t spawnVisualAtWeaponBone; //0x0082
	uint8_t activeForceSpawnToCamera; //0x0083
	char pad_0084[12]; //0x0084
}; //Size: 0x0090
static_assert(sizeof(ShotConfigData) == 0x90);

class OverHeatData
{
public:
	char pad_0000[80]; //0x0000
	float heatPerBullet; //0x0050
	float heatDropPerSecond; //0x0054
	float overHeathPenalityTime; //0x0058
	float overHeathThreshold; //0x005C
	char pad_0060[40]; //0x0060
}; //Size: 0x0088
static_assert(sizeof(OverHeatData) == 0x88);

class FiringFunctionData
{
public:
	char pad_0000[96]; //0x0000
	class ShotConfigData shotConfigData; //0x0060
	class OverHeatData overHeat; //0x00F0
	char pad_0178[280]; //0x0178
}; //Size: 0x0290
static_assert(sizeof(FiringFunctionData) == 0x290);

class BulletEntityData
{
public:
	char pad_0008[104]; //0x0008
	uint64_t N00000A43; //0x0070
	char pad_0078[24]; //0x0078
	float velocity; //0x0090
	float caliber; //0x0094
	float N00000A48; //0x0098
	float N00000B3F; //0x009C
	float N00000A49; //0x00A0
	float N00000B00; //0x00A4
	float N00000A4A; //0x00A8
	float N00000B38; //0x00AC
	float N00000A4B; //0x00B0
	float N00000B3A; //0x00B4
	char pad_00B8[72]; //0x00B8
	float N00000A55; //0x0100
	float N00000B45; //0x0104
	float N00000A56; //0x0108
	float N00000B47; //0x010C
	char pad_0110[32]; //0x0110
	float gravity; //0x0130
	float N00000A97; //0x0134
	float N00000A5C; //0x0138
	float N00000A99; //0x013C
	float N00000A5D; //0x0140
	float N00000A9B; //0x0144
	float N00000A5E; //0x0148
	float N00000A9D; //0x014C
	float N00000A5F; //0x0150
	float damage; //0x0154
	float N00000A60; //0x0158
	float N00000AA1; //0x015C
	float penetrationDamage; //0x0160
	float N00000AA3; //0x0164
	float N00000A62; //0x0168
	float N00000AA5; //0x016C
	int32_t N00000A63; //0x0170
	float N00000AA7; //0x0174
	float N00000A64; //0x0178
	float N00000AA9; //0x017C
	char pad_0180[520]; //0x0180

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
}; //Size: 0x0388
static_assert(sizeof(BulletEntityData) == 0x388);

class ClientChassisComponent
{
public:
	char pad_0000[56]; //0x0000
	class DynamicPhysicsEntity* dynamicPhysics; //0x0038
}; //Size: 0x0040
static_assert(sizeof(ClientChassisComponent) == 0x40);

class DynamicPhysicsEntity
{
public:
	char pad_0000[160]; //0x0000
	class VehicleBones* bones; //0x00A0
	class PartList* part; //0x00A8
	char pad_00B0[104]; //0x00B0
}; //Size: 0x0118
static_assert(sizeof(DynamicPhysicsEntity) == 0x118);

class PartList
{
public:
	class ClientPartComponent* partCmp1; //0x0000
	char pad_0008[1152]; //0x0008
}; //Size: 0x0488
static_assert(sizeof(PartList) == 0x488);

class ClientPartComponent
{
public:
	char pad_0000[392]; //0x0000
}; //Size: 0x0188
static_assert(sizeof(ClientPartComponent) == 0x188);

class VehicleBones
{
public:
	Matrix4x4 boneArray[200]; //0x0000
}; //Size: 0x3200
static_assert(sizeof(VehicleBones) == 0x3200);

class AxisAlignedBox
{
public:
	Vector4 min; //0x0000
	Vector4 max; //0x0010
}; //Size: 0x0020
static_assert(sizeof(AxisAlignedBox) == 0x20);

class ClientVehicleEntity
{
public:
	char pad_0008[40]; //0x0008
	class VehicleEntityData* vehicleEntityData; //0x0030
	char pad_0038[264]; //0x0038
	class HealthComponent* healthCmp; //0x0140
	char pad_0148[8]; //0x0148
	int32_t someID; //0x0150
	char pad_0154[228]; //0x0154
	class DynamicPhysicsEntity* dynamicPhysicsEntity; //0x0238
	char pad_0240[16]; //0x0240
	AxisAlignedBox m_childrenAABB; //0x0250
	Vector4 m_dirtColor; //0x0270
	Vector4 m_prevSpeed; //0x0280
	Vector4 m_prev2Speed; //0x0290
	char pad_02A0[2296]; //0x02A0

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void computeBoundsInfo(SpatialBoundsInfo&);
}; //Size: 0x0B98
static_assert(sizeof(ClientVehicleEntity) == 0xB98);

class VehicleEntityData
{
public:
	char pad_0000[240]; //0x0000
	char* Type; //0x00F0
	char pad_00F8[144]; //0x00F8
}; //Size: 0x0188
static_assert(sizeof(VehicleEntityData) == 0x188);

class SoldierFuncArray
{
public:
	void* functions[150]; //0x0000
	char pad_04B0[384]; //0x04B0
}; //Size: 0x0630
static_assert(sizeof(SoldierFuncArray) == 0x630);

class Component
{
public:
	class ComponentType* component; //0x0000
	char pad_0008[24]; //0x0008
}; //Size: 0x0020
static_assert(sizeof(Component) == 0x20);

class Components
{
public:
	class Component component[90]; //0x0000
	char pad_0B40[152]; //0x0B40
}; //Size: 0x0BD8
static_assert(sizeof(Components) == 0xBD8);

class ComponentType
{
public:
	char pad_0000[128]; //0x0000
}; //Size: 0x0080
static_assert(sizeof(ComponentType) == 0x80);

class ClientZeroingWeapon
{
public:
	class WeaponData* weaponData; //0x0008
	char pad_0010[8]; //0x0010
	class WeaponFiringData* firingData; //0x0018
	class WeaponModifierCore* weaponModifier; //0x0020
	char pad_0028[8]; //0x0028
	Vector3 m_moveSpeed; //0x0030
	float null; //0x003C
	Matrix4x4 m_shootSpace; //0x0040
	Matrix4x4 m_shootSpaceId; //0x0080
	char pad_00C0[464]; //0x00C0
	float cameraFOV; //0x0290
	char pad_0294[2220]; //0x0294
	class ProjectileSyncInfo* projectileList; //0x0B40
	class N00001F18* something; //0x0B48
	char pad_0B50[8]; //0x0B50

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
}; //Size: 0x0B58
static_assert(sizeof(ClientZeroingWeapon) == 0xB58);

class Deviaton
{
public:
	float pitch; //0x0000
	float yaw; //0x0004
	float roll; //0x0008
}; //Size: 0x000C
static_assert(sizeof(Deviaton) == 0xC);

class GunSway
{
public:
	char pad_0008[344]; //0x0008
	class Deviaton recoilDeviaton; //0x0160

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
}; //Size: 0x016C
static_assert(sizeof(GunSway) == 0x16C);

class WeaponData
{
public:
	char pad_0000[392]; //0x0000
}; //Size: 0x0188
static_assert(sizeof(WeaponData) == 0x188);

class WeaponModifierCore
{
public:
	char pad_0000[64]; //0x0000
	uint8_t breathControl; //0x0040
	uint8_t supportedShooting; //0x0041
	uint8_t unzoomOnBoltAction; //0x0042
	uint8_t holdBoltActionUntilZoomRelease; //0x0043
	char pad_0044[100]; //0x0044
	class WeaponAimingSimulationModifier* aimingSimulationModifier; //0x00A8
	char pad_00B0[216]; //0x00B0
}; //Size: 0x0188
static_assert(sizeof(WeaponModifierCore) == 0x188);

class WeaponAimingSimulationModifier
{
public:
	char pad_0000[24]; //0x0000
	class AimingSimulationData* aimingSimulationdData; //0x0018
}; //Size: 0x0020
static_assert(sizeof(WeaponAimingSimulationModifier) == 0x20);

class AimingSimulationData
{
public:
	char pad_0000[392]; //0x0000
}; //Size: 0x0188
static_assert(sizeof(AimingSimulationData) == 0x188);

class N00001F18
{
public:
	char pad_0000[32]; //0x0000
	Matrix4x4 N00001F1D; //0x0020
	Matrix4x4 N00001F1E; //0x0060
	Matrix4x4 N00001F1F; //0x00A0
	Matrix4x4 N00001F20; //0x00E0
	char pad_0120[328]; //0x0120
}; //Size: 0x0268
static_assert(sizeof(N00001F18) == 0x268);

class ProjectileSyncInfo
{
public:
	class ProjectileBlueprint* projectileBP; //0x0000
	class BulletEntityData* projectileData; //0x0008
	bool localPlayer; //0x0010
	char pad_0011[7]; //0x0011
	class N00002043* shooter; //0x0018
	Matrix4x4 shootSpace; //0x0020
	Matrix4x4 visualShootSpace; //0x0060
	float initialSpeedX; //0x00A0
	float initialSpeedY; //0x00A4
	float initialSpeedZ; //0x00A8
	char pad_00AC[4]; //0x00AC
	uint32_t randomSeed; //0x00B0
	uint32_t trace; //0x00B4
	Vector3** targetPosition; //0x00B8
	class ClientPhyisicsEntity* targetObject; //0x00C0
	float damageMultiplier; //0x00C8
	float explosionDamagMultiplier; //0x00CC
	class WeaponUnlockAsset* weaponAsset; //0x00D0
	class CientProjectileSpawnConext* spawnContext; //0x00D8
}; //Size: 0x00E0
static_assert(sizeof(ProjectileSyncInfo) == 0xE0);

class ProjectileBlueprint
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(ProjectileBlueprint) == 0x88);

class N00002043
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(N00002043) == 0x88);

class WeaponUnlockAsset
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(WeaponUnlockAsset) == 0x88);

class CientProjectileSpawnConext
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(CientProjectileSpawnConext) == 0x88);

class ClientPhyisicsEntity
{
public:
	char pad_0000[136]; //0x0000
}; //Size: 0x0088
static_assert(sizeof(ClientPhyisicsEntity) == 0x88);

class CustomizableCamo
{
public:
	char pad_0008[8]; //0x0008
	Vector4 color; //0x0010
	Vector4 color1; //0x0020
	Vector4 color2; //0x0030
	Vector4 color3; //0x0040
	char pad_0050[16]; //0x0050

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0060
static_assert(sizeof(CustomizableCamo) == 0x60);

class OnlineManager
{
public:
	char pad_0000[56]; //0x0000
	class ClientConnection* clientConnection; //0x0038
	char pad_0040[72]; //0x0040
}; //Size: 0x0088
static_assert(sizeof(OnlineManager) == 0x88);

class ClientConnection
{
public:
	char pad_0000[9120]; //0x0000
	class ClientDamageStream* clientDamageStream; //0x23A0
	float N000020CB; //0x23A8
	float N000021CD; //0x23AC
	uint32_t N000020CC; //0x23B0
	float N000021D0; //0x23B4
	float N000020CD; //0x23B8
	float N000021D3; //0x23BC
	float fps; //0x23C0
	char pad_23C4[196]; //0x23C4
}; //Size: 0x2488
static_assert(sizeof(ClientConnection) == 0x2488);

class ClientDamageStream
{
public:
	char pad_0000[16]; //0x0000
	class DamageData* damageData; //0x0010
	char pad_0018[112]; //0x0018
}; //Size: 0x0088
static_assert(sizeof(ClientDamageStream) == 0x88);

class DamageData
{
public:
	char pad_0000[136]; //0x0000
	int32_t victimPlayerId; //0x0088
	int32_t victimInstanceId; //0x008C
	int32_t inflictiorPlayerId; //0x0090
	int32_t hitReactionType; //0x0094
	class WeaponUnlockAsset* weaponUnlockAsset; //0x0098
	Vector4 direction; //0x00A0
	float damage; //0x00B0
	bool clientAIKilled; //0x00B4
	char pad_00B5[3]; //0x00B5
	int32_t ID; //0x00B8
	int32_t compressionCostant; //0x00BC
	char pad_00C0[16]; //0x00C0
}; //Size: 0x00D0
static_assert(sizeof(DamageData) == 0xD0);
