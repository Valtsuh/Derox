
struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->ref = RGB(this->r, this->g, this->b);
	};
	~COLOR() {};
	DINT r, g, b;
	COLORREF ref;
	void _set(COLOR color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
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
		this->x = 0;
		this->y = 0;
		this->size = 1;
		this->exist = 0;
	};
	~PIXEL() {};
	DINT x, y, size, exist;
	COLOR color;

	void _set(DINT x = 0, DINT y = 0, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->color._set(color);
	}

	void _scale(HDC tool, DINT x, DINT y, DINT size = 2, DINT mode = 0) {
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
};

struct MODEL {
	MODEL() {};
	~MODEL() {};
	DIMENSION position, to, boundary, client;
	PIXEL pixel;
	COLOR color;
	

	void _set(DINT x, DINT y, DINT w, DINT h) {
		DIMENSION dimension;
		dimension.x = x;
		dimension.y = y;
		dimension.w = w;
		dimension.h = h;
		this->position._set(dimension);
		this->to._set(dimension);
		this->boundary._set(dimension);
		//this->client._set(dimension);
	}

};