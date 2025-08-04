#pragma once
#include <functional>
#include <Il2cpp_Resolver/Includes.hpp>

class EntityManager;
class CameraController;
class PlayerManager;

class Base {
protected:
  void* ptr = nullptr;

public:
  Base(void* ptr): ptr(ptr) {};

  inline bool is_valid() { return (bool)this->ptr; };
};

class PlayerManager : public Base {
public:
  PlayerManager(void* ptr = nullptr);

  Unity::CTransform* GetCurrentAuthViewTarget();
  Unity::CTransform* GetFollowTarget();
  std::string GetPlayerName(bool anonymousEnemies = false);

  void* get_follow_target();
  EntityManager get_char_manager();
};


class CameraController : public Base {
public:
  CameraController(void* ptr = nullptr);

  Unity::CCamera* get_camera();
};

class EntityManager : public Base {
public:
  EntityManager(void* ptr = nullptr);

  Unity::CGameObject* get_obj();
  bool is_player();
};
