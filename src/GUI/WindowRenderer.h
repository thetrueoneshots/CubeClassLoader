#pragma once
#include "cwsdk.h"
#include "../../imgui-1.73/imgui.h"
#include "../../imgui-1.73/examples/imgui_impl_dx11.h"
#include "../../imgui-1.73/examples/imgui_impl_win32.h"
#include "../class.h"
#include "Window.h"
//#include "public.h"

class WindowRenderer {
	// Todo: Rewrite these to flags
	bool initialized = false;
	bool wantMouse = false;
	bool wantKeyboard = false;
	bool awaitingKeyRemap = false;
	bool keyRemapComplete = false;

	std::unique_ptr<Window> window = std::make_unique<MenuWindow>(this);
	cube::Game* game;
	std::vector<Class*>* classVector;
public:
	WindowRenderer(std::vector<Class*>* vector);
	void Present();
	bool Initialize();
	int WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnGetKeyboardState(BYTE* diKeys);
	void OnGetMouseState(DIMOUSESTATE* diMouse);


	void SetWindow(WindowType type);
};
