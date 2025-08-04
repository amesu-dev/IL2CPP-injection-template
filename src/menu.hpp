#pragma once
#include <imgui/imgui.h>
#include <kiero/functions.h>
#include <kiero/Dumper.hpp>
#include <kiero/Lists.hpp>
using namespace ImGui;

#include <unordered_map>
#include "pages/__general.hpp"
extern std::unordered_map<std::string, cheat_page* const> pages;

void help_marker(const char* text);
void draw_inspector();  // IDK what it does
void set_theme();

// Main function
void draw_menu();

