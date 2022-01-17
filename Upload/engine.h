typedef unsigned int DINT;
typedef int SINT;
#include <time.h>
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
		struct DRAW {
			DRAW(COLOR a = {255, 0, 0}, COLOR b = {}, COLOR c = {}, COLOR d = {}, COLOR e = {}, COLOR f = {}, COLOR g = {}, COLOR h = {}, COLOR i = {}, COLOR j = {}, COLOR k = {}, COLOR l = {}, COLOR m = {}, COLOR n = {}, COLOR o = {0, 0, 255}) {
				DINT mode = 2;
				switch (mode) {
				default: {

					this->position[0]._set(0, 0, a);
					this->position[1]._set(1, 0, b);
					this->position[2]._set(2, 0, c);
					this->position[3]._set(3, 0, d);
					this->position[4]._set(4, 0, e);
					this->position[5]._set(0, 1, f);
					this->position[6]._set(1, 1, g);
					this->position[7]._set(2, 1, h);
					this->position[8]._set(3, 1, i);
					this->position[9]._set(4, 1, j);
					this->position[10]._set(0, 2, k);
					this->position[11]._set(1, 2, l);
					this->position[12]._set(2, 2, m);
					this->position[13]._set(3, 2, n);
					this->position[14]._set(4, 2, o);
					break;
				}
				case 1: {
					this->position[0]._set(0, 0, a);
					this->position[1]._set(0, 1, b);
					this->position[2]._set(0, 2, c);
					this->position[3]._set(0, 3, d);
					this->position[4]._set(0, 4, e);
					this->position[5]._set(1, 0, f);
					this->position[6]._set(1, 1, g);
					this->position[7]._set(1, 2, h);
					this->position[8]._set(1, 3, i);
					this->position[9]._set(1, 4, j);
					this->position[10]._set(2, 0, k);
					this->position[11]._set(2, 1, l);
					this->position[12]._set(2, 2, m);
					this->position[13]._set(2, 3, n);
					this->position[14]._set(2, 4, o);
					break;
				}
				case 2: {
					this->position[0]._set(0, 0, a);
					this->position[1]._set(1, 0, b);
					this->position[2]._set(2, 0, c);
					this->position[3]._set(0, 1, d);
					this->position[4]._set(1, 1, e);
					this->position[5]._set(2, 1, f);
					this->position[6]._set(0, 2, g);
					this->position[7]._set(1, 2, h);
					this->position[8]._set(2, 2, i);
					this->position[9]._set(0, 3, j);
					this->position[10]._set(1, 3, k);
					this->position[11]._set(2, 3, l);
					this->position[12]._set(0, 4, m);
					this->position[13]._set(1, 4, n);
					this->position[14]._set(2, 4, o);
					break;
				}
				}
			};
			~DRAW() {};

			PIXEL position[15];
		};

		struct DRAWER {
			PAINTSTRUCT paint;
			HDC tool, mem;
			RECT client, measure;
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

		};
		
		struct DUSSCAL {
			DUSSCAL(double identifier = 0.0, SINT key = -1, SINT numeric = -1, char character = ' ', char secondary = ' ', DRAW draw = {}) {
				this->identifier = identifier;
				this->key = key;
				this->numeric = numeric;
				this->character[0] = character;
				this->character[1] = secondary;
				this->uCharacter[0] = (unsigned char)this->character[0];
				this->uCharacter[1] = (unsigned char)this->character[1];
				this->wCharacter[0] = (wchar_t)this->character[0];
				this->wCharacter[1] = (wchar_t)this->character[1];
				this->pixel = draw;
				
			};
			~DUSSCAL() {};
			double identifier;
			DINT exist, capital;
			SINT key, numeric;
			char character[2];
			unsigned uCharacter[2];
			wchar_t wCharacter[2];
			BINT bit[8];
			DRAW pixel;
			COUNTER counter;

		};

		struct TYPOGRAPH {
			TYPOGRAPH(DUSSCAL zero = {}, DUSSCAL one = {}, DUSSCAL two = {}, DUSSCAL three = {}, DUSSCAL four = {}, DUSSCAL five = {}, DUSSCAL six = {}, DUSSCAL seven = {}, DUSSCAL eight = {}, DUSSCAL nine = {}, DUSSCAL a = {}, DUSSCAL b = {}, DUSSCAL c = {}, DUSSCAL d = {}, DUSSCAL e = {}, DUSSCAL f = {}, DUSSCAL g = {}, DUSSCAL h = {}, DUSSCAL i = {}, DUSSCAL j = {}, DUSSCAL k = {}, DUSSCAL l = {}, DUSSCAL m = {}, DUSSCAL n = {}, DUSSCAL o = {}, DUSSCAL p = {}, DUSSCAL q = {}, DUSSCAL r = {}, DUSSCAL space = {}, DUSSCAL question = {}) {
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
				this->lit._set(space);
				this->lit._set(question);
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
			};
			~WRITER() {};
			
			DINT length, spacing;
			TYPOGRAPH dscr;
			DRAWER drawer;
			DUSSCAL read[1];
			LIST <DUSSCAL> text;
			char write[8];
			wchar_t wwrite[8];

			void _type(const char text[], DINT x, DINT y, DINT s = 4) {
				DINT px, py, tw = 0;
				for (this->length = 0; text[this->length] != '\0'; this->length++) {
					this->read[this->length] = this->dscr._compare(text[this->length]);

					for (DINT p = 0; p < 15; p++) {
						px = x + this->read[this->length].pixel.position[p].x * s + (this->length * s * 4);
						py = y + this->read[this->length].pixel.position[p].y * s;
						this->read[this->length].pixel.position[p]._scale(this->drawer.mem, px, py, s);
					}
				}


			}

			char* _itoc(DINT number = 9) {
				DINT length = 1;
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
			};
			~WINDOW() {};
			HWND handle;
			WNDCLASS info;
			RECT client;
			unsigned int width, heigth, x, y;
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
				return this->handle;
			}

			void _client() {
				GetClientRect(this->handle, &this->client);
			}

		};

		WINDOW window;
		WRITER writer;
		GAME game;

		LRESULT _caller(HWND window, UINT msg, WPARAM w, LPARAM l) {


			switch (msg) {
			default:
				/*
			*/
				//system("pause");
				return DefWindowProc(window, msg, w, l);
			case WM_ERASEBKGND:
				return 1;

			case WM_MOUSEHOVER:
			case WM_NCMOUSEHOVER:
			case WM_MOUSEMOVE:
			case WM_NCMOUSEMOVE:
			case WM_MOUSELEAVE:
			case WM_NCMOUSELEAVE:
			case WM_MOUSEACTIVATE:
			case WM_PAINT:
				this->writer.drawer._begin(window);
				this->writer.drawer._bkgd(window, {185, 215, 155});
				this->_paint();
				this->writer.drawer._end(window);
				break;
			}
			return 0;
		};

		void _config() {
			srand((unsigned int)time(NULL));
			this->game.time._clock();
			this->game.played = 1;
			this->window._client();
			this->game.client.x = this->window.client.left;
			this->game.client.y = this->window.client.top;
			this->game.client.w = this->window.client.right;
			this->game.client.h = this->window.client.bottom;
		}

		void _paint() {
			this->writer._type(this->writer._itoc(this->game.statistics.fps.current), 5, 5, 3);
			this->writer._type(this->writer._itoc(this->game.statistics.loop.current), 85, 5, 3);
			this->writer._type(this->writer._itoc(this->game.dus.length), 5, 25, 3);
			this->writer._type(this->writer._itoc(this->game.current.elapsed), 5, 55, 3);
			this->writer._type("?. 0123456789", 5, 85, 3);
			this->writer._type("abcdefghijklmnopqrstuvwxyz", 5, 125, 3);
			
			//this->writer._type(this->writer._itoc(this->game.dus.item[0].))
			
			for (DINT d = 0; d < this->game.dus.length; d++) {
				if (this->game.dus.existance[d] == 1) {
					//this->writer._type(this->game.dus.item[d].name.text, 5, 155 + (d * 25), 3);
				//	if(this->game.dus.item[d].model.position.x >= 0) this->writer._type(this->writer._itoc(this->game.dus.item[d].model.position.x), 5, 55 + (d * 25), 3);
				//	if(this->game.dus.item[d].model.position.y >= 0) this->writer._type(this->writer._itoc(this->game.dus.item[d].model.position.y), 55, 55 + (d * 25), 3);
					//if (this->game.dus.item[d].model.position.x >= 0) this->writer._type(this->writer._itoc(this->game.dus.item[d].model.client.w), 5, 105 + (d * 25), 3);
					//if (this->game.dus.item[d].model.position.y >= 0) this->writer._type(this->writer._itoc(this->game.dus.item[d].model.client.h), 55, 105 + (d * 25), 3);
				
				}
			}

			for (DINT c = 0; c < this->game.carrier.length; c++) {
				if (this->game.carrier.existance[c] == 1) {
					this->writer._type(this->game.carrier.item[c].name.text, 5, 155 + (c * 25), 3);
					
					if(this->game.carrier.item[c].unique >= 0) this->writer._type(this->writer._itoc(this->game.carrier.item[c].unique), 125, 155 + (c * 25), 3);
					
				}
			}

			for (DINT c = 0; c < this->game.carrier.length; c++) {
				if (this->game.carrier.existance[c] == 1) {
					this->game.carrier.item[c]._draw(this->writer.drawer.mem);
				}
			}
			
			//this->writer._type(this->writer._itoc(this->game.current._difference(this->game.time)), 105, 5, 3);
			//this->writer._type("0123 A hello.   ", this->game.dice._roll(0, 250), this->game.dice._roll(0, 250), 2);
			//this->writer._type("0123456789 ", 5, 35, 3);

		}
	};


}