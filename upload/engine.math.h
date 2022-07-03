
struct MATH {
	MATH() {
	};
	~MATH() {};
	static DINT _ntop(SINT value = -1) {
		DINT p = 0;
		if (value < 0) {
			do {
				p++;
				value++;
			} while (value < 0);
		}
		else {
			p = (SINT)value;
		}
		return p;
	}

	static SINT _pton(DINT value = 1) {
		SINT n = 0;
		do {
			n--;
			value--;
		} while (value > 0);
		return n;
	}

	static DINT _iap(DINT *values = {}) {
		DINT position = 0;
		DINT value = 0;
		for (DINT p = 0; &values[position] != nullptr; p++) {
			value += values[position];
		}
		return value;

	}

	static DINT _abs(const SINT value = -1) {
		DINT val = 0;
		if (value < 0) {
			val = (-1) * value;
		}
		else {
			val = value;
		}
		return val;
	}

	static double _dabs(const double value = -1.0) {
		double val = 0.0;
		if (value < 0) {
			val = (-1.0) * value;
		}
		else {
			val = value;
		}
		return val;
	}


	static DINT _pow(const DINT a = 1, DINT b = 2) {
		DINT value = 1;
		if (a > 0 && b > 0) {
			value = 1;
			do {
				value = a * value;
				b--;
			} while (b > 0);
		}
		return value;
	}

	static DINT _fact(const DINT a = 1) {
		DINT value = 1;
		DINT i = 1;
		do {
			value *= i;
			i++;
		} while (i <= a);
		return value;
	}

	static double _pi() {
		return 3.1415926535;
	}

	static DINT _sq(DINT number = 1) {
		return number * number;
	}

	static double _dsq(double number = 1.0) {
		if (number < 0.0) {
			return -(MATH::_dabs(number) * MATH::_dabs(number));
		}
		else {
			return number * number;
		}
	}

	template <typename a, DINT s>
	static SINT _min(a (&values)[s]) {
		SINT value = values[0];
		for (DINT i = 0; i < s; i++) {
			value = (values[i] < value) ? (values[i]) : (value);
		}

		return value;
	}

	template <typename a, DINT s>
	static SINT _max(a (&values)[s]) {

		SINT value = values[0];
		for (DINT i = 0; i < s; i++) {
			value = (values[i] > value) ? (values[i]) : (value);
		}
		return value;
	}

	static SINT _imax(INDEX<SINT> index) {
		SINT first = index._first();
		SINT value;
		if (first >= 0) {
			value = index.item[first];

			for (DINT i = first; i < index.size; i++) {
				if (index.exist[i]) value = (index.item[i] > value) ? (index.item[i]) : (value);
			}
		}
		else {
			value = 0;
		}
		return value;
	}


	static SINT _cmax(CHART<SINT> index) {
		SINT first = index._first();
		SINT value = index[first];

		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index[i] > value) ? (index[i]) : (value);
		}
		return value;
	}

	static SINT _imin(INDEX<SINT> index) {
		DINT first = index._first();
		SINT value = index.item[first];

		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index.item[i] < value) ? (index.item[i]) : (value);
		}
		return value;
	}

	static SINT _cmin(CHART<SINT> index) {
		SINT first = index._first();
		SINT value = index[first];
		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index[i] < value) ? (index[i]) : (value);
		}
		return value;
	}

	static double _rad(double degree = 90.0) {
		return degree * (MATH::_pi() / 180.0);
	}

	static double _length(SPOT a, SPOT b) {
		double x = MATH::_dabs(a.x - b.x);
		double y = MATH::_dabs(a.y - b.y);
		return (x > y) ? (x) : (y);

	}

	static double _side(double x1, double x2) {
		return (x1 - x2 > 0) ? (-1.0) : (1.0);
	}

	/*
	
		Study.
		
	*/

	static double _srt(double number = 2.18, double accuracy = 0.1) {
		double value = 0.0;
		double counter = 0.0, lcounter = 0.0;
		double last = 0.0;
		do {
			counter += accuracy;
			value = counter * counter;
			//std::cout << "\n" << counter << " = " << value;
			//std::cout << "\n" << MATH::_dabs(number - last) << " < " << MATH::_dabs(number - value);
			if (MATH::_dabs(number - last) < MATH::_dabs(number - value)) {
				counter = lcounter;
				break;
			}
			lcounter = counter;
			last = value;
		} while (value < number);
		//std::cout << "\nSRT: " << counter;
		return counter;
	}

	static double _sin(double angle, double accuracy = 0.0001) {
		double value, sinx, sinval, temp;
		DINT den;
		value = MATH::_rad(angle);
		temp = value;
		sinx = value;
		sinval = sin(value);
		for (DINT j = 1; accuracy <= MATH::_dabs(sinval - sinx); j++) {
			den = 2 * j * (2 * j + 1);
			temp = -temp * value * value / (double)den;
			sinx += temp;
		}
		return sinx;

	}

	static double _cos(double angle, double accuracy = 0.0001) {
		double value, temp, cosx, cosval;
		DINT den;
		value = MATH::_rad(angle);
		temp = 1.0;
		cosx = temp;
		cosval = cos(value);
		for (DINT j = 1; accuracy <= MATH::_dabs(cosval - cosx); j++) {
			den = 2 * j * (2 * j - 1);
			temp = -temp * value * value / (double)den;
			cosx += temp;
		}
		return cosx;
	}

	static double _tan(double angle) {
		return MATH::_sin(angle) / MATH::_cos(angle);

	}

	static double _ballCollision(double x1, double x2, double y1, double y2, double r1, double r2) {
		return MATH::_dabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};

	static double _ballDistance(double x1, double x2, double y1, double y2, double r1, double r2) {
		return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	};
};