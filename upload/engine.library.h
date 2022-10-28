
struct STATISTICS {
	STATISTICS() {
		this->fps = 0;
		//Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
		//Engine2::ENGINE::STATISTICS::lf = nf - frames{ 1 };
		//Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
		STATISTICS::nf = std::chrono::system_clock::now();
		STATISTICS::lf = std::chrono::system_clock::now();
	};

	DINT fps;
	COUNTER loops;
	TIME elapsed;
	static TIME last;
	static std::chrono::system_clock::time_point nf, lf;


	void _loop() {
		this->loops.current += 1;
		this->elapsed._increment(this->elapsed);
		DINT since = this->elapsed._since();
		if (this->loops.current > 0 && since > 0) {
			/*
			std::cout << "\n> ";
			std::cout << this->elapsed.lh << ":" << this->elapsed.lm;
			std::cout << ":" << this->elapsed.ls << ":" << this->elapsed.lms;
			std::cout << "(" << this->elapsed._since() << ")";
			*/
			this->fps = this->loops.current / since;
		}
	}

	void _sleep(SINT target = 60) {
		if (target != -1 && target < 60) {
			target = 1000 / (target + target / 2);
			/*
			std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - Engine2::ENGINE::STATISTICS::lf).count() << " ms";
			std::this_thread::sleep_until(Engine2::ENGINE::STATISTICS::nf);
			Engine2::ENGINE::STATISTICS::lf = Engine2::ENGINE::STATISTICS::nf;
			Engine2::ENGINE::STATISTICS::nf += frames {1};
			*/

			//Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
			STATISTICS::lf = std::chrono::system_clock::now();
			//std::chrono::duration<double, std::milli> work = Engine2::ENGINE::STATISTICS::lf - Engine2::ENGINE::STATISTICS::nf;
			std::chrono::duration<double, std::milli> work = STATISTICS::lf - STATISTICS::nf;
			if (work.count() < target) {
				std::chrono::duration<double, std::milli> delta_ms(target - work.count());
				auto delta_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
				std::this_thread::sleep_for(std::chrono::milliseconds(delta_duration.count()));
			}
			//Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
			STATISTICS::nf = std::chrono::system_clock::now();
			//std::chrono::duration<double, std::milli> sleep = Engine2::ENGINE::STATISTICS::nf - Engine2::ENGINE::STATISTICS::lf;
			std::chrono::duration<double, std::milli> sleep = STATISTICS::nf - STATISTICS::lf;

			//std::cout << "\nSleep: " << (work.count() + sleep.count()) << " ms";
			//Engine2::ENGINE::STATISTICS::last.elapsed = (DINT)(work.count() + sleep.count());
			STATISTICS::last.elapsed = (DINT)(work.count() + sleep.count());
			//std::cout << "\n" << STATISTICS::last.elapsed;

		}
	}

};

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
		DICE dice;
		for (DINT c = 0; c < 5; c++) dice._dbl(-123.123, 0.00456, 0.00001);
		TIME time;
		time._clock(0);
		this->_build();
		DIRECTORY dir = ENGINE_MAP_DIRECTORY_SPRITE;
		//dir._dump();

		for (DINT f = 0; f < dir.file.length; f++) {
			if (dir.file.exist[f]) {
				DINT sfound = 0;
				for(DINT s = 0; s < sprite.length; s++){
					if (dir.file[f]._match(sprite[s].name.text)) {
						sfound = 1;
						break;
					}
				}
				if(sfound == 0) sprite << dir.file[f].text;
				STRING name = dir.file[f].text;
				this->_animate(dir.file[f]);
			}
		}

		/*
		for (DINT a = 0; a < animation.length; a++) {
			if (animation[a].sprite[0].name._includes("move")) {
				MOVE m = animation[a];
				move << m;
			}
		}
		*/
		prefix = ENGINE_MAP_PREFIX_POOL;
		suffix = ENGINE_MAP_SUFFIX_POOL;
		base = ENGINE_MAP_BASE_POOL;

		time._increment(time);
		std::cout << "\nConstructed CODEX in " << time._since(1) << "ms.";
	};
	struct DUMMY {
		DUMMY() {
			this->sprite = ENGINE_MAP_SPRITE_DUMMY;
			this->animation = ENGINE_MAP_ANIMATION_DUMMY;
			//this->move = this->animation;
		};
		SPRITE sprite;
		ANIMATION animation;
		//MOVE move;
	};

	DUMMY dummy;
	static CHART<SPRITE> sprite;
	static CHART<ANIMATION> animation;
	//static CHART<MOVE> move;
	//static CHART<ABILITY> ability;
	static CHART<PREFIX> prefix;
	static CHART<SUFFIX> suffix;
	static CHART<STRING> base;

	static SINT _search(const char name[]) {
		for (DINT s = 0; s < sprite.length; s++) {
			if (sprite.exist[s]) {
				if (sprite[s].name._match(name)) return s;
			}
		}

		return -1;
	}

	static SINT _asearch(const char name[]) {
		STRING n = name;
		for (DINT a = 0; a < animation.length; a++) {
			if (animation.exist[a]) {
				if (n._includes(animation[a]._name())) return a;
			}
		}
		return -1;
	}

	void _build() {
		
		sprite << this->dummy.sprite;
		animation << this->dummy.animation;
		//move << this->dummy.move;
	}

	void _animate(STRING file) {
		STRING name = file.text;
		name._slice(' ', '#');
		SINT anm = this->_asearch(name.text);
		if(anm != -1){
			//std::cout << " - Adding to animation";
			animation[anm].sprite << sprite[this->_search(file.text)];
		}
		else {
			
			//std::cout << " - No animation, creating one.";
			ANIMATION a;
			a = { sprite[this->_search(file.text)] };
			animation << a;

		}
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

CHART <SPRITE> CODEX::sprite;
CHART <ANIMATION> CODEX::animation;
//CHART <MOVE> CODEX::move;
//CHART <GAME::ABILITY> CODEX::ability;
CHART <PREFIX> CODEX::prefix;
CHART <SUFFIX> CODEX::suffix;
CHART <STRING> CODEX::base;

std::chrono::system_clock::time_point STATISTICS::nf;
std::chrono::system_clock::time_point STATISTICS::lf;
TIME STATISTICS::last;
//CHART<MOVE> LIBRARY::move;