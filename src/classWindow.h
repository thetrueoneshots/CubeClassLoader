#pragma once
#include "../cwmods/cwsdk.h"
#include "../imgui-1.73/imgui.h"
#include "../imgui-1.73/examples/imgui_impl_dx11.h"
#include "../imgui-1.73/examples/imgui_impl_win32.h"
#include "class.h"
//#include "public.h"

class ClassWindow {
	// Todo: Rewrite these to flags
	bool initialized = false;
	bool wantMouse = false;
	bool wantKeyboard = false;
	bool awaitingKeyRemap = false;
	bool keyRemapComplete = false;

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
	
	bool show_skill_tree;

	cube::Game* game;
	void SelectClass(Class* classInstance);
	void Update();
	void SaveClasses();
	void PresentSkillTree();
public:
	ClassWindow(std::vector<Class*>* vector);
	void Present();
	bool Initialize();
	int WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnGetKeyboardState(BYTE* diKeys);
	void OnGetMouseState(DIMOUSESTATE* diMouse);
};
