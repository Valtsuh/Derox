
#pragma comment(lib, "user32.lib")
#pragma execution_character_set("utf-8")
#pragma comment(linker, "/STACK:10000000") // 2MB(first increment), little bits crash?
#include <time.h>

#define DETOX
#define DETOX_DRAWN

 
// If gfx, incase of errors, remember to check project properties -> system -> subsystem -> windows(!console)
// Or pragmas windows/console

	// crashes / freezes
		// array variables
		// SINT / DINT (signed / unsinged), does not handle negative writes yet


#ifdef DETOX_DRAWN 
#pragma comment(linker, "/SUBSYSTEM:Windows")
#include <Windows.h>
#include "Engine.database.h"
#include "Engine.h"

#define DETOX_MAIN wWinMain

#ifndef UNICODE
#define UNICODE
#endif

HHOOK mh;
engine::ENGINE soft;
const wchar_t name[16] = L"Window class";
LRESULT CALLBACK MouseProc(int nCode, WPARAM w, LPARAM l) {
	return NULL;
};

void MP(HHOOK hook);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	soft.window._register(WindowProc, hInstance, name);
	soft.window._set(640, 480, 25, 25);
	soft._config();

	soft.sleep = ENGINE_DATABASE_FPS_SMOOTHER;
	soft.time._clock();
	soft.played = 1;
	thread(MP);

	while (soft._gather()) {
		soft._rest();
	}

	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return soft._caller(hwnd, uMsg, wParam, lParam);
}

void MP(HHOOK hook) {
	Sleep(1000);
	SetWindowsHook(WH_MOUSE, MouseProc);
}


#else
#pragma comment(linker, "/SUBSYSTEM:Console")
int main() {

	return 0;
}

#endif

