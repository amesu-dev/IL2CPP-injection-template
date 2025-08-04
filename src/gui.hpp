#pragma once
// #include <kiero/sdk.h>
#include <kiero/includes.h>
#include <Il2cpp_Resolver/Includes.hpp>
#include <minhook/include/MinHook.h>
#include <kiero/Lists.hpp>

// #include <imgui/imgui_impl_win32.h>
#include <kiero/Rendering.hpp>

#include "menu.hpp"
#include "utils/Font.h"
#include "utils/variables.hpp"

void init_gui();
void render_gui();

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
