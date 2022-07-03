//#pragma comment(linker, "/STACK:2000000")
//#pragma comment(linker, "/HEAP:10000000")
#pragma comment(linker, "/SUBSYSTEM:Windows")

#define DEROX_DRAWN
#include <Windows.h>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <fstream>
#include "engine.h"
drx1::ENGINE engine = {};
LRESULT CALLBACK _caller(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK _caller(HWND window, UINT msg, WPARAM w, LPARAM l)
{
	//if (window != engine.window.handle) return DefWindowProc(window, msg, w, l);
	switch (msg) {
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY:
		engine._end();
		break;
	case WM_NCCREATE:
	case WM_CREATE:
		return DefWindowProc(window, msg, w, l);
		/*
	case WM_NCMOUSEMOVE:
	case WM_MOUSEHOVER:
	case WM_NCMOUSEHOVER:
	case WM_MOUSELEAVE:
	case WM_NCMOUSELEAVE:
	case WM_MOUSEACTIVATE:
		return DefWindowProc(window, msg, w, l);
	case WM_KEYUP:
	case WM_KEYDOWN:
	case WM_NCPAINT:
	case WM_PAINT:
	*/
	default:
		return DefWindowProc(window, msg, w, l);
	case WM_KEYUP:

		if (w == VK_NUMPAD1) {
			//engine.game.doll._test();
			engine.rand._roll(0, 3);
			std::cout << "\n" << engine.rand.value.i;
		}
		if (w == VK_NUMPAD2) {

		}
		if (w == VK_NUMPAD5) {
			if (engine.delay == 0) {
				engine.delay = ENGINE_MODE_SLEEP;
			}
			else {
				engine.delay = 0;
			}
		}

		if (w == VK_ESCAPE) {
			engine._end();
		}

		if (w == VK_NUMPAD0) {
			drx1::ENGINE::DUSSCAL a;
			a = ENGINE_MAP_TEST;

			for (DINT i = 0; i < a.shape.pixels.size; i++) {
				PIXEL p = a.shape.pixels[i];
				std::cout << "\n> " << p.exist << ": " << p.x << ", " << p.y;
				std::cout << "(" << p.color.r << ", " << p.color.g << ", " << p.color.b << ")";
			}


		}

		if (w == VK_SPACE) {
			CHART<BINT> bints;
			TIME time;
			DINT f = engine.rand._roll(0, 9999);
			std::cout << "\nClocking " << f;
			time._clock();
			for (DINT b = 0; b < f; b++) {
				bints << (BINT)f;
			}
			std::cout << "\n" << time._difference(time) << "ms";
			engine.game.doll._drop();
		}
	case WM_KEYDOWN:
	case ENGINE_DRAW:
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
	case WM_NCMOUSELEAVE:
	case WM_PAINT: {

		engine.writer.drawer._begin(window);
		engine.writer.drawer._bkgd(engine.window.handle, LGR);
		engine.writer.drawer._rect(engine.game.atlas.measure.x, engine.game.atlas.measure.y, engine.game.atlas.measure.w, engine.game.atlas.measure.h, engine.game.atlas.bg);
		DINT wi = LOWORD(w);
		DINT li = LOWORD(l);
		engine._paint(msg, wi, li);
		//engine._screen();
		engine.writer.drawer._end(window);
		return DefWindowProc(window, msg, w, l);
	}
	}
	return 0;
}
void _update() {
	engine._update();
}

#ifdef DEROX_DRAW


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{	
	engine.window._register(_caller, hInstance, L"Window class");
	engine.window._set(640, 480, 25, 25);
	engine._config();
	do {
		std::thread t(_update);
		engine.game._play();
		RedrawWindow(engine.window.handle, NULL, NULL, ENGINE_DRAW);
		BOOL result = 0;
		while (result = GetMessage(&engine.window.msg, engine.window.handle, 0, 0) != -1) {
			if (result != -1) {
				TranslateMessage(&engine.window.msg);
				DispatchMessage(&engine.window.msg);
				break;
			}
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
		t.join();
		Sleep(s);
		
	} while (engine.window.handle && engine.game.played);

	return 0;
}

#else

#pragma comment(linker, "/SUBSYSTEM:Console")

using namespace std;

int main(HINSTANCE hInstance) {
	if (engine.configured == 0) {
		engine.window._register(_caller, hInstance, L"Window class");
		engine.window._set(800, 600, 25, 75);
		engine._config();
		std::cout << "\nEngine configured.";
		engine.configured = 1;
	}
	/*
	do {

		CHART <DINT> *dint = new CHART<DINT>;
		*dint << 1;
		std::cout << "\n> " << dint->length << " / " << dint->size;
		if (dint->length >= 1000) {
			std::cout << ", " << dint->length;
			DINT i = 0;
			do {
				std::cout << " >> " << i;
				*dint >> i;
				i++;
			} while (dint->length > 0);
		}
		delete[] dint->exist;
		delete[] dint->item;
		delete dint;
		//Sleep(250);
		//dint >> 0;
	} while (engine.game.played);
	*/
	
	IMAGE *img = new IMAGE;
	img->_read("rect.png", -1);
	img->_close();
	delete img;

	std::cout << "\nStamping.";
	engine.timer._clock();
	DINT size = 8;
	CHART <int> i = size;
	i << 123;
	for (DINT c = 0; c < 100; c++) {
		//std::cout << "\n" << c << ": " << i[c] << " - " << i.length << " / " << i.size;

		i << engine.rand._roll(0, 999);
		//i._add(rand());
		//std::cout << "\n> " << c << "[" << i.exist[c] << "]: " << i.item[c] << " of " << i.size;
	}
	std::cout << "\nStamp: " << engine.timer._difference(engine.timer);
	do {
		//engine.timer._clock();
		engine._update();
		engine.game._play();
		//engine._simulate();
		//engine.game.statistics._loop();
		RedrawWindow(engine.window.handle, NULL, NULL, ENGINE_DRAW);
		BOOL result = 0;
		while (result = GetMessage(&engine.window.msg, engine.window.handle, 0, 0) != -1) {
			//std::cout << "Processing msg, (" << result << ") " << engine.window.msg.message << "\n";
			if (result != -1) {
				TranslateMessage(&engine.window.msg);
				DispatchMessage(&engine.window.msg);
				break;
			}
		}
		DINT s = 0;
		if (engine.delay == 0) {
			if (engine.game.statistics.fps.current > 60) {
				s = engine.game.statistics.fps.current - 60;
			}

		}
		else {
			s = engine.delay;
		}
		//std::cout << "Sleeping: " << s << "\n";
		Sleep(s);
		//system("pause");
		//std::cout << "\n -- " << engine.timer._difference(engine.timer);
	} while (engine.window.handle && engine.game.played);
	
	return 0;
}


#endif