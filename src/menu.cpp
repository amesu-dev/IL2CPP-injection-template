#include "menu.hpp"

#include <exception>

#include "pages/visual.hpp"
#include "pages/tests.hpp"

std::unordered_map<std::string, cheat_page* const> pages = std::unordered_map<std::string, cheat_page* const>({
	{ visual_page::name, new visual_page() },
	{ test_page::name, new test_page() }
});



void help_marker(const char* text) {
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(text);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void set_theme() {
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	ImGuiStyle& style = ImGui::GetStyle();
	//style.WindowPadding = ImVec2(8.00f, 8.00f);
	//style.FramePadding = ImVec2(5.00f, 2.00f);
	//style.CellPadding = ImVec2(6.00f, 6.00f);
	//style.ItemSpacing = ImVec2(6.00f, 6.00f);
	//style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	//style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	//style.FrameBorderSize = 1;
	style.WindowRounding = 4;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
}

void draw_inspector() {
	ImGui::SetNextWindowSize(ImVec2(600.000f, 1000.000f), ImGuiCond_Once);
	if (!ImGui::Begin("Inspector", nullptr, 2)) {
		ImGui::End();
		return;
	}

	static std::vector<std::string> components;
	static std::vector<std::string> classes;
	static std::vector<std::string> methods;
	static std::string current_comp = "";

	ImGui::Text("Components");
	if (ImGui::Button("Update##comp")) {
		components = Dumper::DumpComponentsString();
	}
	ImGui::SetNextItemWidth(150.000f);
	static int component_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter c_filter;
	c_filter.Draw("Search##compfilter");
	if (ImGui::BeginListBox("##Components", ImVec2(-FLT_MIN, 200))) {
		for (size_t n = 0; n < components.size(); n++) {
			if (!c_filter.PassFilter(components[n].c_str())) {
				continue;
			}
			const bool comp_is_selected = (component_current_idx == (int)n);
			if (ImGui::Selectable(components[n].c_str(), comp_is_selected))
				component_current_idx = (int)n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (comp_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}
	ImGui::Spacing();
	ImGui::Text("Classes");
	if (ImGui::Button("Update##class")) {
		classes = Dumper::DumpClassesString(components[component_current_idx]);
		current_comp = components[component_current_idx];
	}

	ImGui::SetNextItemWidth(150.000f);
	static int class_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter cl_filter;
	cl_filter.Draw("Search##classfilter");
	if (ImGui::BeginListBox("##Class", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < classes.size(); n++)
		{
			if (!cl_filter.PassFilter(classes[n].c_str())) {
				continue;
			}
			const bool class_is_selected = (class_current_idx == (int)n);
			if (ImGui::Selectable(classes[n].c_str(), class_is_selected)) {
				class_current_idx = (int)n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (class_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::Spacing();
	ImGui::Text("Methods");
	if (ImGui::Button("Update##Methods")) {
		methods = Dumper::DumpMethodsString(current_comp, classes[class_current_idx]);
	}

	ImGui::SetNextItemWidth(150.000f);
	static int method_current_idx = 0; // Here we store our selection data as an index.
	static ImGuiTextFilter me_filter;
	me_filter.Draw("Search##methodfilter");
	if (ImGui::BeginListBox("##Methods", ImVec2(-FLT_MIN, 200)))
	{
		for (size_t n = 0; n < methods.size(); n++)
		{
			if (!me_filter.PassFilter(methods[n].c_str())) {
				continue;
			}
			const bool meth_is_selected = (method_current_idx == (int)n);
			if (ImGui::Selectable(methods[n].c_str(), meth_is_selected))
				method_current_idx = (int)n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (meth_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}

static cheat_page* cur_page = (*pages.begin()).second; // get first page
void draw_menu() {
	set_theme();
	// draw_inspector();
	static int page = 0;

	// true - opened
	// false - colapsed
	bool result = ImGui::Begin(
		"[  Template  ]", nullptr,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings
	);

  if (!result) return (void)ImGui::End();

	// Set begin pos and size
	ImGui::SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(375, 400), ImGuiCond_Once);

	// Draw pages dynamicly
	for (const auto& [name, page_ptr] : pages) {
		ImGui::SameLine();
		if (ImGui::Button(name.c_str())) {
			cur_page = page_ptr;
		}
	}

	ImGui::Separator();

	if (cur_page) cur_page->draw();
	
	// 	ImGui::Checkbox("Aim", &vars::aimbot);
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Aimbot lol");

	// 	/*
	// 	ImGui::Checkbox("Silent Aim", &vars::silent_aim);
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Aimbot without moving camera");
	// 		*/

	// 	ImGui::Checkbox("Aim FOV", &vars::fov_check);
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Aim FOV Check");
	// 	if (vars::fov_check)
	// 	{
	// 		ImGui::SliderFloat("Aimbot FOV", &vars::aim_fov, 0, 1000.0f);
	// 		if (ImGui::IsItemHovered())
	// 			ImGui::SetTooltip("Circle FOV");
	// 	}
	// 	ImGui::SliderFloat("Aimbot Smoothing", &vars::smooth, 1, 10.0f);
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Humanized Aim");

		
	// 	ImGui::Combo("Aim Bone", &vars::boneselected, vars::bones, IM_ARRAYSIZE(vars::bones));
	// 	break;
	// case 2:
	// 	ImGui::Checkbox("##RecoilMulti", &vars::recoileditor);
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Enable");
	// 	ImGui::SameLine();
	// 	ImGui::SliderFloat("##recoilpower", &vars::recoiledited, 0.0f, 1000.0f, "Recoil: %.0f");
	// 	if (ImGui::IsItemHovered())
	// 		ImGui::SetTooltip("Edit your recoil!");			
	// 	break;
	// }
	
	ImGui::End();
}

