#include "Window.h"

/*void ClassWindow::PresentSkillTree() {
	ImVec2 size(550, 300);
	ImGui::Begin("Skill Tree", nullptr, size, -1.0);
	std::string label = std::string("Available skill points: ").append(std::to_string(game->GetPlayer()->entity_data.level + 3));
	ImGui::Text(label.c_str());
	ImGui::Separator();
	ImGui::Separator();
	for (int i = 0; i < selectedClass->skillTree.GetSize(); i++) {
		if (selectedClass->skillTree.GetSelectedSkill() == selectedClass->skillTree.GetSkillType(i)) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.30f, 0.60f, 1.00f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.35f, 0.75f, 1.00f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.35f, 0.75f, 1.00f));
			if (ImGui::Button(std::to_string(selectedClass->skillTree.GetSkillType(i)).c_str())) {
				selectedClass->skillTree.SelectSkill(-1);
			}
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		else if (ImGui::Button(std::to_string(selectedClass->skillTree.GetSkillType(i)).c_str())) {
			game->PrintMessage(L"Selected skill\n");
			selectedClass->skillTree.SelectSkill(i);
		}
	}
	ImGui::End();
}*/

SkillTreeWindow::SkillTreeWindow(SkillTree* skillTree) 
{
	this->skillTree = skillTree;
}

void SkillTreeWindow::Render()
{
	ImGui::Begin("Skill Tree Window", &this->is_open, ImVec2(150, 100), -1.0);
	for (int i = 0; i < StatType::STAT_TYPE_END; i++) {
		if (ImGui::Button(STAT_NAMES[i])) {
			skillTree->stats.IncreaseStat((StatType) i);
		}
	}
	ImGui::End();
	return;
}

bool SkillTreeWindow::IsOpen()
{
	return is_open;
}