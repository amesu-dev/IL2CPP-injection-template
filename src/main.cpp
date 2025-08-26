#include <mutex>
#include <thread>
#include <chrono>

#include <Il2cpp_Resolver/Functions/Callback.hpp>
#include <Il2cpp_Resolver/il2cpp_resolver.hpp>
#include <kiero/includes.h>

#include <template/gui.hpp>
#include <template/utils/variables.hpp>

struct enum_params {
	HWND handle = nullptr;
	uint64_t target_pid = -1;
};

HWND find_window() {
	enum_params param;
	param.target_pid = GetCurrentProcessId();

	EnumWindows([](HWND handle, LPARAM lParam) {
		auto* param = (enum_params*)lParam;

		unsigned long pid = 0;
		GetWindowThreadProcessId(handle, &pid);
		if (pid != param->target_pid) return TRUE;

		param->handle = handle;
		return FALSE;
	}, (LPARAM)&param);
	return param.handle;
}

void CreateConsole() {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("IL2CPP");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

void initvars() {
	if (IL2CPP::Initialize(true)) {
		printf("[ DEBUG ] Il2Cpp initialized\n");
	}
	else {
		printf("[ DEBUG ] Il2Cpp initialize failed, quitting...");
		Sleep(300);
		exit(0);
	}
	sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
	printf("[ DEBUG ] Base Address: 0x%llX\n", sdk::Base);
	global::GameAssembly = sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
	printf("[ DEBUG ] GameAssembly Base Address: 0x%llX\n", sdk::GameAssembly);
	sdk::UnityPlayer = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
	printf("[ DEBUG ] UnityPlayer Base Address: 0x%llX\n", sdk::UnityPlayer);
	printf("----------------------------------------------------------\n");
	printf("\n");
}

void initchair() {
#define DEBUG
#ifdef DEBUG
	CreateConsole(); // if using melonloader console is already created
	system("cls");
#endif // DEBUG
	initvars();
	// find_sigs();
	IL2CPP::Callback::Initialize();
	// EnableHooks();
	
	kiero::bind(8, (void**)&global::orig_Present, hkPresent); //? For drawing using Game DirectX

	// CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hkPresent, NULL, NULL, NULL);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
	do {
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
			initchair();

			global::is_initialized = true;
		}
	} while (!global::is_initialized);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, LPVOID lpReserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(mod);
    CreateThread(nullptr, 0, MainThread, mod, 0, nullptr);
  }
  
  return TRUE;
}
