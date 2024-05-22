#include "Drawing.h"
#include "Visual.h"
#include <string>
#include <sstream>

using namespace _Utils;


ESP::ESP() {
	VisualUpdateInstruction = (uintptr_t*)((uintptr_t)GetModuleHandle("bf4.exe") + 0x0098558E);
	uint8_t ModifiedInstruction[] = {
		0xC6, 0x83, 0xEC, 0x00, 0x00, 0x00, 0x01
	};
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)VisualUpdateInstruction, 0x7, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy(OriginalInstruction, (LPVOID)VisualUpdateInstruction, 0x7);
	memcpy(VisualUpdateInstruction, (LPVOID)ModifiedInstruction, sizeof(ModifiedInstruction));

	VirtualProtect((LPVOID)VisualUpdateInstruction, 0x7, OldProtect, &OldProtect);
}


//ImNotEvenSparta credit
void ESP::Render() {
	DrawCircle(windowSize.cx / 2, windowSize.cy / 2, GetPixelFov(menuSettings->FovCircle), PURPLE, 160);
	GameRender* gameRender = GetGameRender();
	if (gameRender) {
		RenderView* renderView = gameRender->renderView;
		if (IsValidPtr(renderView)) {
			Matrix4x4 viewMatrix;
			memcpy(viewMatrix, renderView->m_viewProjectionMatrix, sizeof(Matrix4x4));
			ClientPlayer * localPlayer = GetLocalPlayer();
			NetworkableEntity * EntityList = GetEntityList();
			for (uintptr_t i = 0; i < 60; i++) {
				ClientPlayer* currentEntity = EntityList->EntityArray[i];
				if (IsValidPtr(currentEntity) && IsValidPtr(localPlayer)) {
					ClientSoldierEntity* currentEntityControllable = currentEntity->attachedControllable;
					ClientSoldierEntity* LPControllable = localPlayer->attachedControllable;
					if (IsValidPtr(currentEntityControllable) && IsValidPtr(LPControllable)) {
						if (!currentEntity->IsInVehicle()) {
							HealthComponent* currentEntityHealthComponent = currentEntityControllable->healthComponent;
							if (IsValidPtr(currentEntityHealthComponent) && currentEntityHealthComponent->health > 0) {

								if (localPlayer->teamID != currentEntity->teamID) {
									RGBA* color = RED;
									if (!currentEntityControllable->isOccluded)
										color = GREEN;
									
									if (menuSettings->Skeleton) {

										// Lower Body Part

										Vector3 RightBottom = GetBonePosition(currentEntity, 184);
										Vector3 RightKnee = GetBonePosition(currentEntity, 183);
										Vector2 RightBottomScreenPos{};
										Vector2 RightKneeScreenPos{};

										Vector3 LeftBottom = GetBonePosition(currentEntity, 198);
										Vector3 LeftKnee = GetBonePosition(currentEntity, 197);
										Vector2 LeftBottomScreenPos{};
										Vector2 LeftKneeScreenPos{};

										if (WorldToScreen(RightBottom, RightBottomScreenPos, viewMatrix, windowSize)) {
											if (WorldToScreen(RightKnee, RightKneeScreenPos, viewMatrix, windowSize)) {
												DrawLine(RightBottomScreenPos.x, RightBottomScreenPos.y, RightKneeScreenPos.x, RightKneeScreenPos.y, color, 2.f);
											}
										}


										if (WorldToScreen(LeftBottom, LeftBottomScreenPos, viewMatrix, windowSize)) {
											if (WorldToScreen(LeftKnee, LeftKneeScreenPos, viewMatrix, windowSize)) {
												DrawLine(LeftBottomScreenPos.x, LeftBottomScreenPos.y, LeftKneeScreenPos.x, LeftKneeScreenPos.y, color, 2.f);
											}
										}

										Vector3 RightJustBelowWaist = GetBonePosition(currentEntity, 182);
										Vector2 RightJustBelowWaistPos{};

										Vector3 LeftJustBelowWaist = GetBonePosition(currentEntity, 196);
										Vector2 LeftJustBelowWaistPos{};


										if (WorldToScreen(RightKnee, RightKneeScreenPos, viewMatrix, windowSize)) {
											if (WorldToScreen(RightJustBelowWaist, RightJustBelowWaistPos, viewMatrix, windowSize)) {
												DrawLine(RightKneeScreenPos.x, RightKneeScreenPos.y, RightJustBelowWaistPos.x, RightJustBelowWaistPos.y, color, 2.f);
											}
										}

										if (WorldToScreen(LeftKnee, LeftKneeScreenPos, viewMatrix, windowSize)) {
											if (WorldToScreen(LeftJustBelowWaist, LeftJustBelowWaistPos, viewMatrix, windowSize)) {
												DrawLine(LeftKneeScreenPos.x, LeftKneeScreenPos.y, LeftJustBelowWaistPos.x, LeftJustBelowWaistPos.y, color, 2.f);
											}
										}

										Vector3 Pelvis = GetBonePosition(currentEntity, 203);
										Vector2 PelvisPos{};

										if (WorldToScreen(RightJustBelowWaist, RightJustBelowWaistPos, viewMatrix, windowSize)) {
											if (WorldToScreen(Pelvis, PelvisPos, viewMatrix, windowSize)) {
												DrawLine(RightJustBelowWaistPos.x, RightJustBelowWaistPos.y, PelvisPos.x, PelvisPos.y, color, 2.f);
											}
										}

										if (WorldToScreen(LeftJustBelowWaist, LeftJustBelowWaistPos, viewMatrix, windowSize)) {
											if (WorldToScreen(Pelvis, PelvisPos, viewMatrix, windowSize)) {
												DrawLine(LeftJustBelowWaistPos.x, LeftJustBelowWaistPos.y, PelvisPos.x, PelvisPos.y, color, 2.f);
											}
										}

										Vector3 Neck = GetBonePosition(currentEntity, 43);
										Vector2 NeckPos{};

										if (WorldToScreen(Pelvis, PelvisPos, viewMatrix, windowSize)) {
											if (WorldToScreen(Neck, NeckPos, viewMatrix, windowSize)) {
												DrawLine(PelvisPos.x, PelvisPos.y, NeckPos.x, NeckPos.y, color, 2.f);
											}
										}

										Vector3 LeftShoulder = GetBonePosition(currentEntity, 9);
										Vector2 LeftShoulderPos{};
										Vector3 RightShoulder = GetBonePosition(currentEntity, 109);
										Vector2 RightShoulderPos{};

										if (WorldToScreen(Neck, NeckPos, viewMatrix, windowSize)) {
											if (WorldToScreen(LeftShoulder, LeftShoulderPos, viewMatrix, windowSize)) {
												DrawLine(NeckPos.x, NeckPos.y, LeftShoulderPos.x, LeftShoulderPos.y, color, 2.f);
											}
										}

										if (WorldToScreen(Neck, NeckPos, viewMatrix, windowSize)) {
											if (WorldToScreen(RightShoulder, RightShoulderPos, viewMatrix, windowSize)) {
												DrawLine(NeckPos.x, NeckPos.y, RightShoulderPos.x, RightShoulderPos.y, color, 2.f);
											}
										}

										Vector3 LeftElbow = GetBonePosition(currentEntity, 11);
										Vector2 LeftElbowPos{};
										Vector3 RightElbow = GetBonePosition(currentEntity, 111);
										Vector2 RightElbowPos{};


										if (WorldToScreen(LeftShoulder, LeftShoulderPos, viewMatrix, windowSize)) {
											if (WorldToScreen(LeftElbow, LeftElbowPos, viewMatrix, windowSize)) {
												DrawLine(LeftShoulderPos.x, LeftShoulderPos.y, LeftElbowPos.x, LeftElbowPos.y, color, 2.f);
											}
										}

										if (WorldToScreen(RightShoulder, RightShoulderPos, viewMatrix, windowSize)) {
											if (WorldToScreen(RightElbow, RightElbowPos, viewMatrix, windowSize)) {
												DrawLine(RightShoulderPos.x, RightShoulderPos.y, RightElbowPos.x, RightElbowPos.y, color, 2.f);
											}
										}

										Vector3 LeftHand = GetBonePosition(currentEntity, 35);
										Vector2 LeftHandPos{};
										Vector3 RightHand = GetBonePosition(currentEntity, 135);
										Vector2 RightHandPos{};

										if (WorldToScreen(LeftElbow, LeftElbowPos, viewMatrix, windowSize)) {
											if (WorldToScreen(LeftHand, LeftHandPos, viewMatrix, windowSize)) {
												DrawLine(LeftElbowPos.x, LeftElbowPos.y, LeftHandPos.x, LeftHandPos.y, color, 2.f);
											}
										}

										if (WorldToScreen(RightElbow, RightElbowPos, viewMatrix, windowSize)) {
											if (WorldToScreen(RightHand, RightHandPos, viewMatrix, windowSize)) {
												DrawLine(RightElbowPos.x, RightElbowPos.y, RightHandPos.x, RightHandPos.y, color, 2.f);
											}
										}

										Vector3 Head = GetBonePosition(currentEntity, 46);
										Vector2 HeadPos{};

										if (WorldToScreen(Neck, NeckPos, viewMatrix, windowSize)) {
											if (WorldToScreen(Head, HeadPos, viewMatrix, windowSize)) {
												DrawLine(NeckPos.x, NeckPos.y, HeadPos.x, HeadPos.y, color, 2.f);
											}
										}


									}
									if (menuSettings->ShowLines) {
										Vector3 CurrentEntityPelvis = GetBonePosition(currentEntity, 184);
										Vector2 CurrentEntityPelvisScreen{};

										if (WorldToScreen(CurrentEntityPelvis, CurrentEntityPelvisScreen, viewMatrix, windowSize)) {
											DrawLine(960, 1080, CurrentEntityPelvisScreen.x, CurrentEntityPelvisScreen.y, PURPLE, 1.f);
										}
									}
									if (menuSettings->ShowBox) {
										Vector3 CurrentEntityHead = GetBonePosition(currentEntity, 46);
										Vector2 CurrentEntityHeadScreen{};
										Vector3 CurrentEntityFoot = GetBonePosition(currentEntity, 3);
										Vector2 CurrentEntityFootScreen{};
										Vector3 LocalPlayerFoot = GetBonePosition(localPlayer, 3);


										if (WorldToScreen(CurrentEntityHead, CurrentEntityHeadScreen, viewMatrix, windowSize)) {
											if (WorldToScreen(CurrentEntityFoot, CurrentEntityFootScreen, viewMatrix, windowSize)) {
												float distance = Get3DDistance(LocalPlayerFoot, CurrentEntityFoot);
												float heigh = CurrentEntityFootScreen.y - CurrentEntityHeadScreen.y;
												float width = heigh / 2;
												float health = IsValidPtr(currentEntityHealthComponent) ? currentEntityHealthComponent->health : 0.f;
												float healthPerc = health / 100;
												DrawCornerBox(CurrentEntityHeadScreen.x - width / 2, CurrentEntityHeadScreen.y, width, heigh, 1, PURPLE);
												if (menuSettings->HealthBar) {
													if (health > 65)
														DrawFilledRect(CurrentEntityHeadScreen.x - width / 2, CurrentEntityHeadScreen.y - 5, width * healthPerc, 3, GREEN);
													else if (health > 25)
														DrawFilledRect(CurrentEntityHeadScreen.x - width / 2, CurrentEntityHeadScreen.y - 5, width * healthPerc, 3, GOLD);
													else
														DrawFilledRect(CurrentEntityHeadScreen.x - width / 2, CurrentEntityHeadScreen.y - 5, width * healthPerc, 3, RED);

												}
												
												DrawHealthCircle({CurrentEntityFootScreen.x + heigh/ 2, CurrentEntityFootScreen.y}, health, 100, 8);
												


												if (menuSettings->Distance) {
													
													std::stringstream dist;
													dist << (int)distance;
													std::string distTxt = "Distance: " + dist.str() + " m";
													DrawString(distTxt, CurrentEntityFootScreen.x - width, CurrentEntityFootScreen.y + 5, PURPLE);
												}
												if (menuSettings->Health) {
													std::stringstream healthS;
													healthS << (int)(health);
													std::string healthTxt = "HP: " + healthS.str();
													DrawString(healthTxt, CurrentEntityHeadScreen.x + width / 2 + 1, CurrentEntityHeadScreen.y - 10, WHITE);
												}

												if (menuSettings->Names) {
													if (IsValidPtr(currentEntity->Name)) {
														std::string name(currentEntity->Name);
														DrawString(name, CurrentEntityHeadScreen.x + width / 2 + 1, CurrentEntityHeadScreen.y - 15, GOLD);
													}
													else {
														std::string name = "Name Error";
														DrawString(name, CurrentEntityHeadScreen.x + width / 2 + 1, CurrentEntityHeadScreen.y - 15, GOLD);
													}
												}
											}
										}
									}
								}
							}
						}
						if (currentEntity->IsInVehicle()) {
							SpatialBoundsInfo info;
							ClientVehicleEntity* vehicleEnt = (ClientVehicleEntity*)currentEntityControllable;
							if (IsValidPtr(vehicleEnt)) {
								vehicleEnt->computeBoundsInfo(info);
							}
							DrawAABB(info, viewMatrix, windowSize, RED);
							Vector2 screenPos;
							if (WorldToScreen(GetVehicleBonePosition((ClientVehicleEntity*)currentEntityControllable, 40), screenPos, viewMatrix, windowSize)) {
								VehicleEntityData* vehicleData = vehicleEnt->vehicleEntityData;
								std::string name = (IsValidPtr(vehicleData) && IsValidPtr(vehicleData->Type)) ? vehicleData->Type : "Unknown";
								DrawString(name, screenPos.x, screenPos.y ,RED);
								DrawString(name, screenPos.x -1, screenPos.y - 1, RED);
								DrawString(name, screenPos.x, screenPos.y-2, RED);
								
								if (IsValidPtr(vehicleEnt)) {
									HealthComponent* healthCmp = vehicleEnt->healthCmp;
									if (IsValidPtr(healthCmp)) {
										std::stringstream healthS;
										healthS << (int)(healthCmp->health2);
										std::string healthTxt = "HP:  " + healthS.str();
										if (healthCmp->health2 > 150) {
											DrawString(healthTxt, screenPos.x, screenPos.y + 10, GREEN);
											DrawString(healthTxt, screenPos.x, screenPos.y + 11, GREEN);
										}
											
										else if (healthCmp->health2 > 50) {
											DrawString(healthTxt, screenPos.x, screenPos.y + 10, GOLD);
											DrawString(healthTxt, screenPos.x , screenPos.y + 11, GOLD);
										}
										else {
											DrawString(healthTxt, screenPos.x, screenPos.y + 10, RED);
											DrawString(healthTxt, screenPos.x , screenPos.y + 11, RED);
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
void ESP::CleanUp() {

}
ESP::~ESP() {
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)VisualUpdateInstruction, 0x7, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy(VisualUpdateInstruction, (LPVOID)OriginalInstruction, 0x7);

	VirtualProtect((LPVOID)VisualUpdateInstruction, 0x7, OldProtect, &OldProtect);
}