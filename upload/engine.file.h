struct DRX {
	DRX() {};
	std::fstream file;
	STRING name;
	void _open(STRING file, bool out = true, DINT type = 1) {
		switch (type) {
		default:
			break;
		case 0:
			file._append(".sdrx");
			break;
		case 1:
			file._append(".pdrx");
			break;
		}

		this->name = file.text;
		if (out) {
			this->file.open(this->name.text, std::fstream::out);
		}
		else {
			this->file.open(this->name.text, std::fstream::in);
		}
	}
};

struct SDRX : DRX {

	SPRITE sprite;

	void _load(STRING file, bool spr = false) {
		std::cout << "\nLoading SPRITE " << file.text;
		STRING path = ENGINE_MAP_DIRECTORY_SPRITE;
		if(path.length > 0) path._app('\\');
		path._append(file.text);
		this->_open(path, false,  0);
		if (this->file.is_open()) {
			TIME time;
			time._clock(0);
			TIME t2;
			t2._clock(0);
			DINT l = 0;
			INTC colors, w, h;
			char line[128];
			IMAP<PIXEL> pixels;
			while (!this->file.eof()) {
				this->file.getline(line, 128);
				switch (line[0]) {
					default:
						break;
					case 'c': {
						PIXEL p;
						SINT cl = -1;
						for (DINT i = 0; line[i] != '-'; i++) {
							if (cl == 4) break;
							if (line[i] != ' ') {
								colors << (SLINT)UTILS::_ctn(line[i]);
								switch (cl) {
								default:
									break;
								case 0:
									p.color.r = (DINT)colors._number();
									break;
								case 1:
									p.color.g = (DINT)colors._number();
									break;
								case 2:
									p.color.b = (DINT)colors._number();
									break;
								case 3:
									p.color.exist = (DINT)colors._number();
									break;

								}
							}
							else {
								cl++;
								colors._close();
							}
						}
						pixels << p;
					} break;
					case 'w': {
						DINT i = 0;
						do {
							if (line[i] != ' ') {
								w << (SLINT)UTILS::_ctn(line[i]);
							}
							i++;
						} while (line[i] != '-');
					} break;
					case 'h': {
						DINT i = 0;
						do {
							if (line[i] != ' ') {
								h << (SLINT)UTILS::_ctn(line[i]);
							}
							i++;
						} while (line[i] != '-');
					} break;
				}
			}

			DINT width = (DINT)w._number();
			DINT height = (DINT)h._number();

			for (DINT i = 0; i < width; i++) {
				IMAP<PIXEL> ip;
				this->sprite.pixels << ip;
			}

			this->sprite.size.w = width;
			this->sprite.size.h = height;
			this->sprite.scale = { 1.0, 1.0 };

			t2._increment(t2);

			SINT cl = 0;
			DINT x = 0, y = 0;
			TIME t4;
			t4._clock(0);
			for (DINT px = 0; px < pixels.length; px++) {
				PIXEL* pix = &pixels[px];
				pix->x = x;
				pix->y = y;
				this->sprite.pixels[x] << *pix;
				y++;
				if (y == height) {
					y = 0;
					x++;
				}
			}
			t4._increment(t4);
			this->sprite.loaded = true;
			this->sprite.name = file.text;
			time._increment(time);
			std::cout << " in ";
			time._took();

		}
		else {
			std::cout << " > Unable to open " << this->name.text;
			std::cout << "\n" << std::filesystem::current_path();
		}
	}

	void _close() {
		this->file.close();
		this->sprite.pixels._close();
	}

	void operator << (COLOR color) {
		if (this->file.is_open()) {
			this->file << "c ";

			this->file << WRITER::_itc(color.r);
			this->file << " ";
			this->file << WRITER::_itc(color.g);
			this->file << " ";
			this->file << WRITER::_itc(color.b);

			if (color.exist == 0) this->file << " " << '0'; else this->file << " " << '1';
			this->file << "-\n";
		}
	}

	void _size(DINT w, DINT h) {
		if (this->file.is_open()) {
			this->file << "w " << WRITER::_itc(w) << "-\n";
			this->file << "h " << WRITER::_itc(h) << "-\n";
		}

	}

};

struct PDRX : DRX {

	POLYGON polygon;

	void _load(STRING file, bool center = true, bool face = false) {
		TIME time;
		time._clock(0);
		STRING path = ENGINE_MAP_DIRECTORY_POLYGON;
		if (path.length > 0) path._app('\\');
		path._append(file.text);
		this->_open(path, false, 1);
		if (this->file.is_open()) {
			file._strip(file.length - 5, file.length - 1);
			this->polygon.name = file.text;
			char line[128];
			while (!this->file.eof()) {
				this->file.getline(line, 128);
				switch (line[0]) {
					default:
						break;
					case 'n': {
						for (DINT i = 1; line[i] != '='; i++) {
							//if (line[i] != ' ') this->polygon.name._app(line[i]);
						}
					} break;
					case 's': {
						SPOT s;
						SINT cl = -1;
						STRING x, y, z, d;
						for (DINT i = 1; line[i] != '='; i++) {
							if (line[i] == ' ') {
								switch (cl) {
								default:
									break;
								case 0:
									x = d.text;
									break;
								case 1:
									y = d.text;
									break;
								case 2:
									z = d.text;
									break;
								}

								d._clear();
								cl++;
							}
							else {
								d._app(line[i]);
							}
						}

						s = { WRITER::_ctd(x.text), WRITER::_ctd(y.text), WRITER::_ctd(z.text) };

						this->polygon.spot << s;
						this->polygon.calc << s;
						this->polygon.draw << s;
						this->polygon.multi << s;
						//std::cout << "\nx: " << x.text << " y: " << y.text << " z: " << z.text;
					} break;
					case 'p': {
						PAIR pair;
						SINT cl = -1;
						for (DINT i = 1; line[i] != '='; i++) {
							if (line[i] == ' ') {
								cl++;
							}
							else {
								switch (cl) {
								default:
									break;
								case 0:
									pair.a = UTILS::_ctn(line[i]);
									break;
								case 1:
									pair.b = UTILS::_ctn(line[i]);
									break;

								}
							}
						}
						this->polygon.pair << pair;
					} break;
					case 'f': {
						if (!face) {
							FACE face;
							INTC n;
							for (DINT i = 2; line[i] != '='; i++) {
								if (line[i] == ' ') {
									face.i << (DINT)n._number();
									n._close();
								}
								else {
									n.number << UTILS::_ctn(line[i]);
								}
							}
							this->polygon.face << face;
						}
					} break;
				}

			}

			if (face) {


			}

			if (center) {
				SSPOT values = true;
				IMAP<SPOT> spots;
				for (DINT i = 0; i < this->polygon.spot.length; i++) {
					spots << this->polygon.spot[i];
				}
				MATH::_makePoint(spots, &values);

				for (DINT i = 0; i < this->polygon.spot.length; i++) {
					SPOT* s = &this->polygon.spot[i];
					s->x -= values.w / 2.0;
					s->y -= values.h / 2.0;
					s->z -= values.d / 2.0;
				}
				spots._close();
			}

			time._increment(time);
			std::cout << " in ";
			time._took();
		}
		else {
			std::cout << " > Unable to open " << path.text;
		}
	};


	void _close() {
		this->file.close();
		this->polygon.spot._close();
		this->polygon.draw._close();
		this->polygon.calc._close();
		this->polygon.multi._close();
		this->polygon.pair._close();
		this->polygon.group._close();
		this->polygon.face._close();
	};

};
