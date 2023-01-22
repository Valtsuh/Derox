
struct PREFIX {
	PREFIX(const char name[]) {
		this->name._write(name);
	};
	PREFIX() {};
	STRING name;
};

struct SUFFIX {
	SUFFIX(const char name[]) {
		this->name._write(name);
	};
	SUFFIX() {};
	STRING name;
};

struct CODEX {
	CODEX() {
		srand((unsigned int)time(NULL));
		TIME time;
		time._clock(0);
		this->_build();
		sprites = ENGINE_MAP_DIRECTORY_SPRITE;
		polygons = ENGINE_MAP_DIRECTORY_POLYGON;
		time._increment(time);
		std::cout << "\nConstructed CODEX in " << time._since(1) << "ms.";
	};
	struct DUMMY {
		DUMMY() {
			//this->move = this->animation;
		};
		SPRITE sprite, tile;
		ANIMATION animation;
		//MOVE move;
	};

	DUMMY dummy;
	static DIRECTORY sprites, polygons;
	static IMAP<SPRITE> sprite;
	static IMAP<ANIMATION> animation;
	static IMAP<POLYGON> polygon;

	//static CHART<MOVE> move;
	//static CHART<ABILITY> ability;
	static CHART<PREFIX> prefix;
	static CHART<SUFFIX> suffix;
	static CHART<STRING> base;

	static SINT _search(const char name[]) {
		for (DINT s = 0; s < sprite.length; s++) {
			if (sprite.package[s].exist) {
				if (sprite[s].name._match(name)) return s;
			}
		}

		for (DINT f = 0; f < sprites.file.length; f++) {
			bool sfound = 0;
			STRING file = sprites.file[f];
			if (file._match(name)) {
				STRING n = file.text;
				DINT l = 0;
				if (n._match("sdrx")) {
					l = 5;
				}
				else {
					l = 4;
				}
				n._slice(n.length - l, n.length - 1);
				if (n._exact(name)) {
					bool match = file._match(".sdrx");
					if (match) {
						SDRX sdrx;
						sdrx._load(name);
						sprite << sdrx.sprite;
					}
					else {
					}
					//_animate(file);
					return sprite.length - 1;
				}
			}
		}
		return -1;
	}

	static SINT _asearch(const char name[]) {
		for (DINT a = 0; a < animation.length; a++) {
			if (animation.package[a].exist) {
				STRING n = animation[a]._name();
				if (n._match(name)) return a;
			}
		}
		
		SINT sprite = CODEX::_search(name);
		if (sprite >= 0) {
			CHART<SPRITE> ss;
			for (DINT i = 0; i < sprites.file.length; i++) {
				STRING file = sprites.file[i];
				if (file._match(name)) {
					DINT l = 0;
					if (file._match("sdrx")) {
						l = 5;
					}
					else {
						l = 4;
					}
					file._slice(file.length - l, file.length - 1);
					sprite = CODEX::_search(file.text);
					if (sprite >= 0) ss << CODEX::sprite[sprite];
				}
			}

			ANIMATION animation = ss;
			CODEX::animation << animation;
			ss._close();
			return CODEX::animation.length - 1;
		}
		return -1;
	}

	static SINT _psearch(const char name[]) {
		for (DINT s = 0; s < polygon.length; s++) {
			if (polygon.package[s].exist) {
				if (polygon[s].name._match(name)) return s;
			}
		}
		for (DINT f = 0; f < polygons.file.length; f++) {
			bool sfound = 0;
			STRING file = polygons.file[f];
			bool match = file._match(".pdrx");
			if (file._match(name)) {
				file._slice(file.length - 5, file.length - 1);
				PDRX pdrx;
				pdrx._load(file);
				//POLYGON pol = { file.text, true };
				polygon << pdrx.polygon;
				return polygon.length - 1;
			}
		}


		return -1;

	}

	void _build() {
		
		sprite << this->dummy.sprite;
		animation << this->dummy.animation;
		//move << this->dummy.move;
	}

	void _dump() {
		std::cout << "\nSprites: ";
		for (DINT s = 0; s < sprite.length; s++) {
			std::cout << "\n> " << sprite[s].name.text;
		}
		std::cout << "\nAnimationws: ";
		for (DINT s = 0; s < animation.length; s++) {
			std::cout << "\n> " << animation[s]._name();
		}
		/*
		std::cout << "\nMoves: ";
		for (DINT s = 0; s < move.length; s++) {
			std::cout << "\n> " << move[s].name.text;
		}
		*/
		std::cout << "\nPrefixes: ";
		for (DINT s = 0; s < prefix.length; s++) {
			std::cout << "\n>" << prefix[s].name.text;
		}
		std::cout << "\nSuffixes: ";
		for (DINT s = 0; s < suffix.length; s++) {
			std::cout << "\n>" << suffix[s].name.text;
		}

	}

};

IMAP <SPRITE> CODEX::sprite;
DIRECTORY CODEX::sprites;

IMAP <ANIMATION> CODEX::animation;

IMAP <POLYGON> CODEX::polygon;
DIRECTORY CODEX::polygons;

CHART <PREFIX> CODEX::prefix;
CHART <SUFFIX> CODEX::suffix;
CHART <STRING> CODEX::base;

//CHART<MOVE> LIBRARY::move;