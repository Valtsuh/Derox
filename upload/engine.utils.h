
#include <time.h>

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
	SINT i;
	double d;
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
		this->microsecond = 0;
		this->nanosecond = 0;
		this->success = 0;
		this->precision = 0;
		this->count = 0;
		this->system = {};
		this->difference = 0;
		//uint64_t nanos;
		//nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 10 / 10;
		//std::cout << "\n Nanos: " << nanos;
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
	DINT year, month, day, hour, hms, minute, mms, second, sms, millisecond, microsecond, nanosecond, success, precision, count, elapsed, difference;
	SYSTEMTIME system;
	
	void _clock() {
		this->_reset();
		GetLocalTime(&this->system);
		LINT nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 10 / 10;
		//std::cout << "\n Micros: " << (DINT)micros << " / " << micros;
		this->year = this->system.wYear;
		this->month = this->system.wMonth;
		this->day = this->system.wDay;
		this->hour = this->system.wHour;
		this->minute = this->system.wMinute;
		this->second = this->system.wSecond;
		this->millisecond = this->system.wMilliseconds;
		LINT mccounter = 1000000;
		LINT mcs = nanos / mccounter;
		this->microsecond = (DINT)(nanos - mcs * mccounter) / 1000;
		LINT ncounter = 1000;
		LINT ns = nanos / ncounter;
		this->nanosecond = (DINT)(nanos - ns * ncounter);
		//std::cout << "\n Milliseconds: "  << nanos << ": (" << ns << ", " << mcs << ") - (" << this->nanosecond << ", " << this->microsecond << " / " << this->millisecond << ")";
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
		this->microsecond = 0;
		this->nanosecond = 0;
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

struct DICE {
	DICE() {
		this->seed.i = 0;
		this->seed.d = 0.0;
		this->value.i = 0;
		this->seed.d = 0.0;

	};
	
	DUAL seed, value;
	TIME time;
	operator DICE() const {
		return *this;
	}

	SINT _roll(SINT min, SINT max) {
		this->time._clock();
		this->seed.i = (this->time.nanosecond) % (max + 1 - min); // 0 - 9
		this->value.i = this->seed.i + min;
		this->value.i = (this->value.i > max) ? (max) : (this->value.i);
		//std::cout << "\nSeed: " << this->seed.i << ", Value: " << this->value.i << " (" << min << ", " << max << ")";
		return this->value.i;
	}

	double _droll(double min, double max, double accuracy = 0.01) {
		this->time._clock();
		if (min > max) {
			double tmin = min;
			min = max;
			max = tmin;
		}
		double addition = 0.0;
		DINT cmin = 0, cmax = 0;
		DINT hcount = 0;

		double nmin = min;
		double nmax = max;
		do {
			nmin += 1.0;
			addition += 1.0;
		} while (nmin < 0.0);

		do {
			nmin *= 10.0;
			cmax++;
		} while (min / nmin > accuracy);
		SINT dmin = (SINT)nmin;
		nmax += addition;
		do {
			nmax *= 10.0;
			cmin++;
		} while (max / nmax > accuracy);
		SINT dmax = (SINT)nmax;
		DINT value = 1;
		hcount = (cmin > cmax) ? (cmin) : (cmax);
		for (DINT c = 1; c <= hcount + 2; c++) {
			value *= value * c + this->_roll(10, 20);
		}
		this->seed.i = (this->time.nanosecond * value) % (dmax + 1 - dmin);
		this->value.i = this->seed.i + dmin;
		this->value.d = (double)this->value.i;
		for (DINT c = 0; c < hcount; c++) {
			this->value.d /= 10.0;
		}
		this->value.d -= addition;
		if (this->value.d < min) this->value.d = min;
		//std::cout << "\nDouble roll: " << this->value.d << " (" << min << ", " << max << ")";
		return this->value.d;

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

struct DIMENSION {
	DIMENSION(DINT x = 0, DINT y = 0) {
		this->x = x;
		this->y = y;
		this->w = 0;
		this->h = 0;
		this->size = 0;
		this->direction = 0;
	}
	~DIMENSION() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->size = 0;
		this->direction = 0;
	};
	DINT x, y, w, h, size, direction;


	void _set(DIMENSION dimension) {
		this->x = dimension.x;
		this->y = dimension.y;
		this->w = dimension.w;
		this->h = dimension.h;
		this->size = dimension.size;
	}
};
struct SPOT {
	SPOT(double x = 0.0, double y = 0.0, double z = 0.0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	~SPOT() {};
	double x, y, z;
};
struct POSITION {
	POSITION() {
		this->x = 0.0;
		this->y = 0.0;
		this->acceleration.y = 0.279;
		this->velocity = {};
		this->force = {};
		this->w = 0;
		this->h = 0;
	};
	~POSITION() {};

	SPOT acceleration, velocity, force;
	double x, y;
	DINT w, h;
};
struct DIRECTION {
	DIRECTION(DINT value = 0, DINT exist = 0, DINT available = 0) {
		this->value = value;
		this->exist = exist;
		this->available = available;
	};
	~DIRECTION() {
		this->value = 0;
		this->exist = 0;
		this->available = 0;
	};
	DINT value, exist, available;


	void _set(DINT number) {
		this->value = number;
		this->exist = 1;
		this->available = 0;
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
	~STRING() {
		this->length = 0;
		*this->wtext = {};
		*this->text = {};
		*this->utext = {};
	};
	DINT length;
	wchar_t wtext[128];
	char text[128];
	unsigned char utext[128];
	DICE dice;

	void _generate(DINT length = 5) {
		if (length > 127) length = 127;
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
			this->length++;
		}
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
		for (DINT length = 0; length < 128; length++) {
			this->wtext[length] = L'\0';
			this->text[length] = '\0';
			this->utext[length] = (unsigned char)'\0';
		}
		this->length = 0;
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
	DINT value;
	SINT current, total;

	void _add(DINT value = 0) {
		this->current += value;
		this->total += value;
	}

	DINT _difference(COUNTER counter) {
		return this->current - counter.current;
	}
};
struct FIGURE {
	FIGURE() {
		this->current = 0.0;
		this->total = 0.0;
		this->value = 0.0;
	};
	~FIGURE() {};
	double current, total, value;

	void _add(double amount) {
		this->current += amount;
		this->total += amount;
	}

};
template <typename LIST_ITEM>
struct LIST {
	LIST() {
		this->length = 0;
		this->total = 0;
		*this->item = {};
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			//this->item[i] = { 0 };
			this->exist[i] = 0;
		}
	};
	~LIST() {

		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			//this->item[i] = { 0 };
			this->exist[i] = 0;
		}
		*this->item = {};
		this->length = 0;
		this->total = 0;
	};

	DINT length, total;
	LIST_ITEM item[ENGINE_DATABASE_LIST_LENGTH_MAX]; // approx. max array length
	DINT exist[ENGINE_DATABASE_LIST_LENGTH_MAX];

	DINT _exist(DINT position) {
		return this->exist[position];
	}

	DINT _amount() {
		DINT a = 0, b = 0;
		do {
			if(this->exist[a] == 1) a++;
			b++;
		} while (b < ENGINE_DATABASE_LIST_LENGTH_MAX);
		return a;
	}

	DINT _add(LIST_ITEM item) {
		DINT added = 0;
		LIST <LIST_ITEM>* list = this;
		for (DINT d = 0; d < ENGINE_DATABASE_LIST_LENGTH_MAX; d++) {
			if (list->exist[d] == 0) {
				this->item[d] = item;
				this->exist[d] = 1;
				this->length++;
				this->total++;
				added = 1;
				break;
			}
		}
		list = {};
		return added;
	}

	void _total() {
		DINT i = 0;
		for (DINT e = 0; e < ENGINE_DATABASE_LIST_LENGTH_MAX; e++) {
			if (this->exist[e]) i++;
		}
		this->total = i;
	}

	void _remove(DINT position = 0) {
		this->existance[position] = 0;
		this->length--;
		LIST <LIST_ITEM> *list = new LIST;
		LIST <LIST_ITEM>* current = this;
		for (DINT a = 0; a < ENGINE_DATABASE_LIST_LENGTH_MAX; a++) {
			if (current->exist[a] == 1) {
				list->_set(current->item[a]);
				if (list->length == current->length) break;
			}
		}
		current->_clear();
		list->total = this->total;
		*this = *list;
		list->_clear();
		delete list;
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
	CHART(DINT block = 8) {
		//std::cout << "\nConstructing chart.";
		this->block = block;
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->filled = 0;		
		//this->item = new ITEM[this->block];
		//this->exist = new BINT[this->block];
		this->dummy = {};
	}	
	~CHART() {
		this->size = 0;
		this->block = 0;
		this->filled = 0;
		this->last = 0;
		this->length = 0;
		this->total = 0;
	}
	DINT size, block, filled;
	SINT last;
	BINT length, total;
	ITEM* item;
	ITEM dummy;
	BINT* exist;
	STRING name;
	
	void _resize(DINT size = 0) {
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
			for (DINT k = 0; k < total; k++) {
				if (this->exist[k]) {
					items[l] = this->item[k];
					exists[l] = 1;
					l++;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
			DINT j = 0;
			for (this->length = 0; this->length < l && j < this->size; this->length++) {
				if (exists[this->length]) {
					this->item[j] = items[this->length];
					this->exist[j] = 1;
					j++;
				}
			}
			delete[] items;
			delete[] exists;
		}
		else {
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
		}
	};

	DINT _existance() {
		if (this->size > 0) {
			ITEM* item = new ITEM[this->length];
			BINT* exist = new BINT[this->length];
			DINT j = 0;
			for (DINT i = 0; i < this->size; i++) {
				if (this->exist[i]) {
					item[j] = this->item[i];
					exist[j] = 1;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			this->item = new ITEM[j];
			this->exist = new BINT[j];
			for (this->length = 0; this->length < j; this->length++) {
				this->item[this->length] = item[this->length];
				this->exist[this->length] = 1;
			}
			delete[] item;
			delete[] exist;
			this->size = this->length;
			return this->length; //
		}
		else {
			return 0;
		}
	}

	SINT _first() {
		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i]) return i;
		}
		return -1;
	};

	void operator<<(ITEM item) {

		if (this->size == 0 || this->length == this->size) {
			//std::cout << "\n>Sizing. (" << this->size << ")";
			this->_resize();
		}
		DINT offset = this->last;
		for (DINT i = offset; i < this->size; i++) {
			if (this->exist[i] == 0) {
				this->item[i] = item;
				this->exist[i] = 1;
				this->length++;
				this->total++;
				if (i == this->last) {
					this->filled = 1;
					this->last = 0;
				}
				break;
			}
		}
	};

	void operator>>(DINT position) {
		ITEM item = {};
		if (position < this->size && position >= 0) {
			this->exist[position] = 0;
			this->item[position] = item;
			this->length--;
			if (this->filled == 1) {
				this->last = position;
				this->filled = 0;
			}
			if (this->length == 0) {
				std::cout << "\nSize 0, deleting.";
				delete[] this->exist;
				delete[] this->item;
				this->size = 0;
			}
			//if(position < this->last) this->last = position;
		}
		else {
			std::cout << "\nOut of bounds.";
		}
	};

	ITEM& operator[](DINT position) {
		if (position >= this->size) {
			this->dummy;
		}
		return this->item[position];
	};

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
			this->~CHART();
			//delete this;
		}
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
	STRING time;
	STRING limit;
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

	void _load() {
		std::cout << "\nLoading save file: ";
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
		this->time.length = 0;
		for (DINT i = this->streak.length + this->streaker.length + 2; this->data.text[i] != ' '; i++) {
			this->time.text[this->time.length] = this->data.text[i];
			this->time.length++;
		}
		this->time.text[this->time.length] = '\0';
		std::cout << this->streaker.text << " - " << this->streak.text << " " << this->time.text << " loops.";

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
		return this->ts.size();
	}
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

