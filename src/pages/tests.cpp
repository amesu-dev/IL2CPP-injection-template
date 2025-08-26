#include <template/pages/tests.hpp>

void test_page::draw() {
    // ImGui::Checkbox("Start tests", &this->is_tests_allowed);
    if (ImGui::Button("Make general")) {
      this->test();
    }
    
    ImGui::Separator();
    
    ImGui::BeginGroup();
    ImGui::InputText("Module", this->module_name, this->ns_name_length);
    ImGui::InputText("Namespace", this->namespace_name, this->ns_name_length);

    if (ImGui::Button("Make test namespace")) {
      this->test_namespace();
    }
    
    ImGui::Separator();
    
    ImGui::InputText("Class name", this->class_name, this->ns_name_length);
    ImGui::InputText("Function name", this->function_name, this->ns_name_length);
    
    if (ImGui::Button("Make check all obj addresses")) {
      this->test_address();
    }
    
    // ImGui::SameLine(0, 12);
    
    if (ImGui::Button("Fetch all fields in class")) {
      this->test_offset();
    }
    if (ImGui::Button("Fetch function address")) {
      this->test_function_address();
    }
    ImGui::EndGroup();
}

void test_page::test() {
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

void test_page::test_namespace() {
  // if (!) return;
  IL2CPP::Class::FetchClasses(&this->m_vClasses, this->module_name, namespace_name);

  if (!m_vClasses.size()) printf("No classes found!\n");
  else {
    printf("Objects!\n");
  
    for (auto* game_class : m_vClasses) {
      auto *objs = Unity::Object::FindObjectsOfType<Unity::CGameObject>(IL2CPP::Class::GetSystemType(game_class));
  
      if (!objs) {
        printf("Not found objects of %s\n", game_class->m_pName);
        continue;
      }
  
      int count = 0;
      for(size_t index = 0; index < objs->m_uMaxLength; index += 1) {
        auto* obj = objs->At(index);
        if (!obj) break;
  
        printf("There are obj %s at %p\n", obj->m_Object.m_pClass->m_pName, obj);
      }
    }
  }
}

void test_page::test_address() {
  auto* objects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(IL2CPP::Class::GetSystemType(this->class_name));
  if (!objects || !objects->m_uMaxLength) return (void)printf("No objects of class '%s' found\n", this->class_name);

  for (size_t index = 0; index < objects->m_uMaxLength; index += 1) {
    if (!objects->At(index)) break;
    printf("Object of %s at %p\n", this->class_name, objects->At(index));
  }
}

void test_page::test_offset() {
  auto* game_class = IL2CPP::Class::Find(this->class_name);
  if (!game_class) return (void)printf("No class '%s' found\n", this->class_name);
  std::vector<Unity::il2cppFieldInfo *> fields;
  IL2CPP::Class::FetchFields(game_class, &fields);

  printf("------------------------------------------\n");
  printf("Class '%s' fields:\n", this->class_name);
  for (auto* field : fields) {
    printf("%s (0x%x)\n", field->m_pName, field->m_iOffset); // Field (0x00)
  }
  printf("------------------------------------------\n");
}

void test_page::test_function_address() {
  void* func = IL2CPP::ResolveCall(this->function_name);
  if (!func) return (void) printf("Function '%s' not found\n", this->function_name);
  
  printf("Function '%s' at 0x%p\n", this->function_name, func);
}

