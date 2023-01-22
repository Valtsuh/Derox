
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

	static double _min(double a, double b) {
		return (a < b) ? (a) : (b);
	}

	static double _max(double a, double b) {
		return (a > b) ? (a) : (b);
	}

	static double _pi() {
		return 3.1415926535;
	}

	static double _rad(double degree = 90.0) {
		return degree * (MATH::_pi() / 180.0);
	}

	static double _deg(double rad = 1.0) {
		return rad * (180.0 / MATH::_pi());
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

	static double _dgap(double value, double range = 2.0) {
		DICE dice;
		double a = value - range, b = value + range;
		if (a < b) {
			return dice._droll(a, b);
		}
		else {
			return dice._droll(b, a);
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

	static double _remainder(double d) {
		for (; d >= 1.0; d -= 1.0);
		return d;
	}

	static double _length(double a, double b) {
		if (a > b) {
			double c = b;
			b = a;
			a = c;
		}

		return b - a;
	}

	static double _posAngle(SPOT a, SPOT b, double degree) {
		double radius = MATH::_distance(a, b);
		SPOT c = { a.x + cos(MATH::_rad(degree + 90.0)) * radius, a.y + sin(MATH::_rad(degree + 90.0)) * radius };
		double rad = atan2(b.y - a.y, b.x - a.x);
		double deg = MATH::_deg(rad);
		/*
		//double rad = atan(slope);
		double deg = MATH::_dabs(MATH::_deg(rad));
		double calc = 0.0;
		if (a.x >= c.x && a.y <= c.y) {
			// 0 - 90
			std::cout << "\n 0 ";
			calc = deg - degree - 90.0;
		}
		else if (a.x >= c.x && a.y >= c.y) {
			// 90 - 180
			std::cout << "\n 1 ";
			calc = deg - degree + 270.0;
		}
		else if (a.x <= c.x && a.y >= c.y) {
			// -180 - -90
			std::cout << "\n 2 ";
			calc = deg - degree + 180.0;
		}
		else if (a.x <= c.x && a.y <= c.y) {
			// -90 - 0
			std::cout << "\n 3 ";
			calc = deg - degree + 90.0;
		}
		else {
			// err
		}


		std::cout << rad << ", " <<  deg << ", " << calc;
		*/

		return deg;
	}

	static bool _between(double p, double a, double b) {
		if (b < a) {
			double c = b;
			b = a;
			a = c;
		}
		return a <= p && p <= b;
	}

	static double _pointAngle(SPOT a, SPOT b, double degree) {
		double radius = MATH::_distance(a, b);
		SPOT c = { a.x + cos(MATH::_rad(degree + 90.0)) * radius, a.y + sin(MATH::_rad(degree + 90.0)) * radius };
		double m = (c.y - b.y) / (c.x - b.x);
		double rad = atan(m);
		double deg = MATH::_deg(rad);
		return deg;
		
	}
	static bool _toLeft(SPOT a, SPOT b, double degree) {
		double angle = MATH::_posAngle(a, b, degree);
		angle = (DINT)(angle - degree) % 360;
		if (MATH::_between(angle, 0.0, 89.0) || MATH::_between(angle, -360.0, -271.0)) {
			return true;
		}
		return false;
	}
	static bool _toRight(SPOT a, SPOT b, double degree) {
		double angle = MATH::_posAngle(a, b ,degree);
		angle = (DINT)(angle - degree) % 360;
		if (MATH::_between(angle, 91.0, 180.0) || MATH::_between(angle, -269.0, -160.0)) {
			return true;
		}
		return false;
	}

	static bool _behind(SPOT a, SPOT b, double degree) {
		double angle = MATH::_posAngle(a, b, degree);
		angle = (DINT)(angle - degree) % 360;
		//std::cout << "\n>" << angle;
		if (
			MATH::_between(angle, -90.0, 0.0) || 
			MATH::_between(angle, -90.0, -180.0) ||
			MATH::_between(angle, 180.0, 270.0) ||
			MATH::_between(angle, 270.0, 360.0)
			) return true;
		//if (angle > -90.0 && angle > -30.0) return true;
		//if (angle > -40.0) return true;
		return false;
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

	static SPOT _transform2D(SPOT p, SPOT angle, bool rad = false) {
		for (; angle.x >= 360.0; angle.x -= 360.0);
		SPOT n;
		double c, s;
		if (rad) {
			c = cos(MATH::_rad(angle.x)); 
			s = sin(MATH::_rad(angle.x));
		}
		else {
			c = cos(angle.x);
			s = sin(angle.x);
		}
		n.x = p.x * c - p.y * s;
		n.y = p.x * s + p.y * c;
		return n;
	}

	static SPOT _transform3D(SPOT p, SPOT angle, bool rad = false) {
		SPOT c, s;
		if (rad) {
			c = { cos(MATH::_rad(angle.x)), cos(MATH::_rad(angle.y)), cos(MATH::_rad(angle.z)) };
			s = { sin(MATH::_rad(angle.x)), sin(MATH::_rad(angle.y)), sin(MATH::_rad(angle.z)) };
		}
		else {
			c = { cos(angle.x), cos(angle.y), cos(angle.z) };
			s = { sin(angle.x), sin(angle.y), sin(angle.z) };
		}
		SPOT n; // = MATH::_transform2D(p, angle);

		n.y = p.y * c.x - p.z * s.x;
		n.z = p.y * s.x + p.z * c.x;

		n.x = p.x * c.y + n.z * s.y;
		n.z = p.x * s.y - n.z * c.y;

		//n.y = n.y * c.z + p.x * s.z;
		//n.x = p.y * s.z - n.x * c.z;

		
		return n;

	}

	static void _makePoint(IMAP<SPOT> spots, SSPOT *p) {
		for (DINT i = 0; i < spots.length; i++) {
			SPOT s = spots[i];
			if (s.x < p->x) p->x = s.x;
			if (s.x > p->w) p->w = s.x;
			if (s.y < p->y) p->y = s.y;
			if (s.y > p->h) p->h = s.y;
			if (s.z < p->z) p->z = s.z;
			if (s.z > p->d) p->d = s.z;
		}
	}
	
	static void _intersect(SPOT a, SPOT b, SSPOT *scan) {
		double slope = UTILS::_slope(a.x, b.x, a.y, b.y);
		if (b.x > a.x) slope = MATH::_dpolar(slope);
	}

	static double _distance(SPOT a, SPOT b) {
		double x = a.x - b.x;
		double y = a.y - b.y;
		return (MATH::_dabs(x) + MATH::_dabs(y));

	}

	static bool _spotInTriangle(SPOT p, IMAP<SPOT> spots) {
		if (spots.length == 0) return false;
		SSPOT e = true;
		MATH::_makePoint(spots, &e);
		if (p.x < e.x || p.x > e.w || p.y < e.y || p.y > e.h) return false;

		bool inside = false;

		for (DINT i = 0; i < spots.length; i++) {
			SPOT a = spots[i];
			SPOT b = spots[(i + 1) % spots.length];

			//bool ba = (a.y > p.y) != (b.y > p.y);
			//bool bb = (p.x < (b.x - a.x)* (p.y - a.y) / (b.y - p.y) + a.x);
			
			//if(ba && bb) inside = !inside;

			if (
				(a.y > p.y) != (b.y > p.y) &&
				(p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x)
				) inside = !inside;
		}

		return inside;
	}

	static bool _spotInDegree(SPOT p, IMAP<SPOT> spots) {

		double degree = 0.0;
		for (DINT i = 0; i < spots.length; i++) {
			SPOT a = spots[i];
			SPOT b = spots[(i + 1) % spots.length];
			/*
			if(i != spots.length){
				a = spots[i];
				b = spots[i + 1];
			}
			else {
				a = spots[i];
				b = spots[0];
			}
			*/

			double da = MATH::_distance(a, b);
			double db = MATH::_distance(p, a);
			double dc = MATH::_distance(p, b);

			SPOT dira, dirb;
			dira = { a.x - p.x, a.y - p.y };
			dirb = { b.x - p.x, b.y - p.y };

			double cross = dirb.y * dira.x - dirb.x * dira.y;
			bool clockwise = cross < 0.0;
			double m = cos((db * db + dc * dc - da * da) / (2.0 * db * dc));
			if (clockwise) {
				degree += MATH::_deg(m);
			}
			else {
				degree -= MATH::_deg(m);
			}
		}
		if (MATH::_dabs(round(degree) - 360.0) <= 3.0) return true;

		return false;

	}

	static bool _onLineExact(SPOT a, SPOT b, SPOT p) {

		if (a.x > b.x) {
			SPOT c = { a.x, a.y };
			a = { b.x, b.y };
			b = { c.x, c.y };
		}
		//if (a.x == p.x || a.y == p.y && b.x == p.x || b.y == p.y) return true;
		//if (a.x == p.x) return b.x == p.x;
		//if (a.y == p.y) return b.y == p.y;
		return (a.x - p.x) * (a.y - p.y) == (p.x - b.x) * (p.y - b.y);

	}

	static bool _inArea(SPOT a, SPOT b, SPOT p) {
		bool x = false, y = false;
		if (a.x < b.x && p.x >= a.x && p.x <= b.x ||
			a.x > b.x && p.x <= a.x && p.x >= b.x
			) x = true;
		if (
			a.y < b.y && p.y >= a.y && p.y <= b.y ||
			a.y > b.y && p.y <= a.y && p.y >= b.y
			) y = true;
		return x && y;
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

	static SLINT _tnth(DINT a, DINT th) {
		SLINT value = a;
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
