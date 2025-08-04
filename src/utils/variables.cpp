#include "./variables.hpp"

namespace global {
  bool is_initialized = false;
  bool is_hkPresent_init = false;

  uintptr_t GameAssembly = -1;
  std::array<PlayerManager, 8> player_list {
    nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr
  };
  std::mutex players_mutex; 

  Present orig_Present;

  thread_pool t_pool { 5 };

  ImDrawData* draw_data = nullptr;
  std::mutex draw_mutex;

  HWND original_window = NULL;
  HWND render_window = NULL;
  WNDPROC oWndProc;

  ID3D11Device* pDevice = NULL;
  ID3D11DeviceContext* pContext = NULL;
  IDXGISwapChain* pSwapChain = NULL;
  ID3D11RenderTargetView* mainRenderTargetView;

  DWORD lastShotTime = 0;
  DWORD last_tick = 0;

  ImVec4 Rainbow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

  D3D11_VIEWPORT viewport;
  UINT vps = 1;
}