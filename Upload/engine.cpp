#define DEROX_DRAWN

#include <Windows.h>
#include "engine.h"
#ifdef DEROX_DRAWN

#pragma comment(linker, "/STACK:30000000")

#pragma comment(linker, "/SUBSYSTEM:Windows")

drx1::ENGINE engine;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t name[16] = L"Window class";
	engine.window._register(WindowProc, hInstance, name);
	engine.window._set(640, 480, 25, 25);
	engine._config();
	MSG msg = {};
	while (engine.window.handle != NULL && engine.game._play()) {
		if (PeekMessage(&msg, engine.window.handle, 0, 0, PM_REMOVE) != -1) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		RedrawWindow(engine.window.handle, NULL, NULL, WM_NCPAINT);
	}
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	return engine._caller(hwnd, uMsg, wParam, lParam);
}

#else

#pragma comment(linker, "/SUBSYSTEM:Console")

#include <iostream>

using namespace std;


int main() {


	std::cout << "hello";
	return 0;
}

#endif