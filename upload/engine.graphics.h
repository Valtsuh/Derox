struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255, DINT exist = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
	};
	~COLOR() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->ref = 0;
		this->exist = 0;
	};
	DINT r, g, b, exist;
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
	PIXEL(DINT x = 0, DINT y = 0, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->size = 1;
		this->exist = 1;
		this->color = color;
		this->shaded = 0;
		this->lighted = 0;
	};
	~PIXEL() {
		this->x = 0;
		this->y = 0;
		this->size = 0;
		this->exist = 0;
		//this->color.~COLOR();
	};
	DINT x, y, size, exist, shaded, lighted;
	COLOR color;

	void _set(DINT x = 0, DINT y = 0, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->color._set(color);
	}

	void _draw(HDC tool) {
		SetPixel(tool, this->x, this->y, this->color.ref);
	}

	void _scale(HDC tool, SINT x, SINT y, DINT size = 2, DINT mode = 1) {
		if (this->exist == 1) {
			switch (mode) {
				default: {
					for (DINT w = 0; w < size; w++) {
						for (DINT h = 0; h < size; h++) {
							SetPixel(tool, x + w, y + h, this->color.ref);
						}
					}
					break;
				}
				case 1: {
					HBRUSH brush = this->color._brush();
					RECT rect = {};
					rect.left = x;
					rect.right = x + size;
					rect.top = y;
					rect.bottom = y + size;
					FillRect(tool, &rect, brush);
					DeleteObject(brush);
					break;
				}
				case 2: {

					break;
				}
			}
		}
	}
};


struct LINE {
	/*
		
			Study.
	
	*/
	LINE(DINT px = 0, DINT py = 0, double ax = 0.0, double ay = 0.0, double bx = 0.0, double by = 0.0, COLOR color = {}) {
		//std::cout << "\nLine constructor called. (" << ax <<", " << ay << " - " << bx << ", " << by << ")";
		this->scale = 1;
		this->slope = 0.0;
		this->_position(px, py);
		this->_set(ax, ay, bx, by);
		this->color = color;

	};
	LINE(double fx, double fy, double length, double angle, COLOR color = {}, DINT center = 0) {
		this->scale = 1;
		this->slope = 0.0;
		this->color = color;
		this->length = length;
		this->from.x = fx;
		this->from.y = fy;
		switch (center) {
		default:
			this->_angular(angle, length);
			break;
		case 1:
			this->_center(angle, length);
			break;
		}
	}
	LINE(COLOR color, double fx, double fy, double tx, double ty) {
		this->scale = 1;
		this->slope = 0.0;
		this->color = color;
		this->_set(fx, fy, tx, ty);
	}
	~LINE() {
	};
	DINT scale;
	double slope, length;
	COLOR color;
	POSITION position, from, current, to;
	//INDEX <PIXEL> pixels;

	void _position(DINT px, DINT py) {
		this->position.x = (double)px;
		this->position.y = (double)py;
	}

	void _angular(double degree, double length) {
		this->_set(this->from.x, this->from.y, this->from.x + length * MATH::_cos(degree), this->from.y + length * MATH::_sin(degree));
	}

	void _center(double degree, double length) {
		this->_set(this->from.x - length * MATH::_cos(degree), this->from.y - length * MATH::_sin(degree), this->from.x + length * MATH::_cos(degree), this->from.y + length * MATH::_sin(degree));
	}
	void _set(double ax, double ay, double bx, double by) {
		this->current.x = ax;
		this->current.y = ay;
		this->from.x = ax;
		this->from.y = ay;
		this->to.x = bx;
		this->to.y = by;
		this->slope = 0.0;
		if (this->from.x != this->to.x) {
			if (this->from.x < this->to.x) {
				this->slope = (this->to.y - this->from.y) / (this->to.x - this->from.x);
			}
			else {
				this->slope = (this->from.y - this->to.y) / (this->from.x - this->to.x);
			}
		}

	}

	void _draw(HDC tool) {
		PIXEL pixel = {};
		double steps = 0.0;
		pixel.color = this->color;
		if (this->from.x != this->to.x && MATH::_dabs(this->slope) <= 1.0) {
			if (this->from.x > this->to.x) {
				steps = this->to.y - this->slope * this->to.x;
				for (double x = this->to.x; x < this->from.x; x += 1.0) {
					const double y = this->slope * (double)x + steps;
					pixel._scale(tool, (DINT)this->position.x + (DINT)x, (DINT)this->position.y + (DINT)y, this->scale);
				}
			}
			else {
				steps = this->from.y - this->slope * this->from.x;
				for (double x = this->from.x; x < this->to.x; x += 1.0) {
					const double y = this->slope * (double)x + steps;
					pixel._scale(tool, (DINT)this->position.x + (DINT)x, (DINT)this->position.y + (DINT)y, this->scale);

				}
			}
		}
		else {
			if (this->from.y > this->to.y) {
				this->slope = ((double)this->from.x - (double)this->to.x) / ((double)this->from.y - (double)this->to.y);
				steps = this->to.x - this->slope * this->to.y;
				for (double y = this->to.y; y < this->from.y; y += 1.0) {
					const double x = this->slope * (double)y + steps;
					pixel._scale(tool, (DINT)this->position.x + (DINT)x, (DINT)this->position.y + (DINT)y, this->scale);
				}

			}
			else {
				this->slope = ((double)this->to.x - (double)this->from.x) / ((double)this->to.y - (double)this->from.y);
				steps = this->from.x - this->slope * this->from.y;
				for (double y = this->from.y; y < this->to.y; y += 1.0) {
					const double x = this->slope * (double)y + steps;
					pixel._scale(tool, (DINT)this->position.x + (DINT)x, (DINT)this->position.y + (DINT)y, this->scale);
				}

			}
		}
	}

};

struct TRIANGLE {
	TRIANGLE() {
		this->a = {};
		this->b = {};
		this->c = {};
	};
	~TRIANGLE() {};

	LINE a, b, c;
	COLOR color;
	void _set(DIMENSION a, DIMENSION b, DIMENSION c, COLOR color = {}) {
		this->color = color;
		this->a._set(a.x, a.y, b.x, b.y);
		this->b._set(b.x, b.y, c.x, c.y);
		this->c._set(c.x, c.y, a.x, a.y);
	}

	void _draw(HDC tool) {

		this->a._draw(tool);
		this->b._draw(tool);
		this->c._draw(tool);
	}
};

struct RCT {
	RCT(double ax = 0.0, double ay = 0.0, double bx = 0.0, double by = 0.0, COLOR color = R) {
		this->pa = { ax, ay, 0.0 };
		this->pb = { bx, ay, 0.0 };
		this->pc = { bx, by, 0.0 };
		this->pd = { ax, by, 0.0 };
		this->color = color;
		this->_set();
	}

	SPOT pa, pb, pc, pd;
	LINE a, b, c, d;
	COLOR color;
	void _set() {
		this->a = { 0, 0, this->pa.x, this->pa.y, this->pb.x, this->pb.y, this->color };
		this->b = { 0, 0, this->pb.x, this->pb.y, this->pc.x, this->pc.y, this->color };
		this->c = { 0, 0, this->pc.x, this->pc.y, this->pd.x, this->pd.y, this->color };
		this->d = { 0, 0, this->pd.x, this->pd.y, this->pa.x, this->pa.y, this->color };

	}

	void _draw(HDC tool) {
		this->a._draw(tool);
		this->b._draw(tool);
		this->c._draw(tool);
		this->d._draw(tool);
	}
};

struct CRCL {
	CRCL(double x = 0.0, double y = 0.0, double radius = 5, double angle = 180.0, COLOR color = {}) {
		this->center.x = x;
		this->center.y = y;
		this->radius = radius;
		this->angle = angle;
		this->color = color;
		this->angular = {0, 0, x, y, x + radius * MATH::_cos(angle, 0.0001), y + radius * MATH::_sin(angle, 0.0001), DG };
	}

	POSITION center;
	double radius, angle;
	LINE angular;
	COLOR color;

	void _draw(HDC tool, double accuracy = 1.0) {
		PIXEL pixel;
		pixel.color = this->color;
		double x, y, d = this->radius * 2.0;
		LINE line;
		line = this->angular;
		line.scale = 1;
		for (double a = 0.0; a < 360.0; a += accuracy) {
			x = this->center.x + this->radius * MATH::_cos((SINT)a, 0.0025);
			y = this->center.y + this->radius * MATH::_sin((SINT)a, 0.0025);
			pixel._scale(tool, (DINT)x, (DINT)y, 1);
		}
		line._draw(tool);
	}
};

template <class S>
struct SHAPE : S {


};

struct HEADER {
	HEADER() {
		*this->type = {};
	};
	~HEADER() {};

	char type[4];
};

struct IBYTE {
	IBYTE() {
		this->integer = 0;
		this->character = ' ';
	};
	~IBYTE() {};

	DINT integer;
	char character;
};

struct IMAGE {
	IMAGE() {
		this->open = 0;
		this->cursor = 0;
		this->length = 0;
		this->readable = 0;
		this->read = {};
	};
	~IMAGE() {};

	DIMENSION measure;
	DINT length, readable;
	std::ifstream in;
	std::ofstream out;
	IBYTE* read;
	HEADER header;
	STRING file;
	STRING path;
	DINT open;
	DINT cursor;
	DINT _read(const char name[], SINT length = 16) {
		this->file._write(name);
		wchar_t cwd[128];
		GetCurrentDirectory(128, cwd);
		this->path._wwrite(cwd);
		std::cout << "\nCurrent directory: " << this->path.text;
		this->in.open(name, std::ios::in | std::ios::binary);
		this->open = this->in.is_open();
		if (this->open) {
			this->out.open("image.txt");
			if (this->out.is_open()) {
				if (length > 0) {
					this->length = length;
				}
				else {
					this->in.seekg(0, this->in.end);
					this->length = (DINT)this->in.tellg();
					this->in.seekg(0, this->in.beg);
				}

				std::cout << "\nWriting image length of " << this->length;
				IBYTE* data = new IBYTE[this->length];
				unsigned char read;
				DINT i = 0;
				while (this->in >> read && i < this->length) {
					//if ((DINT)read < 256) {
						data[i].character = read;
						data[i].integer = (DINT)read;
						i++;
					//}
				}
				this->readable = i;
				this->read = data;
				std::cout << "\nReading image, readable length of " << this->readable;
				for (DINT r = 0; r < this->readable; r++) {
					this->out << this->read[r].character << " ";
				}
				this->in.close();
				this->out.close();
				return 1;
			}
			else {
				this->in.close();
				std::cout << "\nUnable to read";
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	void _close() {
		if (this->file.length > 0) {
			std::cout << "\nClosing image.";
			delete[] this->read;
			// delete this;
		}
	}
	
};

struct GROUND {
	GROUND() {
		this->occupied = 0;
		this->identifier = 0;
	};
	~GROUND() {};

	CHART <PIXEL> pixels;
	DIMENSION size;
	DINT occupied, identifier;
	COLOR color;

	void _set(DINT type, SINT position) {
		if (this->pixels.length == 0) {
			this->size.w = 8;
			this->size.h = 8;
			for (DINT x = 0; x < 8; x++) {
				for (DINT y = 0; y < 8; y++) {
					PIXEL p = { x, y, this->color};
					this->pixels << p;
				}
			}
		}
		
		for (DINT pixel = 0; pixel < this->pixels.length; pixel++) {
			PIXEL *p = &this->pixels[pixel];
			switch (position) {
			default:
				break;
			case 0:
				if (p->x == 0 || p->x == 7 || p->y == 0 || p->y == 7) {
					p->shaded = 1;
					//p->lighted = 1;
				}
				else {
					////p->color = this->b;
				}
				break;
			case 1:
				if (p->x == 0 || p->y == 7) {
					p->shaded = 1;
				}
				else {
					////p->color = this->b;
				}
				break;
			case 11:
				if (p->x == 0 || p->y == 7 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 2:
				if (p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 12:
				if (p->x == 0 || p->x == 7 || p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 21:
				if (p->y == 7 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 22:
				if (p->y == 7 || p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 23:
				if (p->y == 7 || p->x == 7 && p->y == 0 || p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 3:
				if (p->x == 7 || p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 31:
				if (p->x == 7 || p->y == 7 || p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 4:
				if (p->x == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 14:
				if (p->y == 0 || p->y == 7 || p->x == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 41:
				if (p->x == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 42:
				if (p->x == 0 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 43:
				if (p->x == 0 || p->x == 7 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 5:
				break;
			case 501:
				if (p->x == 0 && p->y == 0 || p->x == 0 && p->y == 7 || p->x == 7 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 502:
				if (p->x == 0 && p->y == 0 || p->x == 0 && p->y == 7 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 503:
				if (p->x == 0 && p->y == 0 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 504:
				if (p->x == 0 && p->y == 0 || p->x == 7 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 505:
				if (p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 506:
				if (p->x == 0 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 507:
				if (p->x == 0 && p->y == 0 || p->x == 0 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 508:
				if (p->x == 0 && p->y == 0 || p->x == 0 && p->y == 7 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 509:
				if (p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 510:
				if (p->x == 0 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 511:
				if (p->x == 0 && p->y == 7 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 512:
				if (p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 513:
				if (p->x == 7 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 514:
				if (p->x == 0 && p->y == 7 || p->x == 7 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 515:
				if (p->x == 0 && p->y == 7 || p->x == 7 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 6:
				if (p->x == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 16:
				if (p->y == 0 || p->y == 7 || p->x == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 61:
				if (p->x == 7 || p->x == 0 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 62:
				if (p->x == 7 || p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 63:
				if (p->x == 7 || p->x == 0 && p->y == 7 || p->x == 0 && p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 7:
				if (p->x == 0 || p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 71:
				if (p->x == 0 || p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 8:
				if (p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 18:
				if (p->x == 0 || p->x == 7 || p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 81:
				if (p->y == 0 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 82:
				if (p->y == 0 || p->x == 0 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 83:
				if (p->y == 0 || p->x == 0 && p->y == 7 || p->x == 7 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 9:
				if (p->x == 7 || p->y == 0) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 91:
				if (p->x == 7 || p->y == 0 || p->x == 0 && p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 99:
				if (p->x == 0 && p->y == 0 || p->x == 7 && p->y == 7) {
					p->color = R;
				}

				break;
			case 101:
				if (p->x == 0 || p->x == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			case 102:
				if (p->y == 0 || p->y == 7) {
					p->shaded = 1;
				}
				else {
					//p->color = this->b;
				}
				break;
			}
		}
	}
	void _draw(HDC tool, DINT x, DINT y, DINT scale = 2) {
		DINT px, py;
		PIXEL pix;
		//std::cout << "\nDraw: " << this->pixels[0].color.r << ", " << this->pixels[0].color.g << ", " << this->pixels[0].color.b;
		for (DINT p = 0; p < this->pixels.size; p++) {
			if (this->pixels.exist[p]) {
				pix = this->pixels[p];
				if (pix.color.exist) {
					px = x + pix.x * scale;
					py = y + pix.y * scale;
					if (this->occupied) {
						//pix.color = PNK;
						pix.lighted = 1;
					}
					if (pix.shaded) {
						double s = 0.5;
						pix.color._set({ (DINT)(pix.color.r * s), (DINT)(pix.color.g * s), (DINT)(pix.color.b * s) });
					}
					if (pix.lighted) {
						DINT l = 45;
						DINT r = pix.color.r + l;
						DINT g = pix.color.g + l;
						DINT b = pix.color.b + l;
						pix.color._set({r, g, b});
					}
					pix._scale(tool, px, py, scale);
				}
			}
		}
		//system("pause");
	}

	void _color(COLOR c) {
		this->color = c;
		for (DINT p = 0; p < this->pixels.length; p++) {
			if (this->pixels.exist[p]) {
				this->pixels[p].color = c;
			}
		}
	}
};

struct LITERAL {
	LITERAL(std::initializer_list<COLOR> colors, DINT width = 3, DINT height = 5) {
		DINT mode = 1;
		HOLDER<COLOR> holder = colors;
		PIXEL pixel;
		DINT p = 0;
		for (DINT x = 0; x < width; x++) {
			for (DINT y = 0; y < height; y++) {
				pixel = { x, y, holder[p] };
				//std::cout << "\n> " << pixel.x << ", " << pixel.y << " (" << pixel.color.r << ", " << pixel.color.g << ", " << pixel.color.b << ")";
				this->pixels << pixel;
				p++;
			}
		}		

		this->size.w = width;
		this->size.h = height;
	};
	LITERAL() {};
	~LITERAL() {};

	CHART <PIXEL> pixels;
	DIMENSION size;

	PIXEL _get(DINT x, DINT y) {
		for (DINT i = 0; i < this->pixels.size; i++) {
			if (this->pixels[i].x == x && this->pixels[i].y == y) return this->pixels[i];
		}
		PIXEL p = {};
		return p;
	}
};

struct SPRT {
	SPRT(std::initializer_list<COLOR> colors) {
		//std::cout << "Constructing sprite.";
		HOLDER<COLOR> clrs = colors;
		DINT size = 8;
		this->size.w = size;
		this->size.h = size;
		DINT c = 0;
		this->pixels = this->size.w * this->size.h;
		for (DINT y = 0; y < size; y++) {
			for (DINT x = 0; x < size; x++) {
				PIXEL pixel = { x, y, clrs[c] };
				this->pixels << pixel;
				c++;
			}
		}

	};



	SPRT() {};

	~SPRT(){};
	/*
	SPRT(std::initializer_list<COLOR> colors = {}, DINT width = 0, DINT height = 0) {
		COLORS clrs = colors;
		DINT c = 0;
		this->size.w = width;
		this->size.h = height;
		for (DINT x = 0; x < width; x++) {
			for (DINT y = 0; y < height; y++) {
				this->pixels._add({ x, y, clrs[c] });
				c++;
			}
		}
	}
	*/
	CHART <PIXEL> pixels;
	DIMENSION size;

	void _draw(HDC tool, DINT x, DINT y, DINT scale = 2) {
		DINT px, py;
		for (DINT p = 0; p < this->pixels.size; p++) {
			if (this->pixels.exist[p]) {
				if(this->pixels.item[p].color.exist) {
					px = x + this->pixels.item[p].x * scale;
					py = y + this->pixels.item[p].y * scale;
					this->pixels.item[p]._scale(tool, px, py, scale);
				}
			}
		}
	}
};

struct ANM {
	ANM(std::initializer_list<SPRT> sprites) {
		HOLDER<SPRT> sprts = sprites;
		for (this->length = 0; this->length < sprts._size(); this->length++) {
			this->sprites << sprts[this->length];
		}
		this->stage = 0;
	};
	ANM() {
		this->length = 0;
		this->stage = 0;
	};
	~ANM() {};
	CHART<SPRT> sprites;
	DINT length, stage;
};

struct MDL {
	MDL() {
		this->scale = 2;
		this->facing = 0;
		this->collision = 0;
		this->type = 0;
	};
	~MDL() {};

	ANM animation;
	DIMENSION position, to;
	DINT scale, facing, collision, type;


	void _set(DINT x, DINT y, DINT scale, DINT w, DINT h) {
		DIMENSION set;
		set.x = x;
		set.y = y;
		set.w = w;
		set.h = h;
		set.size = scale;
		this->position._set(set);
		this->to._set(set);
	}

	void _draw(HDC tool) {
		SPRT sprite = this->animation.sprites[this->animation.stage];
		DINT px, py;
		COLOR collision;
		PIXEL pixel;
		switch (this->collision) {
		default:
			break;
		case 0:
			collision = ENGINE_COLOR_FACING;
			break;
		case 1:
			switch (this->type) {
			default:
				break;
			case ENGINE_TYPE_CREATURE:
				collision = R;
				break;
			case ENGINE_TYPE_RESOURCE:
				collision = G;
				break;
			}
			break;
		}
		for (DINT p = 0; p < sprite.pixels.size; p++) {
			if (sprite.pixels.exist[p]) {
				if (sprite.pixels[p].x < this->position.w && sprite.pixels[p].y < this->position.h) {
					pixel = sprite.pixels[p];
					switch (this->facing) {
					default:
						break;
					case 2:
						if (pixel.y == this->position.h - 1) pixel.color._set(collision);
						break;
					case 4:
						if (pixel.y == 0) pixel.color._set(collision);
						break;
					case 6:
						if (pixel.x == this->position.w - 1) pixel.color._set(collision);
						break;
					case 8:
						if (pixel.y == 0) pixel.color._set(collision);
						break;
					}
					if (pixel.color.exist) {
						px = this->position.x + sprite.pixels[p].x * this->position.size;
						py = this->position.y + sprite.pixels[p].y * this->position.size;
						pixel._scale(tool, px, py, this->position.size);
					}
				}
			}
		};
		//this->animation.sprites[this->animation.stage]._draw(tool, this->position.x, this->position.y, this->position.size);
		this->animation.stage++;
		if (this->animation.stage == this->animation.length) this->animation.stage = 0;
	}

};

struct DISPLAY {
	DISPLAY(DINT width = 0, DINT height = 0) {
		std::cout << "\nDisplay constructor.";
		COLOR color = LGR;
		DINT p = 0;
		TIME time;
		time._clock();
		this->pixels = width * height + 1;
		for (DINT x = 0; x < width; x++) {
			for (DINT y = 0; y < height; y++) {
				//std::cout << "\nAdding pixel " << p;
				PIXEL pixel = { x, y, color };
				this->pixels << pixel;
				p++;
				
			}
		}
		std::cout << "\nDisplay constructed. " << time._difference(time);
	}
	DISPLAY() {};
	~DISPLAY() {};

	CHART<PIXEL> pixels;

};

struct BOX {
	BOX(double x, double y, double size, SPOT angle, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->size = size;
		this->angle = angle;
		this->outline = color;
		this->_construct();
	};
	BOX() {};
	~BOX() {};

	double x, y, size;
	SPOT angle;
	COLOR outline;
	CHART <SPOT> point;

	void _outline(SPOT spot) {
		this->point << spot;
	}

	void _construct() {
		this->point._close();
		this->_outline({ 0.0, 0.0, 0.0 });
		this->_outline({ this->size, 0.0, 0.0 });
		this->_outline({ this->size, this->size, 0.0 });
		this->_outline({ 0.0, this->size, 0.0 });

		this->_outline({ 0.0, 0.0, this->size });
		this->_outline({ this->size, 0.0, this->size });
		this->_outline({ this->size, this->size, this->size });
		this->_outline({ 0.0, this->size, this->size });
	}

	LINE _line(DINT pa, DINT pb) {
		LINE line = {};
		if (pa >= this->point.length || pb >= this->point.length) return line;
		SPOT a = this->point[pa], b = this->point[pb];
		line = { this->outline, this->x + a.x + a.z * MATH::_sin(this->angle.x), this->y + a.y + a.z * MATH::_cos(this->angle.y), this->x + b.x + b.z * MATH::_sin(this->angle.x), this->y + b.y + b.z * MATH::_sin(this->angle.y)};
		return line;
	}

	void _draw(HDC tool) {
		LINE line;
		CHART <LINE> out;
		line = this->_line(0, 1);
		out << line;
		line = this->_line(1, 2);
		out << line;
		line = this->_line(2, 3);
		out << line;
		line = this->_line(3, 0);
		out << line;
		line = this->_line(4, 0);
		out << line;
		line = this->_line(5, 1);
		out << line;
		line = this->_line(6, 2);
		out << line;
		line = this->_line(7, 3);
		out << line;
		line = this->_line(4, 5);
		out << line;
		line = this->_line(5, 6);
		out << line;
		line = this->_line(6, 7);
		out << line;
		line = this->_line(7, 4);
		out << line;
		for (DINT l = 0; l < out.length; l++) {
			out[l]._draw(tool);
		}
	}
};