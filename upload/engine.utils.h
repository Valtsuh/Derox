typedef int DINT;
typedef signed int SINT;
typedef long int LINT;
typedef long long int SLINT;
typedef long double LBLE;

enum class DIR { ASC = 1, DESC = -1 };

#define ENGINE_DATABASE_LIST_LENGTH_MAX 128
#define ENGINE_DATABASE_INDEX_BLOCK_SIZE 8
#define ENGINE_TEXT_MAX_LENGTH 96
#define ENGINE_DRAW	101
#include <time.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <string>


struct UTILS {
	struct HEX {
		HEX() {
			this->value = 0x1;
		};

		DINT value;

	};
	struct MATRIX {
		double m[4][4] = { 0 };
	};
	static char _ntc(DINT num) {
		if (num == 0) return '0';
		if (num == 1) return '1';
		if (num == 2) return '2';
		if (num == 3) return '3';
		if (num == 4) return '4';
		if (num == 5) return '5';
		if (num == 6) return '6';
		if (num == 7) return '7';
		if (num == 8) return '8';
		if (num == 9) return '9';
		return '?';
	}
	static DINT _ctn(char num) {
		if (num == '0') return 0;
		if (num == '1') return 1;
		if (num == '2') return 2;
		if (num == '3') return 3;
		if (num == '4') return 4;
		if (num == '5') return 5;
		if (num == '6') return 6;
		if (num == '7') return 7;
		if (num == '8') return 8;
		if (num == '9') return 9;
		return 0;
	}
	static SINT _isnum(const char character) {
		if (character == '0') return 0;
		if (character == '1') return 1;
		if (character == '2') return 2;
		if (character == '3') return 3;
		if (character == '4') return 4;
		if (character == '5') return 5;
		if (character == '6') return 6;
		if (character == '7') return 7;
		if (character == '8') return 8;
		if (character == '9') return 9;
		return -1;

	}

	static SLINT _tnth(DINT a, DINT th) {
		SLINT value = a;
		for (; th > 0; th--) value *= 10;
		return value;
	}


	static SLINT _abs(SLINT value = -1) {
		if (value < 0) {
			value = (-1) * value;
		}
		return value;
	}
	static double _slope(double ax, double bx, double ay, double by) {
		if (ax != bx) {
			return (by - ay) / (bx - ax);
		}
		else {
			return 0.0;
		}
	}

	static float _distance(SINT ax, SINT ay, SINT bx, SINT by) {
		SLINT x = (SLINT)ax - (SLINT)bx;
		SLINT y = (SLINT)ay - (SLINT)by;
		return (float)(UTILS::_abs(x) + UTILS::_abs(y));
	}

	static float _heuristic(SINT ax, SINT ay, SINT bx, SINT by) {
		float d = UTILS::_distance(ax, ay, bx, by);
		return d;
	}

	static DINT _direction(SINT fx, SINT fy, SINT tx, SINT ty) {
		//std::cout << "\n>" << fx << ", " << fy << " - " << tx << ", " << ty;
		if (fx + 1 == tx && fy == ty) return 6;
		if (fx - 1 == tx && fy == ty) return 4;
		if (fx == tx && fy + 1 == ty) return 2;
		if (fx == tx && fy - 1 == ty) return 8;
		return 5;

	}
	
};
struct BINT {
	BINT(DINT value = 0) {
		this->value = value;
	};
	~BINT() {
		this->value = 0;
	};
	DINT value;

	operator DINT() const {
		return this->value;
	}

	DINT operator++(int amount) {
		this->value = this->value + 1;
		return this->value;
	}

	DINT operator--(int amount) {
		if (this->value > 0) this->value = this->value - 1;
		return this->value;
	}
};

struct DUAL {
	SLINT i;
	double d;

	operator SLINT() const {
		return this->i;
	}
};
struct COUNTER {
	COUNTER(DINT total = 0) {
		this->value = 0;
		this->current = total;
		this->total = total;
	};
	~COUNTER() {
		this->value = 0;
		this->current = 0;
		this->total = 0;
	};
	SINT value, current, total;

	operator SINT() const {
		return this->current;
	}
	void operator =(SINT value) {
		this->current = value;
	}
	void operator ++(SINT value) {
		this->current += value;
	}
	void _add(DINT value = 0) {
		this->current += value;
		this->total += value;
	}

	DINT _difference(COUNTER counter) {
		return this->current - counter.current;
	}

	void _reset() {
		this->current = 0;
		this->total = 0;
		this->value = 0;
	}

	DINT _full() {
		return (this->current >= this->total) ? (1) : (0);
	}
};

struct RANDOM {
	RANDOM() {
		this->min = 0;
		this->max = 1;
		this->value = 0;
	};
	~RANDOM() {
		this->min = 0;
		this->max = 1;
		this->value = 0;
	};
	DINT min, max, value;


	DINT _roll(SINT min = -1, SINT max = -1) {
		if (min < 0 && max >= 0) {
			if (this->min == 0) max++;
			this->value = rand() % max + this->min;
		}
		if (min >= 0 && max < 0) {
			if (min == 0) this->max++;
			this->value = rand() % this->max + min;
			if (min == 0) this->max--;
		}
		if (min < 0 && max < 0) {
			if (this->min == 0) this->max++;
			this->value = rand() % this->max + this->min;
			if (this->min == 0) this->max--;
		}
		if (min >= 0 && max >= 0) {
			if (min == 0) max++;
			this->value = rand() % max + min;
		}
		return this->value;
	}

	double _droll(double min = -1.0, double max = 1.0) {
		double value = 0.0;
		value = min + (double)(rand() % (SINT)max) + max / 2;
		std::cout << "\nRoll: " << value;
		return value;
	}

};

struct PAIR {
	PAIR(DINT a, DINT b) {
		this->a = a;
		this->b = b;
	};
	PAIR() {
		this->a = 0;
		this->b = 0;
	};

	DINT a, b;
};
struct DIMENSION {
	DIMENSION(DINT x = 0, DINT y = 0) {
		this->x = x;
		this->y = y;
		this->w = 0;
		this->h = 0;
		this->d = 0;
		this->size = 0;
		this->direction = 0;
		this->id = -1;
	}
	DIMENSION(DINT x, DINT y, DINT w, DINT h, DINT d = 0) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->d = d;
		this->size = 1;
		this->direction = 0;
		this->id = -1;
	}
	~DIMENSION() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->size = 0;
		this->direction = 0;
	};
	DINT x, y, w, h, d, size, direction;
	SINT id;

	DINT _within(DINT x, DINT y) {
		return (x >= this->x && x <= this->w + this->x && y >= this->y && y <= this->h + this->y);
	}
	void _set(DIMENSION dimension) {
		this->x = dimension.x;
		this->y = dimension.y;
		this->w = dimension.w;
		this->h = dimension.h;
		this->size = dimension.size;
	}

	void _vert(SINT x = 0) {
		this->x -= x;
		this->w -= x;
	}

	void _hori(SINT y = 0) {
		this->y -= y;
		this->h -= y;
	}

	void _dump() {
		std::cout << "\n" << x << ", " << y << " (" << w << " / " << h << ")";
	}
};
struct POS {
	POS(SINT x = 0, SINT y = 0) {
		this->x = x;
		this->y = y;
		this->w = 0;
		this->h = 0;
		this->blocked = 0;
		this->checked = 0;
		this->total = 0;
	}
	POS(SINT x, SINT y, SINT w, SINT h) {

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->blocked = 0;
		this->checked = 0;
		this->total = 0;
	}
	SINT x, y, w, h, checked, total;
	bool blocked;
	void _dump() {
		std::cout << "\nPOS: " << this->x << ", " << this->y;
	}

	DINT operator == (POS b) {
		if (b.x == this->x && b.y == this->y) return 1;
		return 0;
	}

	DINT operator != (POS b) {
		if (b.x != this->x || b.y != this->y) return 1;
		return 0;
	}

	DINT _direction(POS next) {
		DINT dir = 5;
		if (this->x < next.x && this->y == next.y) dir = 6;
		if (this->x > next.x && this->y == next.y) dir = 4;
		if (this->x == next.x && this->y < next.y) dir = 2;
		if (this->x == next.x && this->y > next.y) dir = 8;
		//std::cout << "\n Dir: " << dir;
		return dir;
	}

};
struct SPOT {
	struct COLOR {
		COLOR(DINT r, DINT g, DINT b) {
			this->r = r;
			this->g = g;
			this->b = b;
		};
		COLOR() {};
		DINT r, g, b;
	};
	SPOT(double x = 0.0, double y = 0.0, double z = 0.0, COLOR color = {0, 0, 0}) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->color = color;
		this->locked = false;
		this->max = 0.0;
		this->min = 0.0;
	};
	~SPOT() {};
	double x, y, z, min, max;
	bool locked;
	COLOR color;

	bool operator == (SPOT b) {
		if (this->x == b.x && this->y == b.y && this->z == b.z) return true;
		return false;
	}

	void _dump() {
		std::cout << "\n> X " << this->x << ", Y " << this->y << ", Z " << this->z;
		std::cout << " ( " << this->color.r << ", " << this->color.g << ", " << this->color.b << " )";
	}

	POS _pos() {
		return { (SINT)this->x, (SINT)this->y };
	}

	bool _round(double r, SPOT c) {
		double x = this->x - r;
		double y = this->y - r;
		double w = this->x + r;
		double h = this->y + r;

		return (x <= c.x && w >= c.x && y <= c.y && h >= c.y);
	}

};
struct SSPOT : SPOT {
	SSPOT(double x = 0.0, double y = 0.0, double w = 0.0, double h = 0.0, double z = 0.0, double d = 0.0) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->z = z;
		this->d = d;
	};
	SSPOT(bool inf) {
		if (inf) {
			this->x = INFINITY;
			this->y = INFINITY;
			this->z = INFINITY;
			this->w = -INFINITY;
			this->h = -INFINITY;
			this->d = -INFINITY;
		}
		else {
			this->x = 0.0;
			this->y = 0.0;
			this->z = 0.0;
			this->w = 0.0;
			this->h = 0.0;
			this->d = 0.0;
		}
	};
	double w, h, d;


	void _dump() {
		std::cout << "\nSSPOT: " << this->x << " (" << this->w << "), " << this->y << " (" << this->h << "), " << this->z << " (" << this->d <<")";
	}
};

struct DICE {
	DICE() {
		this->seed.i = 0;
		this->seed.d = 0.0;
		this->value.i = 0;
		this->seed.d = 0.0;

	};

	DUAL seed, value;
	//TIME time;
	operator DICE() const {
		return *this;
	}
	SINT _roll(SINT min, SINT max) {
		/*
		this->time._clock();
		this->seed.i = (this->time.microsecond) % (max + 1 - min); // 0 - 9
		this->value.i = this->seed.i + min;
		this->value.i = (this->value.i > max) ? (max) : (this->value.i);
		//std::cout << "\nSeed: " << this->seed.i << ", Value: " << this->value.i << " (" << min << ", " << max << ")";
		return (SINT)this->value.i;
		*/
		max++;
		DINT c = 0;
		do {
			min++;
			max++;
			c++;
		} while (min < 0);
		double r = (double)min + ((double)rand() / (double)RAND_MAX) * (double(max) - (double)min);
		SINT result = (SINT)r - 1 * c;
		return result;
	}

	double _droll(double min, double max) {
		return min + (((double)rand() / (double)RAND_MAX) * (max - min));
	}

	DINT _percent(DINT number, DINT percent = 100) {
		if ((rand() % percent) < number) {
			return 1;
		}
		else {
			return 0;
		}
	}

};
struct STRING {
	STRING() {
		this->length = 0;
		this->wtext[this->length] = L'\0';
		this->utext[this->length] = (unsigned char)'\0';
		this->text[this->length] = '\0';
	};
	STRING(const char text[]) {
		this->length = 0;
		this->wtext[this->length] = L'\0';
		this->utext[this->length] = (unsigned char)'\0';
		this->text[this->length] = '\0';
		this->_write(text);
	}
	~STRING() {
		this->length = 0;
		*this->wtext = {};
		*this->text = {};
		*this->utext = {};
	};
	DINT length;
	wchar_t wtext[ENGINE_TEXT_MAX_LENGTH];
	char text[ENGINE_TEXT_MAX_LENGTH];
	unsigned char utext[ENGINE_TEXT_MAX_LENGTH];
	DICE dice;

	void operator += (const char text[]) {
		this->_append(text);
	}

	void operator << (const char chr) {
		this->text[this->length] = chr;
		this->length++;
	}

	operator STRING() {
		return this->text;
	}

	char operator[] (DINT position) {
		return this->text[position];
	}


	bool _match(const char text[]) {
		DINT t = 0;
		STRING n = text;
		for (DINT c = 0; c < this->text[c] != '\0'; c++) {
			char cursor = this->text[c];
			if (cursor != text[t]) {
				t = 0;
			}
			else {
				t++;
			}
			if (t == n.length) return true;
		}
		return false;
	}

	bool _exact(const char text[]) {
		for (DINT c = 0; c < this->text[c] != '\0'; c++) {
			char cursor = this->text[c];
			if (cursor != text[c]) return false;
		}
		return true;
	}

	void _slice(DINT b, DINT e) {
		STRING sliced;
		for (DINT c = 0; this->text[c] != '\0'; c++) {
			char cursor = this->text[c];
			if (c < b) sliced._app(cursor);
			if (c > e) sliced._app(cursor);
		}
		this->_write(sliced.text);
	}

	bool _strip(char a, char b) {
		STRING stripped;
		bool bFound = false, eFound = false;
		for (DINT c = 0; this->text[c] != '\0'; c++) {
			char cursor = this->text[c];
			//std::cout << cursor;
			if (eFound) {
				stripped._app(cursor);
			}
			else {
				if (!bFound) {
					if (cursor == a) bFound = true;
				}
				else {
					if (cursor == b) eFound = true;
				}
			}
		}
		if(eFound) this->_write(stripped.text);
		return eFound;
	}


	void _replace(char a, char b) {
		for (DINT c = 0; c < this->length; c++) {
			if (this->text[c] == a) this->text[c] = b;
		}
	}

	DINT _has(char a) {
		for (DINT c = 0; c < this->length; c++) {
			if (this->text[c] == a) return 1;
		}
		return 0;
	}

	void _generate(DINT length = 5) {
		if (length > ENGINE_TEXT_MAX_LENGTH - 1) length = ENGINE_TEXT_MAX_LENGTH - 1;
		this->_clear();
		for (; length > this->length;) {
			switch (this->dice._roll(0, 8)) {
			default:
				this->_append("A");
				break;
			case 0:
				this->_append("No");
				break;
			case 1:
				this->_append("Ka");
				break;
			case 2:
				this->_append("o");
				break;
			case 3:
				this->_append("V");
				break;
			case 4:
				this->_append("de");
				break;
			case 5:
				this->_append("r");
				break;
			case 6:
				this->_append("qu");
				break;
			case 7:
				this->_append("s");
				break;
			}
		}
		this->text[length] = '\0';
	}

	void _append(const char text[]) {
		for (DINT i = 0; text[i] != '\0'; i++) {
			this->text[this->length] = text[i];
			this->wtext[this->length] = (wchar_t)text[i];
			this->length++;
		}
		this->text[this->length] = '\0';
		this->wtext[this->length] = L'\0';
	}

	void _app(const char character) {
		this->text[this->length] = character;
		this->length++;
		this->text[this->length] = '\0';
	}

	void _space(const char text[]) {
		if (this->length != 0) {
			this->text[this->length] = ' ';
			this->wtext[this->length] = L' ';
			this->length++;
		}
		this->_append(text);
	}

	void _add(char character) {
		this->text[this->length] = character;
		this->length++;
	}

	void _erase() {
		this->~STRING();
		*this = {};
	}

	void _clear() {
		if (this->length > 0) {
			for (; this->length > 0; this->length--) {
				this->text[this->length - 1] = '\0';
				this->utext[this->length - 1] = (unsigned char)'\0';
				this->wtext[this->length - 1] = L'\0';
			}
		}
	}

	void _reverse() {
		STRING temp = {};
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
		this->text[this->length] = '\0';
		this->wtext[this->length] = L'\0';
		this->utext[this->length] = (unsigned char)'\0';
	}

	void _uwrite(unsigned char text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = (wchar_t)text[this->length];
			this->utext[this->length] = text[this->length];
		}
		this->text[this->length] = '\0';
	}

	void _wwrite(const wchar_t text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = text[this->length];
			this->utext[this->length] = (unsigned char)text[this->length];
		}
		this->text[this->length] = '\0';
	}

	void _prev() {
		if(this->length > 0) this->text[this->length - 1] = '\0';
		if(this->length > 0) this->length--;
	}

	void _dump() {
		std::cout << "\n>STRING: " << this->text;
	}
};

struct TIME {
	TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
		this->success = 0;
		this->precision = 0;
		this->count = 0;
		this->system = {};
		this->difference = 0;
		this->elapsed = 0;
		this->lh = 0;
		this->lm = 0;
		this->ls = 0;
		this->lms = 0;
	};
	~TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
		this->count = 0;
		this->elapsed = 0;
		this->difference = 0;
	};
	DINT year, month, day, hour, minute, second, success, precision, elapsed, difference;
	DINT millisecond, microsecond, nanosecond;
	LINT count;
	SYSTEMTIME system;
	DINT lh, lm, ls, lms;

	void _clock(DINT type = 1) {
		this->_reset();
		switch (type) {
		default:
			GetLocalTime(&this->system);
			this->month = this->system.wMonth;
			this->day = this->system.wDay;
			this->hour = this->system.wHour;
			this->minute = this->system.wMinute;
			this->second = this->system.wSecond;
			this->millisecond = this->system.wMilliseconds;
			this->microsecond = 0;
			this->nanosecond = 0;
			break;
		case 1:
			//std::chrono::time_point<std::chrono::system_clock> tp = std::chrono::system_clock::now();
			std::chrono::steady_clock::time_point tp = std::chrono::high_resolution_clock::now();
			auto duration = tp.time_since_epoch();
			typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<2>>::type> Days;

			Days days = std::chrono::duration_cast<Days>(duration);
			this->day = (DINT)days.count();
			duration -= days;

			auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
			this->hour = (DINT)hours.count(); // +13;
			duration -= hours;

			auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
			duration -= minutes;
			this->minute = (DINT)minutes.count();

			auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
			duration -= seconds;
			this->second = (DINT)seconds.count();

			auto mss = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
			duration -= mss;
			this->millisecond = (DINT)mss.count();

			auto uss = std::chrono::duration_cast<std::chrono::microseconds>(duration);
			duration -= uss;
			this->microsecond = (DINT)uss.count();

			auto nss = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
			this->nanosecond = (DINT)nss.count();
			break;
		}
		DINT view = 0;
		if (view) {
			std::cout << "\nYear: " << this->year;
			std::cout << "\nMonth: " << this->month;
			std::cout << "\nDay: " << this->day;
			std::cout << "\nHour: " << this->hour;
			std::cout << "\nMinute: " << this->minute;
			std::cout << "\nSecond: " << this->second;
			std::cout << "\nMs: " << this->millisecond;
			std::cout << "\nMcrs: " << this->microsecond;
			std::cout << "\nNs: " << this->nanosecond;
		}
	}

	DINT _duration(TIME time, DINT ms = 0, DINT type = 0) {
		this->count = 0;
		this->_clock(type);
		this->hour = (this->hour > time.hour) ? ((this->hour == 0) ? (11) : (0)) : (this->hour);
		//this->count += (LINT)this->year * 12 * 30 * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->month * 30 * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->day * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->hour * 60 * 60 * 1000;
		this->count += (LINT)this->minute * 60 * 1000;
		this->count += (LINT)this->second * 1000;
		this->count += (LINT)this->millisecond;
		time.hour = (time.hour > this->hour) ? ((time.hour == 0) ? (11) : (0)) : (time.hour);
		//time.count += (LINT)time.year * 12 * 30 * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.month * 30 * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.day * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.hour * 60 * 60 * 1000;
		time.count += (LINT)time.minute * 60 * 1000;
		time.count += (LINT)time.second * 1000;
		time.count += (LINT)time.millisecond;
		switch (ms) {
		default:
			this->elapsed = (DINT)((this->count - time.count) / 1000);
			break;
		case 1:
			this->elapsed = (DINT)(this->count - time.count);
			break;
		}
		return this->elapsed;
	}
	void _increment(TIME time, bool reset = false) {
		if (reset) {
			this->ls = 0;
			this->lm = 0;
			this->lh = 0;
			this->lms = 0;
		}
		this->_clock(0);
		this->count += (LINT)this->hour * 60 * 60 * 1000;
		this->count += (LINT)this->minute * 60 * 1000;
		this->count += (LINT)this->second * 1000;
		this->count += (LINT)this->millisecond;
		time.count += (LINT)time.hour * 60 * 60 * 1000;
		time.count += (LINT)time.minute * 60 * 1000;
		time.count += (LINT)time.second * 1000;
		time.count += (LINT)time.millisecond;
		this->lms += (this->count > time.count) ? ((DINT)(this->count - time.count)) : ((DINT)(time.count - this->count));
		for (; this->lms > 999; this->lms -= 1000) {
			this->ls += 1;
		}
		for (; this->ls > 59; this->ls -= 60) {
			this->lm += 1;
		}
		for (; this->lm > 59; this->lm -= 60) {
			this->lh += 1;
		}
		this->count = 0;

	}
	void _reset() {
		this->count = 0;
		this->difference = 0;
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
		/*
		this->count = 0;
		this->lh = 0;
		this->lms = 0;
		this->lm = 0;
		this->ls = 0;
		*/
	}

	void _difference(TIME time) {

	}

	DINT _since(DINT ms = 0) {
		DINT count = 0;
		count += this->lh * 60 * 60 * ((ms) ? (1000) : (1));
		count += this->lm * 60 * ((ms) ? (1000) : (1));
		count += this->ls * ((ms) ? (1000) : (1));
		count += (ms) ? (this->lms) : (0);
		return count;
	}

	void _took() {
		/*
		STRING in;
		if (this->lh > 0) {
			in += WRITER::_itc(this->lh);
			in += "h ";
		}
		if (this->lm > 0) {
			in += WRITER::_itc(this->lm);
			in += "m ";
		}
		if (this->ls > 0) {
			in += WRITER::_itc(this->ls);
			in += "s ";
		}
		in += WRITER::_itc(this->lms);
		in += "ns ";
		*/

		if (this->lh > 0) std::cout << this->lh << "h ";
		if (this->lm > 0) std::cout << this->lm << "m ";
		if (this->ls > 0) std::cout << this->ls << "s ";
		std::cout << this->lms << "ms ";

	}
};

template <typename T>
struct HOLDER {
	HOLDER(std::initializer_list<T> ts) {
		this->ts = ts;
	};
	HOLDER() {};
	std::initializer_list<T> ts;

	T operator[](DINT position) {
		return *(this->ts.begin() + position);
	}
	DINT _size() {
		return (DINT)this->ts.size();
	}
};
template <typename LIST_ITEM>
struct LIST {
	LIST() {
		this->length = 0;
		this->total = 0;
		this->last = -1;
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) this->exist[i] = 0;
	};
	~LIST() {
		this->last = -1;
		this->length = 0;
		this->total = 0;
	};

	DINT length, total;
	SINT last;
	LIST_ITEM item[ENGINE_DATABASE_LIST_LENGTH_MAX]; // approx. max array length
	DINT exist[ENGINE_DATABASE_LIST_LENGTH_MAX];

	DINT _exist(DINT position) {
		return this->exist[position];
	}

	DINT _amount() {
		DINT a = 0, b = 0;
		do {
			if (this->exist[a] == 1) a++;
			b++;
		} while (b < ENGINE_DATABASE_LIST_LENGTH_MAX);
		return a;
	}

	void _add(LIST_ITEM item) {
		DINT pos = (this->last != -1) ? (this->last) : (this->length);
		this->item[pos] = item;
		this->exist[pos] = 1;
		this->length++;
		this->total++;
	}

	void _open(LIST_ITEM item) {
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			if (this->exist[i] == 0) {
				this->item[i] = item;
				this->item[i] = 1;
				break;
			}
		}
	}

	void _total() {
		DINT i = 0;
		for (DINT e = 0; e < ENGINE_DATABASE_LIST_LENGTH_MAX; e++) {
			if (this->exist[e]) i++;
		}
		this->total = i;
	}

	void _remove(DINT position = 0) {
		LIST_ITEM item = {};
		this->item[position] = item;
		this->existance[position] = 0;
		this->length--;
		this->last = position;
	}

	void _specific(LIST_ITEM item, DINT position) {
		this->item[position] = item;
		this->exist[position] = 1;
		this->length++;
	}

	LIST_ITEM _get(DINT position = 0) {
		return this->item[position];
	}

	void _clear() {
		this->~LIST();
		*this = {};
	}
};

template <typename ITEM>
struct INDEX {
	INDEX(DINT block = ENGINE_DATABASE_INDEX_BLOCK_SIZE) {
		this->length = 0;
		this->total = 0;
		this->size = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->current = 0;
		this->block = block;
		this->identifier = 0;
		this->last = -1;
		//std::cout << "\nIndex constructor called. (" << this->identifier << ")";
	};
	~INDEX() {
		this->length = 0;
		this->total = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->size = 0;
		this->block = 0;
		this->last = -1;
	};
	BINT length, size, total, current, block, identifier;
	SINT last;
	ITEM* item;
	BINT* exist;
	DICE dice;

	void _add(ITEM item) {
		//INDEX <ITEM> *current = this;
		if (this->size == 0) {
			this->identifier = this->dice._roll(0, 999);
		}
		if (this->size <= this->length) {
			//if (this->size == 0) std::cout << "\nCreating index."; else std::cout << "\nResizing index.";
			DINT size = this->size + this->block;
			INDEX <ITEM>* n = new INDEX <ITEM>;
			n->item = new ITEM[size];
			n->exist = new BINT[size];
			n->size = size;
			n->total = this->total;
			n->block = this->block;
			DINT i = 0;

			for (DINT j = 0; n->length < this->size && j < this->size; j++) {
				if (this->exist[j] == 1) {

					n->item[n->length] = this->item[j];

					n->exist[n->length] = 1;
					this->exist[j] = 0;

					n->length = n->length + 1;
				}
			}

			n->item[n->length] = item;
			n->exist[n->length] = 1;
			n->length = n->length + 1;
			n->total = n->total + 1;
			delete[] this->exist;
			delete[] this->item;
			*this = *n;
			n->_clear();
			delete[] n->item;
			delete[] n->exist;
			delete n;
		}
		else {
			for (DINT p = 0; p < this->size; p++) {
				if (this->exist[p] == 0) {
					this->item[p] = item;
					this->exist[p] = 1;
					this->length = this->length + 1;
					this->total = this->total + 1;
					this->last = p;
					break;
				}
			}
		}
		/*
		INDEX <ITEM>* n = new INDEX <ITEM>;
		n->item = new ITEM[this->length + 1];
		n->exist = new BINT[this->length + 1];
		DINT i = 0;

		for (DINT j = 0; n->length < this->length && j < this->length; j++) {
			if (this->exist[j]) {
				n->item[n->length] = this->item[j];
				this->item[j] = {};
				n->exist[n->length] = 1;
				this->exist[j] = 0;
				n->length = n->length + 1;
			}
		}
		n->item[n->length] = item;
		n->exist[n->length] = 1;
		n->length = n->length + 1;

		delete[] this->item;
		delete[] this->exist;
		this->_clear();
		*this = *n;
		n->_clear();
		delete[] n->exist;
		delete[] n->item;
		delete (n);
		*/
		/*
		if (current->length > 0) {
			do {
				if (current->exist[i] == 1) {

					n->item[n->length] = current->item[i];
					current->item[i] = {};
					this->item[i] = {};

					n->exist[n->length] = 1;
					current->exist[i] = 0;
					this->exist[i] = 0;

					n->length++;
				}
				i++;
			} while (n->length < current->length && i < current->length);
		}
		*/
		//current->_clear();
	}

	void _remove(DINT position) {
		if (position >= 0 && position < this->size) {
			this->exist[position] = 0;
			this->length = this->length - 1;
		}
		/*
		INDEX <ITEM>* current = this;
		INDEX <ITEM>* n = new INDEX <ITEM>;
		n->item = new ITEM[current->length - 1];
		n->exist = new DINT[current->length - 1];
		for (DINT j = 0; n->length < this->length && j < this->length; j++) {
			if (this->exist[j]) {
				n->item[n->length] = this->item[j];
				this->item[j] = {};
				n->exist[n->length] = 1;
				this->exist[j] = 0;
				n->length++;
			}
		}
		*/
		/*
		DINT i = 0;
		do {
			if (current->exist[i] == 1) {
				n->item[n->length] = current->item[i];
				current->item[i] = {};
				this->item[i] = {};

				n->exist[n->length] = 1;
				current->exist[i] = 0;
				this->exist[i] = 0;
				n->length++;
			}
			i++;
		} while (n->length < current->length && i < current->length);
		*/
		/*
		delete[] this->item;
		delete[] this->exist;
		this->_clear();
		current->_clear();
		*this = *n;
		n->_clear();
		delete (n);
		*/
	}

	ITEM _get(DINT position) {
		if (position < this->length) {
			if (this->exist[position] == 1) return this->item[position];
		}
		ITEM item = {};
		return item;
	}

	void _clear() {
		this->length = 0;
		this->current = 0;
		this->total = 0;
		this->item = { 0 };
		this->exist = { 0 };
		*this = {};
	}

	void _reverse() {
		INDEX <ITEM>* list = new INDEX<ITEM>;
		list->item = new ITEM[this->size];
		list->exist = new BINT[this->size];
		for (DINT r = this->size; r > 0; r--) {
			if (this->exist[r - 1] == 1) {
				list->_add(this->item[r - 1]);
			}
		}
		*this = *list;
		list->_clear();

		delete[] list->item;
		delete[] list->exist;
		delete list;
	}

	SINT _first(DINT offset = 0) {
		if (offset >= this->size) offset = this->size - 1;
		for (DINT i = offset; i < this->size; i++) {
			if (this->exist[i] == 1) return i;
		}
		return -1;
	}

	void _swap(DINT a, DINT b) {
		if (a < this->size && b < this->size && a != b) {
			ITEM one = this->item[a];
			DINT c = this->exist[a];
			this->item[a] = this->item[b];
			this->exist[a] = this->exist[b];
			this->item[b] = one;
			this->exist[b] = c;

		}
	}

	void _pop(SINT side = 1) {
		SINT popped = -1;

		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i] == 1) {
				popped = i;
				if (side == -1) break;
			}
		}
		if (popped >= 0) {
			this->exist[popped] = 0;
			this->item[popped] = { 0 };
		}
	}

	void _pend(ITEM item, SINT side = 1) {
		if (side == -1) {
		}
		else {

		}
	}


	void _close() {
		if (this->length > 0) {
			delete[] this->item;
			delete[] this->exist;
			delete this;
		}
	}
};

template <typename ITEM>
struct CHART {
	struct PACKAGE {
		PACKAGE() {
			//this->item = {};
			this->z = (SINT)INFINITY;
		};
		ITEM item;
		bool exist;
		SINT z;
		
		void operator = (PACKAGE p) {
			this->item = p.item;
			this->exist = p.exist;
			this->z = p.z;
		}

		void _set(ITEM item, SINT z = 0) {
			this->item = item;
			this->z = z;
			this->exist = true;
		}

		void _loose() {
			this->item = nullptr;
			this->z = (SINT)INFINITY;
			this->exist = false;
		}
		
		void _copy(PACKAGE pk) {
			this->item = pk.item;
			this->exist = pk.exist;
			this->z = pk.z;
		}
	};
	struct COLOR {
		COLOR() {
			this->r = this->dice._roll(0, 255);
			this->g = this->dice._roll(0, 255);
			this->b = this->dice._roll(0, 255);
		};
		DINT r, g, b;
		RANDOM dice;
	};
	CHART(DINT block) {
		//std::cout << "\nConstructing chart.";
		this->block = block;
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = nullptr;
		this->exist = nullptr;
		this->package = nullptr;
		this->filled = 0;
		//this->item = new ITEM[this->block];
		//this->exist = new BINT[this->block];
		this->dummy = {};
		this->debug = 0;
	}
	CHART(std::initializer_list<ITEM> l) {
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = nullptr;
		this->exist = nullptr;
		this->package = nullptr;
		this->filled = 0;
		//this->item = new ITEM[this->block];
		//this->exist = new BINT[this->block];
		this->dummy = {};
		HOLDER<ITEM> items = l;
		this->block = items._size();
		for (DINT i = 0; i < items._size(); i++) {
			ITEM item = items[i];
			*this << item;
		}
		this->debug = 0;

	}
	CHART() {
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = nullptr;
		this->exist = nullptr;
		this->package = nullptr;
		this->filled = 0;
		this->block = 8;
		this->debug = 0;
	};
	~CHART() {
		this->size = 0;
		//this->block = 0;
		this->filled = 0;
		this->last = 0;
		this->length = 0;
		this->total = 0;
	}
	DINT size, block, filled, length, debug;
	SINT last;
	BINT total;
	ITEM* item;
	ITEM dummy;
	BINT* exist;
	PACKAGE* package;
	STRING name;
	COLOR color;

	void _dump() {
		std::cout << "\n" << this->name.text << " -> " << this->length;

	}

	DINT _exist(DINT position) {
		return this->exist[position];
	}

	void _resize(DINT size = 0) {
		//if (this->debug) std::cout << "\n Resising (" << this->size;
		DINT total = this->size;
		if (size > 0) {
			this->size = size;
		}
		else {
			this->size = this->size + this->block;
		}
		DINT l = 0;
		if (total > 0) {
			ITEM* items = new ITEM[total];
			BINT* exists = new BINT[total];
			//PACKAGE* packages = new PACKAGE[total];
			for (DINT k = 0; k < total; k++) {
				if (this->exist[k]) {
					items[l] = this->item[k];
					exists[l] = 1;
					//packages[l]._set(this->item[k], l);
					l++;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			//delete[] this->package;
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
			//this->package = new PACKAGE[this->size];
			DINT j = 0;
			for (this->length = 0; this->length < l && j < this->size; this->length++) {
				if (exists[this->length]) {
					this->item[j] = items[this->length];
					this->exist[j] = 1;
					//this->package[j]._copy(packages[this->length]);
					j++;
				}
			}
			delete[] items;
			delete[] exists;
			//delete[] packages;
		}
		else {
			this->length = 0;
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
			//this->package = new PACKAGE[this->size];
		}
		//if(this->debug) std::cout << " -> " << this->size << ")";
	};

	void _reverse() {
		CHART <ITEM> reversed;
		for (DINT i = this->length; i > 0; i--) {
			reversed << this->item[i - 1];
		}
		this->_close();
		*this = reversed;

	}

	SINT _first() {
		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i]) return i;
		}
		return -1;
	};

	SINT _last() {
		for (DINT i = this->size - 1; i >= 0; i--) {
			if (this->exist[i]) return i;
		}
		return -1;
	};

	SINT _open() {
		if (this->size == 0) return 0;
		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i] == 0) {
				this->last = i;
				return i;
			}
		}
		return -1;
	}
	void operator<<(ITEM item) {
		//if(this->debug) std::cout << "\nSetting item " << this->last;
		if (this->size == 0 || this->length == this->size) this->_resize();

		for (SINT i = this->last; i < this->size; i++) {
			if (this->exist[i] != 1) {
				this->item[i] = item;
				this->exist[i] = 1;
				this->length++;
				this->total++;
				this->last = i;
				//this->package[i]._set(item, i);
				break;
			}
		}
	};

	void operator>>(DINT position) {
		if (position >= 0) {
			if (this->size > 0 && this->length > 0 && position < this->size && position >= 0) {
				if (this->exist[position]) {
					this->exist[position] = 0;
					this->item[position] = {};
					//this->package[position]._loose();
					this->length--;
					if (this->length > 0) {
						this->last = (position != 0) ? (position - 1) : (0);
						/*
						ITEM* items = new ITEM[this->length];
						BINT* exists = new BINT[this->length];
						DINT l = 0;
						for (DINT i = 0; i < this->length; i++) {
							if (this->exist[i] == 1) {
								items[l] = this->item[i];
								exists[l] = 1;
								l++;
							}
						}

						delete[] this->item;
						delete[] this->exist;
						this->item = new ITEM[l];
						this->exist = new BINT[l];
						this->size = 0;
						for (this->length = 0; this->length < l; this->length++) {
							this->item[this->length] = items[this->length];
							this->exist[this->length] = 1;
							this->size++;
						}
						delete[] items;
						delete[] exists;
						*/
					}

				}
				if (this->length == 0) {
					if (this->size > 0) {
						delete[] this->exist;
						delete[] this->item;
						//delete[] this->package;
						this->size = 0;
					}
				}
			}
			else {
				std::cout << "\nOut of bounds.";
			}
		}
	};

	ITEM& operator[](DINT position) {
		if (position < this->size && position >= 0) {
			return this->item[position];
		}
		return this->dummy;
	};

	void _prepend(ITEM item) {
		ITEM* items = new ITEM[this->length];
		BINT* exists = new BINT[this->length];
		//PACKAGE* packages = new PACKAGE[this->length];
		DINT l = 0;

		if (this->size > 0) {
			for (DINT i = 0; i < this->length; i++) {
				if (this->exist[i]) {
					items[l] = this->item[i];
					exists[l] = 1;
					//packages[l]._set(this->item[i], i);
					l++;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			//delete[] this->package;

		}
		this->item = new ITEM[l + 1];
		this->exist = new BINT[l + 1];
		//this->package = new PACKAGE[l + 1];
		this->item[0] = item;
		this->exist[0] = 1;
		//this->package[0]._set(item, 0);
		this->last = 0;
		this->size = 1;
		for (this->length = 1; this->length < l + 1; this->length++) {
			if (exists[this->length - 1] == 1) {
				this->item[this->length] = items[this->length - 1];
				this->exist[this->length] = 1;
				//this->package[this->length]._set(items[this->length - 1], this->length - 1);
				this->size++;
			}
		}
		delete[] items;
		delete[] exists;
		//delete[] packages;

	}

	void _copy(CHART<ITEM> copy) {
		if (this->length > 0) {
			delete[] this->item;
			delete[] this->exist;
		}
		this->item = new ITEM[copy.size];
		this->exist = new BINT[copy.size];
		this->length = 0;
		this->size = copy.size;
		this->total = 0;
		for (DINT i = 0; i < copy.size; i++) {
			if (copy.exist[i]) {
				this->item[this->length] = copy.item[i];
				this->exist[this->length] = 1;
				this->length++;
			}
		}

	}

	void _close() {
		if (this->size > 0) {
			delete[] this->item;
			delete[] this->exist;
			//delete[] this->package;
			this->~CHART();
			//delete this;
		}
	}

	void _swap(DINT a, DINT b) {
		ITEM ia = this->item[a];
		this->item[a] = this->item[b];
		this->item[b] = ia;

	}

};

template <typename ITEM>
struct IMAP {
	struct PACKAGE {
		PACKAGE() {
			this->z = 0;
			this->exist = false;
			this->item = {};
		};

		PACKAGE(ITEM item, bool exist, double z) {
			ITEM* i = new ITEM(item);
			this->item = *i;
			this->exist = exist;
			this->z = z;
			delete i;
		}

		~PACKAGE() {
			this->z = 0;
			this->exist = false;
			this->item = {};
		}

		ITEM item;
		bool exist;
		double z;

		/*
		void operator = (PACKAGE p) {
			this->item = p.item;
			this->exist = p.exist;
			this->z = p.z;
		}
		*/

		void _dump() {
			std::cout << "\nPACKAGE: " << this->exist << " (" << this->z << ")";
		}
	};

	IMAP(DINT block = 8) {
		this->block = block;
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->counter = 0;
		this->package = nullptr;
		this->z = false;
	};

	DINT block, size, length, last, counter;
	bool z;
	PACKAGE* package;
	PACKAGE dummy;


	void _resize(DINT size = 0) {
		DINT total = this->size;
		if (size > 0) {
			this->size += size;
		}
		else {
			this->size += this->block;
		}

		if (this->length > 0) {
			PACKAGE* package = new PACKAGE[total];
			DINT c = 0;
			for (DINT i = 0; i < total; i++) {
				if (this->package[i].exist) {
					package[c] = this->package[i];
					c++;
				}
			}
			delete[] this->package;
			this->package = new PACKAGE[this->size];
			for (DINT i = 0; i < total; i++) {
				if (package[i].exist) {
					this->package[i] = package[i];
				}
			}
			delete[] package;
		}
		else {
			this->package = new PACKAGE[this->size];
		}
	}

	void _swap(DINT a, DINT b) {
		PACKAGE pb = this->package[b];
		this->package[b] = this->package[a];
		this->package[a] = pb;
	}

	SLINT _sort(SINT dir = 1) {
		SLINT swaps = 0;
		for (DINT i = 0; i < this->size; i++) {
			for (DINT c = 0; c < this->size; c++) {
				if (i != c) {
					PACKAGE a = this->package[i];
					PACKAGE b = this->package[c];
					if (a.exist && b.exist) {
						switch (dir) {
						default:
							break;
						case -1:
							if (a.z < b.z) {
								this->_swap(i, c);
								swaps++;
							}
							break;
						case 1:
							if (a.z > b.z) {
								this->_swap(i, c);
								swaps++;
							}
							break;
						}
					}
				}
			}
		}


		return swaps;
	}

	void _s(DINT dir = 1) {

		SINT minc = 0, maxc = this->size - 1, min, max;
		min = (SINT)INFINITY;
		max = (SINT)-INFINITY;
		for (DINT i = 0; i < this->size; i++) {

		}

	}

	void operator << (ITEM item) {
		DICE dice;
		if (this->size == 0 || this->length == this->size) this->_resize();
		for (DINT i = this->last; i < this->size; i++) {
			if (!this->package[i].exist) {
				double z;
				if (this->z) {
					bool found;
					do {
						found = false;
						z = dice._droll(0, this->size);
						for (DINT c = 0; c < this->size; c++) {
							if (this->package[c].z == z) found = true;
						}
					} while (found);
				}
				else {
					z = this->counter;
				}
				ITEM* it = new ITEM(item);
				this->package[i] = { *it, true, z};
				delete it;
				this->last = i;
				this->length++;
				this->counter++;
				break;
			}
		}
	}

	void operator >> (DINT pos) {
		if (pos >= 0 && pos < this->size) {
			this->package[pos].~PACKAGE();
			this->length--;
		}
	}

	ITEM& operator [] (DINT pos) {
		if (pos >= 0 && pos < this->size) return this->package[pos].item;		
		return this->dummy.item;
	}

	void _dump() {
		std::cout << "\nDUMPING " << this->length << " / " << this->size;
		for (DINT i = 0; i < this->size; i++) {
			//if (this->package[i].exist) {
				this->package[i]._dump();
			//}
		}
	}

	void _close() {
		if (this->size > 0) {
			delete[] this->package;
			this->size = 0;
			this->length = 0;
			this->last = 0;
			this->counter = 0;
			this->z = false;
		}
	}

};


struct INTC {
	INTC(SLINT large, SLINT rounded = 10) {
		DINT roundee = 0;
		this->rounder = rounded;
		if (rounded == -1) {
			for (SLINT i = large; i >= 10; i /= 10) {
				roundee++;
			}
			rounded = UTILS::_tnth(1, roundee);
		}
		else {
			for (SLINT i = rounded; i > 1; i /= 10) roundee++;
		}
		if (large > 0) {
			for (; large > 0;) {
				for (DINT i = 0; i <= roundee; i++) {
					this->number << 0;
					for (; large > rounded - 1;) {
						large -= rounded;
						this->number[i] += 1;
					}
					rounded /= 10;
				}
			}
		}
		else {
			if (large < 0) {

			}
			else {
				this->number << 0;
			}
		}
		this->_number();
	};
	INTC() {};
	IMAP <SLINT> number;
	SLINT rounder;
	SLINT large;
	operator SLINT() const {
		return this->large;
	}
	operator INTC() const {
		return this->large;
	}
	void operator += (SLINT a) {
		*this = { this->_number() + a, -1};

	}
	void operator -= (SLINT a) {
		SLINT n = this->_number() - a;
		if (n > 0) {
			*this = { n, -1 };
		}
		else {
			*this = { 0, 1 };
		}
	}
	void operator ++ (DINT a) {

		*this = { this->_number() + 1, -1};
	}
	void operator -- (DINT b) {
		SLINT n = this->_number() - 1;
		if (n >= 0) {
			*this = { n, -1 };
		}
		else {
			*this = { 0, 1 };
		}

	}
	SLINT operator *= (SLINT a) {
		SLINT n = this->_number();
		*this = { n *= a, -1 };
		return *this;
	}
	SLINT operator /= (SLINT a) {
		SLINT n = this->_number();
		*this = { n /= a, -1 };
		return *this;
	}

	void operator << (SLINT a) {
		this->number << a;
	}

	SLINT _number() {
		SLINT n = 0;
		SLINT roundee = UTILS::_tnth(1, this->number.length - 1);
		for (DINT i = 0; i < this->number.length; i++) {
			n += roundee * this->number[i];
			roundee /= 10;
		}
		this->large = n;
		return n;
	}

	double _double() {
		//this->_dump(true);
		double r = 0.0;
		SLINT roundee = UTILS::_tnth(1, this->number.length - 1);
		SLINT rd = roundee;
		bool nmet = false;
		for (DINT i = 0; i < this->number.length; i++) {
			r += (double)roundee * this->number[i];
			roundee /= 10;
		}
		r /= rd;
		return r;
	}

	SLINT _rnumber() {
		SLINT n = 0;
		return n;
	}

	void _dump(bool blocks = false) {
		if (!blocks) {
			std::cout << "\n>";
			for (DINT i = 0; i < this->number.length; i++) {
				std::cout << this->number[i];
			}
		}
		else {
			for (DINT i = 0; i < this->number.length; i++) {
				std::cout << "\n> number[" << i << "] = " << this->number[i];
			}
		}

	}

	void _close() {
		this->number._close();
		this->rounder = 0;
		this->large = 0;
	}

};


struct SAVE {
	SAVE() {
	};
	~SAVE() {};

	std::fstream file;
	STRING data;
	STRING streaker;
	STRING streak;
	STRING loops;
	STRING limit;
	STRING experience;

	template <typename DATA>
	void _save(DATA data, DINT mode = 0) {
		switch (mode) {
		default:
			this->file.open("save.drx", std::ios_base::app);
			break;
		case 1:
			this->file.open("save.drx", std::fstream::out);
			break;
		}
		if (this->file.is_open()) {
			this->file << data;
			this->file << " ";
			this->file.close();
		}
	}

	void _load(DINT view = 0) {
		if (view) std::cout << "\nLoading save file: ";
		this->file.open("save.drx", std::fstream::in);
		if (this->file.is_open()) {
			char cursor;
			this->data._clear();
			while (this->file.good()) {
				this->file.get(cursor);
				this->data._add(cursor);
			}
			this->file.close();
		}
		this->streak.length = 0;
		for (DINT i = 0; this->data.text[i] != ' '; i++) {
			this->streak.text[this->streak.length] = this->data.text[i];
			this->streak.length++;
		}
		this->streak.text[this->streak.length] = '\0';
		this->streaker.length = 0;
		for (DINT i = this->streak.length + 1; this->data.text[i] != ' '; i++) {
			this->streaker.text[this->streaker.length] = this->data.text[i];
			this->streaker.length++;
		}
		this->streaker.text[this->streaker.length] = '\0';
		this->loops.length = 0;
		for (DINT i = this->streak.length + this->streaker.length + 2; this->data.text[i] != ' '; i++) {
			this->loops.text[this->loops.length] = this->data.text[i];
			this->loops.length++;
		}
		this->loops.text[this->loops.length] = '\0';
		this->experience.length = 0;
		for (DINT i = this->streak.length + this->streaker.length + this->loops.length + 3; this->data.text[i] != ' '; i++) {
			this->experience.text[this->experience.length] = this->data.text[i];
			this->experience.length++;
		}
		if (view) std::cout << this->streaker.text << " - " << this->streak.text << " " << this->loops.text << " loops.";

	}

};

struct GROUP {
	GROUP(DINT a, CHART<DINT> g) {
		this->a = a;
		for (DINT b = 0; b < g.length; b++) {
			this->g << g[b];
		}
	};
	GROUP() {
		this->a = 0;
	};
	DINT a;
	CHART<DINT> g;


	void _dump() {
		std::cout << "\n>" << this->a << " (";
		for (DINT i = 0; i < this->g.length; i++) {
			std::cout << this->g[i] << ", ";
		}
		std::cout << ")";
	}
};

struct FACE {
	IMAP<DINT> i;
};

struct THREAD {
	THREAD() {
		this->started = 0;
		this->working = 0;
		this->finished = 0;
		this->sleep = 1;
	};
	~THREAD() {};

	DINT started, working, finished, sleep;
	std::thread worker;

};


struct DIRECTORY {
	DIRECTORY(const char name[]) {
		std::cout << "\nDIRECTORY: " << name;
		if (std::filesystem::exists(std::filesystem::path({ name }))) {
			this->path._write(name);
			for (const auto& file : std::filesystem::directory_iterator(this->path.text)) {
				STRING f = file.path().string().c_str();
				for (; f._strip('.', '\\');) {
					//std::filesystem::current_path(std::filesystem::current_path().parent_path());
				}
				f._strip('s', '\\');
				//if (!f._match(".drx")) f._append(".drx");
				//f._dump();
				this->file << f;
			}
		}
	}
	DIRECTORY() {};
	STRING path;
	CHART <STRING> file;


	void _dump() {
		std::cout << "\n Dumping /" << this->path.text;
		for (DINT i = 0; i < this->file.length; i++) {
			std::cout << "\n>" << this->file[i].text;
		}

	}

	SINT _search(const char file[]) {
		for (DINT f = 0; f < this->file.length; f++) {
			if (this->file.exist[f]) {
				if (this->file[f]._match(file)) {
					return f;
				}
			}
		}
		return -1;
	}
};


static DINT _iati(CHART <DINT> nums) {
	nums._reverse();
	DINT value = 0;
	for (DINT i = 0; i < nums.length; i++) {
		DINT v = nums[i];
		DINT c = i;
		for (; c > 0; c--) {
			v *= 10;
		}
		value += v;
	}
	nums._close();
	return value;
}

static double _iatdz(CHART<DINT> nums) {
	double value = 0.0;
	nums._reverse();
	for (DINT i = 0; i < nums.length; i++) {
		value += (double)nums[i];
		value /= 10.0;
	}
	nums._close();
	return value;
}

struct EXA : SPOT {
	EXA(double x, double y, double z, std::initializer_list<DINT> ps = {}) {
		HOLDER pairs = ps;
		for (DINT p = 0; p < pairs._size(); p++) this->pair << pairs[p];
		this->x = x;
		this->y = y;
		this->z = z;
	};
	EXA(SPOT spot, CHART<DINT> pairs, CHART<DINT> groups) {
		this->x = spot.x;
		this->y = spot.y;
		this->z = spot.z;
		for (DINT p = 0; p < pairs.length; p++) this->pair << pairs[p];
		for (DINT g = 0; g < groups.length; g++) this->group << groups[g];
	};
	EXA() {};
	CHART <DINT> pair;
	CHART <DINT> group;
	SPOT _spot() {
		return { this->x, this->y, this->z };
	}
};

struct DATA {
	DATA() {
		this->type = -1;
	};

	STRING file;
	std::fstream stream;
	SINT type;
	CHART <EXA> exas;
	bool _read(const char file[], DINT type = 0, bool debug = false) {

		bool loaded = false;
		switch (type) {
		default:
			this->file._write(ENGINE_MAP_DIRECTORY_SPRITE);
			this->file._app('\\');
			this->file._append(file);
			if(!this->file._match(".drx")) this->file._append(".drx");
			break;
		case 1:
			this->file._write(ENGINE_MAP_DIRECTORY_POLYGON);
			this->file._app('\\');
			this->file._append(file);
			if(!this->file._match(".pdrx")) this->file._append(".pdrx");
			break;			
		}
		this->stream.open(this->file.text);
		bool open = this->stream.is_open();
		if (open) {
			char cursor;
			CHART <char> content;
			//STRING cont;
			while (this->stream.good()) {
				this->stream >> cursor;
				//cont._app(cursor);
				content << cursor;
			}
			//std::cout << "\n" << cont.text;
			if(debug) std::cout << "\nRead a content of " << content.length << " characters. (" << this->file.text << ")";
			
			for (DINT c = 0; c < content.length; c++) {
				cursor = content[c];
				if (cursor == '{') {
					EXA exa;
					CHART <DINT> x;
					bool neg = false;
					c++;
					do {
						if (content[c] == '-') neg = true; else x << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != '.');
					exa.x = (double)_iati(x);
					if (neg) exa.x *= -1.0;
					neg = false;

					
					CHART <DINT> dx;

					c++;
					do {
						dx << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != ',');
					exa.x += _iatdz(dx);

					CHART <DINT> y;
					c++;
					do {
						if (content[c] == '-') neg = true; else y << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != '.');
					exa.y = (double)_iati(y);
					if (neg) exa.y *= -1.0;
					neg = false;

					CHART <DINT> dy;
					c++;
					do {
						dy << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != ',');
					exa.y += _iatdz(dy);


					CHART <DINT> z;
					c++;
					do {
						if (content[c] == '-') neg = true; else z << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != '.');
					exa.z = (double)_iati(z);
					if (neg) exa.z *= -1.0;

					CHART <DINT> dz;

					c++;
					do {
						dz << UTILS::_isnum(content[c]);
						c++;
					} while (content[c] != ',' && content[c] != '}');
					exa.z += _iatdz(dz);

					

					if (content[c] == ',') {
						//std::cout << "\nPairing.";
						c+= 2;
						do {
							CHART <DINT> prs;
							//std::cout << "\n";
							if (content[c] != '}') {
								do {
									//std::cout << content[c];
									SINT n = UTILS::_isnum(content[c]);
									if (n != -1) prs << (DINT)n;
									c++;
								} while (content[c] != ',' && content[c] != '}');
								exa.pair << _iati(prs);
							}
							if (content[c] != '}') c++;
						} while (content[c] != ',' && content[c] != '}');
						if (content[c + 1] == ',') {
							c++;
							//std::cout << "\nGrouping.";
							do {
								CHART <DINT> grps;
								do {
									SINT n = UTILS::_isnum(content[c]);
									if (n != -1) grps << (DINT)n;
									c++;
								} while (content[c] != ',' && content[c] != '}');
								exa.group << _iati(grps);
							} while (content[c] != '}');
						}
						else {
							//c++
						}
					}
					else {
						//c++;
					}
					
					//std::cout << "\nSPOT: " << exa.x << ", " << exa.y << ", " << exa.z << " - ";
					//for (DINT p = 0; p < exa.pair.length; p++) std::cout << exa.pair[p] << " ";
					this->exas << exa;
				}
			//	break;
			}
			
			content._close();
			this->stream.close();
			loaded = true;
		}
		return loaded;
	}



};

static SINT _exist(CHART<POS> chart, POS pos) {
	for (DINT p = 0; p < chart.length; p++) {
		if (chart[p].x == pos.x && chart[p].y == pos.y && chart[p].blocked == 0) return p;
	}
	return -1;
}


static POS _closerX(POS a, POS b, POS target) {
	SINT ax = a.x - target.x;
	SINT bx = b.x - target.x;

	if (ax == 0) return a;
	if (bx == 0) return b;
	if (ax < 0 && bx < 0) {
		if (ax > bx) return b; else return a;
	}
	else {
		if (ax > 0 && bx > 0) {
			if (ax < bx) return a; else return b;
		}
		else {
			return a;
		}
	}
}

static POS _closerY(POS a, POS b, POS target) {
	SINT ay = a.y - target.y;
	SINT by = b.y - target.y;

	if (ay == 0) return a;
	if (by == 0) return b;
	if (ay < 0 && by < 0) {
		if (ay > by) return b; else return a;
	}
	else {
		if (ay > 0 && by > 0) {
			if (ay < by) return a; else return b;
		}
		else {
			return a;
		}
	}
}


static POS _dir(CHART <POS> chart, POS current, POS target, POS blocked) {
	POS up = { current.x, current.y - 1 }, down = { current.x, current.y + 1 }, left = { current.x - 1, current.y }, right = {current.x + 1, current.y};
	
	if (blocked == up || blocked == down) {
		POS r = _closerX(left, right, target);
		if (_exist(chart, r) != -1) return r;
	}
	if (blocked == left || blocked == right) {
		POS r = _closerY(up, down, target);
		if (_exist(chart, r) != -1) return r;
	}
	
	if (blocked == current) {
		POS r = _closerX(left, right, target);
		if (_exist(chart, r) != -1) {
			return r;
		}
		else {
			return _closerY(up, down, target);
		}
	}

	return current;


}

struct SCORE {
	SCORE(DINT id, DINT score) {
		this->id = id;
		this->value = score;
	}
	DINT id, value;
};

struct NODE : POS {
	NODE() {
		this->exist = 0;
		this->g = 0.0f;
		this->l = 0.0f;
		this->f = 0.0f;
		this->d = 0.0f;
		this->h = 0.0f;
		this->xd = 0;
		this->yd = 0;
		this->index = 0;
		this->dir = 0;
		this->save = 0;
		this->blacklisted = 0;
		this->parent = nullptr;
	};
	CHART<NODE*> neighbour;
	NODE* parent;
	DINT exist, xd, yd, index, dir, save, blacklisted;
	float d, g, l, f, h;
	POS draw;

	void _dump() {
		if (this != nullptr) {
			std::cout << "\n>" << this->x << ", " << this->y << " (";
			if (this->parent != nullptr) {
				std::cout << this->parent->x << ", " << this->parent->y;
			}
			else {
				std::cout << "null";
			}
			std::cout << ")";
			std::cout << " " << this->checked;
			std::cout << " " << this->blocked;
		}
		else {
			std::cout << "\n>Null";
		}
	}

};

NODE* _getNode(CHART<NODE> nodes, SINT x, SINT y, DINT dir = 5) {
	for (DINT n = 0; n < nodes.length; n++) {
		if (nodes[n].x == x && nodes[n].y == y) return &nodes[n];
	}
	//std::cout << "\nNot found.";
	return nullptr;
}

SINT _getID(CHART<NODE*> nodes, NODE n) {
	if (nodes.length > 0) {
		for (DINT i = 0; i < nodes.length; i++) {
			if (nodes[i] != nullptr) {
				if (nodes[i]->x == n.x && nodes[i]->y == n.y) return i;
			}
		}
	}
	return -1;
}


static CHART <POS> _path(CHART <NODE> *nodes, POS start, POS end, DINT tries = 5) {
	CHART<POS> set;
	CHART<NODE*> open;
	//NODE* b = _getNode(*nodes, start.x, start.y);
	open << _getNode(*nodes, start.x, start.y);
	NODE* current;
	DINT able = 0;
	do {
		if (open.length == 0) break;
		DINT w = 0;
		for (DINT l = 0; l < open.length; l++) {
			NODE *node = open[l];
			if (node != nullptr && open[w] != nullptr && node->g < open[w]->g) w = l;
		}

		current = open[w];
		if (current != nullptr) {
			if (current->x == end.x && current->y == end.y) {
			//	std::cout << "\nDone.";
				able = 1;
				break;
			}

			open >> _getID(open, *current);

			for (DINT n = 0; n < current->neighbour.length; n++) {
				NODE* ne = current->neighbour[n];
				if (ne != nullptr) {
					if (ne->blocked == 0 && ne->checked == 0) {
						float tempg = UTILS::_distance(ne->x, ne->y, end.x, end.y);
						if (tempg < ne->g) {
							ne->g = tempg;
							ne->parent = current;
							open << ne;
						}
					}
				}
			}
			current->checked = 1;
		}
		else {
			break;
		}
	} while (open.length > 0);
	if (able) {
		current = _getNode(*nodes, end.x, end.y);
		do {
			POS pos = { current->x, current->y };
			set << pos;
			current = current->parent;
			//current->_dump();
		} while (current != nullptr);
		//std::cout << " Length: " << set.length;
	}
	return set;
}