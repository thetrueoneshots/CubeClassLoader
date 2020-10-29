#include "Window.h"
#include "cwsdk.h"
#include <string>

int SkillTreeWindow::GetAvailablePoints()
{
	int level = game->GetPlayer()->entity_data.level;
	int usedPoints = skillTree->GetUsedSkillPoints();
	return 4 + level - usedPoints;
}

SkillTreeWindow::SkillTreeWindow(SkillTree* skillTree, cube::Game* game)
{
	this->skillTree = skillTree;
	this->game = game;
}

void SkillTreeWindow::Render()
{
	int availablePoints = this->GetAvailablePoints();
	ImGui::Begin("Skill Tree Window", &this->is_open, ImVec2(150, 100), -1.0);
	ImGui::Text("Available SkillPoints: %d", availablePoints);
	for (int i = 0; i < StatType::STAT_TYPE_END; i++) {
		ImGui::Separator();
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (availablePoints == 0 ? 0.5f : 1.0f));

		if (ImGui::Button(STAT_NAMES[i])) {
			if (availablePoints >= 1)
				skillTree->stats.IncreaseStat((StatType)i);
		}
		
		ImGui::PopStyleVar();
		
		ImGui::LabelText(STAT_NAMES[i], "Level: %d", this->skillTree->stats.GetStatLevel((StatType)i));
	}
	ImGui::End();
	return;
}

bool SkillTreeWindow::IsOpen()
{
	return is_open;
}