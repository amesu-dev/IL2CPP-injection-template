#include <template/pages/visual.hpp>

void visual_page::draw() {
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

void visual_page::change_fov() {
  if (!this->fov_changer) return;
  Unity::CCamera* camera = this->is_character_camera
    ? utils::get_camera() : Unity::Camera::GetMain();
  
  if (camera == nullptr) return;

  camera->CallMethodSafe<void*>(
    "set_fieldOfView",
    this->fov_changer ? this->camera_FOV : this->default_FOV
  );
}

void visual_page::draw_crosshair() {
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

void visual_page::draw_snaplines() {
  if (!this->player_snaplines) return;
  auto* camera = this->get_camera();

  ImColor color = this->snapline_color;

  // if (this->snapline_rainbow)
  //   color = ImColor(vars::Rainbow.x, vars::Rainbow.y, vars::Rainbow.z);

  ImVec2 center = { global::viewport.Width / 2, global::viewport.Height / 2 };
  Unity::Vector2 onscreen_pos { 0, 0 };
  
  auto* drawlist = ImGui::GetBackgroundDrawList();
  // global::players_mutex.lock();
  // // ImGui::GetOverlayDrawList()->Clear();
  // for (auto& player : global::player_list) {
  //   if (!player.is_valid()) break;

  //   EntityManager char_mng = player.get_char_manager();
  //   auto root_pos = char_mng.get_obj()->GetTransform()->GetPosition();
  //   printf("Pos { %f, %f, %f }\n", root_pos.x, root_pos.y, root_pos.z);
  //   Unity::Vector3 nroot_pos {0,0,0};

  //   if (utils::world2screen(nroot_pos, camera, &onscreen_pos)) {
  //     drawlist->AddLine(ImVec2(center.x, center.y), ImVec2(onscreen_pos.x, onscreen_pos.y), color, 2.0f);
  //   }
  // }
  // global::players_mutex.unlock();

  printf("Camera at 0x%p\n", camera);
  printf("Camera at 0x%p\n", Unity::Camera::GetMain());
  Unity::Vector3 root_pos { 0, 0, 0 };

  if (utils::world2screen(root_pos, Unity::Camera::GetMain(), &onscreen_pos)) {
    drawlist->AddLine(ImVec2(center.x, center.y), ImVec2(onscreen_pos.x, onscreen_pos.y), color, 2.0f);
  }
}

Unity::CCamera* visual_page::get_camera(bool is_main) {
  if (!this->main_camera) this->main_camera = Unity::Camera::GetMain();

  if (is_main) return this->main_camera;

  if (!this->camera) return this->camera = utils::get_camera();
  if (!this->camera) return this->camera = this->main_camera = Unity::Camera::GetMain();
  
  return nullptr;
}