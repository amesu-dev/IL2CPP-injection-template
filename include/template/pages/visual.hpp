#pragma once
#include <template/pages/__general.hpp>

#include <vector>

#include <imgui/imgui.h>
#include <Il2cpp_Resolver/Unity/Includes.hpp>

#include <template/utils/variables.hpp>
#include <template/utils/utils.hpp>

//! Use `public` deriving for casting to `cheat_page`

class visual_page : public cheat_page {
public:
  static inline const std::string name { "Visual" };

  virtual void draw();

protected:
  // Put there your variables
  bool player_snaplines = false;
  bool snapline_rainbow = false;
  ImColor snapline_color = ImColor(255, 255, 255); // white

  bool fov_changer = false;
  float camera_FOV = 120.0f;
  const float default_FOV = 90.0f;
  int is_character_camera = 1;

  bool crosshair = false;
  bool rainbow_crosshair = false;
  ImColor crosshair_color = ImColor(0, 255, 255); // cyan
  int crosshair_size = 8; // px

  Unity::CCamera* camera = nullptr;
  Unity::CCamera* main_camera = nullptr;

public:
  inline bool is_snaplines() const { return this->player_snaplines; }
  inline bool is_fov_changer() const { return this->fov_changer; }
  inline bool is_crosshair() const { return this->crosshair; }

  // Sets fov from internal value
  void change_fov();

  void draw_crosshair();

  void draw_snaplines();

protected:
  Unity::CCamera* get_camera(bool is_main = false);
};
