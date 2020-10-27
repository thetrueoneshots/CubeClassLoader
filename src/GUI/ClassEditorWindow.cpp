#include "Window.h"
#include "../class.h"
#include "cwsdk.h"
#include <fstream>

ClassEditorWindow::ClassEditorWindow(cube::Game* game, std::vector<Class*>* classVector) {
	this->game = game;
	this->classVector = classVector;
}

void ClassEditorWindow::Render()
{
	ImGui::Begin("Class Editor Window", &this->is_open, ImVec2(550, 300), -1.0, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Add Class", "Creates a new custom class")) {
				Class* classInstance = new Class();
				if (classInstance != nullptr) {
					SelectClass(classInstance);
					classInstance->id = GetUniqueClassId(*classVector);
					classVector->push_back(classInstance);
				}
				else {
					game->PrintMessage(L"Error adding a new class\n", (unsigned char)255, 0, 0);
				}
			}
			if (ImGui::MenuItem("Save Classes", "Saves all custom classes")) {
				SaveClasses();
				game->PrintMessage(L"Saved all custom classes. \n", 0, (unsigned char)255, 0);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (selectedClass != nullptr) {
		ImGui::Separator();
		ImGui::Separator();

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Selected Class");

		ImGui::Separator();
		ImGui::Separator();

		ImGui::InputText("Name", className, IM_ARRAYSIZE(className));
		ImGui::InputInt("Item Class", &selectedClass->itemClass, 1, 1);

		ImGui::Separator();
		ImGui::Text("Specialization 1");

		ImGui::InputText("Spec 1 Name", specName1, IM_ARRAYSIZE(specName1));
		ImGui::InputInt("Spec 1 R", &selectedClass->specializations[0]->rAbility, 1, 10);
		ImGui::InputInt("Spec 1 CDR (in ms)", &selectedClass->specializations[0]->cooldown, 100, 1000);
		ImGui::InputInt("Spec 1 Shift", &selectedClass->specializations[0]->shiftAbility, 1, 1);

		ImGui::Separator();
		ImGui::Text("Specialization 2");

		ImGui::InputText("Spec 2 name", specName2, IM_ARRAYSIZE(specName1));
		ImGui::InputInt("Spec 2 R", &selectedClass->specializations[1]->rAbility, 1, 10);
		ImGui::InputInt("Spec 2 CDR (in ms)", &selectedClass->specializations[1]->cooldown, 100, 1000);
		ImGui::InputInt("Spec 2 Shift", &selectedClass->specializations[1]->shiftAbility, 1, 1);

		if (ImGui::Button("Skill Tree")) {
			//show_skill_tree = !show_skill_tree;
		}

		Update();
	}
	else {
		//show_skill_tree = false;
	}

	/*
	if (show_skill_tree) {
		//PresentSkillTree();
	}*/

	ImGui::Separator();
	ImGui::Separator();

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "All Custom Classes");

	ImGui::Separator();
	ImGui::Separator();

	for (int i = 0; i < classVector->size(); i++) {
		std::string name = *classVector->at(i)->name;
		ImGui::Text("Class: %s", name.c_str());
		std::string nameLbl = name + "(id: " + std::to_string(classVector->at(i)->id) + ")";
		std::string labelEdit = "Edit " + nameLbl;
		std::string labelDelete = "Delete " + nameLbl;
		if (ImGui::Button(labelEdit.c_str())) {
			SelectClass(classVector->at(i));
		}
		ImGui::SameLine(10 * labelEdit.size() - 10);
		if (ImGui::Button(labelDelete.c_str())) {
			if (selectedClass == classVector->at(i)) {
				selectedClass = nullptr;
			}
			delete classVector->at(i);
			classVector->erase(classVector->begin() + i);
		}

		ImGui::Separator();
	}

	ImGui::Separator();

	ImGui::End();
	return;
}

bool ClassEditorWindow::IsOpen()
{
	return this->is_open;
}

void ClassEditorWindow::SelectClass(Class* classInstance) {
	selectedClass = classInstance;
	//show_skill_tree = false;
	sprintf_s(className, 16, selectedClass->name->c_str());
	sprintf_s(specName1, 50, selectedClass->specializations[0]->name->c_str());
	sprintf_s(specName2, 50, selectedClass->specializations[1]->name->c_str());
}

void ClassEditorWindow::Update() {
	// Update Class*
	selectedClass->name->replace(0, strlen(className) + 1, className);
	selectedClass->specializations[0]->name->replace(0, strlen(specName1) + 1, specName1);
	selectedClass->specializations[1]->name->replace(0, strlen(specName2) + 1, specName2);

	// Update speech map
	std::pair<uint32_t, uint32_t> def(4 + selectedClass->id, 0);

	std::string* spec = selectedClass->specializations[0]->name;
	std::wstring specName(spec->begin(), spec->end());
	game->speech.specialization_type_id_map.insert_or_assign(def, specName);

	def.second = 1;
	spec = selectedClass->specializations[1]->name;
	specName = std::wstring(spec->begin(), spec->end());
	game->speech.specialization_type_id_map.insert_or_assign(def, specName);
}

void ClassEditorWindow::SaveClasses() {
	char fileName[256] = { 0 };
	const char* folderName = "Mods\\Classes";

	CreateDirectory(folderName, NULL);

	//File for this Zone
	sprintf(fileName, "%s\\save.cwb", folderName);
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);


	//Write each block to file
	for (Class* classInstance : *classVector) {
		const char* name = classInstance->name->c_str();
		const char* spec1Name = classInstance->specializations[0]->name->c_str();
		const char* spec2Name = classInstance->specializations[1]->name->c_str();
		file.write((char*)classInstance, sizeof(*classInstance));
		file.write((char*)name, strlen(name) + 1);
		file.write((char*)classInstance->specializations[0], sizeof(*classInstance->specializations[0]));
		file.write((char*)spec1Name, strlen(spec1Name) + 1);
		file.write((char*)classInstance->specializations[1], sizeof(*classInstance->specializations[1]));
		file.write((char*)spec2Name, strlen(spec2Name) + 1);
	}
	file.close();
}