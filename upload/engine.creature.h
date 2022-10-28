
struct FIGURE {
	FIGURE(const char name[], const char abbr[], DINT amount) {
		this->name = name;
		this->abbr = abbr;
		this->point.current = amount;
		this->point.total = amount;
	};
	FIGURE() {};

	STRING name, abbr;
	COUNTER point;
	DICE dice;
	STRING _text() {
		STRING text;
		text._append(WRITER::_itc(this->point.current));
		text._app('/');
		text._append(WRITER::_itc(this->point.total));
		return text;
	}
};

struct STATUS {
	STATUS() {
		this->immune = 0;
		this->burning = 0;
		this->frozen = 0;
		this->vulnerable = 0;
	};

	DINT immune, burning, frozen, vulnerable;
};

struct BIOME {
	BIOME() {};


};

struct MOVEMENT {
	MOVEMENT() {
		this->arrived = 1;
		this->speed = 1.0;
		this->direction = 5;
	}
	SPOT travelled, travelling;
	POS id, current, to;
	DINT arrived, direction;
	double speed;
	CHART <DINT> type;

	void _clamp() {
		switch (this->direction) {
		default:
			break;
		case 2:
			if (this->current.x < this->to.x) this->current.x = this->to.x;
			if (this->current.y > this->to.y) this->current.y = this->to.y;
			break;
		case 4:
			if (this->current.x < this->to.x) this->current.x = this->to.x;
			if (this->current.y < this->to.y) this->current.y = this->to.y;
			break;
		case 6:
			if (this->current.x > this->to.x) this->current.x = this->to.x;
			if (this->current.y > this->to.y) this->current.y = this->to.y;
			break;
		case 8:
			if (this->current.x > this->to.x) this->current.x = this->to.x;
			if (this->current.y < this->to.y) this->current.y = this->to.y;
			break;
		}
		if (this->to.x == this->current.x && this->to.y == this->current.y) this->arrived = 1;
	}

	void _advance(double speed) {
		this->speed = speed;
		switch (this->direction) {
		default:
			break;
		case 2:
			this->travelled.x -= this->speed * 2.0;
			this->travelled.y += this->speed;
			break;
		case 4:
			this->travelled.x -= this->speed * 2.0;
			this->travelled.y -= this->speed;
			break;
		case 6:
			this->travelled.x += this->speed * 2.0;
			this->travelled.y += this->speed;
			break;
		case 8:
			this->travelled.x += this->speed * 2.0;
			this->travelled.y -= this->speed;
			break;
		}
	}

	DINT _able(DINT type) {
		for (DINT i = 0; i < this->type.length; i++) {
			if (this->type[i] == type) return 1;
		}
		return 0;
	}

};
struct SEX {
	SEX() {};
	FIGURE gender;
};

struct ITEM {
	ITEM(const char name[]) {
		this->name = name;
		this->amount = 0;
	};
	ITEM() {
		this->amount = 0;
	};

	STRING name;
	DINT amount;

};

struct INVENTORY {
	INVENTORY() {};

	CHART <ITEM> item;


	void _trash() {
		this->item._close();

	}

};