#include "Window.h"
#include "WindowRenderer.h"

MenuWindow::MenuWindow(WindowRenderer* windowRenderer) {
	this->windowRenderer = windowRenderer;
}

void MenuWindow::Render()
{
	ImGui::Begin("Menu Window", nullptr, ImVec2(150, 100), -1.0);
	// Todo: Disable skill tree if there is no skill tree for the character
	if (ImGui::Button("Skill Tree")) {
		windowRenderer->SetWindow(WindowType::SKILL_TREE);
	}
	if (ImGui::Button("Class Editor")) {
		windowRenderer->SetWindow(WindowType::CLASS_EDITOR);
	}
	ImGui::End();
	return;
}

bool MenuWindow::IsOpen() 
{
	return true;
}