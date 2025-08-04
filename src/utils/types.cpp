#include "./types.hpp"


using namespace IL2CPP;
using namespace IL2CPP::Class::Utils;
// Little macros for boilerplate
#define GET_WITH_OFFSET(ptr, offset) ( *(void**)((char*)(ptr) + (offset)) )

// ------------------------------------------
// Class PlayerManager

// Define this here for optimize memory space
//! Only for using in class PlayerManager !
namespace PlayerManager_util {
  bool is_initialized = false;

  namespace ptr {
    std::function<void*(void*)> GetCurrentAuthViewTarget_ptr;
    std::function<void*(void*)> GetFollowTarget_ptr;
    std::function<char*(void*, bool)> GetPlayerName_ptr;
  }

  namespace offset {
    int followTargetOverride = -1;
    int primaryCharManager = -1;
  }
}

PlayerManager::PlayerManager(void* ptr): Base(ptr) {
  if(!ptr) return;
  if(PlayerManager_util::is_initialized) return;

  PlayerManager_util::ptr::GetCurrentAuthViewTarget_ptr = (void*(*)(void*)) ResolveCall("BAPBAP.Entities.PlayerManager::GetCurrentAuthViewTarget");
  PlayerManager_util::ptr::GetFollowTarget_ptr = (void*(*)(void*)) ResolveCall("BAPBAP.Entities.PlayerManager::GetCurrentAuthViewTarget");
  PlayerManager_util::ptr::GetPlayerName_ptr = (char*(*)(void*, bool)) ResolveCall("BAPBAP.Entities.PlayerManager::GetPlayerName");

  PlayerManager_util::offset::followTargetOverride = GetFieldOffset("BAPBAP.Player.PlayerManager", "followTargetOverride");
  PlayerManager_util::offset::primaryCharManager = GetFieldOffset("BAPBAP.Player.PlayerManager", "primaryCharManager");

  PlayerManager_util::is_initialized = true;
}

Unity::CTransform* PlayerManager::GetCurrentAuthViewTarget() {
  return reinterpret_cast<Unity::CTransform*>(PlayerManager_util::ptr::GetCurrentAuthViewTarget_ptr(this->ptr));
}

Unity::CTransform* PlayerManager::GetFollowTarget() {
  return reinterpret_cast<Unity::CTransform*>(PlayerManager_util::ptr::GetFollowTarget_ptr(this->ptr));
}

std::string PlayerManager::GetPlayerName(bool anonymousEnemies) {
  return PlayerManager_util::ptr::GetPlayerName_ptr(this->ptr, anonymousEnemies);
}

void* PlayerManager::get_follow_target() {
  return GET_WITH_OFFSET(
    this->ptr, PlayerManager_util::offset::followTargetOverride
  );
}
EntityManager PlayerManager::get_char_manager() {
  return GET_WITH_OFFSET(
    this->ptr, PlayerManager_util::offset::primaryCharManager
  );;
}

// ------------------------------------------
// Class CameraController
namespace CameraController_util {
  bool is_initialized = false;

  namespace ptr {
  }

  namespace offset {
    uint32_t cam = -1;
    uint32_t currentDriver = -1;
  }
}

CameraController::CameraController(void* ptr): Base(ptr) {
  if(CameraController_util::is_initialized) return;
  CameraController_util::offset::cam = GetFieldOffset("BAPBAP.Local.CameraController", "cam");
  
  // Werid thing...
  // CameraController_util::offset::Cam = GetFieldOffset("BAPBAP.Local.CameraController", "Cam");
  
  CameraController_util::offset::currentDriver = GetFieldOffset("BAPBAP.Local.CameraController", "currentDriver");

  CameraController_util::is_initialized = true;
}

Unity::CCamera* CameraController::get_camera() {
  return (Unity::CCamera*)GET_WITH_OFFSET(this->ptr, CameraController_util::offset::cam); // Offset to Camera pointer
}

// ------------------------------------------
// Class CameraController
namespace EntityManager_util {
  bool is_initialized = false;

  namespace ptr {
  }

  namespace offset {
    uint32_t playerObj = -1;
    uint32_t isPlayer = -1;
  }
}

EntityManager::EntityManager(void* ptr): Base(ptr) {
  if(EntityManager_util::is_initialized) return;

  EntityManager_util::offset::playerObj = GetFieldOffset("BAPBAP.Entities.EntityManager", "playerObj");
  EntityManager_util::offset::isPlayer = GetFieldOffset("BAPBAP.Entities.EntityManager", "isPlayer");

  EntityManager_util::is_initialized = true;
}

Unity::CGameObject* EntityManager::get_obj() {
  return (Unity::CGameObject*) GET_WITH_OFFSET(
    this->ptr, EntityManager_util::offset::playerObj
  );
}
bool EntityManager::is_player() {
  return (bool) GET_WITH_OFFSET(
    this->ptr, EntityManager_util::offset::isPlayer
  );
};

// ------------------------------------------
