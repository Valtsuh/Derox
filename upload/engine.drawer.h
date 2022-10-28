

struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255, DINT exist = 1, DINT brk = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
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
	DINT r, g, b, exist, apply, brk;
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
};
struct PIXEL {
	PIXEL(DINT x = 0, DINT y = 0, COLOR c = {}) {
		this->x = x;
		this->y = y;
		this->color = c;
		this->apply = 1;
	};
	COLOR color;
	DINT x, y, apply;
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
	SINT* pixel;


	void _config(SINT x = -1, SINT y = -1, SINT w = -1, SINT h = -1) {
		if (this->memory) VirtualFree(this->memory, 0, MEM_RELEASE);
		this->memory = VirtualAlloc(0, this->_size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (x >= 0) this->x = (DINT)x;
		if (y >= 0) this->y = (DINT)y;
		if (w >= 0) this->w = (DINT)w;
		if (h >= 0) this->h = (DINT)h;
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
		this->pixel = (SINT*)this->memory + this->h * this->w - (y + 1) * this->w + x;
		*this->pixel = c.ref;

	}

	void _set(SINT px, SINT py, COLOR c = {}, DINT width = 1, DINT height = 1, DINT refUsage = 0) {
		px = this->_clamp(0, px, this->w);
		SINT tx = this->_clamp(0, px + width, this->w);
		py = this->_clamp(0, py, this->h);
		SINT ty = this->_clamp(0, py + height, this->h);

		for (SINT y = py; y < ty; y++) {
			this->pixel = (SINT*)this->memory + this->h * this->w - (y + 1) * this->w + px;
			for (SINT x = px; x < tx; x++) {
				*this->pixel++ = (refUsage)?(c.ref):(c._ref());
			}
		}
	}

	void _clear(COLOR c = LGR) {
		this->pixel = (SINT*)this->memory;
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
		StretchDIBits(tool, this->x, this->y, this->w, this->h, 0, 0, this->w, this->h, this->memory, &this->bi, DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(handle, tool);
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
				state._set((DINT)pb, (DINT)pa, color);
			}
			else {
				state._set((DINT)pa, (DINT)pb, color);
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
};


struct RECTANGLE {
	RECTANGLE(DIMENSION d, COLOR c = BL) {
		this->measure._set(d);
		this->color = c;
	}
	RECTANGLE(DINT x, DINT y, DINT w, DINT h, COLOR c) {
		this->measure = { x, y, w, h };
		this->color = c;
	};
	RECTANGLE(DINT w, DINT h, COLOR c) {
		this->measure.w = w;
		this->measure.h = h;
		this->color = c;
	}
	RECTANGLE() {};
	DIMENSION measure;
	COLOR color;

	void _draw(SINT x = 0, SINT y = 0, DINT scale = 1) {
		state._set(x + this->measure.x, y + this->measure.y, this->color, this->measure.w * scale, this->measure.h * scale);
	}
};

struct SPRITE {
	SPRITE(std::initializer_list<COLOR> clrs, SINT w, SINT h) {
		HOLDER<COLOR> colors = clrs;
		DINT size = 8;
		this->size.w = (w != -1) ? (w) : (size);
		this->size.h = (h != -1) ? (h) : (size);
		DINT c = 0;
		PIXEL pixel;
		this->scale = 1;
		this->facing = 0;
		this->pixels = this->size.w * this->size.h;
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				pixel = { x, y, colors[c] };
				this->pixels << pixel;
				c++;
			}
		}
		this->name._write("Unnamed");
		//std::cout << "\nConstructed sprite: " << this->pixels.length << " (" << this->size.w << ", " << this->size.h << ")";
		return;
	}
	SPRITE(const char filename[]) {
		TIME time;
		time._clock(0);
		this->facing = 0;
		this->scale = 1;
		std::ifstream file;
		STRING f;
		f._append("sprites/");
		f._append(filename);
		f._append(".drx");
		file.open(f.text);
		if (file.is_open()) {
			CHART <char> text;
			char cursor;
			while (file.good()) {
				file.get(cursor);
				text << cursor;
			}
			text << '\0';
			//std::cout << "\nSOF(" << text.length << ")";
			for (DINT c = 2; c < text.length; c++) {
				if (text[c] == '{') {
					char exist = ' ';
					CHART <DINT> red, green, blue;
					DINT re = 0, gr = 0, bl = 0;
					COLOR color;
					c++;
					do {
						red << UTILS::_isnum(text[c]);
						c++;
					} while (text[c] != ',');
					red._reverse();
					for (DINT a = 0; a < red.length; a++) {
						if (a == 0) {
							re = red[a];
						}
						else {
							re += MATH::_tnth(red[a], a);
						}
					}
					red._close();
					c++;
					do {
						green << UTILS::_isnum(text[c]);
						c++;
					} while (text[c] != ',');
					green._reverse();
					for (DINT b = 0; b < green.length; b++) {
						if (b == 0) {
							gr = green[b];
						}
						else {
							gr += MATH::_tnth(green[b], b);
						}
					}
					green._close();
					c++;
					do {
						blue << UTILS::_isnum(text[c]);
						c++;
					} while (text[c] != ',' && text[c] != '}');

					blue._reverse();
					for (DINT c = 0; c < blue.length; c++) {
						if (c == 0) {
							bl = blue[c];
						}
						else {
							bl += MATH::_tnth(blue[c], c);
						}
					}
					blue._close();

					if (text[c] == ',') color.exist = 0; else color.exist = 1;

					color = { re, gr, bl, color.exist };
					PIXEL p;
					p.color = color;
					this->pixels << p;
					//std::cout << "\n" << r.text << " - " << g.text << " - " << b.text;
					//std::cout << "\n" << re << ", " << gr << ", " << bl;
					//std::cout << "\n" << color.r << "(" << r.text << "), " << color.g << "(" << g.text << "), " << color.b << "(" << b.text << "), " << color.exist;
					//system("pause");
				}

				if (text[c] == '}' && text[c + 1] == '}') {
					CHART <DINT> w, h;
					DINT width = 0, height = 0;
					c += 3;
					do {
						//std::cout << text[c];
						w << (DINT)UTILS::_isnum(text[c]);
						c++;
					} while (text[c] != ',');
					w._reverse();
					for (DINT x = 0; x < w.length; x++) {
						if (x == 0) {
							width = w[x];
						}
						else {
							width += MATH::_tnth(w[x], x);
						}
					}
					w._close();
					//std::cout << "\nWidth: " << width;
					c += 2;
					do {
						h << (DINT)UTILS::_isnum(text[c]);
						c++;
					} while (text[c] != '}');
					h._reverse();
					for (DINT y = 0; y < h.length; y++) {
						if (y == 0) {
							height = h[y];
						}
						else {
							height += MATH::_tnth(h[y], y);
						}
					}
					h._close();
					//std::cout << "\nHeight: " << height;
					this->size.w = width;
					this->size.h = height;
				}
			}
			this->name._write(filename);
			//std::cout << "\nLoaded " << filename << ": " << this->pixels.length << " (" << this->size.w << ", " << this->size.h << ")";
			//std::cout << "\nVerifying pixels.";
			DINT x = 0, y = 0;

			for (DINT p = 0; p < this->pixels.length; p++) {
				PIXEL* pix = &this->pixels[p];
				pix->x = x;
				pix->y = y;
				y++;
				if (y == this->size.h) {
					y = 0;
					x++;
				}
				//std::cout << "\n" << pix->x << ", " << pix->y << " - " << pix->color.r << ", " << pix->color.g << ", " << pix->color.b;
			}
			//system("pause");

			//std::cout << "\nEOF.";		
			file.close();
		}
		time._increment(time);
		std::cout << "\n" << filename << " in " << time._since(1) << " ms.";
		//system("pause");
	}
	SPRITE(DINT w, DINT h) {
		//std::cout << "\nSPRITE";
		this->size = { 0, 0, w, h };
		this->scale = 1;
		this->facing = 0;
		this->name._write("Unnamed");
		PIXEL p = 0;
		for (DINT x = 0; x < w; x++) {
			for (DINT y = 0; y < h; y++) {
				p = { x, y, G };
				this->pixels << p;
			}
		}
		//system("pause");
	}
	SPRITE() {
		this->facing = 0;
		this->scale = 1;
	};
	CHART <PIXEL> pixels;
	DIMENSION size;
	DINT scale, facing;
	STRING name;

	void _draw(SINT scale = -1, SINT x = -1, SINT y = -1, DINT outline = 0, DINT mirror = 0) {
		if (this->pixels.length > 0) {
			DINT px, py;
			PIXEL pix;
			x = (x == -1) ? (this->size.x) : (x);
			y = (y == -1) ? (this->size.y) : (y);
			scale = (scale == -1) ? (this->scale) : (scale);
			/*
			for (DINT p = 0; p < this->pixels.length; p++) {
				if (this->pixels.exist[p]) {
					pix = this->pixels[p];
					if (outline) {
						if (pix.x == 0 || pix.y == 0 || pix.x == this->size.w - 1 || pix.y == this->size.h - 1) {
							pix.color = R;
							pix.color.exist = 1;
						}
					}
					if (pix.color.exist) {
						px = x + pix.x * scale;
						py = y + pix.y * scale;
						state._set(px, py, pix.color, scale, scale);
					}
				}
			}
			*/
			DINT p = 0;
			DINT pixx = 0;
			for (DINT w = this->size.w - 1; w >= 0; w--) {
				for (DINT h = 0; h < this->size.h; h++) {
					pix = this->pixels[p];
					if (pix.color.exist) {
						pixx = (mirror) ? (w) : (pix.x);
						px = x + pixx * scale;
						py = y + pix.y * scale;
						//if ((w == 0 || w == this->size.w - 1) && outline) pix.color = R;
						//if ((h == 0 || h == this->size.h) && outline) pix.color = R;
						state._set(px, py, pix.color, scale, scale);
					}
					p++;
				}
			}
		}
	}

	PIXEL* _get(DINT x, DINT y) {
		PIXEL* p = {};
		for (DINT i = x * y - 1; i < this->pixels.length; i++) {
			p = &this->pixels[i];
			if (p->x == x && p->y == y) return p;
		}
		return p;
	}

	void _dump() {
	}
};


struct TEXTURE {
	TEXTURE(CHART <LINE> outline) {
		for (DINT i = 0; i < outline.length; i++) {
			SPOT a = outline[i].a, b = outline[i].b;
			if (this->size.x == 0.0 || a.x < this->size.x) this->size.x = (DINT)a.x;
			if (b.x < this->size.x) this->size.x = (DINT)b.x;

			if (this->size.y == 0.0 || a.y < this->size.y) this->size.y = (DINT)a.y;
			if (b.y < this->size.y) this->size.y = (DINT)b.y;

			if (a.x > this->size.w) this->size.w = (DINT)a.x;
			if (b.x > this->size.w) this->size.w = (DINT)b.x;

			if (a.y > this->size.h) this->size.h = (DINT)a.y;
			if (b.y > this->size.h) this->size.h = (DINT)b.y;
		}
		this->measure.w = this->size.w - this->size.x;
		this->measure.h = this->size.h - this->size.y;
		this->base = { this->measure.w, this->measure.h };
	};
	TEXTURE(CHART<SPOT> spot) {

	};
	TEXTURE() {};
	
	DIMENSION size, measure;
	SPRITE base;
	
};


struct POLYGON {
	POLYGON(std::initializer_list<SPOT> spts, double w, double h, double d, std::initializer_list<PAIR> prs) {
		HOLDER<SPOT> spots = spts;
		for (DINT s = 0; s < spots._size(); s++) {
			SPOT a = spots[s];
			this->spot << spots[s];
			this->calc << spots[s];
			this->draw << spots[s];
		}
		HOLDER<PAIR> pairs = prs;
		for (DINT p = 0; p < pairs._size(); p++) this->pair << pairs[p];
		this->scale = 2.0;
		this->measure = { w * this->scale, h * this->scale, d * this->scale };
		this->_size();
		this->fov = 75.0;
	}
	POLYGON(double w, double h, double d, std::initializer_list<EXA> exas) {
		HOLDER exs = exas;
		for (DINT e = 0; e < exs._size(); e++) {
			this->spot << exs[e]._spot();
			this->calc << exs[e]._spot();
			this->draw << exs[e]._spot();
			for (DINT p = 0; p < exs[e].pair.length; p++) {
				PAIR pair = { e, exs[e].pair[p] };
				this->pair << pair;
			}
		}
		this->scale = 0.1;
		this->measure = { w, h, d };
		this->_size(3.0);
	};
	POLYGON(double w, double h, double d, const char file[]) {
		std::cout << "\n Constructing POLYGON";
		TIME time;
		time._clock(0);
		DATA data;
		data._read(file, ENGINE_MAP_DIRECTORY_POLYGON, 1);
		for (DINT e = 0; e < data.exas.length; e++) {
			this->spot << data.exas[e]._spot();
			this->calc << data.exas[e]._spot();
			this->draw << data.exas[e]._spot();
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
				if(f == -1){
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
		this->scale = 0.1;
		this->measure = { w, h, d };
		this->_size(3.0);
		time._increment(time);
		std::cout << time._since(1) << "ms.";

	}

	POLYGON() {
		this->fov = 75.0;
		this->scale = 0.1;
	};

	CHART<SPOT> spot, calc, draw;
	CHART<PAIR> pair;
	CHART<GROUP> group;
	CHART<TEXTURE> texture;
	SPOT measure, angle, mouse, center;
	double fov, scale;

	void _pos(double x, double y) {
		this->center = { x, y, 0.0 };
	}

	void _track(SPOT m) {
		this->mouse = m;
	}

	void _size(double scale = 0.0) {
		scale = (scale > 0.0) ? (scale) : (this->scale);
		SPOT a;
		for (DINT c = 0; c < this->calc.length; c++) {
			a = this->spot[c];
			a.x *= this->measure.x * scale;
			a.y *= this->measure.y * scale;
			a.z *= this->measure.z * scale;
			this->calc[c] = { a.x, a.y, a.z };
		}
	}

	void _draw(DINT x = 0, DINT y = 0) {
		SPOT spot;
		this->angle.y = 25.0;
		MATH::_change(&this->angle, 1.5, 0.0, 0.0);
		for (DINT s = 0; s < this->spot.length; s++) {
			if (this->spot.exist[s]) {
				spot = this->calc[s];
				MATH::_rotate(&spot, this->angle);
				spot.x += this->mouse.x;// (double)x;
				spot.y += this->mouse.y; // (double)y;
				//spot.x -= this->measure.x * this->scale;
				this->draw[s] = { spot.x, spot.y, spot.z };
				state._set((DINT)spot.x - 1, (DINT)spot.y - 1, BL, 2, 2);
			}
		}
		COLOR color;

		for (DINT p = 0; p < this->pair.length; p++) {
			PAIR pair = this->pair[p];
			SPOT a = this->draw[pair.a], b = this->draw[pair.b];
			if (p % 2 == 0) color = R; else color = GR;
			LINE l = { a, b, 1, color };
			l._draw();
		}
		/*
		CHART<TEXTURE> texture;
		for (DINT g = 0; g < this->group.length; g++) {
			CHART <LINE> outline;
			//std::cout << "\n" << this->group[g].a;
			for (DINT n = 0; n < this->group[g].g.length; n++) {
				//std::cout << " " << this->group[g].g[n];
				LINE line = { this->draw[this->group[g].a], this->draw[this->group[g].g[n]] };
				outline << line;
			}
			TEXTURE t = { outline };
			outline._close();
			texture << t;
			t.base.pixels._close();
		}
		//system("pause");
		for (DINT t = 0; t < texture.length; t++) {
			//texture[t].base._draw(-1, x, y);
			//texture[t].base.pixels._close();
		}
		texture._close();
		*/
		//texture.base._draw();
		
		//system("pause");
	}
};

struct ANIMATION {
	enum DIR {ASC = 1, DESC = -1};
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
		this->direction = ASC;
		this->loop = 0;
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
		this->direction = ASC;
		this->loop = 0;
	}

	ANIMATION() {
		this->stage = 0;
		this->scale = 1;
		this->facing = 0;
		this->direction = ASC;
		this->loop = 0;
	};
	CHART <SPRITE> sprite;
	DIMENSION size;
	DINT stage, scale, facing, loop;
	DIR direction;

	void _draw(DINT scale = -1, SINT stage = -1, SINT x = -1, SINT y = -1, DINT mirror = 0, DINT outline = 0) {
		if (this->sprite.length > 0) {
			x = (x != -1) ? (x) : (this->size.x);
			y = (y != -1) ? (y) : (this->size.y);
			scale = (scale != -1) ? (scale) : (this->scale);
			if (stage == -1) {
				this->sprite[this->stage]._draw(scale, x, y, outline, mirror);
				if (this->sprite.length > 1) {
					if (this->loop >= 15) {
						this->stage += this->direction;
						if (this->stage == this->sprite.length - 1) {
							this->direction = DESC;
						}
						if (this->stage == 0) {
							this->direction = ASC;
						}
						this->loop = 0;
					}
				}
				this->loop++;
			}
			else {
				this->sprite[stage]._draw(scale, x, y, 0, mirror);
			}
		}
	}

	char* _name() {
		return this->sprite[0].name.text;
	}


};

struct ANCHOR {
	ANCHOR(SPOT center) {
		this->center = center;
		this->w = 25;
		this->h = 25;
		this->d = 25;
	};
	ANCHOR() {
		this->w = 0.0;
		this->h = 0.0;
		this->d = 0.0;
	};

	SPOT center, angle;
	double w, h, d;


	void _draw() {
		//this->angle.y = 25.0;
		MATH::_change(&this->angle, 2.0, 1.0, 1.0);
//		this->center._dump();
		SPOT n = { this->center.x, this->center.y, this->center.z };
		MATH::_rotate(&n, this->angle);

		LINE x = { this->center, {n.x + this->w, n.y, n.z}, 1, R };
		LINE y = { this->center, {n.x, n.y + this->h, n.z}, 1, G };
		LINE z = { this->center, {n.x, n.y, n.z + this->d}, 1, BL };
		
		x._draw();
		y._draw();
		z._draw();
		//system("pause");
	}

};


struct IMAGE {
	struct HEADER {
		HEADER(DINT size = 0) {
			if (size > 0) {
				this->size = size;
				this->content = new unsigned char[this->size];
			}
			else {
				this->size = 0;
				this->content = nullptr;
			}
		};
		DINT size;
		unsigned char* content;


		void _close() {
			this->size = 0;
			if (this->content != nullptr) delete[] this->content;
		}

	};

	IMAGE() {};
	DIMENSION size;
	CHART <PIXEL> pixel;
	HEADER h, i;
	void _read(const char* path) {

		std::ifstream f;
		f.open(path, std::ios::in | std::ios::binary);
		if (!f.is_open()) {
			std::cout << "\n>Unable to open " << path;
			return;
		}

		this->h = 14;
		f.read(reinterpret_cast<char*>(this->h.content), this->h.size);

		if (this->h.content[0] != 'B' || this->h.content[1] != 'M') {
			std::cout << "\n>" << path << " is not a bitmap";
			f.close();
			return;
		}

		this->size.d = this->h.content[2] + (this->h.content[3] << 8) * +(this->h.content[4] << 16) + (this->h.content[5] << 24);
		this->i = 40;
		f.read(reinterpret_cast<char*>(this->i.content), this->i.size);

		this->size.w = this->i.content[4] + (this->i.content[5] << 8) + (this->i.content[6] << 16) + (this->i.content[7] << 24);
		this->size.h = this->i.content[8] + (this->i.content[9] << 8) + (this->i.content[10] << 16) + (this->i.content[11] << 24);

		this->pixel = this->size.w * this->size.h;

		const int padding = ((4 - (this->size.w * 3) % 4) % 4);

		COLOR color;
		for (DINT y = this->size.h - 1; y >= 0; y--) {
			for (DINT x = 0; x < this->size.w; x++) {
				unsigned char clr[3];
				f.read(reinterpret_cast<char*>(clr), 3);
				color.r = clr[0];
				color.g = clr[1];
				color.b = clr[2];
				PIXEL p;
				p.color = color;
				p.x = x;
				p.y = y;
				this->pixel << p;

			}
			f.ignore(padding);
		}
		f.close();
		/*
		for (DINT c = 0; c < this->pixel.length; c++) {
			COLOR cl = this->pixel[c].color;
			std::cout << "\n" << cl.r << ", " << cl.g << ", " << cl.b;
		}
		*/


		std::cout << "\n>" << path << " read and closed.";
	}


	void _close() {

		this->pixel._close();
		this->i._close();
		this->h._close();
	}

};
