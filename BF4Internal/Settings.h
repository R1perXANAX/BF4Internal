#pragma once



class MenuSettings {
public:
	//VISUAL
		bool Skeleton = true;
		bool ShowLines =true;
		bool ShowBox = true;
		bool HealthBar = false;
		bool Health = false;
		bool Distance =false;
		bool Names = false;
	
		float FovCircle = 20;

	//PLAYER
		bool noSniperBreath = true;
};