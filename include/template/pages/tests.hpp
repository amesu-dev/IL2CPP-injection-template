#pragma once
#include <template/pages/__general.hpp>

#include <vector>
#include <string>

#include <imgui/imgui.h>
#include <Il2cpp_Resolver/Unity/Includes.hpp>

#include "../utils/variables.hpp"
#include "../utils/utils.hpp"

//! Use `public` deriving for casting to `cheat_page`

class test_page : public cheat_page {
public:
  static inline const std::string name { "Dev Tests" };

  virtual void draw();
protected:
  // Put there your variables
  std::vector<Unity::il2cppClass*> m_vClasses;

  static inline const int ns_name_length = 128;
  char namespace_name[ns_name_length];
  char class_name[ns_name_length];

private:
  void test();

  void test_namespace();

  void test_address();

  void test_offset();
};
