
struct COLOR {
	COLOR(DINT r = 0, DINT g = 0, DINT b = 0, DINT a = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->ref = RGB(this->r, this->g, this->b);
	};
	~COLOR() {};
	DINT r, g, b, a;
	COLORREF ref;

	void _set(COLOR color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->ref = RGB(this->r, this->g, this->b);
	}

	COLOR _get() {
		return *this;
	}
};
struct PIXEL {
	PIXEL(DINT x = 0, DINT y = 0, DINT exist = 0, COLOR color = {}) {
		this->x = x;
		this->y = y;
		this->unique = 0;
		this->color._set(color);
		this->exist = exist;
		this->active = 0;
	};
	~PIXEL() {};
	SINT x, y, unique, exist, active;
	COLOR color, temp;


	void _set(SINT x, SINT y, COLOR color) {
		if (x >= 0) this->x = x; else this->x = 0;
		if (y >= 0) this->y = y; else this->y = 0;
		this->unique = x + 1 + y + 1;
		this->color._set(color);
		this->exist = 1;
	}


	void _draw(HDC tool, DINT x, DINT y) {
		if (x >= 0 && y >= 0) {
			SetPixel(tool, this->x + x, this->y + y, this->color.ref);
		}
	}
	PIXEL _get() {
		return *this;
	}

};


struct CANVAS {
	CANVAS() {
		this->info = {};
		this->measure = {};
		this->tool = 0;
		this->mem = 0;
		this->bm = {};
		this->client = {};
		this->clnt = {};
		this->drawn = 0;
		this->current = 0;
	};
	~CANVAS() {};
	PAINTSTRUCT info;
	RECT measure, client, clnt;
	HDC tool, mem, current;
	HBITMAP bm;
	DINT drawn;

	void _begin(HWND window) {
		GetClientRect(window, &this->client);
		this->mem = BeginPaint(window, &this->info);

	}

	void _end(HWND window) {
		ReleaseDC(window, this->mem);
		DeleteDC(this->mem);
		EndPaint(window, &this->info);
	}

	void _mbegin(HWND window) {
		// Invalid handle (errore code 6)
		GetClientRect(window, &this->client);
		this->clnt.right = this->client.right - this->client.left;
		this->clnt.bottom = this->client.bottom - this->client.top;
		this->tool = BeginPaint(window, &this->info);
		this->mem = CreateCompatibleDC(this->mem);

		this->bm = CreateCompatibleBitmap(this->tool, this->clnt.right, this->clnt.bottom);
		SelectObject(this->mem, this->bm);
	}

	void _mend(HWND window) {
		// Invalid handle (errore code 6)
		BitBlt(this->tool, 0, 0, this->clnt.right, this->clnt.bottom, this->mem, 0, 0, SRCCOPY);
		ReleaseDC(window, this->tool);
		ReleaseDC(window, this->mem);
		ReleaseDC(window, this->current);
		DeleteDC(this->tool);
		DeleteDC(this->mem);
		DeleteDC(this->current);
		DeleteObject(this->bm);
		EndPaint(window, &this->info);
	}

	void _tool(HDC tool) {
		this->tool = tool;
	}
	void _text(const wchar_t text[], DINT length = 8, DINT x = 5, DINT y = 5) {
		TextOut(this->mem, x, y, text, length);
	}

	void _bkgd(COLOR color) {
		RECT rect = this->client;
		HBRUSH brush = CreateSolidBrush(color.ref); // freeze at ~10k loops, if not variabled
		FillRect(this->mem, &rect, brush);
		DeleteObject(brush);

	}


};
struct SHAPE {
	SHAPE() {};
	~SHAPE() {};

};

