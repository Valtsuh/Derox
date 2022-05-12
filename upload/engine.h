typedef unsigned int DINT;
typedef int SINT;
#include "engine.database.h"
#include "engine.utils.h"
#include "engine.graphics.h"
#include "engine.game.h"
namespace drx1 {
	struct ENGINE {
		struct BINT {
			BINT() {
				this->value = 0;
			};
			~BINT() {};
			unsigned int value;
		};

		struct DRAWER {
			DRAWER() {
				this->bkgd = {};
				this->bm = {};
				this->client = {};
				this->measure = {};
				this->temp = {};
				this->tool = 0;
				this->mem = 0;
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
				this->tool = BeginPaint(window, &paint);
				this->mem = CreateCompatibleDC(this->mem);
				this->bm = CreateCompatibleBitmap(this->tool, this->client.right, this->client.bottom);
				SelectObject(this->mem, this->bm);
			}

			void _end(HWND window) {
				BitBlt(this->tool, 0, 0, this->client.right, this->client.bottom, this->mem, 0, 0, SRCCOPY);
				ReleaseDC(window, this->tool);
				ReleaseDC(window, this->mem);
				DeleteDC(this->tool);
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
				RECT rect;
				rect.left = x;
				rect.right = x + w;
				rect.top = y;
				rect.bottom = y + h;
				FillRect(this->mem, &rect, brush);
				DeleteObject(brush);

			}

		};
		
		struct DUSSCAL {
			DUSSCAL(double identifier = 0.0, SINT key = -1, SINT numeric = -1, char character = ' ', char secondary = ' ', LITERAL literal = {}) {
				this->identifier = identifier;
				this->key = key;
				this->numeric = numeric;
				this->character[0] = character;
				this->character[1] = secondary;
				this->uCharacter[0] = (unsigned char)this->character[0];
				this->uCharacter[1] = (unsigned char)this->character[1];
				this->wCharacter[0] = (wchar_t)this->character[0];
				this->wCharacter[1] = (wchar_t)this->character[1];
				this->literal = literal;
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
			BINT bit[8];
			LITERAL literal;
			COUNTER counter;

		};

		struct TYPOGRAPH {
			TYPOGRAPH(DUSSCAL zero = {}, DUSSCAL one = {}, DUSSCAL two = {}, DUSSCAL three = {}, DUSSCAL four = {}, DUSSCAL five = {}, DUSSCAL six = {}, DUSSCAL seven = {}, DUSSCAL eight = {}, DUSSCAL nine = {}, DUSSCAL a = {}, DUSSCAL b = {}, DUSSCAL c = {}, DUSSCAL d = {}, DUSSCAL e = {}, DUSSCAL f = {}, DUSSCAL g = {}, DUSSCAL h = {}, DUSSCAL i = {}, DUSSCAL j = {}, DUSSCAL k = {}, DUSSCAL l = {}, DUSSCAL m = {}, DUSSCAL n = {}, DUSSCAL o = {}, DUSSCAL p = {}, DUSSCAL q = {}, DUSSCAL r = {}, DUSSCAL s = {}, DUSSCAL t = {}, DUSSCAL u = {}, DUSSCAL v = {}, DUSSCAL w = {}, DUSSCAL x = {}, DUSSCAL y = {}, DUSSCAL z = {}, DUSSCAL space = {}, DUSSCAL question = {}, DUSSCAL minus = {}, DUSSCAL plus = {}, DUSSCAL amp = {}, DUSSCAL exc = {}) {
				this->lit._set(zero);
				this->lit._set(one);
				this->lit._set(two);
				this->lit._set(three);
				this->lit._set(four);
				this->lit._set(five);
				this->lit._set(six);
				this->lit._set(seven);
				this->lit._set(eight);
				this->lit._set(nine);
				this->lit._set(a);
				this->lit._set(b);
				this->lit._set(c);
				this->lit._set(d);
				this->lit._set(e);
				this->lit._set(f);
				this->lit._set(g);
				this->lit._set(h);
				this->lit._set(i);
				this->lit._set(j);
				this->lit._set(k);
				this->lit._set(l);
				this->lit._set(m);
				this->lit._set(n);
				this->lit._set(o);
				this->lit._set(p);
				this->lit._set(q);
				this->lit._set(r);
				this->lit._set(s);
				this->lit._set(t);
				this->lit._set(u);
				this->lit._set(v);
				this->lit._set(w);
				this->lit._set(x);
				this->lit._set(y);
				this->lit._set(z);
				this->lit._set(space);
				this->lit._set(question);
				this->lit._set(minus);
				this->lit._set(plus);
				this->lit._set(amp);
				this->lit._set(exc);
			};
			~TYPOGRAPH() {
			
			};

			LIST <DUSSCAL> lit;
			DUSSCAL dummy;


			DUSSCAL _compare(char character) {
				DUSSCAL dsc;
				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.existance[d] == 1) {
						if (this->lit.item[d].character[0] == character || this->lit.item[d].character[1] == character) {
							return this->lit.item[d];
						}
					}
				}
				return this->dummy;
			}

			char _ccompare(DINT number) {

				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.existance[d] == 1) {
						if (this->lit.item[d].numeric == number) return this->lit.item[d].character[0];
					}
				}
				return '?';
			}

			wchar_t _wcompare(char character) {

				for (DINT d = 0; d < this->lit.length; d++) {
					if (this->lit.existance[d] == 1) {
						if (this->lit.item[d].character[0] == character) return this->lit.item[d].wCharacter[0];
						if (this->lit.item[d].character[1] == character) return this->lit.item[d].wCharacter[1];
					}
				}
				return L'?';
			}

		};
	
		struct WRITER {
			WRITER() {
				this->dscr = ENGINE_TYPOGRAPH;
				this->spacing = 4;
				this->length = 0;
				for (DINT r = 0; r < 16; r++) {
					if (r < 8) {
						this->wwrite[r] = L' ';
					}
					this->write[r] = ' ';
				}
			};
			~WRITER() {};
			
			DINT length, spacing;
			TYPOGRAPH dscr;
			DRAWER drawer;
			DUSSCAL read[1];
			LIST <DUSSCAL> text;
			char write[16];
			wchar_t wwrite[8];
			void _type(const char text[], DINT x, DINT y, DINT size = 4, DINT transparency = 1, DINT spacing = 4) {
				DINT px, py, tw = 0, ll = 0;
				PIXEL p = {};
				DUSSCAL tmp = {};
				for (this->length = 0; text[this->length] != '\0'; this->length++) {
					tmp = this->dscr._compare(text[this->length]);
					for (DINT h = 0; h < tmp.literal.size.h; h++) {
						for (DINT w = 0; w < tmp.literal.size.w; w++) {
							p = tmp.literal._get(w, h);
							if (p.color.exist == 1) {
								//p.color = B;
								px = x + (p.x * size) + (ll * size) + (this->length * spacing);
								py = y + (p.y * size);
								p._scale(this->drawer.mem, px, py, size);
							}
							else {
								if(transparency == 1){
								}
							}
						}
					}
					/*
					for (DINT p = 0; p < tmp.literal.size.w * tmp.literal.size.h; p++) {					
						if (tmp.literal.pixel[p].color.exist == 1) {
							px = x + tmp.literal.pixel[p].x * s + (this->length * s * 4);
							py = y + tmp.literal.pixel[p].y * s;
							tmp.literal.pixel[p]._scale(this->drawer.mem, px, py, s);
						}
					}
					*/
					ll += tmp.literal.size.w;
				}


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
			~WINDOW() {};
			HWND handle;
			WNDCLASS info;
			RECT client, window;
			DINT width, heigth, x, y;
			MSG msg;
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

			};


			HWND _set(unsigned int w, unsigned int h, unsigned int x, unsigned int y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Engine", WS_OVERLAPPEDWINDOW, this->x, this->y, this->width, this->heigth, NULL, NULL, this->info.hInstance, NULL);
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
		};
		~ENGINE() {};

		WINDOW window;
		WRITER writer;
		GAME game;
		RANDOM rand;
		TIME timer;
		THREAD thread[2];
		LRESULT _caller(HWND window, UINT msg, WPARAM w, LPARAM l) {


			switch (msg) {
			//default:
				/*
			*/
			//system("pause");
				//return DefWindowProc(window, msg, w, l);
			//case WM_ERASEBKGND:
			//	return 1;

			case WM_CLOSE:
			case WM_QUIT:
				this->game.played = 0;
				break;
				/*
			case WM_MOUSEHOVER:
			case WM_NCMOUSEHOVER:
			case WM_MOUSEMOVE:
			case WM_NCMOUSEMOVE:
			case WM_MOUSELEAVE:
			case WM_NCMOUSELEAVE:
			case WM_MOUSEACTIVATE:
			case WM_KEYUP:
			case WM_KEYDOWN:
			case WM_NCPAINT:
			case ENGINE_DRAW:
			case WM_PAINT:
			*/
			default:
				this->writer.drawer._begin(window);
				this->writer.drawer._bkgd(window, { 185, 215, 155 });
				this->writer.drawer._rect(this->game.atlas.measure.x, this->game.atlas.measure.y,this->game.atlas.measure.w, this->game.atlas.measure.h, this->game.atlas.bg);
				DINT wi = LOWORD(w);
				DINT li = LOWORD(l);
				this->_paint(msg, wi, li);
				this->writer.drawer._end(window);
				return DefWindowProc(window, msg, w, l);
			}
			return 0;
		};


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
			/*
			this->writer._type(this->writer._itoc(this->game.statistics.fps.current), 5, 5, 3);
			this->writer._type(this->writer._itoc(this->game.statistics.loop.current), 85, 5, 3);
			this->writer._type(this->writer._itoc(this->game.statistics.current.elapsed), 165, 5, 3);
			this->writer._type(this->writer._itoc(msg), 245, 5, 3);
			this->writer._type(this->writer._itoc(w), 65, 25, 3);
			this->writer._type(this->writer._itoc(l), 95, 25, 3);
			*/
			this->writer._type("& ?.-+0123456789!", 5, 85, 3);
			this->writer._type("abcdefghijklmnopqrstuvwxyz", 5, 125, 2); 
			//this->writer._type(this->writer._itoc(this->game.atlas.resources.length), 10, 250, 2);
			//this->writer._type(this->writer._itoc(this->game.atlas.resources.total), 10, 275, 2);
			
			this->game.atlas._draw(this->writer.drawer.mem);

			for (DINT m = 0; m < this->game.atlas.maps.length; m++) {
				if (this->game.atlas.maps.exist[m] == 1) {
					this->game.atlas.maps.items[m]._draw(this->writer.drawer.mem);
					this->writer._type(this->writer._itoc(this->game.atlas.maps.items[m].measure.x), 10, m * 15 + 200, 2);
					this->writer._type(this->writer._itoc(this->game.atlas.maps.items[m].measure.y), 110, m * 15 + 200, 2);
				}
			}

			DINT view = 1;
			for (DINT d = 0; d < this->game.atlas.creatures.length; d++) {
				if (this->game.atlas.creatures.exist[d] == 1) {
					this->game.atlas.creatures.items[d]._draw(this->writer.drawer.mem);
					if (view == 1) {
						//this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].inventory.items.length), 5, 10 + (d * 25), 2);
						for (DINT i = 0; i < this->game.atlas.creatures.items[d].inventory.items.length; i++) {
							//this->writer._type(this->game.atlas.creatures.item[d].inventory.items.item[i].name.text, 10 + (i * 50), d * 25, 1);
							//this->writer._type(this->writer._itoc(this->game.atlas.creatures.item[d].inventory.items.item[i].amount), 50 + (i * 50), d * 25, 1, 1, 2);
						}
					}
				}
			}


			//this->writer._type(this->writer._itoc(this->game.atlas.resources._amount()), 10, 25);
			for (DINT r = 0; r < this->game.atlas.resources.length; r++) {
				if (this->game.atlas.resources.exist[r] == 1) {
					this->game.atlas.resources.items[r]._draw(this->writer.drawer.mem);
					//this->writer._type(this->writer._itoc(this->game.atlas.resources.item[r].item.amount), 10, (r + 1) * 12, 1);
				}
			}

			
			//this->writer._type(this->writer._itoc(this->game.current._difference(this->game.time)), 105, 5, 3);
			//this->writer._type("0123 A hello.   ", this->game.dice._roll(0, 250), this->game.dice._roll(0, 250), 2);
			//this->writer._type("0123456789 ", 5, 35, 3);

		}
	
	};


}