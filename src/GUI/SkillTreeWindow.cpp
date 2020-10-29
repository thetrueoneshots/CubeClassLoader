#include "Window.h"
#include "cwsdk.h"
#include <string>

int SkillTreeWindow::GetAvailablePoints()
{
	int level = game->GetPlayer()->entity_data.level;
	int usedPoints = skillTree->GetUsedSkillPoints();
	return 4 + level - usedPoints;
}

void SkillTreeWindow::RenderUltimateSkills()
{
	int selectedUltimate = this->skillTree->ultimateSkills.GetSelectedSkill();
	int availablePoints = this->GetAvailablePoints();

	if (selectedUltimate == UltimateType::ULTIMATE_SKILL_TYPE_END)
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "ULTIMATE");
	}
	else
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "ULTIMATE: %s", ULTIMATE_NAMES[selectedUltimate]);
	}

	for (int i = 0; i < UltimateType::ULTIMATE_SKILL_TYPE_END; i++) {
		UltimateType type = (UltimateType)i;
		char buffer[250];

		ImGui::Separator();
		if (this->skillTree->ultimateSkills.IsSkillUnlocked(type))
		{
			if (i == selectedUltimate)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, SELECTED_BUTTON_COLOR);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, SELECTED_BUTTON_COLOR_ACTIVE);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, SELECTED_BUTTON_COLOR_HOVERED);

				sprintf(buffer, "Ultimate: %s", ULTIMATE_NAMES[i]);
				if (ImGui::Button(buffer)) {
					this->skillTree->ultimateSkills.SelectSkill(type);
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, UNLOCKED_BUTTON_COLOR);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, UNLOCKED_BUTTON_COLOR_ACTIVE);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, UNLOCKED_BUTTON_COLOR_HOVERED);

				sprintf(buffer, "Select Ultimate: %s", ULTIMATE_NAMES[i]);
				if (ImGui::Button(buffer)) {
					this->skillTree->ultimateSkills.SelectSkill(type);
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
		}
		else
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (availablePoints < ULTIMATE_COSTS[i] ? 0.5f : 1.0f));
			sprintf(buffer, "Unlock Ultimate: %s", ULTIMATE_NAMES[i]);
			if (ImGui::Button(buffer)) {
				if (availablePoints >= ULTIMATE_COSTS[i])
					this->skillTree->ultimateSkills.UnlockSkill(type, availablePoints);
			}
			ImGui::SameLine();
			ImGui::Text("Cost: %d", ULTIMATE_COSTS[i]);
			ImGui::PopStyleVar();
		}
	}
}

// Todo: Implement
void SkillTreeWindow::RenderShiftSkills()
{
	int selectedShiftSkill = this->skillTree->shiftSkills.GetSelectedSkill();
	int availablePoints = this->GetAvailablePoints();

	if (selectedShiftSkill == ShiftSkillType::SHIFT_SKILL_TYPE_END)
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "SHIFT SKILL");
	}
	else
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "SHIFT SKILL: %s", SHIFT_SKILL_NAMES[selectedShiftSkill]);
	}

	for (int i = 0; i < ShiftSkillType::SHIFT_SKILL_TYPE_END; i++) {
		ShiftSkillType type = (ShiftSkillType)i;
		char buffer[250];

		ImGui::Separator();
		if (this->skillTree->shiftSkills.IsSkillUnlocked(type))
		{
			if (i == selectedShiftSkill)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, SELECTED_BUTTON_COLOR);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, SELECTED_BUTTON_COLOR_ACTIVE);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, SELECTED_BUTTON_COLOR_HOVERED);

				sprintf(buffer, "Shift Skill: %s", SHIFT_SKILL_NAMES[i]);
				if (ImGui::Button(buffer)) {
					this->skillTree->shiftSkills.SelectSkill(type);
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, UNLOCKED_BUTTON_COLOR);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, UNLOCKED_BUTTON_COLOR_ACTIVE);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, UNLOCKED_BUTTON_COLOR_HOVERED);

				sprintf(buffer, "Select Shift Skill: %s", SHIFT_SKILL_NAMES[i]);
				if (ImGui::Button(buffer)) {
					this->skillTree->shiftSkills.SelectSkill(type);
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
		}
		else
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (availablePoints < SHIFT_SKILL_COSTS[i] ? 0.5f : 1.0f));
			sprintf(buffer, "Unlock Shift Skill: %s", SHIFT_SKILL_NAMES[i]);
			if (ImGui::Button(buffer)) {
				if (availablePoints >= SHIFT_SKILL_COSTS[i])
					this->skillTree->shiftSkills.UnlockSkill(type, availablePoints);
			}
			ImGui::SameLine();
			ImGui::Text("Cost: %d", SHIFT_SKILL_COSTS[i]);
			ImGui::PopStyleVar();
		}
	}
}

void SkillTreeWindow::RenderStats()
{
	int availablePoints = this->GetAvailablePoints();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "STATS");
	for (int i = 0; i < StatType::STAT_TYPE_END; i++) {
		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (availablePoints == 0 ? 0.5f : 1.0f));

		char buffer[250];
		sprintf(buffer, "Increase %s", STAT_NAMES[i]);
		if (ImGui::Button(buffer)) {
			if (availablePoints >= 1)
				skillTree->stats.IncreaseStat((StatType)i);
		}

		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::Text("Level: %d", this->skillTree->stats.GetStatLevel((StatType)i));
		//ImGui::LabelText(STAT_NAMES[i], "Level: %d", this->skillTree->stats.GetStatLevel((StatType)i));
	}
}

// Todo: Implement
void SkillTreeWindow::RenderPassives()
{
	return;
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
	ImGui::Text("Available SkillPoints: %d (Used: %d)", availablePoints, skillTree->GetUsedSkillPoints());

	this->RenderUltimateSkills();
	this->RenderShiftSkills();
	this->RenderStats();
	this->RenderPassives();
	
	ImGui::End();
	return;
}

bool SkillTreeWindow::IsOpen()
{
	return is_open;
}