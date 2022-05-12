//#pragma comment(linker, "/STACK:2000000")
//#pragma comment(linker, "/HEAP:10000000")
#pragma comment(linker, "/SUBSYSTEM:Windows")

#define DEROX_DRAWN
#include <Windows.h>
#include <thread>
#include "engine.h"
#ifdef DEROX_DRAWN


drx1::ENGINE engine;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{	
	const wchar_t name[16] = L"Window class";
	engine.window._register(WindowProc, hInstance, name);
	engine.window._set(640, 480, 25, 25);
	engine._config();
	do {
		engine.game._play();
		//engine.time._clock();
		/*
		if (PeekMessage(&msg, engine.window.handle, 0, 0, PM_REMOVE) != -1) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		*/
		RedrawWindow(engine.window.handle, NULL, NULL, WM_NCPAINT);

		if(PeekMessage(&engine.window.msg, engine.window.handle, 0, 0, PM_REMOVE) != -1) {
			TranslateMessage(&engine.window.msg);
			DispatchMessage(&engine.window.msg);

		}
		DINT s = 0;
		if (ENGINE_MODE_SLEEP == 0) {
			if (engine.game.statistics.fps.current > 60) {
				s = engine.game.statistics.fps.current - 60;
			}

		}
		else {
			s = ENGINE_MODE_SLEEP;
		}
		Sleep(s);

		
	} while (engine.window.handle && engine.game.played);

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