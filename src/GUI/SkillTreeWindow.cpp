#include "Window.h"
#include "cwsdk.h"
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"
#include "imgui_internal.h"
//#include <d3d11.h>
//#include <d3dcompiler.h>

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
bool StatButton(ID3D11ShaderResourceView* texture, ImVec2 size, int level, float spacing);

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
		/*
		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (availablePoints == 0 ? 0.5f : 1.0f));

		char buffer[250];
		sprintf(buffer, "Increase %s", STAT_NAMES[i]);
		if (ImGui::Button(buffer)) {
			if (availablePoints >= 1)
				this->skillTree->stats.IncreaseStat((StatType)i);
		}

		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::Text("Level: %d", this->skillTree->stats.GetStatLevel((StatType)i));
		*/
		int level = this->skillTree->stats.GetStatLevel((StatType)i);
		ImGui::PushID(STAT_NAMES[i]);
		//if (ImGui::StatButton(this->texture, ImVec2(32, 32), std::to_string(level).c_str()))
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		if (ImGui::StatButton(STAT_TEXTURES[i], ImVec2(32, 32), std::to_string(level).c_str()))
		{
			if (availablePoints >= 1)
				this->skillTree->stats.IncreaseStat((StatType)i);
		}
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(STAT_NAMES[i]);
			ImGui::EndTooltip();
		}
		ImGui::SameLine();
		if ((i + 1) % 5 == 0) {
			ImGui::NewLine();
		}
		ImGui::PopID();
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

	for (int i = 0; i < StatType::STAT_TYPE_END; i++)
	{
		this->my_image_width = 0;
		this->my_image_height = 0;
		//this->texture = NULL;
		char buffer[250];
		sprintf(buffer, "mods/classes/img/%s", STAT_TEXTURE_FILE_NAMES[i]);
		bool ret = LoadTextureFromFile(buffer, &STAT_TEXTURES[i], &my_image_width, &my_image_height);
		IM_ASSERT(ret);
	}
}

// Todo: Put text pos at a better place
bool StatButton(ID3D11ShaderResourceView* texture, ImVec2 size, int level, float spacing)
{
	ImVec2 beginPos = ImGui::GetCursorPos();

	bool val = ImGui::ImageButton((void*)texture, size);

	ImVec2 pos = ImVec2(beginPos.x + size.x / 2.0, beginPos.y + size.y / 2.0);

	ImGui::GetWindowDrawList()->AddText(pos, ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), std::to_string(level).c_str());

	return val;
}

void SkillTreeWindow::Render()
{
	int availablePoints = this->GetAvailablePoints();
	ImGui::Begin("Skills", &this->is_open, ImVec2(150, 100), -1.0);
	//StatButton(this->texture, ImVec2(32, 32), 10);
	ImGui::Text("Points: %d/%d", this->skillTree->GetUsedSkillPoints(), availablePoints);
	ImGui::SameLine();
	if (ImGui::Button("Reset Skill Tree"))
	{
		this->skillTree->Reset(game->GetPlayer());
	}

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

// Simple helper function to load an image into a DX11 texture with common settings
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	cube::GetID3D11Device()->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	cube::GetID3D11Device()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}