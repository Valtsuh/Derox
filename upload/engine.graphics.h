#include <iostream>
#include <fstream>

struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255, DINT exist = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
	};
	~COLOR() {};
	DINT r, g, b, exist;
	COLORREF ref;
	void _set(COLOR color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->exist = color.exist;
		this->_ref();
	}

	COLORREF _ref() {
		this->ref = RGB(this->r, this->g, this->b);
		return this->ref;
	}

	HBRUSH _brush() {
		return CreateSolidBrush(this->_ref());
	}
};

struct PIXEL {
	PIXEL() {
		this->x = -1;
		this->y = -1;
		this->size = 1;
		this->exist = 1;
	};
	~PIXEL() {};
	DINT x, y, size, exist;
	COLOR color;
	RANDOM dice;

	void _set(DINT x = 0, DINT y = 0, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->color._set(color);
	}

	void _scale(HDC tool, DINT x, DINT y, DINT size = 2, DINT mode = 0) {
		if (this->exist == 1) {
			switch (mode) {
			default:
				for (DINT w = 0; w < size; w++) {
					for (DINT h = 0; h < size; h++) {
						SetPixel(tool, x + w, y + h, this->color.ref);
					}
				}
				break;
			case 0:
				HBRUSH brush = this->color._brush();
				RECT rect;
				rect.left = x;
				rect.right = x + size;
				rect.top = y;
				rect.bottom = y + size;
				FillRect(tool, &rect, brush);
				DeleteObject(brush);
				break;
			}
		}
	}

	void _rect(HDC tool, DINT x, DINT y, DINT width = 2, DINT heigth = 2, DINT mode = 1) {
		switch (mode) {
		default:
			for (DINT w = 0; w < width; w++) {
				for (DINT h = 0; h < heigth; h++) {
					SetPixel(tool, x + w, y + h, this->color.ref);
				}
			}
			break;
		case 0:
			HBRUSH brush = this->color._brush();
			RECT rect;
			rect.left = x;
			rect.right = x + width;
			rect.top = y;
			rect.bottom = y + heigth;
			FillRect(tool, &rect, brush);
			DeleteObject(brush);
			break;
		}
	}

	void _worm(HDC tool, DINT x, DINT y, DINT width = 1, DINT heigth = 4, DINT inverted = 0) {
		DINT px, py;
		for (DINT w = 0; w < width; w++) {
			for (DINT h = 0; h < heigth; h++) {
				switch (this->dice._roll(1, 2)) {
				default:
					break;
				case 1:
					switch (inverted) {
					default:
						break;
					case 0:
						y += 1;
						break;
					case 1:
						x += 1;
						break;
					}
					break;
				case 2:
					switch (inverted) {
					default:
						break;
					case 0:
						y -= 1;
						break;
					case 1:
						x -= 1;
						break;
					}
					break;
				}

				px = x + w;
				py = y + h;
				SetPixel(tool, px, py, this->color.ref);
			}
		}
	}
};


struct LINE {
	LINE() {
		this->scale = 2;
	};
	~LINE() {};
	DINT scale, length;
	DIMENSION from, current, to, size;
	LIST <PIXEL> pixels;
	void _set(DINT ax, DINT ay, DINT bx, DINT by) {
		this->current.x = ax;
		this->current.y = ay;
		this->from.x = ax;
		this->from.y = ay;
		this->to.x = bx;
		this->to.y = by;
		if (this->to.x >= this->from.x) {
			this->size.w = this->to.x - this->from.x;
		}
		else {
			this->size.w = this->from.x - this->to.x;
		}
		if (this->to.y >= this->from.y) {
			this->size.h = this->to.y - this->from.y;
		}
		else {
			this->size.h = this->from.y - this->to.y;
		}
	}

	void _draw(HDC tool) {
		for (DINT p = 0; p < this->length; p++) {
			//this->pixel[p]._scale(tool, this->pixel[p].x, this->pixel[p].y, 1);
		}
	}

};

struct IMAGE {
	IMAGE() {
		for (DINT r = 0; r < 16; r++) this->read[r] = 0;
	};
	~IMAGE() {};

	DIMENSION measure;
	std::ifstream strm;
	int read[16];
	STRING file;
	DINT open;

	DINT _read(const char name[]) {
		file._write(name);
		strm.open(name);
		this->open = strm.is_open();


		DINT r = 0;
		return r;
	}
};



struct LITERAL {
	LITERAL(DINT width = 3, DINT height = 5, COLOR a = { 255, 0, 0 }, COLOR b = {}, COLOR c = {}, COLOR d = {}, COLOR e = {}, COLOR f = {}, COLOR g = {}, COLOR h = {}, COLOR i = {}, COLOR j = {}, COLOR k = {}, COLOR l = {}, COLOR m = {}, COLOR n = {}, COLOR o = { 0, 0, 255 }, COLOR p = {}, COLOR q = {}, COLOR r = {}, COLOR s = {}, COLOR t = {}, COLOR u = {}, COLOR v = {}, COLOR w = {}, COLOR x = {}, COLOR y = {0, 0, 255}) {
		DINT mode = 1;
		switch (mode) {
		default: {

			this->pixel[0]._set(0, 0, a);
			this->pixel[1]._set(1, 0, b);
			this->pixel[2]._set(2, 0, c);
			this->pixel[3]._set(3, 0, d);
			this->pixel[4]._set(4, 0, e);
			this->pixel[5]._set(0, 1, f);
			this->pixel[6]._set(1, 1, g);
			this->pixel[7]._set(2, 1, h);
			this->pixel[8]._set(3, 1, i);
			this->pixel[9]._set(4, 1, j);
			this->pixel[10]._set(0, 2, k);
			this->pixel[11]._set(1, 2, l);
			this->pixel[12]._set(2, 2, m);
			this->pixel[13]._set(3, 2, n);
			this->pixel[14]._set(4, 2, o);
			break;
		}
		case 1: {
			this->pixel[0]._set(0, 0, a);
			this->pixel[1]._set(0, 1, b);
			this->pixel[2]._set(0, 2, c);
			this->pixel[3]._set(0, 3, d);
			this->pixel[4]._set(0, 4, e);
			this->pixel[5]._set(1, 0, f);
			this->pixel[6]._set(1, 1, g);
			this->pixel[7]._set(1, 2, h);
			this->pixel[8]._set(1, 3, i);
			this->pixel[9]._set(1, 4, j);
			this->pixel[10]._set(2, 0, k);
			this->pixel[11]._set(2, 1, l);
			this->pixel[12]._set(2, 2, m);
			this->pixel[13]._set(2, 3, n);
			this->pixel[14]._set(2, 4, o);
			this->pixel[15]._set(3, 0, p);
			this->pixel[16]._set(3, 1, q);
			this->pixel[17]._set(3, 2, r);
			this->pixel[18]._set(3, 3, s);
			this->pixel[19]._set(3, 4, t);
			this->pixel[20]._set(4, 0, u);
			this->pixel[21]._set(4, 1, v);
			this->pixel[22]._set(4, 2, w);
			this->pixel[23]._set(4, 3, x);
			this->pixel[24]._set(4, 4, y);
			break;
		}
		case 2: {
			this->pixel[0]._set(0, 0, a);
			this->pixel[1]._set(1, 0, b);
			this->pixel[2]._set(2, 0, c);
			this->pixel[3]._set(3, 0, d);
			this->pixel[4]._set(4, 0, e);
			this->pixel[5]._set(0, 1, f);
			this->pixel[6]._set(1, 1, g);
			this->pixel[7]._set(2, 1, h);
			this->pixel[8]._set(3, 1, i);
			this->pixel[9]._set(4, 1, j);
			this->pixel[10]._set(0, 2, k);
			this->pixel[11]._set(1, 2, l);
			this->pixel[12]._set(2, 2, m);
			this->pixel[13]._set(3, 2, n);
			this->pixel[14]._set(4, 2, o);
			this->pixel[15]._set(0, 3, p);
			this->pixel[16]._set(1, 3, q);
			this->pixel[17]._set(2, 3, r);
			this->pixel[18]._set(3, 3, s);
			this->pixel[19]._set(4, 3, t);
			this->pixel[20]._set(0, 4, u);
			this->pixel[21]._set(1, 4, v);
			this->pixel[22]._set(2, 4, w);
			this->pixel[23]._set(3, 4, x);
			this->pixel[24]._set(4, 4, y);
			break;
		}
		case 3: {
			this->pixel[0]._set(0, 0, a);
			this->pixel[1]._set(0, 1, b);
			this->pixel[2]._set(0, 0, c);
			this->pixel[3]._set(0, 0, d);
			this->pixel[4]._set(0, 0, e);
			this->pixel[5]._set(1, 0, f);
			this->pixel[6]._set(0, 0, g);
			this->pixel[7]._set(0, 0, h);
			this->pixel[8]._set(0, 0, i);
			this->pixel[9]._set(1, 1, j);
			this->pixel[10]._set(0, 0, k);
			this->pixel[11]._set(0, 0, l);
			this->pixel[12]._set(0, 0, m);
			this->pixel[13]._set(0, 0, n);
			this->pixel[14]._set(0, 0, o);
			this->pixel[15]._set(0, 0, p);
			this->pixel[16]._set(0, 0, q);
			this->pixel[17]._set(0, 0, r);
			this->pixel[18]._set(0, 0, s);
			this->pixel[19]._set(0, 0, t);
			this->pixel[20]._set(0, 4, u);
			this->pixel[21]._set(0, 0, v);
			this->pixel[22]._set(0, 0, w);
			this->pixel[23]._set(0, 0, x);
			this->pixel[24]._set(4, 4, y);
		}
		}
		this->size.w = width;
		this->size.h = height;
	};
	~LITERAL() {};

	PIXEL pixel[25];
	DIMENSION size;

	PIXEL _get(DINT x = 0, DINT y = 0) {
		for (DINT s = 0; s < 25; s++) {
			if (this->pixel[s].x == x) {
				if (this->pixel[s].y == y) return this->pixel[s];
			}
		}
		PIXEL p = {};
		return p;
	}
};


struct SPRITE {
	/*
	template <typename... colors>
	SPRITE(colors... color) {
		DINT p = 0;
		COLOR clr;
		for (DINT h = 0; h < 5; h++) {
			for (DINT w = 0; w < 5; w++) {
				clr = color...[0];
				this->position[p]._set(w, h, clr);
				p++;
			}
		}

	};
	*/
	
	SPRITE(
		COLOR a = {255, 0, 0}, 
		COLOR b = {0, 0, 0, 0}, 
		COLOR c = {}, 
		COLOR d = {}, 
		COLOR e = {}, 

		COLOR f = {}, 
		COLOR g = {}, 
		COLOR h = {}, 
		COLOR i = {}, 
		COLOR j = {}, 
		
		COLOR k = {}, 
		COLOR l = {}, 
		COLOR m = {}, 
		COLOR n = {}, 
		COLOR o = {}, 

		COLOR p = {0, 0, 255}, 
		COLOR q = {}, 
		COLOR r = {}, 
		COLOR s = {}, 
		COLOR t = {}, 

		COLOR u = {}, 
		COLOR v = {},
		COLOR w = {},
		COLOR x = {},
		COLOR y = {0, 0, 255},
		
		COLOR z = {},
		COLOR aa = {},
		COLOR ab = {},
		COLOR ac = {},
		COLOR ad = {},
		
		COLOR ae = {},
		COLOR af = {},
		COLOR ag = {},
		COLOR ah = {},
		COLOR ai = {},
		
		COLOR aj = { 0, 0, 255 }, // 36
		COLOR ak = {},
		COLOR al = {},
		COLOR am = {},
		COLOR an = {},

		COLOR ao = {},
		COLOR ap = {},
		COLOR aq = {},
		COLOR ar = {},
		COLOR as = {},
		
		COLOR at = {},		
		COLOR au = {},
		COLOR av = {},
		COLOR aw = {},
		COLOR ax = {},

		COLOR ay = {},
		COLOR az = {},
		COLOR ba = {},
		COLOR bb = {},
		COLOR bc = {},
		
		COLOR bd = {},
		COLOR be = {},
		COLOR bf = {},
		COLOR bg = {},
		COLOR bh = {},
		
		COLOR bi = {},
		COLOR bj = {},
		COLOR bk = {},
		COLOR bl = { 0, 0, 255 },

		DINT sx = 0,
		DINT sy = 0
	) {
		this->position.x = sx;
		this->position.y = sy;
		this->pixel[0]._set(0, 0, a);
		this->pixel[1]._set(1, 0, b);
		this->pixel[2]._set(2, 0, c);
		this->pixel[3]._set(3, 0, d);
		this->pixel[4]._set(4, 0, e);
		this->pixel[5]._set(5, 0, f);
		this->pixel[6]._set(6, 0, g);
		this->pixel[7]._set(7, 0, h);

		this->pixel[8]._set(0, 1, i);
		this->pixel[9]._set(1, 1, j);
		this->pixel[10]._set(2, 1, k);
		this->pixel[11]._set(3, 1, l);
		this->pixel[12]._set(4, 1, m);
		this->pixel[13]._set(5, 1, n);
		this->pixel[14]._set(6, 1, o);
		this->pixel[15]._set(7, 1, p);

		this->pixel[16]._set(0, 2, q);
		this->pixel[17]._set(1, 2, r);
		this->pixel[18]._set(2, 2, s);
		this->pixel[19]._set(3, 2, t);
		this->pixel[20]._set(4, 2, u);
		this->pixel[21]._set(5, 2, v);
		this->pixel[22]._set(6, 2, w);
		this->pixel[23]._set(7, 2, x);

		this->pixel[24]._set(0, 3, y);
		this->pixel[25]._set(1, 3, z);
		this->pixel[26]._set(2, 3, aa);
		this->pixel[27]._set(3, 3, ab);
		this->pixel[28]._set(4, 3, ac);
		this->pixel[29]._set(5, 3, ad);
		this->pixel[30]._set(6,	3, ae);
		this->pixel[31]._set(7, 3, af);

		this->pixel[32]._set(0, 4, ag);
		this->pixel[33]._set(1, 4, ah);
		this->pixel[34]._set(2, 4, ai);
		this->pixel[35]._set(3, 4, aj);
		this->pixel[36]._set(4, 4, ak);
		this->pixel[37]._set(5, 4, al);
		this->pixel[38]._set(6, 4, am);
		this->pixel[39]._set(7, 4, an);

		this->pixel[40]._set(0, 5, ao);
		this->pixel[41]._set(1, 5, ap);
		this->pixel[42]._set(2, 5, aq);
		this->pixel[43]._set(3, 5, ar);
		this->pixel[44]._set(4, 5, as);
		this->pixel[45]._set(5, 5, at);
		this->pixel[46]._set(6, 5, au);
		this->pixel[47]._set(7, 5, av);

		this->pixel[48]._set(0, 6, aw);
		this->pixel[49]._set(1, 6, ax);
		this->pixel[50]._set(2, 6, ay);
		this->pixel[51]._set(3, 6, az);
		this->pixel[52]._set(4, 6, ba);
		this->pixel[53]._set(5, 6, bb);
		this->pixel[54]._set(6, 6, bc);
		this->pixel[55]._set(7, 6, bd);

		this->pixel[56]._set(0, 7, be);
		this->pixel[57]._set(1, 7, bf);
		this->pixel[58]._set(2, 7, bg);
		this->pixel[59]._set(3, 7, bh);
		this->pixel[60]._set(4, 7, bi);
		this->pixel[61]._set(5, 7, bj);
		this->pixel[62]._set(6, 7, bk);
		this->pixel[63]._set(7, 7, bl);
	};
	
	~SPRITE() {};


	PIXEL pixel[64];
	DIMENSION position;


	PIXEL _get(DINT x = 0, DINT y = 0) {
		for (DINT p = 0; p < 64; p++) {
			if (this->pixel[p].x == x && this->pixel[p].y == y) return this->pixel[p];
		}

		PIXEL pixel = {};
		return pixel;
	}

	void _position(DINT x, DINT y){
		this->position.x = x;
		this->position.y = y;
	}

};

struct ANIMATION {
	ANIMATION(DINT total = 0, SPRITE one = {}, SPRITE two = {}, SPRITE three = {}, SPRITE four = {}) {
		this->current = 0;
		this->total = total;
		this->stage[0] = one;
		this->stage[1] = two;
		this->stage[2] = three;
		this->stage[3] = four;
	};
	~ANIMATION() {};

	SPRITE stage[4];
	DINT current, total;
};

struct MODEL {
	MODEL() {
		this->style = 0;
		this->facing = 0;
		this->collision = 0;
	};
	~MODEL() {};
	DIMENSION position, to, boundary, client, previous, original;
	DINT style, facing, collision;
	SPRITE sprite;
	ANIMATION animation;

	void _set(DINT x, DINT y, DINT w, DINT h, DINT size) {
		DIMENSION dimension;
		dimension.x = x;
		dimension.y = y;
		dimension.w = w;
		dimension.h = h;
		dimension.size = size;
		this->position._set(dimension);
		this->to._set(dimension);
		this->boundary._set(dimension);
		this->original._set(dimension);
		this->previous._set(dimension);
		//this->client._set(dimension);
		this->facing = 0;
	}

	void _animate(HDC tool) {
		DINT px = 0, py = 0;
		PIXEL pixel = {};
		SPRITE sprite = this->animation.stage[this->animation.current];
		COLOR collision = {};
		switch (this->collision) {
		default:
			break;
		case 0:
			collision = ENGINE_COLOR_FACING;
			break;
		case 1:
			collision = R;
			break;
		}
		for (DINT w = 0; w < this->position.w; w++) {
			for (DINT h = 0; h < this->position.h; h++) {
				pixel = sprite._get(w, h);
				switch (this->facing) {
				default:
					break;
				case 2:
					if (h == this->position.h - 1) pixel.color._set(collision);
					break;
				case 4:
					if (w == 0) pixel.color._set(collision);
					break;
				case 6:
					if (w == this->position.w - 1) pixel.color._set(collision);
					break;
				case 8:
					if (h == 0) pixel.color._set(collision);
					break;
				}

				if (pixel.color.exist == 1) {
					px = this->position.x + (this->position.size * w);
					py = this->position.y + (this->position.size * h);
					pixel._scale(tool, px, py, this->position.size);
				}
			}
		}

	}

	void _draw(HDC tool) {
		DINT px = 0, py = 0;
		PIXEL pixel = {};
		COLOR color = {};
		for (DINT w = 0; w < this->position.w; w++) {
			for (DINT h = 0; h < this->position.h; h++) {
				pixel = this->sprite._get(w, h);
				switch (this->facing) {
				default:
					break;
				case 2:
					if (h == this->position.h - 1) pixel.color._set(ENGINE_COLOR_FACING);
					break;
				case 4:
					if (w == 0) pixel.color._set(ENGINE_COLOR_FACING);
					break;
				case 6:
					if (w == this->position.w - 1) pixel.color._set(ENGINE_COLOR_FACING);
					break;
				case 8:
					if (h == 0) pixel.color._set(ENGINE_COLOR_FACING);
					break;
				}
				if (pixel.color.exist == 1) {
					px = this->position.x + (this->position.size * w);
					py = this->position.y + (this->position.size * h);
					pixel._scale(tool, px, py, this->position.size);
				}
			}
		}

	}
};
