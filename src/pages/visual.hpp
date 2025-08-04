#pragma once
#include "__general.hpp"

#include <vector>

#include <imgui/imgui.h>
#include <Il2cpp_Resolver/Unity/Includes.hpp>

#include "utils/variables.hpp"
#include "utils/utils.hpp"

//! Use `public` deriving for casting to `cheat_page`

class visual_page : public cheat_page {
public:
  static inline const std::string name { "Visual" };

  virtual void draw() {
    ImGui::Checkbox("Player Snaplines", &this->player_snaplines);
    ImGui::SameLine();
    ImGui::ColorEdit3("##PlayerSnaplineColor", (float*)&this->snapline_color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
    ImGui::SameLine();
    ImGui::Checkbox("##RGB3", &this->snapline_rainbow);

    ImGui::Checkbox("Crosshair", &this->crosshair);
    ImGui::SameLine();
    ImGui::ColorEdit3("##CrosshairColor", (float*)&this->crosshair_color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
    ImGui::SameLine();
    ImGui::Checkbox("##RGB6", &this->rainbow_crosshair);
    
    ImGui::Checkbox("Fov Changer", &this->fov_changer);
    if (this->fov_changer) {
      ImGui::SliderFloat("##CamFOV", &this->camera_FOV, 20, 180, "Camera FOV: %.0f");
      ImGui::SliderInt("###Camera", &this->is_character_camera, 0, 1);
      if (ImGui::IsItemHovered())
        ImGui::SetTooltip("0 = Main\n1 = Character");
      // ImGui::SliderFloat("##ViewFOV", &this->ViewmodelFOV, 20, 180, "Viewmodel FOV: %.0f");
    }
  }

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

public:
  bool is_snaplines() const { return this->player_snaplines; }
  bool is_fov_changer() const { return this->fov_changer; }
  bool is_crosshair() const { return this->crosshair; }

  // Sets fov from internal value
  void change_fov() {
    if (!this->fov_changer) return;
    Unity::CCamera* camera = this->is_character_camera
      ? utils::get_camera() : Unity::Camera::GetMain();
    
		if (camera == nullptr) return;

    camera->CallMethodSafe<void*>(
      "set_fieldOfView",
      this->fov_changer ? this->camera_FOV : this->default_FOV
    );
  }

  void draw_crosshair() {
    ImColor color = this->crosshair_color;
		if (this->rainbow_crosshair) {
			color = ImColor(global::Rainbow.x, global::Rainbow.y, global::Rainbow.z);
		}

    ImVec2 center = { global::viewport.Width / 2, global::viewport.Height / 2 };

    // Vertical
		ImGui::GetForegroundDrawList()->AddLine(
      ImVec2(center.x - this->crosshair_size, center.y),
      ImVec2(center.x + this->crosshair_size, center.y),
      color, 1.2f
    );

    // Horizontal
		ImGui::GetForegroundDrawList()->AddLine(
      ImVec2(center.x, center.y - this->crosshair_size),
      ImVec2(center.x, center.y + this->crosshair_size),
      color, 1.2f
    );
  }

  void draw_snaplines() {
    if (!this->player_snaplines) return;

    auto* camera = utils::get_camera();

    ImColor color = this->snapline_color;

    if (this->snapline_rainbow)
      color = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);

    ImVec2 center = { global::viewport.Width / 2, global::viewport.Height / 2 };
    Unity::Vector2 onscreen_pos { 0, 0 };

    global::players_mutex.lock();
    // ImGui::GetOverlayDrawList()->Clear();
    auto* drawlist = ImGui::GetBackgroundDrawList();
    for (auto& player : global::player_list) {
      if (!player.is_valid()) break;

      EntityManager char_mng = player.get_char_manager();
      auto root_pos = char_mng.get_obj()->GetTransform()->GetPosition();

      if (utils::world2screen(root_pos, camera, &onscreen_pos)) {
        drawlist->AddLine(ImVec2(center.x, center.y), ImVec2(onscreen_pos.x, onscreen_pos.y), color, 2.0f);
      }
    }
    global::players_mutex.unlock();

    // this->player_snaplines = false;
  }
};
