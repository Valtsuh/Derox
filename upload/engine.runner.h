namespace Engine2 {
	static SPOT mouse;
	static DIMENSION view;
	static RECTANGLE bg;
	struct VERSION {
		VERSION() {
			this->lesser = ENGINE_VERSION_LESSER;
			this->minor = ENGINE_VERSION_MINOR;
			this->large = ENGINE_VERSION_LARGE;
			this->major = ENGINE_VERSION_MAJOR;
		}

		DINT lesser, minor, large, major;

	};
	struct ENGINE {
		ENGINE() {
			this->on = 0;
			this->configured = 0;
			WRITER(ENGINE_TYPOGRAPH);
			this->game.played = 1;
		};
		struct KEYER {
			KEYER() {};

			struct BUTTON {
				BUTTON() {
					this->down = 0;
				};
				DINT down;
			};

			struct MOUSE {
				MOUSE() {};
				BUTTON left, middle, right;
			};

			MOUSE mouse;
			BUTTON ctrl, shift, alt, a, s, d, w;
		};
		struct WINDOW {
			WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
				this->result = -1;
			};
			~WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
			};
			HWND handle;
			WNDCLASS info;
			RECT client, window;
			DINT width, heigth, x, y;
			MSG msg;
			DIMENSION mouse, mouseLast;
			BOOL result;
			static DIMENSION measure;
			//TRACKMOUSEEVENT me;

			CHART<DISPLAY_DEVICE> dd;
			CHART<DEVMODE> dm;

			void _register(WNDPROC proc, HINSTANCE i, const wchar_t name[]) {
				this->info = {};
				this->info.lpfnWndProc = proc;
				this->info.hInstance = i;
				this->info.lpszClassName = name;
				this->info.hbrBackground = 0; // Note to self handle WM_ERASEBKGND [white stuck]
				this->info.hCursor = 0;
				this->info.style = 0;
				RegisterClass(&this->info);
				std::cout << "\nWindow registered. (" << GetCurrentThreadId() << ", " << GetLastError() << ")";

			};

			void _device() {

				DINT device = 0;
				BOOL devi = 0;
				DISPLAY_DEVICE dd = {};
				std::cout << "\nChecking devices.";
				do {
					devi = EnumDisplayDevicesW(NULL, device, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
					device++;
					if (devi != 0)this->dd << dd;

				} while (devi != 0);

				std::cout << "\n Devices found: ";

				for (DINT i = 0; i < this->dd.length; i++) {
					if (this->dd.exist[i]) {
						dd = this->dd[i];
						std::cout << "\n> " << dd.DeviceName;
						std::cout << " - " << dd.DeviceString;
						std::cout << " - " << dd.DeviceID;
						std::cout << " : " << *reinterpret_cast<DWORD64*>(dd.DeviceName);
						std::cout << "\n Graphics modes: ";
						BOOL got = 0;
						DINT j = 0;
						DEVMODE dev = {};
						do {
							got = EnumDisplaySettings(dd.DeviceName, j, &dev);
							std::cout << "\n>> " << dev.dmDeviceName;
							std::cout << " - " << dev.dmDriverVersion;
							std::cout << " - " << dev.dmDriverExtra;
							std::cout << " - " << dev.dmDisplayFrequency;
							if (got != 0) this->dm << dev;
						} while (got != 0);

					}
				}

			}

			HWND _set(unsigned int w, unsigned int h, unsigned int x, unsigned int y, DINT ui = 1) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Title", WS_OVERLAPPEDWINDOW, this->x, this->y, this->width, this->heigth, NULL, NULL, this->info.hInstance, NULL);
				//SetWindowLong(this->handle, GWL_STYLE, WS_BORDER);
				if (this->handle == NULL) {
					system("pause");
				}
				else {
					/*
					this->me.cbSize = sizeof(this->me);
					this->me.dwFlags = TME_HOVER;
					this->me.hwndTrack = this->handle;
					this->me.dwHoverTime = 500;
					TrackMouseEvent(&this->me);
					*/
					std::cout << "\nWindow created. (" << this->handle << ", " << GetLastError() << ")";
					if(ui == 0) SetWindowLong(this->handle, GWL_STYLE, 0);
					this->_position(w, h, x, y);
				}
				return this->handle;
				POINT* m = new POINT;
				if (GetCursorPos(m)) {
					if (ScreenToClient(this->handle, m)) {
						m->x = (m->x < 0) ? (0) : (m->x);
						m->y = (m->y < 0) ? (0) : (m->y);
						this->mouse.x = (DINT)m->x;
						this->mouse.y = (DINT)m->y;
					}
				}
				delete m;
			};

			HWND _position(SINT w, SINT h, SINT x, SINT y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				SetWindowPos(this->handle, HWND_TOP, this->x, this->y, this->width, this->heigth, SWP_SHOWWINDOW);
				this->_client();
				this->_window();
				//ShowWindow(this->handle, SW_SHOW);
				//UpdateWindow(this->handle);
				std::cout << "\nWindow positioned. (" << this->handle << ", " << GetLastError() << "), " << w << ", " << h;
				return this->handle;
			}

			void _client() {
				GetClientRect(this->handle, &this->client);
			}

			void _window() {
				GetWindowRect(this->handle, &this->window);
			}

		};
		void _update() {
			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(this->window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
					//mCenter.x = m->x - Engine2::ENGINE::WINDOW::measure.w / 2;
					//mCenter.y = m->y - Engine2::ENGINE::WINDOW::measure.h / 2;
					SINT x = this->window.mouse.x - (DINT)m->x;
					SINT y = this->window.mouse.y - (DINT)m->y;

					//Engine2::window.mouse.x -= x;
					//Engine2::window.mouse.y -= y;
					Engine2::view._vert(x);
					Engine2::view._hori(y);
					if (this->window.mouse.x != (DINT)m->x || this->window.mouse.y != (DINT)m->y) {
						this->window.mouseLast = this->window.mouse;
						this->window.mouse.x = (DINT)m->x;
						this->window.mouse.y = (DINT)m->y;

						if (Engine2::ENGINE::keyer.mouse.left.down) {
							SINT x = this->window.mouse.x - this->window.mouseLast.x;
							SINT y = this->window.mouse.y - this->window.mouseLast.y;

							for (DINT t = 0; t < this->game.map.tile.length; t++) {
								GAME::TILE* tile = &this->game.map.tile[t];
								tile->center.x += x;
								tile->center.y += y;
								tile->position.x += x;
								tile->position.y += y;
							}
							
							for (DINT b = 0; b < this->game.map.creature.length; b++) {
								GAME::CREATURE* creature = &this->game.map.creature[b];
								//creature->movement.current.x += x;
								//creature->movement.current.y += y;
								//creature->movement.to.x += x;
								//creature->movement.to.y += y;
							}

							//GAME::MAP::position.x += x;
							//GAME::MAP::position.y += y;
							GAME::camera.offset.x += (SINT)(x * GAME::camera.speed);
							GAME::camera.offset.y += (SINT)(y * GAME::camera.speed);
						}
					}
				}
			}
			delete m;
			STRING title;
			title._append("Engine");
			title._space(WRITER::_itc(this->stats.fps));
			title._space(WRITER::_itc(this->version.major));
			title._append(".");
			title._append(WRITER::_itc(this->version.large));
			title._append(".");
			title._append(WRITER::_itc(this->version.minor));
			title._append(".");
			title._append(WRITER::_itc(this->version.lesser));
			this->test._track({ (double)this->window.mouse.x, (double)this->window.mouse.y, 0.0 });
			//title._space(WRITER::_c())
			SetWindowText(this->window.handle, title.wtext);
			/*
			if (Engine2::ENGINE::keyer.a.down) this->game.map.position.x -= 10;
			if (Engine2::ENGINE::keyer.d.down) this->game.map.position.x += 10;
			if (Engine2::ENGINE::keyer.w.down) this->game.map.position.y -= 10;
			if (Engine2::ENGINE::keyer.s.down) this->game.map.position.y += 10;
			*/
		}

		void _config(DINT x = 0, DINT y = 0) {
			/*
			Engine2::ENGINE::WINDOW::measure.w = state.w;
			Engine2::ENGINE::WINDOW::measure.h = state.h;
			Engine2::ENGINE::WINDOW::measure.x = x;
			Engine2::ENGINE::WINDOW::measure.y = y;
			Engine2::mouse.x = (double)state.w / 2.0;
			Engine2::mouse.y = (double)state.h / 2.0;
			Engine2::view.x = -(state.w / 2);
			Engine2::view.y = -(state.h / 2);
			Engine2::view.w = (state.w / 2);
			Engine2::view.h = (state.h / 2);
			Engine2::bg = { Engine2::view };

			*/
			this->configured = 1;
			this->on = 1;
			this->bg = LGR;
			this->game._config();
			this->test = ENGINE_POLYGON_DATA_SHIELD;
			this->test._pos(200, 150);
			this->sprite = GAME::library.sprite[GAME::library._search("blub")];
			this->mirrored = this->sprite;
			SPOT a = { 250.0, 150.0, 0.0 };
			this->anchor = a;
			GAME::camera.center = { 0, 0 };
			GAME::camera.offset = { 0, 0 };
			GAME::camera.tile = { 0, 0 };
			this->info = { 10, 10 };
			//this->image._read("test.bmp");
		}

		void _paint() {
			
			this->game.map._paint();
			//std::cout << "\n----";
			if (GAME::selected >= 0) {
				GAME::CREATURE c = this->game.map.creature[GAME::selected];
				this->info.gender._set(c.sex.gender.name.text);
				this->info.grd._set({ WRITER::_itc(c.guard.point.current) });
				this->info.str._set({ WRITER::_itc(c.strength.point.current) });
				this->info.agi._set({ WRITER::_itc(c.agility.point.current) });
				STRING hlth = WRITER::_itc(c.health.point.current);
				hlth += " / ";
				hlth += WRITER::_itc(c.health.point.total);
				this->info.hlt._set(hlth.text);
				this->info._draw();

			}

			if (GAME::selectedTile >= 0) {
				GAME::TILE tile = this->game.map.tile[GAME::selectedTile];
				STRING info = WRITER::_itc(tile.raining);
				this->tile.info = { info.text, 25, 125 };
				this->tile._draw();
			}

			state._set(GAME::camera.center.x + state.w / 2, GAME::camera.center.y + state.h / 2, BL, 4, 4);
			state._set(GAME::camera.offset.x + state.w / 2, GAME::camera.offset.y + state.h / 2, BL, 4, 4);
			//this->test._draw(200, 150);
			//this->anchor._draw();
			//state._set((DINT)Engine2::mouse.x - 1, (DINT)Engine2::mouse.y - 1, PNK, 2, 2);
			DINT size = 8;
			DINT spacing = 2;
			POS start = { 0, 0 }, end = { 3, 3 };
			COLOR color = W;
			for (DINT n = 0; n < this->aspos.length; n++) {
				NODE node = this->aspos[n];
				color = W;
				if (node.checked) color = GR;
				if (node.x == start.x && node.y == start.y) color = Y;
				if (node.x == end.x && node.y == end.y) color = G;
				if (node.blocked) color = R;
				state._set(node.x * (size + spacing), node.y * (size + spacing), color, size, size);
			}
		}

		COLOR bg;
		static STATISTICS stats;
		static KEYER keyer;
		IMAGE image;
		ART::NOTE note;
		CHART<POS> astar;
		CHART<NODE> aspos;	
		ART::BOX info, tile;
		WINDOW window;
		GAME game;
		DINT on, configured;
		COLOR selected;
		POLYGON test;
		UTILS::HEX hex;
		SPRITE sprite, mirrored;
		ANCHOR anchor;
		VERSION version;
	};

};
//SPOT Engine2::mouse;
STATISTICS Engine2::ENGINE::stats;
DIMENSION Engine2::ENGINE::WINDOW::measure;
Engine2::ENGINE::KEYER Engine2::ENGINE::keyer;
