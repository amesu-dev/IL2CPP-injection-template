#include "./utils.hpp"

#include "./variables.hpp"

namespace utils {
  Unity::CCamera* get_camera() {
    void* controller_ptr = Unity::Object::FindObjectOfType<void>("BAPBAP.Local.CameraController");

    CameraController controller { controller_ptr };

    return controller.get_camera();
  }

  bool world2screen(
    Unity::Vector3 world_pos, Unity::CCamera* camera,
    Unity::Vector3& screen // out
  ) {
		if (!camera) return false;

    auto* world2screen_ptr = (Unity::Vector3 (__cdecl*) (void*, Unity::Vector3))(global::GameAssembly + 0x3237EA0); // w2screen
    // auto* world2view_ptr = (Unity::Vector3 (__cdecl*) (void*, Unity::Vector3))(global::GameAssembly + 0x3238010);
    Unity::Vector3 buffer = world2screen_ptr(camera, world_pos);
    printf("Success!\n");

		if (buffer.x > global::viewport.Width || buffer.y > global::viewport.Height || buffer.x < 0 || buffer.y < 0 || buffer.z < 0) { // check if point is on screen
			return false;
		}

		screen.x = buffer.x;
    screen.y = global::viewport.Height - buffer.y;
    // screen.y = buffer.y;

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
}