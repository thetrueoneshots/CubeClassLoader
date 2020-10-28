#include "Window.h"

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