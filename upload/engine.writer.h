
struct TEXTUAL {
	TEXTUAL(const char text[], DINT x, DINT y, COLOR c = B, DINT scale = 2, DINT spacing = 2) {
		this->string = text;
		this->x = x;
		this->y = y;
		this->color = c;
		this->scale = scale;
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
	DINT x, y, scale, spacing, display;
	SINT id;
	COLOR color;

	void _update(const char text[]) {
		this->string = text;
	}
};

struct WRITER {
	WRITER(std::initializer_list<LIT> lts) {
		std::cout << "\nConstructing WRITER.";
		HOLDER<LIT> lits = lts;
		for (DINT i = 0; i < lits._size(); i++) {
			lit << lits[i];
		}
		//dummy = ENGINE_DUMMY;
		dummy = ENGINE_MAP_DUMMY;
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
					if (tmp.key >= 0) pix.color = c;
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
	static char* _itc(SINT number = -1) {
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
					px = text.x + (pix.x * text.scale) + (ll * text.scale) + (length * text.spacing);
					py = text.y + (pix.y * text.scale);
					state._set(px, py, pix.color, text.scale, text.scale);
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