
struct TEXTUAL {
	TEXTUAL(const char text[], DINT x, DINT y, COLOR c = B, DINT scale = 2, DINT spacing = 2) {
		this->string = text;
		this->x = x;
		this->y = y;
		this->color = c;
		this->scale = {(double)scale, (double)scale};
		this->spacing = spacing;
		this->display = 1;
		this->id = -1;
	};
	TEXTUAL() {
		this->x = 0;
		this->y = 0;
		//this->color = R;
		this->scale = 1;
		this->spacing = 2;
		this->display = 0;
		this->id = -1;
	};
	STRING string;
	DINT x, y, spacing, display;
	SPOT scale;
	SINT id;
	COLOR color;

	void _update(const char text[]) {
		this->string = text;
	}
};

struct WRITER {
	WRITER(std::initializer_list<LIT> lts) {
		TIME time;
		time._clock(0);
		HOLDER<LIT> lits = lts;
		for (DINT i = 0; i < lits._size(); i++) {
			lit << lits[i];
		}
		//dummy = ENGINE_DUMMY;
		dummy = ENGINE_MAP_DUMMY;
		time._increment(time);
		std::cout << "\nConstructed WRITER in " << time._since(1) << " ms.";
	};
	static CHART <LIT> lit;
	static CHART <TEXTUAL> text;
	static LIT dummy;
	static STRING write;
	static void _type(const char text[], DINT x, DINT y, DINT size = 2, DINT spacing = 2, COLOR c = B) {
		DINT px, py, ll = 0;
		LIT tmp;
		PIXEL pix;
		for (DINT length = 0; text[length] != '\0'; length++) {
			tmp = WRITER::_lit(text[length]);
			for (DINT p = 0; p < tmp.shape.pixels.length; p++) {
				pix = tmp.shape.pixels[p];
				if (pix.color.exist) {
					//if (tmp.key >= 0) pix.color = c;
					px = x + (pix.x * size) + (ll * size) + (length * spacing);
					py = y + (pix.y * size);
					state._set(px, py, pix.color, size, size);
				}
			}
			ll += tmp.shape.size.w;
		}
	}

	static LIT _lit(const char character) {
		for (DINT i = 0; i < lit.length; i++) {
			LIT a = lit[i];
			if (a.lower == character || a.upper == character) return a;
		}
		return dummy;
	}

	static char _valid(DINT key) {
		for (DINT i = 0; i < lit.length; i++) {
			if (lit[i].key == key) return lit[i].lower;
		}

		return '?';
	}
	static char _c(DINT n) {
		for (DINT l = n; l < WRITER::lit.length; l++) {
			if (WRITER::lit.exist[l]) {
				LIT li = WRITER::lit[l];
				if (li.numeric == n) {
					return li.upper;
				}
			}
		}
		return '?';
	}
	static char* _itc(SLINT number = -1) {
		//char write[16];
		write = {};
		DINT length = 0;
		if (number < 0) {
			WRITER::write.text[0] = '-';
			number = UTILS::_abs(number);
			length++;
		}
		if (number == 0) {
			write.text[0] = '0';
			write.text[1] = '\0';
		}
		else {
			CHART <DINT> digits;
			DINT count = 0;
			double t = (double)number, calc = 0.0;
			for (; t > 0.91;) {
				t = (double)(number * 0.1);
				number /= 10;
				calc = t - (double)number;
				digits << (DINT)(calc * 10);
			}
			//digits._reverse();			
			for (DINT i = digits.length - 1; i >= 0; i--) {
				write.text[length] = _c(digits[i]);
				length++;
			}
			write.text[length] = '\0';
			digits._close();
		}
		return write.text;
	}

	static char* _dtc(double number = 0.0, DINT decimals = 3) {
		if (number == 0.0) {
			write._append("0.0");
		}
		else {
			STRING back, front;
			if (number < 0.0) {
				front._append("-");
				number = MATH::_dabs(number);
			}

			DINT f = (DINT)number;
			number = number - (double)f;
			front._append(WRITER::_itc(f));
			front._app('.');
			DINT spacing = 0;
			if (number < 1.0) {
				spacing = 1;
				number += 1.0;
			}
			do {
				number *= 10.0;
			} while (number != trunc(number));

			back._append(WRITER::_itc((SLINT)number));


			write._append(front.text);
			STRING decimaled;
			DINT d = 0;
			do {
				decimaled._app(back[d + spacing]);
				decimals--;
				d++;
			} while (decimals > 0);
			write._append(decimaled.text);

		}
		return write.text;
	}
	static double _ctd(const char text[], DINT decimals = 3) {
		INTC f, b;
		DINT l = 0;
		DINT s = (text[0] == '-') ? (1) : (0);
		STRING n = text;
		for (DINT i = s; text[i] != '.'; i++) {
			f.number << UTILS::_ctn(text[i]);
			l++;
		}
		n._slice(0, l);
		DINT rounder = 0;
		DINT ll = (s == 1) ? (l + 1) : (l);
		for (DINT i = ll; text[i] != '\0'; i++) {
			DINT n = UTILS::_ctn(text[i]);
			b.number << UTILS::_ctn(text[i]);
			rounder++;
		}

		double r = (double)f._number();
		double rb = b._double();// (double)b._number() / MATH::_tnth(1, rounder - 1);
		return (s == 1)?(-(r + rb)):(r + rb);
	}
	static SLINT _cti(STRING string) {
		SLINT digits = 0;
		SLINT modifier = 0;
		DINT modder = string.length;
		for (DINT i = 0; i < string.length; i++) {
			LIT chr = WRITER::_lit(string[i]);
			modifier = MATH::_tnth(chr.numeric, modder);
			digits += modifier;
			modder--;
			std::cout << "\n>" << chr.numeric << ", " << modifier;
		}
		digits /= 10;
		std::cout << "\n>>>" << digits;
		return digits;
	}
	static void _draw(TEXTUAL text, COLOR c = X) {
		DINT px, py, ll = 0;
		LIT tmp;
		PIXEL pix;
		for (DINT length = 0; text.string.text[length] != '\0'; length++) {
			tmp = WRITER::_lit(text.string.text[length]);
			for (DINT p = 0; p < tmp.shape.pixels.length; p++) {
				pix = tmp.shape.pixels[p];
				if (pix.color.exist) {
					if (c.exist) pix.color = c;
					px = text.x + (pix.x * (DINT)text.scale.x) + (ll * (DINT)text.scale.x) + (length * text.spacing);
					py = text.y + (pix.y * (DINT)text.scale.y);
					state._set(px, py, pix.color, (DINT)text.scale.x, (DINT)text.scale.y);
				}
			}
			ll += tmp.shape.size.w;
		}
	}

};


CHART<TEXTUAL> WRITER::text;
CHART<LIT> WRITER::lit;
LIT WRITER::dummy;
STRING WRITER::write;