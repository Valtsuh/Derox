#include <Windows.h>
#include <iostream>

#include "engine.literary.h"
#include "engine.database.h"
#include "engine.utils.h"
#include "engine.math.h"
#include "engine.drawer.h"
#include "engine.writer.h"
#include "engine.creature.h"
#include "engine.library.h"
#include "engine.game.h"
#include "engine.art.h"
#include "engine.runner.h"

Engine2::ENGINE engine = {};
LRESULT CALLBACK _caller(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK _caller(HWND window, UINT msg, WPARAM w, LPARAM l)
{
	LRESULT result = 0;
	switch (msg) {
		case WM_KEYDOWN: {
			//std::cout << "\n> KEY: " << w << ", " << l;
			switch (w) {
			default:
				break;
			case 65:
				Engine2::ENGINE::keyer.a.down = 1;
				break;
			case 68:
				Engine2::ENGINE::keyer.d.down = 1;
				break;
			case 83:
				Engine2::ENGINE::keyer.s.down = 1;
				break;
			case 87:
				Engine2::ENGINE::keyer.w.down = 1;
				break;
			}
		} break;
		case WM_KEYUP: {
			switch (w) {
			default:
				break;
			case 65: {
				Engine2::ENGINE::keyer.a.down = 0;				
				engine.aspos._close();
				RANDOM dice;
				DINT count = 0;
				DINT width = 4, height = 4;
				for (DINT x = 0; x < width; x++) {
					for (DINT y = 0; y < height; y++) {
						POS pst = { x, y };
						NODE n = {};
						n.x = pst.x;
						n.y = pst.y;
						switch (dice._roll(0, 8)) {
						default:
							n.blocked = 0;
							break;
						case 1:
							if (n.x != width - 1 && n.y != height - 1) {
								if (n.x != 0 && n.y != 0) {
									n.blocked = 1;
								}
								else {
									n.blocked = 0;
								}
							}
							else {
								n.blocked = 0;
							}
							break;
						}
						n.parent = nullptr;
						n.checked = 0;
						n.g = INFINITY; // this->random._roll(0, 300);
						n.l = INFINITY;
						n.f = 0.0;
						n.h = 0.0;
						n.index = count;
						engine.aspos << n;
						count++;
					}
				}

				for (DINT node = 0; node < engine.aspos.length; node++) {
					NODE *nd = &engine.aspos[node];
					nd->neighbour << _getNode(engine.aspos, nd->x - 1, nd->y, 4);
					nd->neighbour << _getNode(engine.aspos, nd->x, nd->y - 1, 8);
					nd->neighbour << _getNode(engine.aspos, nd->x, nd->y + 1, 2);
					nd->neighbour << _getNode(engine.aspos, nd->x + 1, nd->y, 6);
				}

				_path(&engine.aspos, { 0,0 }, { width - 1, height - 1 });
			} break;
			case 68: {
				Engine2::ENGINE::keyer.d.down = 0;
				if (GAME::selected >= 0) {
					engine.game.map.creature[GAME::selected].health.point.current -= 1;
				}
			} break;
			case 83:
				Engine2::ENGINE::keyer.s.down = 0;
				break;
			case 87:
				Engine2::ENGINE::keyer.w.down = 0;
				break;
			case VK_ESCAPE:
				engine.on = 0;
				break;
			}
		} break;
		case WM_CLOSE:
		case WM_QUIT:
		case WM_DESTROY: {
			engine.on = 0;
		} break;
		case WM_SIZE: {
			RECT rect;
			GetClientRect(window, &rect);
			state.w = rect.right - rect.left;
			state.h = rect.bottom - rect.top;
			Engine2::ENGINE::WINDOW::measure.w = state.w;
			Engine2::ENGINE::WINDOW::measure.h = state.h;
			Engine2::ENGINE::WINDOW::measure.x = rect.top;
			Engine2::ENGINE::WINDOW::measure.y = rect.left;
			state._config();
		} break;
		case WM_RBUTTONDOWN: {
			Engine2::ENGINE::keyer.mouse.right.down = 1;
		} break;
		case WM_RBUTTONUP: {
			Engine2::ENGINE::keyer.mouse.right.down = 0;

		} break;
		case WM_LBUTTONDOWN: {
			Engine2::ENGINE::keyer.mouse.left.down = 1;
		} break;
		case WM_LBUTTONUP: {
			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(engine.window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
				}
			}

			GAME::selected = -1;
			GAME::selectedTile = -1;
			Engine2::ENGINE::keyer.mouse.left.down = 0;
			for (DINT c = 0; c < engine.game.map.creature.length; c++) {
				GAME::CREATURE cr = engine.game.map.creature[c];
				if (m->x > cr.movement.travelling.x - cr.graphic.size.w * GAME::MAP::scale / 2 / 2) {
					if (m->x < cr.movement.travelling.x + cr.graphic.size.w * GAME::MAP::scale / 2 / 2) {
						if (m->y > cr.movement.travelling.y - cr.graphic.size.h * GAME::MAP::scale / 2 / 2) {
							if (m->y < cr.movement.travelling.y + cr.graphic.size.h * GAME::MAP::scale / 2 / 2) {
								GAME::selected = c;
								break;
							}
						}
					}
				}
			}

			for (DINT t = 0; t < engine.game.map.tile.length; t++) {
				GAME::TILE tile = engine.game.map.tile[t];
				if (m->x >= tile.center.x - 10) {
					if (m->x <= tile.center.x + 10) {
						if (m->y >= tile.center.y - 5) {
							if (m->y <= tile.center.y + 5) {
								GAME::selectedTile = t;
								break;
							}
						}
					}
				}
			}

			delete m;
		} break;
		case WM_MOUSEWHEEL: {
			SINT dir = GET_WHEEL_DELTA_WPARAM(w);
			if (dir == -120) {
				// down
				if (GAME::MAP::scale > 1) {
					GAME::MAP::scale -= 1;
					GAME::camera.speed += 0.1;
				}
			}
			if (dir == 120) {
				// up
				if (GAME::MAP::scale < 8) {
					GAME::MAP::scale += 1;
					GAME::camera.speed -= 0.1;
				}
			}

		} break;
		default: {
			result = DefWindowProc(window, msg, w, l);
		}
	}
	return result;
}

int main(HINSTANCE inst)
{
	if (engine.configured != 1) {
		//ShowCursor(FALSE);
		engine.window._register(_caller, inst, L"Title");
		//DINT w = GetSystemMetrics(SM_CXSCREEN);
		//DINT x = GetSystemMetrics(SM_CYSCREEN);
		engine.window._set(600, 480, 25, 25, 1);
		//engine.window._device();
		engine.stats.elapsed._clock(0);
		RECT rect;
		GetClientRect(engine.window.handle, &rect);
		//GetWindowRect(engine.window.handle, &rect);
		//ClipCursor(&rect);
		state.w = rect.right - rect.left;
		state.h = rect.bottom - rect.top;
		state._config(0, 0);
		Engine2::ENGINE::WINDOW::measure = { rect.top, rect.left, state.w, state.h };
		Engine2::mouse.x = (double)state.w / 2.0;
		Engine2::mouse.y = (double)state.h / 2.0;
		Engine2::view = { -(state.w / 2), -(state.h / 2), state.w / 2, state.h / 2 };
		Engine2::bg = { Engine2::view };
		engine._config();


	}
	if (1 == 1) {
		do {
			engine._update();
			engine.game._play();
			while (PeekMessage(&engine.window.msg, engine.window.handle, 0, 0, PM_REMOVE)) {
				TranslateMessage(&engine.window.msg);
				DispatchMessage(&engine.window.msg);
			}
			state._clear(engine.bg);
			engine._paint();
			state._draw(engine.window.handle);
			engine.stats._loop();
			//Engine2::view._dump();
			engine.stats._sleep(15);
		} while (engine.on && engine.game.played);
	}
	return 0;
}
