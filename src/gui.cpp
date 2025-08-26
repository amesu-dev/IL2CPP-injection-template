#include <template/gui.hpp>
// #include "menu.hpp"
#include <thread>
#include <chrono>
#include <d3d11.h>

#include <template/pages/visual.hpp>
#include <template/pages/tests.hpp>

#include <imgui/imgui_impl_dx11.h>

// Found visual page in map
//! May be nullptr
static visual_page* vpage = nullptr;


void init_gui() {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(global::render_window);
	ImGui_ImplDX11_Init(global::pDevice, global::pContext);
}

void render_gui() {
	if (!global::is_initialized)
		return;

	// ! Begin Scene !
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto isFrames = ImGui::GetFrameCount();
	static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
	if (isFrames) {
		if (isGreen == 0.01f && isBlue == 0.0f)
		{
			isRed += 0.01f;
		}
		if (isRed > 0.99f && isBlue == 0.0f)
		{
			isRed = 1.0f;

			isGreen += 0.01f;

		}
		if (isGreen > 0.99f && isBlue == 0.0f)
		{
			isGreen = 1.0f;

			isRed -= 0.01f;

		}
		if (isRed < 0.01f && isGreen == 1.0f)
		{
			isRed = 0.0f;

			isBlue += 0.01f;

		}
		if (isBlue > 0.99f && isRed == 0.0f)
		{
			isBlue = 1.0f;

			isGreen -= 0.01f;

		}
		if (isGreen < 0.01f && isBlue == 1.0f)
		{
			isGreen = 0.0f;

			isRed += 0.01f;

		}
		if (isRed > 0.99f && isGreen == 0.0f)
		{
			isRed = 1.0f;

			isBlue -= 0.01f;

		}
		if (isBlue < 0.01f && isGreen == 0.0f)
		{
			isBlue = 0.0f;

			isRed -= 0.01f;

			if (isRed < 0.01f)
				isGreen = 0.01f;

		}
	}
	vars::Rainbow = ImVec4(isRed, isGreen, isBlue, 1.0f);

	// Draw FPS
	render::DrawOutlinedText(
		gameFont, ImVec2(global::viewport.Width / 2, 5), 13.0f,
		ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z), true,
		"[ %.1f FPS ]", ImGui::GetIO().Framerate
	);

	if (show_menu) {
		draw_menu();
	}

	// Take pages
	if (!vpage) {
		vpage = reinterpret_cast<visual_page*>((*pages.find(visual_page::name)).second);
    printf("[ DEBUG ] vpage: 0x%p\n", vpage);
	}

	if (vpage) {
		vpage->draw_snaplines(); //? Draw only if setting are true
		if (vpage->is_crosshair()) vpage->draw_crosshair();
	}

	// ! End Scene !
	ImGui::Render();

	// Pass rendered data
	global::draw_mutex.lock();
	// global::draw_data = *ImGui::GetDrawData();
	utils::free_drawdata(global::draw_data);
	global::draw_data = utils::copy_drawdata(ImGui::GetDrawData());

	global::draw_mutex.unlock();
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(global::oWndProc, hWnd, uMsg, wParam, lParam);
}

uint64_t render_task_id = -1ULL;
uint64_t last_tick = -1ULL;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!global::is_hkPresent_init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&global::pDevice))) {
			global::pDevice->GetImmediateContext(&global::pContext);
			
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			
			global::render_window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			global::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &global::mainRenderTargetView);
			pBackBuffer->Release();
			
			global::oWndProc = (WNDPROC)SetWindowLongPtr(global::render_window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			
			init_gui();
			
			ImGui::GetIO().Fonts->AddFontDefault();
			ImFontConfig font_cfg;
			font_cfg.GlyphExtraSpacing.x = 1.2;
			gameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
			ImGui::GetIO().Fonts->AddFontDefault();
			
			// Grab A shader Here If You want
			
			global::is_hkPresent_init = true;
		}

		else
			return global::orig_Present(pSwapChain, SyncInterval, Flags);
	}

	global::pContext->RSGetViewports(&global::vps, &global::viewport);
	vars::screen_size = { global::viewport.Width, global::viewport.Height };
	vars::screen_center = { global::viewport.Width / 2.0f, global::viewport.Height / 2.0f };

	// Render
	try {
		// if (
		// 	render_task_id == -1ULL ||
		// 	global::t_pool.calculated(render_task_id)
		// ) {
		// 	// Create new task if only there is no tasks
		// 	render_task_id = global::t_pool.add_task(render_gui);
		// }
		// render_gui();

		
		auto cur_tick = GetTickCount64();
		if (cur_tick - last_tick > 1'000 / 15) {
			render_gui();
			last_tick = cur_tick;
		}
	} catch (...) {}

	if (vpage) {
		vpage->change_fov(); //? Automaticly choice FOV
	}


	// Wait for first draw data...
	global::draw_mutex.lock();
	if (global::draw_data) {
		auto* temp_data = utils::copy_drawdata(global::draw_data); // Just copy
		global::pContext->OMSetRenderTargets(1, &global::mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(temp_data);
		utils::free_drawdata(temp_data);
	}
	global::draw_mutex.unlock();

	if (GetAsyncKeyState(VK_INSERT) & 1)
		show_menu = !show_menu;

	if (GetKeyState(VK_END) & 1) {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		show_menu = false;
	}

	IL2CPP::Thread::Detach(m_pThisThread);

	return global::orig_Present(pSwapChain, SyncInterval, Flags);
}
