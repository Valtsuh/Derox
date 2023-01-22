struct DYE {
	DYE(DINT color) {
		this->value = color;
	};
	DYE() {
		this->value = 0;
	};

	SINT value;


	operator SINT() const {
		return this->value;
	}

	void operator=(SINT value) {
		this->value = value;
	}

	DINT _darken(SINT amount = 0) {
		return this->_clamp(this->value - amount);
	}

	DINT _lighten(SINT amount = 0) {
		return this->_clamp(this->value + amount);
	}

	DINT _clamp(SINT value) {
		if (value > 255) value = 255;
		if (value < 0) value = 0;
		return (DINT)value;
	}

	void operator+=(SINT value) {
		this->value = this->_clamp(this->value + value);
	}
	void operator-=(SINT value) {
		this->value = this->_clamp(this->value - value);
	}

};

struct COLOR {
	COLOR(DYE r = 255, DYE g = 255, DYE b = 255, DINT exist = 1, DINT brk = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = brk;
	};
	/*
	COLOR(DYE r, DYE g, DYE b, DINT exist = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = 0;
	}
	*/
	~COLOR() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->ref = 0;
		this->exist = 0;
	};
	DYE r, g, b;
	DINT exist, apply, brk;
	COLORREF ref;
	void _set(COLOR color) {
		if (color.r > 255) color.r = 255;
		if (color.r < 0) color.r = 0;
		if (color.g > 255) color.g = 255;
		if (color.g < 0) color.g = 0;
		if (color.b > 255) color.b = 255;
		if (color.b < 0) color.b = 0;
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->exist = color.exist;
		//this->exist = color.exist;
		this->_ref();
	}

	COLORREF _ref() {
		this->ref = RGB(this->r, this->g, this->b);
		return this->ref;
	}

	COLOR _darken(SINT amount) {

		COLOR c = { this->r._darken(amount), this->g._darken(amount), this->b._darken(amount) };
		return c;
	}

	COLOR _lighten(SINT amount) {
		COLOR c = { this->r._lighten(amount), this->g._lighten(amount), this->b._lighten(amount) };
		return c;
	}

	DINT operator == (COLOR c) {
		if (this->r != c.r) return 0;
		if (this->g != c.g) return 0;
		if (this->b != c.b) return 0;
		if (this->exist != c.exist) return 0;
		return 1;
	}
	DINT operator != (COLOR c) {
		if (this->r == c.r) return 0;
		if (this->g == c.g) return 0;
		if (this->b == c.b) return 0;
		if (this->exist == c.exist) return 0;
		return 1;
	}

	void _dump() {
		std::cout << "\n" << "(" << this->exist << "): " << this->r << ", " << this->g << ", " << this->b;
	}
};
/*
struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255, DINT exist = 1, DINT brk = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		if (exist == 1) this->exist = true; else this->exist = false;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = brk;
	};
	~COLOR() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->ref = 0;
		this->exist = 0;
	};
	DINT r, g, b, apply, brk;
	bool exist;
	COLORREF ref;
	void _set(COLOR color) {
		if (color.r > 255) color.r = 255;
		if (color.r < 0) color.r = 0;
		if (color.g > 255) color.g = 255;
		if (color.g < 0) color.g = 0;
		if (color.b > 255) color.b = 255;
		if (color.b < 0) color.b = 0;
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		//this->exist = color.exist;
		this->_ref();
	}

	COLORREF _ref() {
		this->ref = RGB(this->r, this->g, this->b);
		return this->ref;
	}

	DINT operator == (COLOR c) {
		if (this->r != c.r) return 0;
		if (this->g != c.g) return 0;
		if (this->b != c.b) return 0;
		if (this->exist != c.exist) return 0;
		return 1;
	}
	DINT operator != (COLOR c) {
		if (this->r == c.r) return 0;
		if (this->g == c.g) return 0;
		if (this->b == c.b) return 0;
		if (this->exist == c.exist) return 0;
		return 1;
	}

	void _dump() {
		std::cout << "\nCOLOR: " << this->r << ", " << this->g << ", " << this->b;
	}

};
*/
struct PIXEL {
	PIXEL(DINT x = 0, DINT y = 0, COLOR c = {}) {
		this->x = x;
		this->y = y;
		this->color = c;
		this->apply = 1;
	};
	COLOR color;
	DINT x, y, apply;

	void _dump() {
		std::cout << "\nPIXEL: " << this->x << ", " << this->y << " (" << this->color.r << ", " << this->color.g << ", " << this->color.b << ", " << this->color.exist << ")";
	}
};
struct LITERAL {
	LITERAL(std::initializer_list<COLOR> colors, DINT width = 3, DINT height = 5) {
		HOLDER<COLOR> holder = colors;
		this->size.w = width;
		this->size.h = height;
		PIXEL pixel;
		DINT p = 0;
		//std::cout << "\n> Lettering colors. " << this->size.w << ", " << this->size.h;
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				pixel = { x, y, holder[p] };
				//std::cout << "\n> " << pixel.x << ", " << pixel.y << " (" << pixel.color.r << ", " << pixel.color.g << ", " << pixel.color.b << ")";
				this->pixels << pixel;
				p++;
			}
		}
		//std::cout << " - " << this->pixels.length;
	};
	LITERAL() {};
	~LITERAL() {};

	CHART <PIXEL> pixels;
	DIMENSION size;

	PIXEL _get(DINT x, DINT y) {
		for (DINT i = 0; i < this->pixels.size; i++) {
			if (this->pixels[i].x == x && this->pixels[i].y == y) return this->pixels[i];
		}
		PIXEL p;
		return p;
	}
};

struct LIT {
	LIT(double identifier, int key, int numeric, const char upper, const char lower, LITERAL shape) {
		this->identifier = identifier;
		this->numeric = numeric;
		this->key = key;
		this->upper = upper;
		this->lower = lower;
		this->shape = shape;
		this->usage = 0;
	};
	LIT() {
		this->identifier = 0.0;
		this->numeric = -1;
		this->key = -1;
		this->upper = '#';
		this->lower = '#';
		this->usage = 0;
	}
	double identifier;
	SINT numeric, key;
	DINT usage;
	char upper, lower;
	LITERAL shape;
};

struct STATE {
	STATE() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->pixel = {};
		this->bi = {};
		this->memory = {};
	}
	SINT w, h, x, y;
	void* memory;
	BITMAPINFO bi;
	LINT* pixel;


	void _config(SINT x = -1, SINT y = -1, SINT w = -1, SINT h = -1) {
		if (x >= 0) this->x = (DINT)x;
		if (y >= 0) this->y = (DINT)y;
		if (w >= 0) this->w = (DINT)w;
		if (h >= 0) this->h = (DINT)h;

		if (this->memory) VirtualFree(this->memory, 0, MEM_RELEASE);
		this->memory = VirtualAlloc(0, this->_size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		this->bi.bmiHeader.biSize = sizeof(this->bi.bmiHeader);
		//std::cout << "\nConfiguring: ";
		//std::cout << "\n" << this->w << " + " << this->x;
		//std::cout << "\n" << this->h << " + " << this->y;
		this->bi.bmiHeader.biWidth = this->w;
		this->bi.bmiHeader.biHeight = this->h;
		this->bi.bmiHeader.biPlanes = 1;
		this->bi.bmiHeader.biBitCount = 32;
		this->bi.bmiHeader.biCompression = BI_RGB;
	}

	LINT _size() {
		return this->w * this->h * sizeof(unsigned int);
	}


	void _position(DINT x, DINT y) {
		this->x = x;
		this->y = y;
	}

	void _precise(DINT x, DINT y, COLOR c = { 125, 25, 240 }) {
		x = this->_clamp(0, x, this->w - 1);
		y = this->_clamp(0, y, this->h - 1);
		this->pixel = (LINT*)this->memory + (SLINT)this->h * (SLINT)this->w - ((SLINT)y + 1) * (SLINT)this->w + (SLINT)x;
		*this->pixel = c.ref;

	}

	void _set(SINT px, SINT py, COLOR c = {}, DINT width = 1, DINT height = 1, bool refUsage = false) {
		px = this->_clamp(0, px, this->w);
		SINT tx = this->_clamp(0, px + width, this->w);
		py = this->_clamp(0, py, this->h);
		SINT ty = this->_clamp(0, py + height, this->h);
		//COLOR color = {c.b, c.g, c.r};
		for (SINT y = py; y < ty; y++) {
			this->pixel = (LINT*)this->memory + (SLINT)this->h * (SLINT)this->w - ((SLINT)y + 1) * (SLINT)this->w + (SLINT)px;
			for (SINT x = px; x < tx; x++) {
				*this->pixel++ = (refUsage) ? (c.ref) : (c._ref());
			}
		}
	}

	void _clear(COLOR c = LGR) {
		this->pixel = (LINT*)this->memory;
		for (DINT y = 0; y < this->h; y++) {
			for (DINT x = 0; x < this->w; x++) {
				*this->pixel++ = c.ref;
				//this->_precise(x, y, c);
			}
		}
	}

	inline DINT _clamp(DINT min, DINT val, DINT max) {
		if (val < min) return min;
		if (val > max) return max - 1;
		return val;
	}

	void _draw(HWND handle) {
		HDC tool = GetDC(handle);	
		/*
		RGBQUAD a = { 0xFF, 0xFF, 0xFF, 0x00 };
		StretchDIBits(tool, this->x, this->y, this->w, this->h, 0, 0, 1, 1, &a, &this->bi, DIB_RGB_COLORS, SRCAND);	
		RGBQUAD alpha = { 0x00, 0x00, 0x00, (BYTE)125 };
		StretchDIBits(tool, this->x, this->y, this->w, this->h, 0, 0, 1, 1, &alpha, &this->bi, DIB_RGB_COLORS, SRCPAINT);
		*/
		StretchDIBits(tool, this->x, this->y, this->w, this->h, 0, 0, this->w, this->h, this->memory, &this->bi, DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(handle, tool);
	}

	void _dump() {
		std::cout << "\nSTATE: " << this->x << " (" << this->w << "), " << this->y << " (" << this->h << ")";
	}

};

STATE state = {};

struct LINE {
	LINE(SPOT a, SPOT b, DINT scale = 1, COLOR c = R) {
		this->a = a;
		this->b = b;
		this->scale = scale;
		this->color = c;
		if (a.x != b.x) {
			this->slope = (b.y - a.y) / (b.x - a.x);
		}
		else {
			this->slope = 0.0;
		}
		this->color = c;
		//std::cout << "\nConstructing LINE: " << this->slope;
	};
	LINE() {
		this->scale = 1;
		this->slope = 0.0;
	};

	SPOT a, b;
	double slope;
	DINT scale;
	COLOR color;
	void _draw(SINT ox = -1, SINT oy = -1, DINT drawPoints = 0, COLOR c = X) {
		SPOT sa = this->a, sb = this->b;
		//std::cout << "\n>" << sa.x << ", " << sa.y << " - " << sb.x << ", " << sb.y;
		if (drawPoints) {
			state._set((DINT)a.x, (DINT)a.y, BL, this->scale * 2, this->scale * 2);
			state._set((DINT)b.x, (DINT)b.y, G, this->scale * 2, this->scale * 2);
		}
		this->slope = 0.0;
		double steps = 0.0, pa = 0.0, end = 0.0;
		DINT rev = 0;
		COLOR color = (c.exist) ? (c) : (this->color);

		if (sb.x != sa.x) {
			this->slope = (sb.y - sa.y) / (sb.x - sa.x);
		}

		if (sb.x != sa.x && MATH::_dabs(this->slope) <= 1.0) {
			if (sa.x > sb.x) {
				sa = this->b;
				sb = this->a;
			}
			pa = sa.x;
			end = sb.x;
			steps = sa.y - this->slope * sa.x;
			/*
			for (double x = sa.x; x < sb.x; x += 1.0) {
				double y = this->slope * x + steps;
				//state._set((DINT)x, (DINT)y, color);
			}
			*/
		}
		else {
			if (sa.y > sb.y) {
				sa = this->b;
				sb = this->a;
			}
			this->slope = (sb.x - sa.x) / (sb.y - sa.y);
			pa = sa.y;
			end = sb.y;
			steps = sa.x - this->slope * sa.y;
			rev = 1;
			/*
			for (double y = sa.y; y < sb.y; y += 1.0) {
				double x = this->slope * y + steps;
				state._set((DINT)x, (DINT)y, color);
			}
			*/
		}
		
		for (; pa < end; pa += 1.0) {
			double pb = this->slope * pa + steps;
			if (rev) {
				state._set((DINT)pb + ox, (DINT)pa + oy, color, this->scale, this->scale);
			}
			else {
				state._set((DINT)pa + ox, (DINT)pb + oy, color, this->scale, this->scale);
			}
		}
		/*
		if (a.x > b.x) {
			a = this->b;
			b = this->a;
		}
		if (a.x != b.x) {
			slope = (b.y - a.y) / (b.x - a.x);
		}

		if (a.x != b.x && MATH::_dabs(slope) <= 1.0) {
				begin = a.x;
				end = b.x;
				steps = a.y - slope * a.x;

		}
		else {
			if (a.y > b.y) {
				a = this->b;
				b = this->a;
			}
			slope = (b.x - a.x) / (b.y - a.y);
			steps = a.x - slope * a.y;
			begin = a.y;
			end = b.y;
		}

		for (double q = begin; q < end; q += 1.0) {
			double r = slope * q + steps;
			state._set((DINT)q, (DINT)r, R);
		}

		*/
	}

	void _update(SPOT s) {
		*this = { {this->a.x, this->a.y}, s };
	}

	void _dump() {
		std::cout << "\nLine: " << this->a.x << ", " << this->a.y << " / " << this->b.x << ", " << this->b.y;

	}
};

struct POLYGON {
	POLYGON(double w, double h, double d, double s, const char file[], bool center = true) {
		std::cout << "\n Constructing POLYGON";
		TIME time;
		time._clock(0);
		DATA data;
		data._read(file, 1);
		this->name = file;
		double hx = 0.0, hy = 0.0, hz = 0.0;

		for (DINT e = 0; e < data.exas.length; e++) {
			SPOT spot = data.exas[e]._spot();
			if (spot.x > hx) hx = spot.x;
			if (spot.y > hy) hy = spot.y;
			if (spot.z > hz) hz = spot.z;
			//spot._dump();
		}
		//std::cout << "\n-------------";
		//std::cout << "\nx " << hx << ", y " << hy << ", z " << hz;
		//std::cout << "\n-------------";
		for (DINT e = 0; e < data.exas.length; e++) {
			//data.exas[e]._dump();
			SPOT spot = data.exas[e]._spot();
			if (center) {
				spot.x -= hx / 2.0;
				spot.y -= hy / 2.0;
				spot.z -= hz / 2.0;
			}
			//spot._dump();
			this->spot << spot;
			this->calc << spot;
			this->draw << spot;
			this->multi << spot;
			for (DINT p = 0; p < data.exas[e].pair.length; p++) {
				PAIR pair = { e, data.exas[e].pair[p] };
				this->pair << pair;
			}
			for (DINT g = 0; g < data.exas[e].group.length; g++) {
				DINT grp = data.exas[e].group[g];
				SINT f = -1;
				for (DINT gp = 0; gp < this->group.length; gp++) {
					if (this->group[gp].a == grp) {
						f = gp;
					}
				}
				if (f == -1) {
					GROUP g = { grp, {e} };
					this->group << g;
				}
				else {
					this->group[f].g << e;
				}
			}
		}
		/*
		for (DINT g = 0; g < this->group.length; g++) {
			std::cout << "\n " << g << "(" << this->group[g].a << "):";
			for (DINT c = 0; c < this->group[g].g.length; c++) {
				std::cout << " " << this->group[g].g[c];
			}
		}
		*/
		data.exas._close();
		this->scale = s;
		this->measure = { w, h, d };
		//this->_center();
		this->_size(this->scale);
		time._increment(time);
		std::cout << " " << time._since(1) << "ms.";
	}
	POLYGON(CHART<SPOT> spots, CHART<PAIR> pairs, SPOT measure) {
		for (DINT s = 0; s < spots.length; s++) {
			SPOT spot = spots[s];
			this->spot << spot;
			this->calc << spot;
			this->draw << spot;
			this->multi << spot;
		}
		for (DINT p = 0; p < pairs.length; p++) {
			this->pair << pairs[p];
		}
		this->measure = measure;
		this->_size(1.0);
	}
	POLYGON(const char file[], bool center = false) {
		TIME time;
		time._clock(0);
		DATA data;
		bool loaded = data._read(file, 1);
		this->name = file;
		double hx = 0.0, hy = 0.0, hz = 0.0;

		if (center) {
			for (DINT e = 0; e < data.exas.length; e++) {
				SPOT spot = data.exas[e]._spot();
				if (spot.x > hx) hx = spot.x;
				if (spot.y > hy) hy = spot.y;
				if (spot.z > hz) hz = spot.z;
			}
		}
		for (DINT e = 0; e < data.exas.length; e++) {
			SPOT spot = data.exas[e]._spot();
			if (center) {
				spot.x -= hx / 2.0;
				spot.y -= hy / 2.0;
				spot.z -= hz / 2.0;
			}
			this->spot << spot;
			this->calc << spot;
			this->draw << spot;
			this->multi << spot;
			for (DINT p = 0; p < data.exas[e].pair.length; p++) {
				PAIR pair = { e, data.exas[e].pair[p] };
				this->pair << pair;
			}
			GROUP grp;
			grp.a = e;
			for (DINT i = 0; i < data.exas[e].group.length; i++) {
				DINT g = data.exas[e].group[i];
				grp.g << g;
			}
			this->group << grp;
		}

		for (DINT i = 0; i < this->group.length; i++) {
			GROUP g = this->group[i];
			g._dump();
		}

		data.exas._close();
		time._increment(time);
		if (loaded) {
			std::cout << " in " << time._since(1) << " ms.";
		}
		else {
			std::cout << " -- unable to load file.";
		}
	}
	/*
	POLYGON(POLYGON& pol) {
		std::cout << "\nCopying POLYGON";
		for (DINT i = 0; i < pol.spot.length; i++) {
			this->spot << pol.spot.package[i].item;
			this->calc << pol.spot.package[i].item;
			this->draw << pol.spot.package[i].item;
			this->multi << pol.spot.package[i].item;
		}
		for (DINT i = 0; i < pol.pair.length; i++) {
			this->pair << pol.pair.item[i];
		}

		for (DINT f = 0; f < pol.face.length; f++) {
			this->face << pol.face.package[f].item;
		}

		this->name = pol.name.text;
		this->fov = 75.0;
		this->scale = 1.0;
		this->weight = 1.0;
		this->rotation = pol.rotation;
		this->direction = { pol.direction.x };
		this->_position(pol.position.x, pol.position.y);
		this->color = pol.color;
		this->radius = pol.radius;
	}
	*/
	POLYGON() {
		this->fov = 75.0;
		this->scale = 1.0;
		this->radius = 0.0;
	};

	IMAP<SPOT> spot, calc, draw, multi;
	IMAP<FACE> face;
	CHART<PAIR> pair;
	CHART<GROUP> group;
	COLOR color;
	SPOT measure, angle, rotation, direction, position;
	double fov, scale, radius;
	STRING name;

	void _close() {
		this->spot._close();
		this->calc._close();
		this->draw._close();
		this->multi._close();
		this->pair._close();
		this->face._close();
		this->group._close();
	}

	void _generate(double r = 25.0, DINT s = 3, double ang = 0.0, bool rz = false, bool triangle = false) {
		this->radius = r;
		if (s < 3) triangle = false;
		double a = 360.0 / (double)s;
		this->direction = { ang };
		double angle = this->direction.x;
		double gap = MATH::_dgap(r, 4.0);
		DICE dice;
		this->_close();
		if (triangle) {
			SPOT center = { 0.0 };
			this->_add(center);
		}
		for (DINT i = 0; i < s; i++) {
			double x = sin(MATH::_rad(angle));
			double y = cos(MATH::_rad(angle));
			SPOT spot = { r * x, r * y };
			PAIR pair;
			FACE face;
			if (i < s - 1) {
				pair = { i, i + 1 };
				if (!triangle) {
					face.i << i;
					face.i << i + 1;
				}
			}
			else {
				pair = { 0, s - 1 };
				if (!triangle) {
					face.i << 0;
					face.i << s - 1;
				}
			}
			this->pair << pair;
			this->face << face;
			this->_add(spot);
			angle += a;
		}

		if (triangle) {

			for (DINT i = 1; i < this->spot.length; i++) {
				FACE face;
				if (i < this->spot.length - 1) {
					face.i << i;
					face.i << i + 1;
				}
				else {
					face.i << 1;
					face.i << this->spot.length - 1;
				}
				face.i << 0;
				this->face << face;
			}

		}

		//this->_resize({ r, r, 0.0 });
	}

	void _add(SPOT s) {
		this->spot << s;
		this->calc << s;
		this->draw << s;
		this->multi << s;
	}

	void _resize(SPOT size) {
		this->measure = { size.x, size.y, size.z };
		for (DINT s = 0; s < this->spot.length; s++) {
			SPOT* calc = &this->calc[s];
			SPOT spot = this->spot[s];
			calc->x = spot.x * size.x;;
			calc->y = spot.y * size.y;
			calc->z = spot.z * size.z;
		}

	}

	void _scale(double scale) {
		for (DINT s = 0; s < this->spot.length; s++) {
			SPOT* spot = &this->calc[s];
			spot->x *= scale;
			spot->y *= scale;
			spot->z *= scale;
		}
	}

	void _size(double scale = 0.0) {
		scale = (scale != 0.0) ? (scale) : (this->scale);
		SPOT a;
		for (DINT c = 0; c < this->calc.length; c++) {
			a = this->spot[c];
			//a._dump();
			a.x *= this->measure.x * scale;
			a.y *= this->measure.y * scale;
			a.z *= this->measure.z * scale;
			this->calc[c] = { a.x, a.y, a.z };
			//this->calc[c]._dump();
			//std::cout << "\n------";
		}
	}

	void _position(double x, double y) {
		this->position.x = x;
		this->position.y = y;

	}

	void _draw(DINT x = 0, DINT y = 0, bool spots = true, bool lines = true, bool fill = false) {
		SPOT spot;
		state._set((SINT)this->position.x - 2, (SINT)this->position.y - 2, DG, 4, 4);

		for (DINT s = 0; s < this->calc.length; s++) {
			if (this->calc.package[s].exist) {

				spot = this->calc[s];

				SPOT out = MATH::_transform3D(spot, this->angle);
				out = MATH::_transform2D(out, this->direction, true);
				this->multi[s] = { out.x, out.y, out.z };
				this->draw[s] = { out.x + this->position.x, out.y + this->position.y, out.z, {this->draw[s].color.r, this->draw[s].color.g, this->draw[s].color.b} };
				SPOT d = this->draw[s];
				//d._dump();
				if (spots) {
					state._set((DINT)this->draw[s].x - 2, (DINT)this->draw[s].y - 2, { d.color.r, d.color.g, d.color.b }, 4, 4);
				}
			}
		}
		if (lines) {
			COLOR color = this->color;
			for (DINT f = 0; f < this->face.length; f++) {
				FACE face = this->face[f];
				for (DINT i = 0; i < face.i.length; i++) {
					SPOT a;
					SPOT b;
					if (i == face.i.length - 1) {
						a = this->draw[face.i[i]];
						b = this->draw[face.i[0]];
					}
					else {
						a = this->draw[face.i[i]];
						b = this->draw[face.i[i + 1]];
					}
					if (!color.exist) {
						if (i % 2 == 0) {
							color = R;
						}
						else {
							color = GR;
						}
					}
					LINE line = { a, b, 2, color };
					line._draw();
				}
			}

			/*
			COLOR color;
			for (DINT p = 0; p < this->pair.length; p++) {
				PAIR pair = this->pair[p];
				SPOT a = this->draw[pair.a], b = this->draw[pair.b];
				SPOT sa = this->multi[pair.a], sb = this->multi[pair.b];
				//if (sa.z > 0.0 || sb.z > 0.0) {
				if (p % 2 == 0) color = R; else color = GR;
				LINE l = { a, b, 2, color };
				l._draw();
				//}
			}
			*/
		}
		/*
		for (DINT i = 0; i < this->face.length; i++) {
			FACE face = this->face[i];
			IMAP<SPOT> spots;
			for (DINT i = 0; i < face.i.length; i++) {
				spots << this->draw[face.i[i]];
			}
			SSPOT sorted = {(double)INFINITY, (double)INFINITY, (double)-INFINITY, (double)-INFINITY};
			MATH::_makePoint(spots, &sorted);
			double x = sorted.x;
			double y = sorted.y;
			SPOT s = MATH::_transform3D({ x, y }, this->angle);
			double w = (sorted.w > sorted.x) ? (sorted.w - x) : (x - sorted.w);
			double h = (sorted.h > sorted.y) ? (sorted.h - y) : (y - sorted.h);
			double sw = w / this->texture.base.size.w;
			double sh = h / this->texture.base.size.h;
			this->texture.base.scale = { 1.0, 1.0 };
			this->texture.base.angle = this->angle;
			this->texture.base._transform3D(this->texture.base.scale, x, y);
			//this->texture.base._draw(x (SINT)y);
		}
		*/

		if (fill) {
			SSPOT r = true;
			MATH::_makePoint(this->draw, &r);
			SSPOT scan = { r.x, r.y, r.w - r.x, r.h - r.y };
			IMAP <SPOT> spots;
			/*
			for (DINT i = 0; i < this->draw.length; i++) {
				spots << this->draw[i];
				spots.package[i].z = (SINT)spots[i].x;
			}

			spots._sort(-1);
			*/
			for (DINT f = 0; f < this->face.length; f++) {
				spots._close();
				for (DINT i = 0; i < this->face[f].i.length; i++) {
					spots << this->draw[this->face[f].i[i]];
				}
				for (double y = r.y; y < r.h; y += 1.0) {
					for (double x = r.x; x < r.w; x += 1.0) {
						/*
						for (DINT sa = 0; sa < this->draw.length; sa++) {
							SPOT a = this->draw[sa];
							for (DINT sb = 0; sb < this->draw.length; sb++) {
								if (sa != sb) {
									SPOT b = this->draw[sb];
									if (MATH::_onLine(a, b, { x, y })) {
										state._set((DINT)x, (DINT)y, DG);
										break;
									}
								}

							}
						}
						*/
						SPOT p = { x, y };
						if (MATH::_spotInTriangle(p, spots)) {
							state._set((DINT)x, (DINT)y, DG);
						}

					}

				}
			}
			spots._close();

		}

		if (this->radius > 0.0) {
			//LINE degree = { this->position, {this->position.x + cos(MATH::_rad(this->direction.x)) * this->radius, this->position.y + sin(MATH::_rad(this->direction.x)) * this->radius}, 2, R };
			//degree._draw();
		}

		LINE first = { this->position, this->draw[0], 2, G };
		first._draw();
	}

	void _junction(POLYGON pol) {
		for (DINT p = 0; p < pol.pair.length; p++) {
			PAIR pair = pol.pair[p];
			pair.a += this->spot.length;
			pair.b += this->spot.length;
			this->pair << pair;
		}
		for (DINT s = 0; s < pol.calc.length; s++) {
			SPOT spot = pol.calc[s];
			bool found = false;
			for (DINT t = 0; t < this->calc.length; t++) {
				if (this->calc[t] == spot) {
					found = true;
					break;
				}
			}
			if (!found) {
				this->spot << spot;
				this->calc << spot;
				this->draw << spot;
				this->multi << spot;
			}
		}

	}

	void _dump() {
		std::cout << "\n\nDumping POLYGON ";
		this->name._dump();
		for (DINT i = 0; i < this->spot.length; i++) {
			this->spot[i]._dump();
			this->calc[i]._dump();
			this->draw[i]._dump();
			std::cout << "\n>>>>";
		}
		this->position._dump();
		std::cout << "\n----------";
		system("pause");

	}


	double _X() {
		double x = state.w;
		for (DINT i = 0; i < this->spot.length; i++) {
			if (this->draw[i].x < x) x = this->draw[i].x;
		}
		return x;
	}

	double _W() {
		double w = 0.0;
		for (DINT i = 0; i < this->spot.length; i++) {
			if (this->draw[i].x > w) w = this->draw[i].x;
		}
		return w;
	}

	double _Y() {
		double y = state.h;
		for (DINT i = 0; i < this->spot.length; i++) {
			if (this->draw[i].y < y) y = this->draw[i].y;
		}
		return y;
	}

	double _H() {
		double h = 0.0;
		for (DINT i = 0; i < this->spot.length; i++) {
			if (this->draw[i].y > h) h = this->draw[i].y;
		}
		return h;
	}


};

struct SPRITE {
	SPRITE() {
		this->loaded = false;
		this->scale = { 1.0, 1.0 };
	};
	IMAP <IMAP<PIXEL>> pixels;
	DIMENSION size, dim;
	STRING name;
	bool loaded;
	SPOT scale;

	void _position(DINT x, DINT y) {
		this->size.x = x;
		this->size.y = y;
	}

	void _palette(COLOR color) {
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				COLOR* clr = &this->pixels[x][y].color;
				for (DINT c = color.b; c > 0; c--) {
					if (clr->r > 0) clr->r -= 1;
					if (clr->g > 0) clr->g -= 1;
				}
			}
		}

	}

	void _draw(SINT px = -1, SINT py = -1, COLOR clr = X) {

		DINT extx = (MATH::_remainder(this->scale.x) != 0.0) ? (1) : (0);
		DINT exty = (MATH::_remainder(this->scale.y) != 0.0) ? (1) : (0);
		SINT posx = (px != -1) ? (px) : (this->size.x);
		SINT posy = (py != -1) ? (py) : (this->size.y);
		this->dim = { px, py, px + (DINT)(this->size.w * this->scale.x), px + (DINT)(this->size.h * this->scale.y) };
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				PIXEL pixel = this->pixels[x][y];
				if (pixel.color.exist) {
					double px = (double)pixel.x;
					double py = (double)pixel.y;
					COLOR color = clr;
					color = (pixel.color.exist) ? (pixel.color) : (color);
					state._set((DINT)(px * this->scale.x) + posx, (DINT)(py * this->scale.y) + posy, color, (DINT)this->scale.x + extx, (DINT)this->scale.y + exty);
				}
			}
		}
	}

	void _dump() {
		std::cout << "\nSPRITE: " << this->size.w << ", " << this->size.h;

		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				PIXEL pixel = this->pixels[x][y];
				//pixel._dump();
			}
		}
	}

};
struct ANIMATION {
	ANIMATION(std::initializer_list<SPRITE> sprts, DINT scale = 2) {
		HOLDER<SPRITE> sprites = sprts;
		//std::cout << "\nConstructing ANIMATION (" << sprites._size() << ")";
		for (DINT s = 0; s < sprites._size(); s++) {
			this->sprite << sprites[s];
		}
		this->size.w = this->sprite[0].size.w;
		this->size.h = this->sprite[0].size.h;
		this->stage = 0;
		this->scale = scale;
		this->facing = 0;
		this->direction = DIR::ASC;
		this->loop = 0;
		this->target = -1;
	}

	ANIMATION(CHART<SPRITE> sprites, DINT scale = 1) {
		for (DINT s = 0; s < sprites.length; s++) {
			if (sprites.exist[s]) {
				this->sprite << sprites[s];
			}
		}
		this->size.w = sprites[0].size.w;
		this->size.h = sprites[0].size.h;
		this->stage = 0;
		this->scale = scale;
		this->facing = 0;
		this->direction = DIR::ASC;
		this->loop = 0;
		this->target = -1;
	}

	ANIMATION() {
		this->stage = 0;
		this->scale = 1;
		this->facing = 0;
		this->direction = DIR::ASC;
		this->loop = 0;
		this->target = -1;
	};
	CHART <SPRITE> sprite;
	DIMENSION size, dim;
	DINT stage, scale, facing, loop;
	DIR direction;
	SINT target;

	void _draw(SINT x = -1, SINT y = -1, DINT mirror = 0, DINT outline = 0, DINT duration = 15, SINT stage = -1) {
		if (this->sprite.length > 0) {
			this->dim = { x, y, this->sprite[0].size.w + x, this->sprite[0].size.h + y };
			x = (x != -1) ? (x) : (this->size.x);
			y = (y != -1) ? (y) : (this->size.y);
			if (stage == -1) {
				if (this->sprite.length > 1) {
					if (this->loop >= duration) {
						DINT dir = 0;
						if (this->direction == DIR::ASC) {
							dir = 1;
						}
						else {
							dir = -1;
						}
						this->stage += dir;
						if (this->stage == this->sprite.length - 1) {
							this->direction = DIR::DESC;
						}
						if (this->stage == 0) {
							this->direction = DIR::ASC;
						}
						this->loop = 0;
					}
					this->loop++;
				}
				this->sprite[this->stage]._draw(x, y);
			}
			else {
				this->sprite[stage]._draw(x, y);
			}
		}
	}

	char* _name() {
		return this->sprite[0].name.text;
	}


};