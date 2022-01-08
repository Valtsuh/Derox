typedef unsigned int DINT; 
typedef int SINT;
struct RANDOM {
	RANDOM(DINT min = 0, DINT max = 1) {
		//this->_set(min, max);
	};
	~RANDOM() {
		this->_set(0, 1);
	};
	DINT min, max, value, tries, comparer;

	void _s() {

		srand((unsigned int)time(NULL));
	}

	DINT _set(DINT min, DINT max) {
		this->tries = 0;
		this->value = 0;
		this->comparer = 0;
		this->min = min;
		this->max = max;
		return this->max;
	}

	DINT _generate() {
		if (this->min == 0) {
			this->value = rand() % this->max;
		}
		else {
			this->value = rand() % (this->max - this->min) + this->min;
		}
		return this->value;
	}

	DINT _roll(SINT min = -1, SINT max = -1) {
		if (min > -1 && max > -1) {
			this->_set(min, max);
		}
		if (this->min == 0) {
			this->value = rand() % (this->max + 1);
		}
		else {
			this->value = this->min + (rand() % this->max);
		}
		return this->value;
	}

	DINT _compare(DINT comparer = 0, SINT min = -1, SINT max = -1) {
		this->comparer = comparer;
		if (this->comparer == this->value && this->tries < 5) {
			this->_roll(min, max);
			this->tries++;
			this->_compare(this->value);
		}
		return this->value;
	}

};
struct TIME { // As predefined -> [word]
	TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->success = 0;
		this->precision = 0;
		this->count = 0;
		this->system = {};
		this->difference = 0;
		this->elapsed = 0;
		this->hms = this->_msh(1);
		this->mms = this->_msm(1);
		this->sms = this->_mss(1);
	};
	~TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
	};
	DINT year, month, day, hour, hms, minute, mms, second, sms, millisecond, success, precision, count, elapsed, difference;
	SYSTEMTIME system;

	void _clock() {
		this->_reset();
		GetLocalTime(&this->system);
		this->year = this->system.wYear;
		this->month = this->system.wMonth;
		this->day = this->system.wDay;
		this->hour = this->system.wHour;
		this->minute = this->system.wMinute;
		this->second = this->system.wSecond;
		this->millisecond = this->system.wMilliseconds;
	}
	DINT _difference(TIME time) {
		this->elapsed = 0;
		this->_clock();
		DINT a = this->_mst();
		DINT b = time._mst();
		if (a > b) this->elapsed = a - b; else this->elapsed = b - a;
		this->elapsed /= 1000;
		if (this->elapsed > 0) return this->elapsed; else return 1;
	}
	void _reset() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
	}

	DINT _h(DINT mshamount = 0) {
		if (mshamount > 0) {
			return (((mshamount / 60) / 60) / 1000);
		}
		else {
			return 0;
		}
	}

	DINT _m(DINT msmamount = 0) {
		if (msmamount > 0) {
			return ((msmamount / 60) / 1000);
		}
		else {
			return 0;
		}
	}

	DINT _s(DINT mssamount = 0) {
		if (mssamount > 0) {
			return (mssamount / 1000);
		}
		else {
			return 0;
		}
	}

	DINT _msh(DINT amount = 0) {
		if (amount > 0) {
			return (((amount * 60) * 60) * 1000);
		}
		else {
			if (this->hour > 0) {
				return (((this->hour * 60) * 60) * 1000);
			}
			else {
				return 0;
			}
		}
	}

	DINT _msm(DINT amount = 0) {
		if (amount > 0) {
			return ((amount * 60) * 1000);
		}
		else {
			if (this->minute > 0) {
				return ((this->minute * 60) * 1000);
			}
			else {
				return 0;
			}
		}
	}

	DINT _mss(DINT amount = 0) {
		if (amount > 0) {
			return (amount * 1000);
		}
		else {
			if (this->second > 0) {
				return (this->second * 1000);
			}
			else {
				return 0;
			}
		}
	}

	DINT _mst(DINT offset = 0) { // addition (?), total in milliseconds
		return this->_msh() + this->_msm() + this->_mss() + this->millisecond + offset;
	}
};

struct COUNTER {
	COUNTER() {
		this->current = 0;
		this->exist = 0;
	};
	~COUNTER() {};
	DINT current, exist;

	void _clear() {
		this->current = 0;
		this->exist = 0;
	}
};
struct STRING {
	STRING() {
		this->length = 0;
		for (DINT l = 0; l < 128; l++) {
			this->wtext[l] = L' ';
			this->text[l] = ' ';
			this->utext[l] = (unsigned char)' ';
		}
	};
	~STRING() {};
	DINT length;
	wchar_t wtext[128];
	char text[128];
	unsigned char utext[128];

	void _clear() {
		for (DINT length = 0; length < 128; length++) {
			this->wtext[length] = L' ';
			this->text[length] = ' ';
		}
		this->length = 0;
	}
		
	void _reverse() {
		STRING temp;
		temp._clear();
		for (temp.length = 0; temp.length < this->length; temp.length++) {
			temp.wtext[temp.length] = this->wtext[this->length - temp.length - 1];
			temp.text[temp.length] = this->text[this->length - temp.length - 1];
			temp.utext[temp.length] = this->utext[this->length - temp.length - 1];
		}
		*this = temp;


	}

	void _write(const char text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = text[this->length];
			this->wtext[this->length] = (wchar_t)text[this->length];
			this->utext[this->length] = (unsigned char)text[this->length];
		}
	}

	void _uwrite(unsigned char text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = (wchar_t)text[this->length];
			this->utext[this->length] = text[this->length];
		}
	}

	void _wwrite(const wchar_t text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = text[this->length];
			this->utext[this->length] = (unsigned char)text[this->length];
		}
	}
};

template <typename LIST_ITEM>
struct LIST {
	LIST() {
		this->length = 0;
		this->total = 0;
		for (DINT i = 0; i < 256; i++) {
			this->item[i];
		}
	};
	~LIST() {};

	DINT length, total;
	LIST_ITEM item[256]; // approx. max array length
	DINT existance[256];
	DINT _set(LIST_ITEM item) {
		for (DINT d = 0; d < 256; d++) {
			if (this->existance[d] == 0) {
				this->item[d] = item;
				this->existance[d] = 1;
				this->length += 1;
				this->total++;
				return d;
			}
		}
		return 0;
	}

	void _remove(DINT position) {
		this->item[position] = { 0 };
		this->existance[position] = 0;
		this->length -= 1;
	}

	LIST_ITEM _get(DINT position = 0) {
		return this->item[position];
	}
};
struct DIMENSION  {
	DIMENSION(DINT x = 0, DINT y = 0, DINT w = 0, DINT h = 0, DINT z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->width = w;
		this->height = h;
	};
	~DIMENSION() {};
	DINT x, y, z, width, height;

	void _set(DIMENSION dimension) {
		this->x = dimension.x;
		this->y = dimension.y;
		this->width = dimension.width;
		this->height = dimension.height;
		this->z = dimension.z;
	}
};

#pragma warning(disable : 4996)

//#include <iostream>
//#include <fstream>
#include <thread>
#include "Engine.graphics.h"

#include "Engine.game.h"

using namespace std;

namespace engine {
	struct ENGINE {
		struct DUSSCAL {
			DUSSCAL(double identifier = 0.0, DINT key = 0, char character = '?', DINT numeric = 0, DINT exist = 0) {
				this->identifier = identifier;
				this->key = key;
				this->numeric = numeric;
				this->character = character;
				this->exist = exist;
				this->counter = {};
			};
			~DUSSCAL() {};
			double identifier;
			DINT numeric, key, exist;
			char character;
			COUNTER counter;
		};
		struct NUMERAL {
			NUMERAL(double identifier = 0.0, DINT key = 0, char character = '?', DINT numeric = 0, DINT exist = 0) {
				this->identifier = identifier;
				this->key = key;
				this->numeric = numeric;
				this->character = character;
				this->exist = exist;
				this->counter = {};
			};
			~NUMERAL() {};
			double identifier;
			DINT numeric, key, exist;
			char character;
			COUNTER counter;

			DINT _amount() {
				return this->counter.current;
			}

			char _compare(DINT number) {
				if (this->numeric == number) return this->character; else return '?';
			}
		};
		struct LITERAL { 
			LITERAL(double identifier = 0.0, DINT key = 0, char smaller = '?', char bigger = '?', DINT exist = 0) {
				this->identifier = identifier;
				this->key = key;
				this->smaller = smaller;
				this->bigger = bigger;
				this->exist = exist;
				this->counter = {};
			};
			~LITERAL() {};
			double identifier;
			DINT key, exist;
			char smaller, bigger;
			COUNTER counter;
		};
		struct TYPOGRAPH {
			TYPOGRAPH(DINT exist = 0, NUMERAL zero = {}, NUMERAL one = {}, NUMERAL two = {}, NUMERAL three = {}, NUMERAL four = {}, NUMERAL five = {}, NUMERAL six = {}, NUMERAL seven = {}, NUMERAL eight = {}, NUMERAL nine = {}, LITERAL a = {}, LITERAL b = {}, LITERAL c = {}, LITERAL d = {}, LITERAL e = {}, LITERAL f = {}, LITERAL g = {}, LITERAL h = {}, LITERAL i = {}, LITERAL j = {}, LITERAL k = {}, LITERAL l = {}, LITERAL m = {}, LITERAL n = {}, LITERAL o = {}, LITERAL p = {}, LITERAL q = {}, LITERAL r = {}, LITERAL s = {}, LITERAL t = {}, LITERAL u = {}, LITERAL v = {}, LITERAL w = {}, LITERAL x = {}, LITERAL y = {}, LITERAL z = {}, LITERAL comma = {}, LITERAL dot = {}, LITERAL space = {}, LITERAL exclamation = {}, LITERAL question = {}, DUSSCAL notranslation = {}) {
				this->zero = zero;
				this->one = one;
				this->two = two;
				this->three = three;
				this->four = four;
				this->five = five;
				this->six = six;
				this->seven = seven;
				this->eight = eight;
				this->nine = nine;
				this->a = a;
				this->b = b;
				this->c = c;
				this->d = d;
				this->e = e;
				this->f = f;
				this->g = g;
				this->h = h;
				this->i = i;
				this->j = j;
				this->k = k;
				this->l = l;
				this->m = m;
				this->n = n;
				this->o = o;
				this->p = p;
				this->q = q;
				this->r = r;
				this->s = s;
				this->t = t;
				this->u = u;
				this->v = v;
				this->w = w;
				this->x = x;
				this->y = y;
				this->z = z;
				this->comma = comma;
				this->dot = dot;
				this->space = space;
				this->exist = exist;
				this->exclamation = exclamation;
				this->question = question;
				this->notranslation = notranslation;
				this->other = {};
				this->exist = exist;
				this->result = 0;
			};
			~TYPOGRAPH() {

			};
			DINT exist, result;
			LITERAL a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, other, dot, comma, space, exclamation, question, literal, dummy;
			NUMERAL zero, one, two, three, four, five, six, seven, eight, nine, nummy, numeral;
			DUSSCAL notranslation;

			char _ncompare(DINT number) {
				if (this->zero.numeric == number) return this->zero.character;
				if (this->one.numeric == number) return this->one.character;
				if (this->two.numeric == number) return this->two.character;
				if (this->three.numeric == number) return this->three.character;
				if (this->four.numeric == number) return this->four.character;
				if (this->five.numeric == number) return this->five.character;
				if (this->six.numeric == number) return this->six.character;
				if (this->seven.numeric == number) return this->seven.character;
				if (this->eight.numeric == number) return this->eight.character;
				if (this->nine.numeric == number) return this->nine.character;

				return '?';
			}

		};
		struct REGEX {
			REGEX() {
				this->temp._clear();
			};
			~REGEX() {};
			STRING temp;

			void _read(const wchar_t text[]) {
				this->temp._wwrite(text);
			}

			wchar_t* _cut(DINT amount) {
				this->temp.wtext[this->temp.length - amount] = L'\0';
				this->temp.length -= amount;
				return this->temp.wtext;
			}

		};
		struct WRITER {
			WRITER() {
				this->typer = ENGINE_DATABASE_TYPOGRAPH;
				for (DINT d = 0; d < 8; d++) this->temp[d] = {};
			};
			~WRITER() {};

			TYPOGRAPH typer;
			STRING string;
			wchar_t temp[8];

			wchar_t* _itow(DINT number = 9, DINT length = 1) {
				for (DINT i = 0; i < 8; i++) this->temp[i] = L'0';
				NUMERAL numerals[8] = {};
				if (number > 0) {
					do{
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
					for (DINT i = 0; i < 8; i++) this->temp[i] = L'x';
				}
				DINT brk = 0;
				for (DINT position = 0; position < 8; position++) {
					if (position < length) {
						for (DINT number = length - position; number > 0; number--) {
							if (numerals[number - 1].counter.current > 0) {
								this->temp[position] = (wchar_t)this->typer._ncompare(numerals[number - 1].counter.current);
								break;
							}
							else {
								this->temp[position] = L'0';
								break;
							}
						}
					}
				}
				/*
				numbers[0] = this->typer._ncompare(numerals[7].counter.current);
				numbers[1] = this->typer._ncompare(numerals[6].counter.current);
				numbers[2] = this->typer._ncompare(numerals[5].counter.current);
				numbers[3] = this->typer._ncompare(numerals[4].counter.current);
				numbers[4] = this->typer._ncompare(numerals[3].counter.current);
				numbers[5] = this->typer._ncompare(numerals[2].counter.current);
				numbers[6] = this->typer._ncompare(numerals[1].counter.current);
				numbers[7] = this->typer._ncompare(numerals[0].counter.current);
				*/
				return this->temp;
			}

			wchar_t* _read(char text[]) {
				wchar_t read[128];
				for (DINT l = 0; l < 128; l++) {
					if (text[l] == '\0') {
						read[l] = L'\0';
						break;
					}
					else {
						read[l] = (wchar_t)text[l];
					}
				}
				return read;
			}

			wchar_t* _cread(const char text[]) {
				this->string._write(text);
				return this->string.wtext;
			}


		};
		struct THREAD {
			THREAD() {
				//this->identifier = GetCurrentThreadId();
			};
			~THREAD() {};
			DINT identifier, status;
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
			DIMENSION size, get, mouse;
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


			HWND _set(DINT w = 640, DINT h = 480, DINT x = 100, DINT y = 100) {
				this->size.x = x;
				this->size.y = y;
				this->size.width = w;
				this->size.height = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Engine", WS_OVERLAPPEDWINDOW, this->size.x, this->size.y, this->size.width, this->size.height, NULL, NULL, this->info.hInstance, NULL);
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

			HWND _position(DINT w = 640, DINT h = 480, DINT x = 100, DINT y = 100) {
				this->size.x = x;
				this->size.y = y;
				this->size.width = w;
				this->size.height = h; 
				SetWindowPos(this->handle, HWND_TOP, this->size.x, this->size.y, this->size.width, this->size.height, SWP_SHOWWINDOW);
				return this->handle;
			}

		};
		
		struct DETOX_FILE {
			DETOX_FILE() {};
			~DETOX_FILE() {};
			COUNTER counter;
			STRING name, cd, temp, full;
			REGEX regex;
			wchar_t* _cd() {
				wchar_t pth[128];
				GetModuleFileName(NULL, pth, 64);
				this->regex._read(pth);
				return this->_path();

			}

			DINT _load(const wchar_t name[]) {
				this->regex._read(name);
				this->_path();
				//this->i.open(this->name.text, ios::binary);
				return 0;
			}

			wchar_t* _path() {  
				STRING file;
				file._clear();
				this->temp._clear();
				for (this->counter.current = this->regex.temp.length; this->regex.temp.wtext[this->counter.current] != L'\\'; this->counter.current--) {
					this->temp.wtext[this->regex.temp.length - this->counter.current - 1] = this->regex.temp.wtext[this->counter.current];
					this->temp.text[this->regex.temp.length - this->counter.current - 1] = (char)this->regex.temp.wtext[this->counter.current];
					this->temp.utext[this->regex.temp.length - this->counter.current - 1] = (unsigned char)this->regex.temp.wtext[this->counter.current];
					if ((SINT)this->counter.current == -1) break; // full path to file or \\file
				};
				this->temp.length = this->regex.temp.length - this->counter.current - 1; // -1 exclude '\'
				this->full = this->regex.temp;
				this->regex._cut(this->regex.temp.length - this->counter.current - 1); // -1 include '\'
				this->temp._reverse();
				this->name = this->temp;
				this->cd = this->regex.temp;
				this->regex.temp._clear();
				this->counter._clear();
				return this->cd.wtext;
			}
		};
		
		struct IMAGE {
			IMAGE() {
				this->length = 0;
				for (DINT d = 0; d < 54; d++) this->info[d] = (unsigned char)' ';
				this->open = 0;
			};
			~IMAGE() {};
			PIXEL pixel[1024]; // 32 * 32
			DETOX_FILE file;
			//ifstream i;
			//ofstream o;
			unsigned char info[54];
			int length, open;
			//PIXEL pixel[4096]; // 64 * 64


			DINT _read(DETOX_FILE file) {
				this->length = 0;
				this->file = file;
				/*
				FILE* f = fopen(file.name.text, "rb");
				fread(this->info, sizeof(unsigned char), 54, f);
				*/

				//this->o.open(this->file.name.text, ios::binary);
				//this->open = this->o.is_open();

				return 0;
			}
		};

		ENGINE() {
			this->played = 0;
			this->sleep = 1;
		};
		~ENGINE() {};

		IMAGE image;
		DINT played, sleep;
		WINDOW window;
		CANVAS background, test, canvas;
		WRITER writer;
		TIME time, elapse;
		GAME game;
		RANDOM r;

		void _config() {
			this->game.canvas = this->canvas;
			this->game.window = this->window.handle;
			this->r._s();
		}

		DINT _play() {
			if (this->game.set != 1) {
				this->game._set();
			}

			this->game._play();

			return 1;
		}

		DINT _gather() {
			this->played = this->_play();
			//UpdateWindow(this->window.handle);
			if (PeekMessage(&this->window.msg, this->window.handle, 0, 0, PM_REMOVE) != -1) {
				TranslateMessage(&this->window.msg);
				DispatchMessage(&this->window.msg);
			}
			RedrawWindow(this->window.handle, NULL, NULL, WM_NCPAINT);
		
			if (this->window.handle == NULL) this->played = 0;
			return this->played;
		};

		DINT _rest() {

			this->game.elapsed.current = this->elapse._difference(this->time);
			this->game.counter.current++;
			if (this->game.counter.current % 50 == 0) this->game.lps.current = (DINT)(this->game.counter.current / this->game.elapsed.current);
			if (ENGINE_DATABASE_SLEEP) {
				DINT sleep = this->game.lps.current - 60;
				if (this->game.lps.current > 60) {
					if (sleep < 0) sleep = 1;
				}
				else {
					sleep = ENGINE_DATABASE_FPS_SMOOTHER;
				}


				Sleep(sleep + ENGINE_DATABASE_SLOW_DOWN);

			}
			else {


			}
			return this->played;
		}

		LRESULT _caller(HWND window, UINT msg, WPARAM w, LPARAM l) {
			DINT err = GetLastError();
			switch (msg) {
			default:	
				//SetCapture(window);
				return DefWindowProc(window, msg, w, l);
			case WM_MOUSEMOVE:
				// Lag
				//SetCapture(window);
				POINT p;
				if (GetCursorPos(&p)) {
					if (ScreenToClient(window, &p)) {
						this->window.mouse.x = p.x;
						this->window.mouse.y = p.y;
					}
				}
				
				//this->window.mouse.
				break;
			case WM_LBUTTONUP:
				if (this->game.dus.length > 0) {
					this->game.dus.item[0].dimension._set({ 0, 0, 16, 16 });
					for (DINT d = 0; d < this->game.dus.length; d++) {
						//this->game.dus.item[d].collision._reset();
					}
				}
				break;
			case WM_RBUTTONUP:
				if (this->game.dus.length > 0) {
					this->game.dus.item[0].dimension._set({ 250, 250, 16, 16 });
					for (DINT d = 0; d < this->game.dus.length; d++) {
						//this->game.dus.item[d].collision._reset();
					}
				}
				break;
			case WM_DESTROY:
				this->played = 0;
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
				//this->game.controls._push(w, ENGINE_DATABASE_KEY_PUSHED);
				break;
			case WM_KEYUP:
				switch (this->game.controls._state(w)) {
				default:
				case ENGINE_DATABASE_KEY_PUSHED:
					this->game.controls._push(w, ENGINE_DATABASE_KEY_NOT_PUSHED);
					break;
				case ENGINE_DATABASE_KEY_NOT_PUSHED:
					this->game.controls._push(w, ENGINE_DATABASE_KEY_PUSHED);
					break;
				}
			case WM_PAINT:
				this->_paint(window);
				break;
			}
			return NULL;
		}

		void _paint(HWND window) {
			this->canvas._mbegin(window);
			this->canvas._bkgd({ 120, 225, 125 });
			STRING string;
			string._wwrite(this->writer._itow(this->game.elapsed.current, 8));
			this->canvas._text(string.wtext, 8, 5, 5);
			string._wwrite(this->writer._itow(this->game.counter.current, 8));
			this->canvas._text(string.wtext, 8, 85, 5);
			string._wwrite(this->writer._itow(this->game.lps.current, 8));
			this->canvas._text(string.wtext, 8, 165, 5);
			//string._wwrite(this->writer._itow(this->game.dus.length, 8));
			string._wwrite(this->writer._itow(this->game.dus.length, 4));
			this->canvas._text(string.wtext, 4, 245, 5);
			string._wwrite(this->writer._itow(this->game.dus.total, 4));
			//string._wwrite(this->writer._itow(GetTickCount(), 8));
			this->canvas._text(string.wtext, 4, 325, 5);
			this->canvas._text(this->writer._itow(this->window.mouse.x, 4), 4, 405, 5);
			this->canvas._text(this->writer._itow(this->window.mouse.y, 4), 4, 445, 5);
			//DETOX_FILE f;
			//f._load(L"carcass.64x64.jpg");
			//this->canvas._text(f.name.wtext, f.name.length, 325, 5);
			//string._wwrite(this->writer._itow(err, 5));
			//this->canvas._text(string.wtext, 5, 165, 5);
			/*
			DETOX_FILE file;
			file._load(L"C:\\Users\\narud\\Desktop\\Detox\\Engine\\Debug\\carcass.64x64.jpg");

			DINT view = 1;
			if (view == 1) {
				this->canvas._text(file.full.wtext, file.full.length, 5, 45);
				this->canvas._text(file.cd.wtext, file.cd.length, 5, 65);
				this->canvas._text(file.name.wtext, file.name.length, 5, 85);
				this->canvas._text(this->writer._itow(file.temp.length, 8), 8, 5, 105);
				this->canvas._text(file.temp.wtext, file.temp.length, 85, 105);
			}
			else {
			}
			//this->image._read(file);
			*/



			//this->canvas._text(this->writer._itow(this->game.dus.length, 2), 2, 245, 5);
			switch (this->game.controls._state(ENGINE_DATABASE_KEY_SELECT)) {
			default:
			case ENGINE_DATABASE_KEY_NOT_PUSHED:
				break;
			case ENGINE_DATABASE_KEY_PUSHED:
			{
				DINT view = 3;
				for (DINT d = 0; d < this->game.dus.length; d++) {
					if (this->game.dus.existance[d] == 1) {
						this->canvas._text(this->writer._itow(this->game.dus.item[d].unique, 3), 3, 5, 25 + (d * 20));
						this->canvas._text(this->game.dus.item[d].name.wtext, 12, 35, 25 + (d * 20));
						switch (view) {
						default:

							this->canvas._text(this->writer._itow(this->game.dus.item[d].health.value, 2), 2, 125, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].damage.value, 2), 2, 145, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].experience.value, 2), 2, 165, 25 + (d * 20));

							this->canvas._text(this->writer._itow(this->game.dus.item[d].offense.value, 2), 2, 205, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].defense.value, 2), 2, 225, 25 + (d * 20));

							this->canvas._text(this->writer._itow(this->game.dus.item[d].collision.amount.current, 2), 2, 265, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].collision.from.current, 2), 2, 285, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].collision.to.current, 2), 2, 305, 25 + (d * 20));

							break;
						case 1:
							this->canvas._text(this->writer._itow(this->game.dus.item[d].move, 4), 4, 5, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].dimension.x, 4), 4, 45, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].to.x + this->game.dus.item[d].to.width, 4), 4, 85, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].previous.x, 4), 4, 125, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].dimension.y, 4), 4, 165, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].to.y + this->game.dus.item[d].to.height, 4), 4, 205, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].previous.y, 4), 4, 245, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].collision.current, 4), 4, 285, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].steady.current, 4), 4, 325, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].unique, 4), 4, 365, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].unique, 4), 4, 405, 25 + (d * 20));
							this->canvas._text(this->game.dus.item[d].name.wtext, this->game.dus.item[d].name.length, 445, 25 + (d * 20));
							break;
						case 2:
							this->canvas._text(this->game.dus.item[d].inventory.item[0].name.wtext, 10, 125, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].inventory.item[0].amount.current, 3), 3, 205, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.dus.item[d].collision.current, 3), 3, 275, 25 + (d * 20));
							this->canvas._text(this->writer._itow(this->game.building.collision.current, 3), 3, 315, 25 + (d * 20));
							break;
						case 3:
							if (this->game.dus.item[d]._description(this->window.mouse) == 1) {
								//this->canvas._text(this->game.dus.item[d].info.description.wtext, this->game.dus.item[d].info.description.length, 125, 25 + (d * 20));
								this->canvas._text(this->game.dus.item[d].info.description.wtext, this->game.dus.item[d].info.description.length, this->window.mouse.x, this->window.mouse.y);
							}
							break;
						}
					}
				}
			}
			break;
			}


			this->game.building._pixelize(this->canvas.mem);
			if (this->game.building._description(this->window.mouse)) {
				this->canvas._text(this->game.building.info.description.wtext, this->game.building.info.description.length, this->window.mouse.x, this->window.mouse.y);
			}
			for (DINT d = 0; d < this->game.dus.length; d++) {
				if (this->game.dus.existance[d] == 1) {
					this->game.dus.item[d]._pixelize(this->canvas.mem);
				}
			}

			this->canvas._mend(window);
			//ReleaseCapture(); 
		}
	};

};