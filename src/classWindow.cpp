#include "classWindow.h"

ClassWindow::ClassWindow(std::vector<Class*>* vector)
{
	classVector = vector;
}

void ClassWindow::SelectClass(Class* classInstance) {
	selectedClass = classInstance;
	sprintf_s(className, 16, selectedClass->name->c_str());
	sprintf_s(specName1, 50, selectedClass->specializations[0]->name->c_str());
	sprintf_s(specName2, 50, selectedClass->specializations[1]->name->c_str());
}

void ClassWindow::Update() {
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

void ClassWindow::Present()
{
	if (!initialized) {
		if (!Initialize()) {
			return;
		}
	}

	if (!game->gui.esc_menu_displayed) {
		wantMouse = false;
		wantKeyboard = false;
		return;
	}

	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.10f, 0.15f, 0.95f);
	ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.10f, 0.15f, 0.95f);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.50f, 0.30f, 0.50f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.30f, 0.15f, 0.30f, 1.00f);

	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.60f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.30f, 0.60f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = ImVec4(0.70f, 0.60f, 0.90f, 1.00f);

	ImGui::GetStyle().PopupRounding = 10.0;
	ImGui::GetStyle().WindowRounding = 10.0;
	ImGui::GetStyle().FrameRounding = 4.0;

	ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.02, 0.5);


	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	wantMouse = io.WantCaptureMouse;
	wantKeyboard = io.WantCaptureKeyboard;
	io.Fonts->AddFontFromFileTTF("resource1.dat", 16.0f);

	ImGui_ImplDX11_NewFrame();
	io.DisplaySize = ImVec2((float)game->width, (float)game->height);
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	int width = 550;
	int height = 300;
	ImVec2 size(width, height);
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(ImVec2(game->width - (width + 20), 20), ImGuiCond_Once);

	// Todo: Implement saving of all classes to files.
	ImGui::Begin("Custom Class Window", nullptr, size, -1.0, ImGuiWindowFlags_MenuBar);
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
					game->PrintMessage(L"Error adding a new class\n", 255, 0, 0);
				}
			}
			if (ImGui::MenuItem("Save Classes", "Saves all custom classes")) { 
				/* Do stuff */ 
				game->PrintMessage(L"Saving a class is not yet implemented... \n");
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

		Update();
	}
	
	ImGui::Separator();
	ImGui::Separator();

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "All Custom Classes");

	ImGui::Separator();
	ImGui::Separator();

	ImGui::BeginChild("Scrolling", ImVec2(300, 100), false, 0);
	for (int i = 0; i < classVector->size(); i++) {
		std::string name = *classVector->at(i)->name;
		ImGui::Text("Class: %s", name.c_str());
		std::string label = "Edit " + name + "(id: " + std::to_string(classVector->at(i)->id) + ")" ;
		if (ImGui::Button(label.c_str())) {
			SelectClass(classVector->at(i));
		}
		ImGui::Separator();
	}
	ImGui::EndChild();

	ImGui::Separator();

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// We just drew over the original cursor, so draw the cursor again on top of the gui
	float guiScale = game->options.guiScale;
	FloatVector2 cursorPosition = game->plasma_engine->mouse_position;
	plasma::Matrix<float>* trans = &game->gui.cursor_node->transformation->matrix;
	plasma::Matrix<float> oldTrans = *trans;
	*trans = trans->scale(guiScale).translate(cursorPosition.x - (cursorPosition.x / guiScale), cursorPosition.y - (cursorPosition.y / guiScale), 0);

	game->gui.cursor_node->Draw(0);

	*trans = oldTrans;
}

bool ClassWindow::Initialize()
{
	// If the user does not have the window active when it starts,
	// then getting the hwnd will fail
	HWND hWnd = GetActiveWindow();
	if (!hWnd) return false;
	game = cube::GetGame();
	initialized = true;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(cube::GetID3D11Device(), cube::GetID3D11DeviceContext());
	return true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int ClassWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	if (wantMouse) {
		switch (msg) {
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			return 1;
		}
	}
	if (wantKeyboard) return 1;

	// It's hacky that we have to handle this in two different places,
	// but the game uses both WindowProc and DInput :/
	if (awaitingKeyRemap && keyRemapComplete) {
		awaitingKeyRemap = false;
		keyRemapComplete = false;
		return 1;
	}

	return 0;
}

void ClassWindow::OnGetKeyboardState(BYTE* diKeys)
{
	if (wantKeyboard) {
		memset(diKeys, 0, 256);
	}
}

void ClassWindow::OnGetMouseState(DIMOUSESTATE* diMouse) 
{
	if (wantMouse) {
		diMouse->rgbButtons[0] = 0;
		diMouse->rgbButtons[1] = 0;
		diMouse->rgbButtons[2] = 0;
	}
}