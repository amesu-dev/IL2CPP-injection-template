#pragma once
#include <string>

//! Use `public` deriving for casting to `cheat_page`

class cheat_page {
public:
  static inline const std::string name { "__general" };

  virtual void draw() = 0;
protected:
  // Put there your variables
};
