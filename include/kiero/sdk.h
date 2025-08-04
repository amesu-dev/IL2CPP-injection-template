#pragma once
#include "il2cpp.h"
#include "vec.h"
#include "vec2.h"
#include <vector>
#include <utility> // for std::pair

#include <d3d11.h>
#include <imgui/imgui.h>
extern bool show_menu;

namespace mem {
	template<typename T> T read(uintptr_t address) {
		try { return *(T*)address; }
		catch (...) { return T(); }
	}

	template<typename T> void write(uintptr_t address, T value) {
		try { *(T*)address; }
		catch (...) { return; }
	}
}

namespace sdk
{
	extern uintptr_t Base;
	extern uintptr_t GameAssembly;
	extern uintptr_t UnityPlayer;

	void mousemove(float tarx, float tary, float X, float Y, int smooth);
}

namespace Offsets {
	extern uintptr_t SetTargetRecoil; // Use This to Hold Offsets for Functions
}

namespace vars {
	extern UINT vps;
	extern Vector2 screen_size;
	extern Vector2 screen_center;
	extern D3D11_VIEWPORT viewport;
	extern bool initil2cpp;

	extern bool PlayerSnaplines;
	extern bool SnaplineRainbow;
	extern bool aimbot;
	extern bool fov_check;
	extern bool fov_changer;
	extern bool crosshair;
	extern bool crosshairRainbow;
	extern bool watermark;

	// todo
	extern bool recoileditor;
	extern float recoiledited;

	extern bool firerate;
	extern bool infjump;
	extern float ViewmodelFOV;

	// Floats
	extern float CameraFOV;
	extern float crosshairsize;
	extern float smooth;
	extern float aim_fov;

	// Ints
	extern int linetype;
	extern int currentplayeridx;

	// Colors
	extern ImColor CrossColor;
	extern ImColor PlayerNameColor;
	extern ImColor skeletonESPCol;
	extern ImColor PlayerSnaplineColor;
	extern ImColor PlayerHealthbarColor;
	extern ImColor SelfChamsColor;
	extern ImColor ChamsColor;
	extern ImColor ItemNameColor;
	extern ImColor ItemSnaplineColor;
	extern ImColor boxESPCol;
	extern ImColor hitdebugcol;
	extern ImVec4 Rainbow;

	// Vector3 PlayerPos;

	extern const char* bones[2];
	extern int boneselected;
}
