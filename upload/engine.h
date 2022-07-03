typedef unsigned int DINT;
typedef int SINT;
typedef long long LINT;
#include "engine.database.h"
#include "engine.utils.h"
#include "engine.math.h"
#include "engine.graphics.h"
#include "engine.physics.h"
#include "engine.game.h"
namespace drx1 {
	struct ENGINE {
		struct DRAWER {
			DRAWER() {
				this->tool = 0;
				this->mem = 0;
				this->bm = 0;
				this->client = {};
				this->measure = {};
				this->temp = {};
				this->paint = {};
			};
			~DRAWER() {};
			PAINTSTRUCT paint;
			HDC tool, mem;
			RECT client, measure, temp;
			COLOR bkgd;
			HBITMAP bm;
			void _begin(HWND window) {
				GetClientRect(window, &this->measure);
				this->client.right = this->measure.right - this->measure.left;
				this->client.bottom = this->measure.bottom - this->measure.top;
				this->tool = BeginPaint(window, &this->paint);
				this->mem = CreateCompatibleDC(NULL);
				this->bm = CreateCompatibleBitmap(this->tool, this->client.right, this->client.bottom);
				SelectObject(this->mem, this->bm);
			}

			void _end(HWND window) {
				BitBlt(this->tool, 0, 0, this->client.right, this->client.bottom, this->mem, 0, 0, SRCCOPY);
				ReleaseDC(window, this->tool);
				//ReleaseDC(window, this->mem);
				//DeleteDC(this->tool);
				DeleteDC(this->mem);
				DeleteObject(this->bm);
				EndPaint(window, &this->paint);
			}

			void _bkgd(HWND window, COLOR color = {}) {
				this->bkgd._set(color);
				HBRUSH brush = this->bkgd._brush();
				FillRect(this->mem, &this->measure, brush);
				DeleteObject(brush);

			}

			void _rect(DINT x, DINT y, DINT w, DINT h, COLOR color) {
				HBRUSH brush = color._brush();
				RECT rect = {};
				rect.left = x;
				rect.right = x + w;
				rect.top = y;
				rect.bottom = y + h;
				FillRect(this->mem, &rect, brush);
				DeleteObject(brush);

			}

		};
		
		struct DUSSCAL {
			DUSSCAL(double identifier = 0.0, SINT key = -1, SINT numeric = -1, char character = ' ', char secondary = ' ', LITERAL shape = {}) {
				this->identifier = identifier;
				this->key = key;
				this->numeric = numeric;
				this->character[0] = character;
				this->character[1] = secondary;
				this->uCharacter[0] = (unsigned char)this->character[0];
				this->uCharacter[1] = (unsigned char)this->character[1];
				this->wCharacter[0] = (wchar_t)this->character[0];
				this->wCharacter[1] = (wchar_t)this->character[1];
				this->shape = shape;
				this->capital = 0;
				this->exist = 0;
				
			};
			~DUSSCAL() {};
			double identifier;
			DINT exist, capital;
			SINT key, numeric;
			char character[2];
			unsigned uCharacter[2];
			wchar_t wCharacter[2];
			//BINT bit[8];
			LITERAL shape;
			//SPRT sprite;
			COUNTER counter;

		};

		struct TYPOGRAPH {
			TYPOGRAPH(DUSSCAL zero = {}, DUSSCAL one = {}, DUSSCAL two = {}, DUSSCAL three = {}, DUSSCAL four = {}, DUSSCAL five = {}, DUSSCAL six = {}, DUSSCAL seven = {}, DUSSCAL eight = {}, DUSSCAL nine = {}, DUSSCAL a = {}, DUSSCAL b = {}, DUSSCAL c = {}, DUSSCAL d = {}, DUSSCAL e = {}, DUSSCAL f = {}, DUSSCAL g = {}, DUSSCAL h = {}, DUSSCAL i = {}, DUSSCAL j = {}, DUSSCAL k = {}, DUSSCAL l = {}, DUSSCAL m = {}, DUSSCAL n = {}, DUSSCAL o = {}, DUSSCAL p = {}, DUSSCAL q = {}, DUSSCAL r = {}, DUSSCAL s = {}, DUSSCAL t = {}, DUSSCAL u = {}, DUSSCAL v = {}, DUSSCAL w = {}, DUSSCAL x = {}, DUSSCAL y = {}, DUSSCAL z = {}, DUSSCAL space = {}, DUSSCAL question = {}, DUSSCAL minus = {}, DUSSCAL plus = {}, DUSSCAL amp = {}, DUSSCAL exc = {}, DUSSCAL dot = {}) {
				this->lit._add(zero);
				this->lit._add(one);
				this->lit._add(two);
				this->lit._add(three);
				this->lit._add(four);
				this->lit._add(five);
				this->lit._add(six);
				this->lit._add(seven);
				this->lit._add(eight);
				this->lit._add(nine);
				this->lit._add(a);
				this->lit._add(b);
				this->lit._add(c);
				this->lit._add(d);
				this->lit._add(e);
				this->lit._add(f);
				this->lit._add(g);
				this->lit._add(h);
				this->lit._add(i);
				this->lit._add(j);
				this->lit._add(k);
				this->lit._add(l);
				this->lit._add(m);
				this->lit._add(n);
				this->lit._add(o);
				this->lit._add(p);
				this->lit._add(q);
				this->lit._add(r);
				this->lit._add(s);
				this->lit._add(t);
				this->lit._add(u);
				this->lit._add(v);
				this->lit._add(w);
				this->lit._add(x);
				this->lit._add(y);
				this->lit._add(z);
				this->lit._add(space);
				this->lit._add(question);
				this->lit._add(minus);
				this->lit._add(plus);
				this->lit._add(amp);
				this->lit._add(exc);
				this->lit._add(dot);
				this->dummy = ENGINE_MAP_DUMMY;
			};
			/*
			TYPOGRAPH(std::initializer_list<DUSSCAL> dscs) {
				HOLDER<DUSSCAL> holder = dscs;
				for (DINT i = 0; i < holder._size(); i++) this->lit << holder[i];
			}
			*/
			~TYPOGRAPH() {
				this->lit.~LIST();
			};

			LIST <DUSSCAL> lit;
			DUSSCAL dummy;


			DUSSCAL _compare(char character) {
				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.exist[d] == 1) {
						if (this->lit.item[d].character[0] == character || this->lit.item[d].character[1] == character) {
							return this->lit.item[d];
						}
					}
				}
				return this->dummy;
			}

			char _ccompare(DINT number) {

				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.exist[d] == 1) {
						if (this->lit.item[d].numeric == number) return this->lit.item[d].character[0];
					}
				}
				return '?';
			}

			wchar_t _wcompare(char character) {

				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.exist[d] == 1) {
						if (this->lit.item[d].character[0] == character) return this->lit.item[d].wCharacter[0];
						if (this->lit.item[d].character[1] == character) return this->lit.item[d].wCharacter[1];
					}
				}
				return L'?';
			}

			DINT _key(char character) {
				for (DINT c = 0; c < this->lit.length; c++) {
					if (this->lit.exist[c] == 1) {
						if (this->lit.item[c].character[0] == character) return this->lit.item[c].key;
						if (this->lit.item[c].character[1] == character) return this->lit.item[c].key;
					}
				}
			}

			char _kcompare(DINT key) {

				for (DINT k = 0; k < this->lit.length; k++) {
					if (this->lit.exist[k] == 1) {
						if (this->lit.item[k].key == key) return this->lit.item[k].character[1];
					}
				}
				return '?';
			}

		};
	
		struct WRITER {
			WRITER() {
				this->spacing = 4;
				this->length = 0;
				*this->wwrite = {};
				*this->write = {};
				/*
				for (DINT r = 0; r < 16; r++) {
					if (r < 8) {
						this->wwrite[r] = L' ';
					}
					this->write[r] = ' ';
				}
				*/
			};
			~WRITER() {
				this->dscr = {};
				this->spacing = 0;
				this->length = 0;
				*this->wwrite = {};
				*this->write = {};
			};
			
			DINT length, spacing;
			TYPOGRAPH dscr;
			DRAWER drawer;
			char write[16];
			wchar_t wwrite[8];
			void _type(const char text[], DINT x, DINT y, DINT size = 4, DINT spacing = 4, COLOR color = B, DINT transparency = 1) {
				

				/*
				auto type = [](HDC tool, const char text[], DINT x, DINT y, DINT size = 4, DINT spacing = 4, COLOR color = B) {	
					std::cout << "\nTyping: " << text;
					DINT px, py, tw = 0, ll = 0;
					PIXEL p = {};
					DUSSCAL tmp = {};
					TYPOGRAPH dscr = ENGINE_TYPOGRAPH;
					for (DINT length = 0; text[length] != '\0'; length++) {
						tmp = dscr._compare(text[length]);
						for (DINT h = 0; h < tmp.literal.size.h; h++) {
							for (DINT w = 0; w < tmp.literal.size.w; w++) {
								p = tmp.literal._get(w, h);
								if (p.color.exist == 1) {
									if (tmp.key >= 0) p.color = color;
									px = x + (p.x * size) + (ll * size) + (length * spacing);
									py = y + (p.y * size);
									p._scale(tool, px, py, size);
								}
								else {
									//if(transparency == 1){
									//}
								}
							}
						}
						ll += tmp.literal.size.w;
					}
					std::cout << ";";
				};

				std::thread t(type, this->drawer.mem, text, x, y, size, spacing, color);
				t.join();
				*/
				DINT px, py, ll = 0, counter = 0;
				PIXEL p = {};
				DUSSCAL tmp;
				for (this->length = 0; text[this->length] != '\0'; this->length++) {
					tmp = this->dscr._compare(text[this->length]);
					for(DINT i = 0; i < tmp.shape.pixels.size; i++){
						if (tmp.shape.pixels.exist[i]) {
							p = tmp.shape.pixels[i];
							if (p.color.exist == 1) {
								if (tmp.key >= 0) p.color = color;
								px = x + (p.x * size) + (ll * size) + (this->length * spacing);
								py = y + (p.y * size);
								p._scale(this->drawer.mem, px, py, size);
							}
							else {
								if (transparency == 1) {
								}
							}
						}
					}
					ll += tmp.shape.size.w;
				}
				
			}

			char* _itoca(SINT number = 0) {
				DINT temp = number;
				DINT length = 0;
				do {
					length++;
					temp /= 10;
				} while (temp >= 10);

				for (DINT i = 0; i < length; i++) {
					this->write[i] = '0';
				}
				this->write[length] = '\0';
				return this->write;
			}

			char* _itoc(SINT number = 9) {
				DINT length = 1;
				if (number >= 0) {
					if (number > 9) length = 2;
					if (number > 99) length = 3;
					if (number > 999) length = 4;
					if (number > 9999) length = 5;
					if (number > 99999) length = 6;
					if (number > 999999) length = 7;
					if (number > 9999999) length = 8;

					for (DINT i = 0; i < 8; i++) this->write[i] = '0';
					if (number > 0) {
						DUSSCAL numerals[8] = {};
						if (number > 0) {
							do {
								number--;
								numerals[0].counter.current++;
								for (DINT c = 0; c < 8; c++) {
									if (numerals[c].counter.current > 9) {
										numerals[c + 1].counter.current++;
										numerals[c].counter.current = 0;
									}
								}
							} while (number > 0);
						}
						else {
							for (DINT i = 0; i < 8; i++) this->write[i] = 'x';
						}
						DINT brk = 0;
						for (DINT position = 0; position < 8; position++) {
							if (position < length) {
								for (DINT number = length - position; number > 0; number--) {
									if (numerals[number - 1].counter.current > 0) {
										//this->write[position] = this->writer.._ncompare(numerals[number - 1].counter.current);
										this->write[position] = this->dscr._ccompare(numerals[number - 1].counter.current);
										brk++;
										break;
									}
									else {
										this->write[position] = '0';
										break;
									}
								}
							}
						}
					}
					this->write[length] = '\0';
				}
				else {
					if (number < -9) length = 2;
					if (number < -99) length = 3;
					if (number < -999) length = 4;
					if (number < -9999) length = 5;
					if (number < -99999) length = 6;
					if (number < -999999) length = 7;
					if (number < -9999999) length = 8;

					for (DINT i = 0; i < 8; i++) this->write[i] = '0';
					this->write[0] = '-';
					if (number < 0) {
						DUSSCAL numerals[8] = {};
						if (number < 0) {
							do {
								number++;
								numerals[0].counter.current++;
								for (DINT c = 0; c < 8; c++) {
									if (numerals[c].counter.current > 9) {
										numerals[c + 1].counter.current++;
										numerals[c].counter.current = 0;
									}
								}
							} while (number < 0);
						}
						else {
							for (DINT i = 0; i < 8; i++) this->write[i] = 'x';
						}
						DINT brk = 0;
						for (DINT position = 0; position < 8; position++) {
							if (position < length) {
								for (DINT number = length - position; number > 0; number--) {
									if (numerals[number - 1].counter.current > 0) {
										//this->write[position] = this->writer.._ncompare(numerals[number - 1].counter.current);
										this->write[position + 1] = this->dscr._ccompare(numerals[number - 1].counter.current);
										brk++;
										break;
									}
									else {
										this->write[position + 1] = '0';
										break;
									}
								}
							}
						}
					}
					this->write[length + 1] = '\0';
					
				}
				return this->write;
			}
			wchar_t* _itow(DINT number = 9) {
				DINT length = 1;
				if (number > 9) length = 2;
				if (number > 99) length = 3;
				if (number > 999) length = 4;
				if (number > 9999) length = 5;
				if (number > 99999) length = 6;
				if (number > 999999) length = 7;
				if (number > 9999999) length = 8;

				for (DINT i = 0; i < 8; i++) this->wwrite[i] = '0';
				if (number > 0) {
					DUSSCAL numerals[8] = {};
					if (number > 0) {
						do {
							number--;
							numerals[0].counter.current++;
							for (DINT c = 0; c < 8; c++) {
								if (numerals[c].counter.current > 9) {
									numerals[c + 1].counter.current++;
									numerals[c].counter.current = 0;
								}
							}
						} while (number > 0);
					}
					else {
						for (DINT i = 0; i < 8; i++) this->wwrite[i] = 'x';
					}
					DINT brk = 0;
					for (DINT position = 0; position < 8; position++) {
						if (position < length) {
							for (DINT number = length - position; number > 0; number--) {
								if (numerals[number - 1].counter.current > 0) {
									//this->write[position] = this->writer.._ncompare(numerals[number - 1].counter.current);
									this->wwrite[position] = (wchar_t)this->dscr._ccompare(numerals[number - 1].counter.current);
									brk++;
									break;
								}
								else {
									this->wwrite[position] = '0';
									break;
								}
							}
						}
					}
				}
				this->wwrite[length] = '\0';
				return this->wwrite;
			}

			SINT _ctoi(const char character) {
				return this->dscr._compare(character).numeric;
			}

			SINT _kcount(const char text[]) {
				SINT count = 0;
				DUSSCAL dsc = {};
				for (DINT c = 0; text[c] != '\0'; c++) {
					dsc = this->dscr._compare(text[c]);
					if (dsc.numeric != -1) {
						count += dsc.numeric;
					}
				}

				return count;
			}

			DINT _catoi(const char text[]) {
				DUSSCAL dsc;
				INDEX <DINT> *list = new INDEX<DINT>;
				for (DINT c = 0; text[c] != '\0'; c++) {
					dsc = this->dscr._compare(text[c]);
					if (dsc.numeric != -1) {
						list->_add(dsc.numeric);
					}

				}				
				DINT count = 0;
				DINT counter = 1;
				list->_reverse();
				for (DINT n = 0; n < list->size; n++) {
					if (list->exist[n]) {
						count += list->item[n] * counter;
						counter *= 10;
					}
				};
				delete[] list->exist;
				delete[] list->item;
				delete list;
				return count;
			}
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
			DIMENSION mouse;
			//TRACKMOUSEEVENT me;


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


			HWND _set(unsigned int w, unsigned int h, unsigned int x, unsigned int y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Engine", WS_OVERLAPPEDWINDOW, this->x, this->y, this->width, this->heigth, NULL, NULL, this->info.hInstance, NULL);
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
					std::cout << "\nWindow created. (" << this->handle <<  ", " << GetLastError() << ")";
					this->_position(w, h, x, y);
				}
				return this->handle;
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

		ENGINE() {
			this->configured = 0;
			this->delay = ENGINE_MODE_SLEEP;
			std::cout << "\nEngine constructor called.";
			//this->test = {};
		};
		~ENGINE() {
			this->game.~GAME();
			this->window.~WINDOW();
			this->writer.~WRITER();
		};

		WINDOW window;
		WRITER writer;
		GAME game;
		DICE rand;
		TIME timer;
		THREAD thread[2];
		SAVE save;
		DINT configured, delay;
		MDL mdl;

		//LINE test;

		void _update() {

			this->window._client();
			this->window._window();

			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(this->window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
					if (this->window.mouse.x != (DINT)m->x || this->window.mouse.y != (DINT)m->y) {
						//std::cout << "Thread 1: Updating mouse.\n";
						this->window.mouse.x = (DINT)m->x;
						this->window.mouse.y = (DINT)m->y;
						this->game.mouse.x = (DINT)m->x;
						this->game.mouse.y = (DINT)m->y;
					}
				}
			}
			delete m;
		}

		void _config() {
			srand((unsigned int)time(NULL));
			this->game.statistics.time._clock();
			this->game.played = 1;
			this->window._client();
			this->window._window();
			this->game.client.x = this->window.client.left;
			this->game.client.y = this->window.client.top;
			this->game.client.w = this->window.client.right;
			this->game.client.h = this->window.client.bottom;
			this->writer.dscr = ENGINE_TYPOGRAPH;
			this->save._load();
			SPOT spot;
			spot.x = 90.0;
			spot.y = 90.0;
			this->game.box = { 350.0, 300.0, 30.0 , spot, R};
			//this->game.water.boundary._set(this->game.client);
			//this->game.doll._form(125, 350, R, this->game.client);
		}

		void _end() {

			char csave[8] = "";
			DINT i = 0, j = 0;
			std::cout << "Reading data: " << this->save.data.text << " : ";
			for (DINT i = 0; this->save.data.text[i] != ' '; i++) {
				csave[i] = this->save.data.text[i];
				j++;
			}
			csave[j] = '\0';
			if (this->game.atlas.streak > this->writer._catoi(csave)) {
				this->save._save(this->game.atlas.streak, 1);
				this->save._save(this->game.atlas.streaker.text);
				this->save._save(this->game.atlas.loops);
			}

			this->game.~GAME();
			this->window.~WINDOW();
			this->writer.~WRITER();
			this->game.played = 0;
		}
		void _draw() {

			this->writer._type(this->writer._itoc(this->game.statistics.fps.current), 5, 5, 3);
			this->writer._type(this->writer._itoc(this->game.statistics.loop.current), 85, 5, 3);
			this->writer._type(this->writer._itoc(this->game.statistics.current.elapsed), 165, 5, 3);
			this->writer._type("?.-+ 0123456789", 5, 25, 3);
			this->writer._type("abcdefghijklmnopqrstuvwxyz", 5, 45, 3);
			IMAGE img;

			DINT rint = img._read("\\header.jpg");

			std::ifstream strm;

			strm.open("\\test.jpg");

			this->writer._type(this->writer._itoc(strm.is_open()), 5, 65, 3);

			DINT r = 0, l = 0;
			char re[128] = "";
			char rea = ' ';
			STRING a;
			strm >> re;
			for (DINT r = 0; r < 128; r++) {
				this->writer._type(&re[r], 5, 85, 3);
			}

		}

		void _paint(DINT msg, DINT w, DINT l) {
			this->writer._type("& ?.-+0123456789!", 5, 250, 3);
			this->writer._type(this->writer._itoc(GetLastError()), 230, 250, 3, 2, R);
			this->writer._type(this->writer._itoc(this->game.statistics.fps.current), 280, 250, 3, 2, R);
			this->writer._type(this->writer._itoc(this->game.statistics.current.elapsed), 330, 250, 3, 2, R);
			this->writer._type(this->writer._itoc(this->game.statistics.loop.current), 380, 250, 3, 2, R);
			this->writer._type("abcdefghijklmnopqrstuvwxyz", 5, 275, 2);
			this->writer._type(this->writer._itoc(this->game.atlas.creatures.total), 325, 275, 2, 2, W);
			this->writer._type(this->writer._itoc(this->game.atlas.streak), 5, 185, 3);
			this->writer._type(this->game.atlas.streaker.text, 35, 185, 3);
			this->writer._type(this->writer._itoc(this->game.atlas.loops), 45 + this->game.atlas.streaker.length * 15, 185, 3);
			this->writer._type(this->writer._itoc(this->writer._catoi(this->save.streak.text)), 5, 225, 3);
			this->writer._type(this->save.streaker.text, 35, 225, 3);
			this->writer._type(this->writer._itoc(this->writer._catoi(this->save.time.text)), 45 + (this->save.streaker.length * 15), 225, 3);
			for (DINT m = 0; m < this->game.atlas.maps.length; m++) {
				if (this->game.atlas.maps.exist[m] == 1) {
					//map = this->game.atlas.maps.item[m];
					this->game.atlas.maps[m]._draw(this->writer.drawer.mem);				
					//this->writer._type(this->writer._itoc(this->game.atlas.maps.item[m].count), this->game.atlas.maps.item[m].measure.x + 5, this->game.atlas.maps.item[m].measure.y + 5, 2, 2, W);
					//this->writer._type(this->writer._itoc(this->game.atlas.maps.item[m].position.x), this->game.atlas.maps.item[m].measure.x + 5, this->game.atlas.maps.item[m].measure.y + 20, 2, 2, W);
					//this->writer._type(this->writer._itoc(this->game.atlas.maps.item[m].position.y), this->game.atlas.maps.item[m].measure.x + 20, this->game.atlas.maps.item[m].measure.y + 20, 2, 2, W);
					//this->writer._type(this->writer._itoc(this->game.atlas.maps.item[m].measure.x), 10, m * 15 + 200, 2);
					//this->writer._type(this->writer._itoc(this->game.atlas.maps.item[m].measure.y), 110, m * 15 + 200, 2);
					/*
					for (DINT t = 0; t < map.terrain.length; t++) {
						if (map.terrain.exist[t] == 1) {
							//this->writer._type(this->writer._itoc(map.terrain.item[t].count), map.terrain.item[t].position.w + 2, map.terrain.item[t].position.h + 2, 1, 3, W);
							this->writer._type(this->writer._itoc(map.terrain.item[t].position.x), map.terrain.item[t].position.w + 2, map.terrain.item[t].position.h + 2, 1, 3, W);
							this->writer._type(this->writer._itoc(map.terrain.item[t].position.y), map.terrain.item[t].position.w + 12, map.terrain.item[t].position.h + 2, 1, 3, W);
						}
					}
					*/
				}
			}

			DINT view = 1;
			GAME::DUS* dus;
			DINT na = 10, nb = 35, ia = 25, ib = 35, la = 35, lb = 35;
			for (DINT d = 0; d < this->game.atlas.creatures.size; d++) {
				if (this->game.atlas.creatures.exist[d] == 1) {;
					this->game.atlas.creatures.item[d]._draw(this->writer.drawer.mem);
					for (DINT m = 0; m < this->game.atlas.creatures[d].mutation.length; m++) {
						if (this->game.atlas.creatures[d].mutation.exist[m]) {
							dus = &this->game.atlas.creatures[d].mutation[m];
							dus->_draw(this->writer.drawer.mem);
						}
					}
					
					if (view == 1) {
						COLOR color;
						if (this->game.atlas.creatures[d].inventory._available(ENGINE_TYPE_RESOURCE_BERRY) > 0) {
							color = DG;
						}
						else {
							color = B;
						}
						this->writer._type(this->game.atlas.creatures.item[d].name.text, 5, na + (d * nb), 2, 4, color);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].unique), 100, na + (d * nb), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].experience.point.total), 125, na + (d * nb), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].health.current), 145, na + (d * nb), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].health.total), 160, na + (d * nb), 2);
						/*
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].unique), 5, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].experience.point.current), 35, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].experience.point.total), 70, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].experience.level.current), 105, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].collision.collie), 140, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].collision.last), 175, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].health.current), 210, 10 + (d * 25), 2);
						this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].health.total), 245, 10 + (d * 25), 2);

						*/

						for (DINT i = 0; i < this->game.atlas.creatures[d].animate.limbs.length; i++) {
							//if (this->game.atlas.creatures[d].animate.limbs[i].exist) {
								this->writer._type(this->game.atlas.creatures[d].animate.limbs[i].name.text, 10 + (i * 70), la + (d * lb), 1, 2);
								this->writer._type(this->writer._itoc(this->game.atlas.creatures[d].animate.limbs[i].health.current), 50 + (i * 70), la + (d * lb), 1, 2);
								this->writer._type(this->writer._itoc(this->game.atlas.creatures[d].animate.limbs[i].health.total), 60 + (i * 70), la + (d * lb), 1, 2);
							//}
						}

						for (DINT i = 0; i < this->game.atlas.creatures.item[d].inventory.items.length; i++) {
							this->writer._type(this->game.atlas.creatures.item[d].inventory.items.item[i].name.text, 10 + (i * 65), ia + (d * ib), 1, 2);
							this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].inventory.items.item[i].amount), 65 + (i * 65), ia + (d * ib), 1, 2);
						}
					}
				}
			}

			for (DINT r = 0; r < this->game.atlas.resources.size; r++) {
				if (this->game.atlas.resources.exist[r] == 1) {
					this->game.atlas.resources.item[r]._draw(this->writer.drawer.mem);
					//this->writer._type(this->writer._itoc(this->game.atlas.resources.item[r].unique), 105, 10 + (r * 25), 2);
				}
			}
			if(this->game.doll.exist) this->game.doll._draw(this->writer.drawer.mem);
			/*
			for (DINT d = 0; d < this->game.water.drops.length; d++) {
				if (this->game.water.drops.exist[d]) {
					this->game.water.drops[d].shape._draw(this->writer.drawer.mem);
				}
			}
			*/
			//this->game.box._draw(this->writer.drawer.mem);
		}
	
	};


}