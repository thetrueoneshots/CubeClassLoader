#include "Window.h"

#include "../classWindow.h"

MenuWindow::MenuWindow(ClassWindow* windowRenderer) {
	this->windowRenderer = windowRenderer;
}

void MenuWindow::Render()
{
	ImGui::Begin("Menu Window", nullptr, ImVec2(150, 100), -1.0);
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