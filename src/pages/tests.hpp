#pragma once
#include "__general.hpp"

#include <vector>
#include <string>

#include <imgui/imgui.h>
#include <Il2cpp_Resolver/Unity/Includes.hpp>

#include "./utils/variables.hpp"
#include "utils/utils.hpp"

//! Use `public` deriving for casting to `cheat_page`

class test_page : public cheat_page {
public:
  static inline const std::string name { "Dev Tests" };

  virtual void draw() {
    // ImGui::Checkbox("Start tests", &this->is_tests_allowed);
    if (ImGui::Button("Make test")) {
      this->test();
    }
    ImGui::InputText("Fetch namespace", this->namespace_name, this->ns_name_length);
  }

protected:
  // Put there your variables
  bool is_tests_allowed = false;

  std::vector<Unity::il2cppClass*> m_vClasses;

  static inline const int ns_name_length = 128;
  char namespace_name[ns_name_length];
  
private:
  void test() {
    // if (!this->is_tests_allowed) return;

    // IL2CPP::Class::FetchClasses(&this->m_vClasses, "Assembly-CSharp", namespace_name);
    // // printf("");
    // if (!m_vClasses.size()) printf("No classes found!\n");
    // else {
    //   printf("Objects!\n");
    //
    //   for (auto* game_class : m_vClasses) {
    //     auto *objs = Unity::Object::FindObjectsOfType<Unity::CGameObject>(IL2CPP::Class::GetSystemType(game_class));
    //
    //     if (!objs) {
    //       printf("Not found objects of %s\n", game_class->m_pName);
    //       continue;
    //     }
    //
    //     int count = 0;
    //     for(size_t index = 0; index < objs->m_uMaxLength; index += 1) {
    //       auto* obj = objs->At(index);
    //       if (!obj) break;
    //
    //       printf("There are obj %s at %p\n", obj->m_Object.m_pClass->m_pName, obj);
    //     }
    //   }
    // }


    auto* cameras = Unity::Object::FindObjectsOfType<Unity::CCamera>("UnityEngine.Camera");
    if (!cameras) return (void)printf("No cameras found!\n");
    for (size_t i = 0; i < cameras->m_uMaxLength; i += 1) {
      if(!cameras->At(i)) break;
      auto* camera = cameras->At(i);

      printf("FOV is %f\n", camera->GetFieldOfView());
      printf("Camera %lld at 0x%p (0x%p)\n", i, camera, camera->m_CachedPtr);
    }

    Unity::Vector3 root_pos {0,0,0};
    Unity::Vector3 pos {0,0,0};
    auto* camera = utils::get_camera();

    // utils::world2screen(root_pos, camera, pos);
    
    auto* ptr = IL2CPP::Class::Utils::GetMethodPointer("UnityEngine.Camera", "WorldToScreenPoint");
    printf("Pointer: 0x%p\n", ptr);

    printf("{ %f, %f, %f }\n", pos.x, pos.y, pos.z);

    printf("-------------------\n");
  }

};
