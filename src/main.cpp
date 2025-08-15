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

void infcollect_player() {
	for (
		// Infinity, sleep 10 sec on each round 
		; true ; std::this_thread::sleep_for(std::chrono::seconds(3))
	) {
		if (!global::is_initialized) continue;
		global::players_mutex.lock();

		auto* list = Unity::Object::FindObjectsOfType<void>("BAPBAP.Player.PlayerManager");
		if(!list) continue;

		for (int i = 0; i < list->m_uMaxLength; i++) {
			if (!list->At(i)) {
				// ! Implicit conversion !
				global::player_list[i] = nullptr;
				continue;
			}
			// printf("Player at 0x%p\n", list->At(i));

			global::player_list[i] = PlayerManager(list->At(i));
		}

		global::players_mutex.unlock();
	}
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
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)infcollect_player, NULL, NULL, NULL);
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
