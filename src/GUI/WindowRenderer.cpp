#include "WindowRenderer.h"
#include <fstream>
#include <iostream>
#include <windows.h>

void SetImGUIColorScheme();
void DrawCursor(cube::Game* game);

WindowRenderer::WindowRenderer(std::vector<Class*>* vector, SkillTree* skillTree)
{
	this->classVector = vector;
	this->skillTree = skillTree;
}

void WindowRenderer::SetWindow(WindowType type) 
{
	switch (type)
	{
	case WindowType::CLASS_EDITOR:
		this->window = std::make_unique<ClassEditorWindow>(this->game, this->classVector);
		break;
	case WindowType::SKILL_TREE:
		this->window = std::make_unique<SkillTreeWindow>(this->skillTree, this->game);
		break;
	case WindowType::MENU:
	default:
		this->window = std::make_unique<MenuWindow>(this);
		break;
	}
	
}

void WindowRenderer::Present()
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

	// Todo: Check if this only needs to be called once
	SetImGUIColorScheme();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	wantMouse = io.WantCaptureMouse;
	wantKeyboard = io.WantCaptureKeyboard;
	io.Fonts->AddFontFromFileTTF("resource1.dat", 16.0f);
	io.DisplaySize = ImVec2((float)game->width, (float)game->height);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(game->width - 570, 20), ImGuiCond_Once);
	
	if (!this->window->IsOpen())
		SetWindow(WindowType::MENU);
	this->window->Render();
	
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// We just drew over the original cursor, so draw the cursor again on top of the gui
	DrawCursor(this->game);
}

bool WindowRenderer::Initialize()
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
int WindowRenderer::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

void WindowRenderer::OnGetKeyboardState(BYTE* diKeys)
{
	if (wantKeyboard) {
		memset(diKeys, 0, 256);
	}
}

void WindowRenderer::OnGetMouseState(DIMOUSESTATE* diMouse) 
{
	if (wantMouse) {
		diMouse->rgbButtons[0] = 0;
		diMouse->rgbButtons[1] = 0;
		diMouse->rgbButtons[2] = 0;
	}
}

void SetImGUIColorScheme() 
{
	//ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.10f, 0.15f, 0.95f);
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
	ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.10f, 0.15f, 0.95f);
	//ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.50f, 0.30f, 0.50f, 1.00f);
	//ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.30f, 0.15f, 0.30f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);

	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.60f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.30f, 0.60f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.35f, 0.75f, 1.00f);
	ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = ImVec4(0.70f, 0.60f, 0.90f, 1.00f);

	ImGui::GetStyle().Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImGui::GetStyle().Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	ImGui::GetStyle().PopupRounding = 10.0;
	//ImGui::GetStyle().WindowRounding = 10.0;
	ImGui::GetStyle().WindowRounding = 2.0;
	ImGui::GetStyle().FrameRounding = 4.0;
	ImGui::GetStyle().WindowBorderSize = 2.0;

	ImGui::GetStyle().AntiAliasedLines = false;

	ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.02, 0.5);
}

void DrawCursor(cube::Game* game)
{
	float guiScale = game->options.guiScale;
	FloatVector2 cursorPosition = game->plasma_engine->mouse_position;
	plasma::Matrix<float>* trans = &game->gui.cursor_node->transformation->matrix;
	plasma::Matrix<float> oldTrans = *trans;
	*trans = trans->scale(guiScale).translate(cursorPosition.x - (cursorPosition.x / guiScale), cursorPosition.y - (cursorPosition.y / guiScale), 0);

	game->gui.cursor_node->Draw(0);

	*trans = oldTrans;
}