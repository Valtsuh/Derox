
struct STATISTICS {
	STATISTICS() {
		this->fps = 0;
		//drx::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
		//drx::ENGINE::STATISTICS::lf = nf - frames{ 1 };
		//drx::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
		STATISTICS::nf = std::chrono::system_clock::now();
		STATISTICS::lf = std::chrono::system_clock::now();
	};

	DINT fps;
	COUNTER loops;
	static double elapsed;
	static TIME last, current;
	static std::chrono::system_clock::time_point nf, lf;
	static std::chrono::high_resolution_clock::time_point hr;


	void _loop() {
		this->loops.current += 1;
		this->current._increment(this->current);
		DINT since = this->current._since();
		if (this->loops.current > 0 && since > 0) {
			/*
			std::cout << "\n> ";
			std::cout << this->elapsed.lh << ":" << this->elapsed.lm;
			std::cout << ":" << this->elapsed.ls << ":" << this->elapsed.lms;
			std::cout << "(" << this->elapsed._since() << ")";
			*/
			this->fps = this->loops.current / since;
		}
	}

	void _sleep(SINT target = 60) {
		if (target != -1 && target < 60) {
			target = 1000 / (target + (target / 2) / 2);
			/*
			std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - drx::ENGINE::STATISTICS::lf).count() << " ms";
			std::this_thread::sleep_until(drx::ENGINE::STATISTICS::nf);
			drx::ENGINE::STATISTICS::lf = drx::ENGINE::STATISTICS::nf;
			drx::ENGINE::STATISTICS::nf += frames {1};
			*/

			//drx::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
			STATISTICS::lf = std::chrono::system_clock::now();
			//std::chrono::duration<double, std::milli> work = drx::ENGINE::STATISTICS::lf - drx::ENGINE::STATISTICS::nf;
			std::chrono::duration<double, std::milli> work = STATISTICS::lf - STATISTICS::nf;
			if (work.count() < target) {
				std::chrono::duration<double, std::milli> delta_ms(target - work.count());
				auto delta_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
				std::this_thread::sleep_for(std::chrono::milliseconds(delta_duration.count()));
			}
			//drx::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
			STATISTICS::nf = std::chrono::system_clock::now();
			//std::chrono::duration<double, std::milli> sleep = drx::ENGINE::STATISTICS::nf - drx::ENGINE::STATISTICS::lf;
			std::chrono::duration<double, std::milli> sleep = STATISTICS::nf - STATISTICS::lf;

			//std::cout << "\nSleep: " << (work.count() + sleep.count()) << " ms";
			//drx::ENGINE::STATISTICS::last.elapsed = (DINT)(work.count() + sleep.count());
			STATISTICS::elapsed = work.count() + sleep.count();
			//std::cout << "\n" << STATISTICS::last.elapsed;

		}
	}

};

namespace drx {
	static SPOT mouse;
	static DICE dice;

	struct CONFIGURATION {
		CONFIGURATION(DINT w, DINT h, DINT s) {
			width = w;
			height = h;
			scale = s;
			srand((unsigned int)time(NULL));
		};
		CONFIGURATION() {};
		static DINT width, height, scale;
	};

	struct WINDOW {
		WINDOW() {
			//drx::WINDOW::handle = 0;
		};
		~WINDOW() {};
		static HWND handle;
		static WNDCLASS info;
		static MSG msg;
		static DIMENSION measure, client, mouse, mouseLast;
		
		static LRESULT CALLBACK _c(HWND hwnd, UINT uMsg, WPARAM w, LPARAM l);

		static void _register(WNDPROC proc, HINSTANCE i, const wchar_t name[]) {
			WINDOW::info = {};
			WINDOW::info.lpfnWndProc = proc;
			WINDOW::info.hInstance = i;
			WINDOW::info.lpszClassName = name;
			WINDOW::info.hbrBackground = 0; // Note to self handle WM_ERASEBKGND [white stuck]
			WINDOW::info.hCursor = 0;
			WINDOW::info.style = 0;
			RegisterClass(&WINDOW::info);
			std::cout << "\nWindow registered. (" << GetCurrentThreadId() << ", " << GetLastError() << ")";

		};

		static HWND _create(DINT w, DINT h, DINT x, DINT y, HINSTANCE i, const wchar_t name[], bool fullscreen = false) {
			
			WINDOW::_register(drx::WINDOW::_c, i, name);
			if (fullscreen) {
				RECT rect;
				GetClientRect(GetDesktopWindow(), &rect);
				WINDOW::handle = CreateWindow(WINDOW::info.lpszClassName, L"Title", WS_BORDER, 0, 0, rect.right, rect.bottom, NULL, NULL, WINDOW::info.hInstance, NULL);
				SetWindowLong(WINDOW::handle, GWL_STYLE, 0);
			}
			else {
				WINDOW::handle = CreateWindow(WINDOW::info.lpszClassName, L"Title", WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, WINDOW::info.hInstance, NULL);
			}
			if (WINDOW::handle == NULL) {
				std::cout << "\nWINDOW::handle null";
				system("pause");
			}
			else {
				std::cout << "\nWindow created. (" << WINDOW::handle << ", " << GetLastError() << ")";
				ShowWindow(WINDOW::handle, SW_NORMAL);
				RECT rect;
				if (fullscreen) {
					GetWindowRect(WINDOW::handle, &rect);
					WINDOW::measure = { 0, 0, rect.right - rect.left, rect.bottom - rect.top };
				}
				else {
					WINDOW::measure = { x, y, w, h };
					GetClientRect(WINDOW::handle, &rect);
				}
				state._config(0, 0, rect.right - rect.left, rect.bottom - rect.top);
			}


			return WINDOW::handle;
		}

	};

	struct VERSION {
		VERSION() {
			lesser = ENGINE_VERSION_LESSER;
			minor = ENGINE_VERSION_MINOR;
			large = ENGINE_VERSION_LARGE;
			major = ENGINE_VERSION_MAJOR;
		}

		static DINT lesser, minor, large, major;

		static STRING _current() {
			STRING c;
			c = WRITER::_itc(VERSION::major);
			c._app('.');
			c._app(*WRITER::_itc(VERSION::large));
			c._app('.');
			c._app(*WRITER::_itc(VERSION::lesser));
			c._app('.');
			c._app(*WRITER::_itc(VERSION::minor));
			return c;
		}

	};
	struct ENGINE {

		ENGINE() {
			this->on = false;
			this->configured = false;
			WRITER(ENGINE_TYPOGRAPH);
		};
		struct KEYER {
			KEYER() {};

			struct BUTTON {
				BUTTON() {
					this->down = false;
				};
				bool down;
			};

			struct MOUSE {
				MOUSE() {};
				BUTTON left, middle, right, up, down;
			};

			MOUSE mouse;
			BUTTON ctrl, shift, alt, a, s, d, w;
		};
		void _refresh() {
			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(drx::WINDOW::handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
					SINT x = drx::WINDOW::mouse.x - (DINT)m->x;
					SINT y = drx::WINDOW::mouse.y - (DINT)m->y;

					//drx::window.mouse.x -= x;
					//drx::window.mouse.y -= y;
					//if (drx::WINDOW::mouse.x != (DINT)m->x || drx::WINDOW::mouse.y != (DINT)m->y) {
						drx::WINDOW::mouseLast.x = drx::WINDOW::mouse.x;
						drx::WINDOW::mouseLast.y = drx::WINDOW::mouse.y;
						drx::WINDOW::mouse.x = (DINT)m->x;
						drx::WINDOW::mouse.y = (DINT)m->y;
					//}
				}
			}
			delete m;
			STRING title;
			title._append("Engine");
			title._space(WRITER::_itc(drx::ENGINE::stats.fps));
			title._space(drx::ENGINE::version._current().text);
			SetWindowText(drx::WINDOW::handle, title.wtext);
		}

		void _config(DINT w, DINT h, DINT x, DINT y, HINSTANCE i, const wchar_t name[], bool console = false, bool fullscreen = false) {
			drx::WINDOW::_create(w, h, x, y, i, name, fullscreen);
			if (!console) ShowWindow(GetConsoleWindow(), SW_HIDE); else ShowWindow(GetConsoleWindow(), SW_SHOW);
			this->_load();
			drx::ENGINE::stats.current._clock(0);
			drx::ENGINE::configured = true;
			drx::ENGINE::on = true;
		}
		virtual void _paint() {}
		virtual void _update() {}
		virtual void _load() {}

		void _run() {

			do {
				state._clear(LGR);
				this->_refresh();
				this->_update();
				while (PeekMessage(&drx::WINDOW::msg, drx::WINDOW::handle, 0, 0, PM_REMOVE)) {
					TranslateMessage(&drx::WINDOW::msg);
					DispatchMessage(&drx::WINDOW::msg);
				}
				this->_paint();
				state._draw(drx::WINDOW::handle);
				drx::ENGINE::stats._loop();
				drx::ENGINE::stats._sleep(20);
				//drx::canvas._clear(DGR);
				//drx::canvas._draw(drx::WINDOW::handle);
			} while (drx::ENGINE::on);
		}

		static STATISTICS stats;
		static KEYER keyer;
		static VERSION version;
		static bool on, configured;
	};

};

LRESULT CALLBACK drx::WINDOW::_c(HWND window, UINT msg, WPARAM w, LPARAM l) {
	LRESULT result = 0;
	switch (msg) {
	case WM_KEYDOWN: {
		//std::cout << "\n> KEY: " << w << ", " << l;
		switch (w) {
		default:
			break;
		case 65:
			drx::ENGINE::keyer.a.down = true;
			break;
		case 68:
			drx::ENGINE::keyer.d.down = true;
			break;
		case 83:
			drx::ENGINE::keyer.s.down = true;
			break;
		case 87:
			drx::ENGINE::keyer.w.down = true;
			break;
		}
	} break;
	case WM_KEYUP: {
		switch (w) {
		default:
			break;
		case 65: {
			drx::ENGINE::keyer.a.down = false;
		} break;
		case 68: {
			drx::ENGINE::keyer.d.down = false;
		} break;
		case 83: {
			drx::ENGINE::keyer.s.down = false;
		} break;
		case 87: {
			drx::ENGINE::keyer.w.down = false;
		} break;
		case VK_ESCAPE:
			drx::ENGINE::on = false;
			break;
		}
	} break;
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY: {
		drx::ENGINE::on = 0;
	} break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(window, &rect);
		state.w = rect.right - rect.left;
		state.h = rect.bottom - rect.top;
		drx::WINDOW::measure = { rect.top, rect.left, state.w, state.h };
		state._config();
	} break;
	case WM_RBUTTONDOWN: {
		drx::ENGINE::keyer.mouse.right.down = true;
	} break;
	case WM_RBUTTONUP: {
		drx::ENGINE::keyer.mouse.right.down = false;

	} break;
	case WM_LBUTTONDOWN: {
		drx::ENGINE::keyer.mouse.left.down = true;
	} break;
	case WM_LBUTTONUP: {
		drx::ENGINE::keyer.mouse.left.down = false;
		POINT* m = new POINT;
		if (GetCursorPos(m)) {
			if (ScreenToClient(drx::WINDOW::handle, m)) {
				m->x = (m->x < 0) ? (0) : (m->x);
				m->y = (m->y < 0) ? (0) : (m->y);
			}
		}		
		delete m;
	} break;
	case WM_MOUSEWHEEL: {
		SINT dir = GET_WHEEL_DELTA_WPARAM(w);
		if (dir == -120) {
			// down
			drx::ENGINE::keyer.mouse.up.down = true;
		}
		if (dir == 120) {
			// up
			drx::ENGINE::keyer.mouse.down.down = true;
		}

	} break;
	default: {
		result = DefWindowProc(window, msg, w, l);
	} break;
	}
	return result;
}

//SPOT drx::mouse;

MSG drx::WINDOW::msg;
HWND drx::WINDOW::handle;
WNDCLASS drx::WINDOW::info;
DIMENSION drx::WINDOW::measure, drx::WINDOW::client, drx::WINDOW::mouse, drx::WINDOW::mouseLast;
drx::VERSION drx::ENGINE::version;
DINT drx::VERSION::lesser, drx::VERSION::minor, drx::VERSION::large, drx::VERSION::major;
bool drx::ENGINE::on, drx::ENGINE::configured;
drx::ENGINE::KEYER drx::ENGINE::keyer;
DINT drx::CONFIGURATION::width, drx::CONFIGURATION::height, drx::CONFIGURATION::scale;

STATISTICS drx::ENGINE::stats;
std::chrono::system_clock::time_point STATISTICS::nf;
std::chrono::system_clock::time_point STATISTICS::lf;
TIME STATISTICS::last, STATISTICS::current;
double STATISTICS::elapsed;
std::chrono::high_resolution_clock::time_point STATISTICS::hr;