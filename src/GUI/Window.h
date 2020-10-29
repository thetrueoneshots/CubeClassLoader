#pragma once
#include <vector>
#include "../imgui-1.73/imgui.h"
#include "../imgui-1.73/examples/imgui_impl_dx11.h"
#include "../imgui-1.73/examples/imgui_impl_win32.h"
#include "../skilltree/SkillTree.h"

class Class;
class WindowRenderer;

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

static ImVec4 SELECTED_BUTTON_COLOR = ImVec4(0.50f, 0.0f, 0.60f, 1.00f);
static ImVec4 SELECTED_BUTTON_COLOR_ACTIVE = ImVec4(0.70f, 0.0f, 0.80f, 1.00f);
static ImVec4 SELECTED_BUTTON_COLOR_HOVERED = ImVec4(0.70f, 0.0f, 0.80f, 1.00f);

static ImVec4 UNLOCKED_BUTTON_COLOR = ImVec4(0.40f, 0.20f, 0.50f, 1.00f);
static ImVec4 UNLOCKED_BUTTON_COLOR_ACTIVE = ImVec4(0.60f, 0.30f, 0.60f, 1.00f);
static ImVec4 UNLOCKED_BUTTON_COLOR_HOVERED = ImVec4(0.60f, 0.30f, 0.60f, 1.00f);

class Window 
{
public:
	virtual void Render() 
	{
		ImGui::Begin("Window", nullptr, ImVec2(100, 100), -1.0, 0);
		ImGui::Text("This is the standard window");
		ImGui::End();
		return;
	}
	virtual bool IsOpen() 
	{
		return true;
	}
};

class MenuWindow : public Window
{
private:
	WindowRenderer* windowRenderer;
public:
	MenuWindow(WindowRenderer* windowRenderer);
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

	// Todo: Move this to a ClassEditorState class.
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
	SkillTree* skillTree;
	cube::Game* game;
	
	int GetAvailablePoints();
	void RenderUltimateSkills();
	void RenderShiftSkills();
	void RenderStats();
	void RenderPassives();
public:
	SkillTreeWindow(SkillTree* skillTree, cube::Game* game);
	void Render() override;
	bool IsOpen() override;
};

