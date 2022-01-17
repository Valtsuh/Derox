
template <typename LIST_ITEM>
struct LIST {
	LIST() {
		this->length = 0;
		this->total = 0;
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			//this->item[i] = { 0 };
			this->existance[i] = 0;
		}
	};
	~LIST() {

		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			//this->item[i] = { 0 };
			this->existance[i] = 0;
		}
		this->length = 0;
		this->total = 0;
	};

	DINT length, total;
	LIST_ITEM item[ENGINE_DATABASE_LIST_LENGTH_MAX]; // approx. max array length
	DINT existance[ENGINE_DATABASE_LIST_LENGTH_MAX];
	DINT _set(LIST_ITEM item) {
		for (DINT d = 0; d < ENGINE_DATABASE_LIST_LENGTH_MAX; d++) {
			if (this->existance[d] == 0) {
				this->item[d] = item;
				this->existance[d] = 1;
				this->length++;
				this->total++;
				return d;
			}
		}
		return 0;
	}

	void _remove(DINT position) {
		this->item[position] = { 0 };
		this->existance[position] = 0;
		this->length--;
	}

	LIST_ITEM _get(DINT position = 0) {
		return this->item[position];
	}

	void _carry(LIST <LIST_ITEM>* list) {
		for (DINT d = 0; d < list->length; d++) {
			if (list->existance[d] == 1) this->_set(list->item[d]);
		}
	}

	void _deconstruct() {
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			this->existance[i] = 0;
		}
		this->length = 0;
		this->total = 0;
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
		if (this->elapsed < 1000) {
			return this->elapsed;
		}
		else {
			this->elapsed /= 1000;
			return this->elapsed;
		}
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
struct RANDOM {
	RANDOM() {

	};
	~RANDOM() {};
	DINT min, max, value;

	DINT _roll(SINT min = -1, SINT max = -1) {
		if (min < 0 && max >= 0) {
			this->value = this->min + rand() % max;
		}
		if (min >= 0 && max < 0) {
			this->value = min + rand() % this->max;
		}
		if (min < 0 && max < 0) {
			this->value = this->min + rand() % this->max;
		}
		if (min >= 0 && max >= 0) {
			this->value = min + rand() % max;
		}
		return this->value;
	}

};
struct COUNTER {
	COUNTER() {
		this->value = 0;
		this->current = 0;
	};
	~COUNTER() {};
	DINT value, current;

};

struct DIMENSION {
	DIMENSION() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->size = 0;
	}
	~DIMENSION() {};
	DINT x, y, w, h, size;


	void _set(DIMENSION dimension) {
		this->x = dimension.x;
		this->y = dimension.y;
		this->w = dimension.w;
		this->h = dimension.h;
		this->size = dimension.size;
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
			this->wtext[length] = L'\0';
			this->text[length] = '\0';
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
		this->text[this->length] = '\0';
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
};