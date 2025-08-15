#pragma once
#include <Il2cpp_Resolver/Includes.hpp>
#include <imgui/imgui.h>

#include <template/utils/types.hpp>

namespace utils {
  /**
   * Gets camera from FIRST found CameraController
   * 
   * @return poiter to original camera 
   */
  Unity::CCamera* get_camera();

  /**
   * Compute point position in the worlds with screen
   * 
   * @param world  point position in thw world (3D) 
   * @param camera camera object
   * @param screen vector to point on screen [OUT]
   * @return `true` if success filled screen, in else `false`
   */
  bool world2screen(
    Unity::Vector3 world, Unity::CCamera* camera,
    Unity::Vector2* out_screen // out
  );

  /**
   * Prints last error in WinApi (with GetLastError)
   */
  void print_last_error();

  /**
   * Makes deep copy of ImDrawData object and returns pointer to it
   * 
   * @param original pointer to object to copy
   * @return pointer to new object. Free it with utils::free_drawdata()
   */
  ImDrawData* copy_drawdata(ImDrawData* original);

  /**
   * Free draw data allocated with utils::copy_drawdata
   * 
   * @param data Pointer to object to free
   * @return `true`  - Success free | `false` - Failed to free
   */
  bool free_drawdata(ImDrawData* data);
}