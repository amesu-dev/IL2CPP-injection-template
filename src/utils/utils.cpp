#include <template/utils/utils.hpp>
#include <template/utils/variables.hpp>

#include <malloc.h>

namespace utils {
  Unity::CCamera* get_camera() {
    void* controller_ptr = Unity::Object::FindObjectOfType<void>("BAPBAP.Local.CameraController");

    CameraController controller { controller_ptr };

    return controller.get_camera();
  }

  bool world2screen(
    Unity::Vector3 world_pos, Unity::CCamera* camera,
    Unity::Vector2* out_screen // out
  ) {
		if (!camera) return false;

    auto* world2screen_ptr = (Unity::Vector3 (__cdecl*) (void*, Unity::Vector3))(global::GameAssembly + 0x3237EA0); // w2screen
    Unity::Vector3 buffer = world2screen_ptr(camera, world_pos);

    printf("Success called w2screen!\n");
    // system("pause");
    // Sleep(30'000);
		out_screen->x = buffer.x;
    out_screen->y = global::viewport.Height - buffer.y;

    return true;
	}

  void print_last_error() {
		// DWORD dwError = GetLastError();
    DWORD errorCode = GetLastError();
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorCode,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      messageBuffer, 0, NULL
    );

    if (messageBuffer != nullptr) {
        std::cout << "Error " << errorCode << ": " << messageBuffer << std::endl;
        LocalFree(messageBuffer); // Free the buffer allocated by FormatMessage
    } else {
        std::cout << "Failed to retrieve error message for code: " << errorCode << std::endl;
    }
  }

  ImDrawData* copy_drawdata(ImDrawData* original) {
    if (!original) return nullptr;

    auto* new_data = (ImDrawData*)malloc(sizeof(ImDrawData));

    // *new_data = *original;
    new_data->Valid = original->Valid;
    new_data->TotalIdxCount = original->TotalIdxCount;
    new_data->TotalVtxCount = original->TotalVtxCount;
    new_data->DisplayPos = original->DisplayPos;
    new_data->DisplaySize = original->DisplaySize;
    new_data->FramebufferScale = original->FramebufferScale;
    new_data->CmdListsCount = original->CmdListsCount;

    new_data->CmdLists = (ImDrawList**)calloc(new_data->CmdListsCount, sizeof(ImDrawList*));
    for (size_t index = 0; index < new_data->CmdListsCount; index += 1) {
      new_data->CmdLists[index] = (ImDrawList*)malloc(sizeof(ImDrawList));

      memcpy(new_data->CmdLists[index], original->CmdLists[index], sizeof(ImDrawList));
    }

    return new_data;
  }
  
  bool free_drawdata(ImDrawData* data) {
    if (!data) return true;

    try { // free(void*) throws error when failed to free memory
      for (size_t index = 0; index < data->CmdListsCount; index += 1) {
        free(data->CmdLists[index]);
      }
      free(data->CmdLists);
      free(data);
    } catch (std::exception err) {
      printf("Exception when free draw data: %s\n", err.what());
      return false;
    }

    return true;
  }
}