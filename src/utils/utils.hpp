#pragma once
#include <Il2cpp_Resolver/Includes.hpp>
#include "./types.hpp"

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
    Unity::Vector3& screen // out
  );

  void print_last_error();
}