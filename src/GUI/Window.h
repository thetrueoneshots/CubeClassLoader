#pragma once
#include <vector>
#include "../imgui-1.73/imgui.h"
#include "../imgui-1.73/examples/imgui_impl_dx11.h"
#include "../imgui-1.73/examples/imgui_impl_win32.h"

class Class;
class ClassWindow;
namespace cube
{
	class Game;
}


enum WindowType 
{
	MENU,
	SKILL_TREE,
	CLASS_EDITOR,
};

class Window 
{
public:
	virtual void Render() {
		ImGui::Begin("Window", nullptr, ImVec2(100, 100), -1.0, 0);
		ImGui::Text("This is the standard window");
		ImGui::End();
		return;
	}
	virtual bool IsOpen() {
		return true;
	}
};

class MenuWindow : public Window
{
private:
	ClassWindow* windowRenderer;
public:
	MenuWindow(ClassWindow* windowRenderer);
	void Render() override;
	bool IsOpen() override;
};

class ClassEditorWindow : public Window
{
private:
	bool is_open = true;

	cube::Game* game;
	Class* selectedClass = nullptr;
	std::vector<Class*>* classVector;

	char className[16];
	int itemClass;

	char specName1[50];
	int specR1;
	int specShift1;
	int specCooldown1;

	char specName2[50];
	int specR2;
	int specShift2;
	int specCooldown2;
	void SelectClass(Class* classInstance);
	void Update();
	void SaveClasses();
public:
	ClassEditorWindow(cube::Game*, std::vector<Class*>* classVector);
	void Render() override;
	bool IsOpen() override;
};

class SkillTreeWindow : public Window
{
	bool is_open;
public:
	SkillTreeWindow();
	void Render() override;
	bool IsOpen() override;
};

