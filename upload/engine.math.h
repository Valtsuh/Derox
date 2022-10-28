
struct MATH {
	MATH() {
	};
	~MATH() {};
	static SINT _polar(SINT value) {
		return (-1) * value;
	} 

	static double _dpolar(double value = 1.0) {
		return (-1) * value;
	}


	static SINT _gap(SINT value = 0, SINT range = -1) {
		DICE dice;
		SINT a = value - range, b = value + range;
		if (a < b) {
			return dice._roll(a, b);
		}
		else {
			return dice._roll(b, a);
		}
	}

	static DINT _iap(DINT *values = {}) {
		DINT position = 0;
		DINT value = 0;
		for (DINT p = 0; &values[position] != nullptr; p++) {
			value += values[position];
		}
		return value;

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

	static void _change(SPOT* s, double x, double y, double z) {
		s->x += x;
		s->y += y;
		s->z += z;

		if (s->x >= 359.0) s->x -= 359.0;
		if (s->x <= -359.0) s->x += 359.0;
		if (s->y >= 359.0) s->y -= 359.0;
		if (s->y <= -359.0) s->y += 359.0;
		if (s->z >= 359.0) s->z -= 359.0;
		if (s->z <= -359.0) s->z += 359.0;
	}

	static void _rotate(SPOT *p, SPOT angle, DINT correction = 1) {		

		if (correction) angle.y += 90.0;
		SPOT c = { cos(angle.x), cos(angle.y), cos(angle.z) };
		//SPOT c = { cos(MATH::_rad(angle.x)), cos(MATH::_rad(angle.y)), cos(MATH::_rad(angle.z))};
		SPOT s = { sin(angle.x), sin(angle.y), sin(angle.z) };
		//SPOT s = { sin(MATH::_rad(angle.x)), sin(MATH::_rad(angle.y)), sin(MATH::_rad(angle.z)) };
		//cos._dump();
		//sin._dump();
		p->x = p->x * c.x + p->z * s.x;
		//p->x = p->x * sin.x + p->y * cos.x;
		p->y = p->y * s.y + p->x * c.y;
		//p->x = p->x * c.x + p->y * MATH::_polar(s.x);

		//p->y = p->y * cos.y + p->x * sin.y;

		//p->z = p->z * sin.z + p->y * cos.z;
		//p->y = p->y * MATH::_polar(s.y) + p->z * c.y; 
		
		//p->z = p->z * s.z + p->x * c.z;
		//p->z = p->z * c.z + p->y * s.z;
	}
	static void _spec(SPOT *p, double angle) {

		//std::cout << "\n" << p->x << ", " << p->y << ", " << p->z;
		//p->z = (p->z == 0.0) ? (1.0) : (p->z);
		//p->x = MATH::_clamp((p->x * angle) / (angle + p->z), -angle, angle);
		//p->y = MATH::_clamp((p->y * angle) / (angle + p->z), -angle, angle);


	}

	static double _clamp(double val, double min, double max) {
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}

	static DINT _tnth(DINT a, DINT th) {
		DINT value = a;
		do {
			value *= 10;
			th--;
		} while (th > 0);
		return value;
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

	static DINT _cmatch(DINT number, CHART<DINT> index) {
		for (DINT i = 0; i < index.length; i++) {
			if (index.exist[i] && index[i] == number) return 1;
		}
		return 0;
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

	static double _ballCollision(double x1, double x2, double y1, double y2, double r1, double r2) {
		return MATH::_dabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};

	static double _ballDistance(double x1, double x2, double y1, double y2, double r1, double r2) {
		return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	};
};
