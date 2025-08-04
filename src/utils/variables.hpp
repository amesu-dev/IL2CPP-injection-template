#pragma once
#include "./types.hpp"

#include <windows.h>
#include <array>
#include <mutex>

#include <kiero/includes.h>
#include <imgui/imgui.h>
#include <ThreadPool/pool.hpp>

namespace global {
  extern bool is_initialized;
  extern bool is_hkPresent_init;

  extern uintptr_t GameAssembly;
  extern std::array<PlayerManager, 8> player_list;
  extern std::mutex players_mutex;

  extern Present orig_Present;

  extern thread_pool t_pool;

  extern ImDrawData* draw_data;
  extern std::mutex draw_mutex;

  extern HWND original_window;
  extern HWND render_window;
  extern WNDPROC oWndProc;
  
  extern ID3D11Device* pDevice;
  extern ID3D11DeviceContext* pContext;
  extern IDXGISwapChain* pSwapChain;
  extern ID3D11RenderTargetView* mainRenderTargetView;

  extern DWORD lastShotTime;
  extern DWORD last_tick;

  extern ImVec4 Rainbow;

  extern D3D11_VIEWPORT viewport;
  extern UINT vps;
}