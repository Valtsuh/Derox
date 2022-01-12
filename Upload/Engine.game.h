

struct BUTTON {
	BUTTON(DINT key = 0, DINT pushed = 0) {
		this->key = key;
		this->pushed = pushed;
	};
	~BUTTON() {};

	DINT key, pushed;
};

struct CONTROLS {
	CONTROLS() {
	
	};
	~CONTROLS() {};

	LIST <BUTTON> button;

	void _set() {
		this->button._set(ENGINE_DATABASE_KEY_UP);
		this->button._set(ENGINE_DATABASE_KEY_SELECT);
	}

	void _push(WPARAM key, SINT state = ENGINE_DATABASE_KEY_NOT_PUSHED) {
		for (DINT b = 0; b < this->button.length; b++) {
			if (this->button.item[b].key == key) {
				this->button.item[b].pushed = state;
				break;
			}
		}
	}

	DINT _state(BUTTON button) {
		for (DINT b = 0; b < this->button.length; b++) {
			if (this->button.item[b].key == button.key) {
				return this->button.item[b].pushed;
			}
		}
		return 0;
	}

};

struct LIMB {
	LIMB(double identifier = 0.0, const char name[] = " ", COLOR color = {25, 0, 0}, DINT width = 1, DINT height = 1, DINT bx = 0, DINT by = 0, DINT bw = 0, DINT bh = 0, DINT exist = 0) {
		this->dimension.width = width;
		this->dimension.height = height;
		this->dimension.x = bw / 2;
		this->dimension.y = bh / 2;
		this->bound.x = bx;
		this->bound.y = by;
		this->bound.width = bw;
		this->bound.height = bh;
		this->pixel.length = 0;
		this->velocity = 1;
		this->name._write(name);
		for (DINT x = 0; x < width; x++) {
			for (DINT y = 0; y < height; y++) {
				this->pixel._set({x, y, 1});
				this->pixel.item[(x * y) + 1]._set(x, y, color);
			}
		}
		this->identifier = identifier;
		this->exist = exist;
	};
	~LIMB() {};
	double identifier;
	STRING name;
	DINT exist, velocity;
	DIMENSION dimension, bound;
	LIST<PIXEL> pixel;
	RANDOM rand;


	void _move() {
		switch (this->rand._roll(0, 7)) {
		default:
			break;
		case 0:
			if(this->dimension.x > this->bound.x + this->velocity) this->dimension.x -= this->velocity;
			break;
		case 1:
			if(this->dimension.x < this->bound.width - this->velocity) this->dimension.x += this->velocity;
			break;
		case 2:
			if(this->dimension.y > this->bound.y + this->velocity) this->dimension.y -= this->velocity;
			break;
		case 3:
			if(this->dimension.y < this->bound.height - this->velocity) this->dimension.y += this->velocity;
			break;
		case 4:
			//if(this->velocity < 4) this->velocity++;
			break;
		case 5:
			//if(this->velocity > 0)this->velocity--;
			break;
		}
	}

	void _boundary() {

	}
};

struct CARCASS {
	CARCASS() {
		this->dimension.x = 225;
		this->dimension.y = 225;
		this->limb.length = 0;
	};
	~CARCASS() {};
	LIST <LIMB> limb;
	DIMENSION dimension;
	RANDOM rand;

	void _set() {
		this->limb._set(ENGINE_DATABASE_LIMB_HEAD);
		this->limb._set(ENGINE_DATABASE_LIMB_CHEST);
		this->limb._set(ENGINE_DATABASE_LIMB_ARM_LEFT);
		this->limb._set(ENGINE_DATABASE_LIMB_ARM_RIGHT);
		this->limb._set(ENGINE_DATABASE_LIMB_LEG_LEFT);
		this->limb._set(ENGINE_DATABASE_LIMB_LEG_RIGHT);
	}

	void _pixelize(HDC tool) {
		if (this->limb.length > 0) {
			DINT x, y;
			SINT p;
			for (DINT l = 0; l < this->limb.length; l++) {
				for (DINT w = 1; w <= this->limb.item[l].dimension.width; w++) {
					for (DINT h = 1; h <= this->limb.item[l].dimension.height; h++) {
						p = (w * h) - 2;
						if (p >= 0) {
							x = this->dimension.x + this->limb.item[l].dimension.x + w;
							y = this->dimension.y + this->limb.item[l].dimension.y + h;
							//this->limb.item[l].pixel.item[p]._set(x, y, this->limb.item[l].pixel.item[p].color.ref);
							this->limb.item[l].pixel.item[p]._draw(tool, x, y);
						}
					 }
				}
			}
		}
	}

	void _generate() {
		switch (this->rand._roll(0, 5)) {
		default:
			break;
		case 0:
			this->limb._set(ENGINE_DATABASE_LIMB_ARM_LEFT);
			break;
		case 1:
			this->limb._set(ENGINE_DATABASE_LIMB_ARM_RIGHT);
			break;
		}
	}

	void _skeletal() {
		if (this->limb.length > 0) {
			for (DINT l = 0; l < this->limb.length; l++) {
				this->limb.item[l]._move();
			}
		}
	}
};

struct ATTRIBUTE {
	ATTRIBUTE() {
		this->value = 0;
		this->modifier = 0;
	};
	~ATTRIBUTE() {};

	DINT value, modifier;
};
struct EXPERIENCE {
	EXPERIENCE() {
		this->value = 0;
	};
	~EXPERIENCE() {};
	DINT value;

};
struct HEALTH {
	HEALTH() {
		this->value = 1;
	};
	~HEALTH() {};
	DINT value;
};
struct DAMAGE {
	DAMAGE() {
		this->value = 1;
	};
	~DAMAGE() {};
	DINT value, min, max;
	RANDOM dice;
};
struct COLLISION {
	COLLISION() {
		this->current = 0;
		this->collie = -1;
	};
	~COLLISION() {
		this->current = 0;
		this->collie = -1;
	};
	DINT current;
	SINT collie;
	COUNTER amount, to, from;

	void _reset() {
		this->~COLLISION();
	}
};
struct ITEM {
	ITEM(DINT identifier = 0, const char text[] = "") {
		this->identifier = identifier;
		this->exist = 0;
		this->name._write(text);
	};
	~ITEM() {};
	DINT exist, identifier;
	COUNTER amount;
	STRING name;
};
struct INVENTORY {
	INVENTORY() {};
	~INVENTORY() {};

	DINT slots;

	ITEM item[ENGINE_DATABASE_INVENTORY_SLOTS];

	void _add(ITEM item) {
		DINT added = 0;
		for (DINT i = 0; i < ENGINE_DATABASE_INVENTORY_SLOTS; i++) {
			if (this->item[i].exist == 1) {
				if (this->item[i].identifier == item.identifier) {
					this->item[i].amount.current += 1;
					system("pause");
					added = 1;
					break;
				}
			}
		}

		if (added == 0) {
			for (DINT j = 0; j < ENGINE_DATABASE_INVENTORY_SLOTS; j++) {
				if (this->item[j].exist == 0) {
					this->item[j] = item;
					this->item[j].amount.current = 1;
				}
			}
		}


	};
};
struct DESCRIPTOR {
	DESCRIPTOR(const char text[] = "No description yet.", DINT value = 0) {
		this->description._write(text);
		this->value = value;
	};
	~DESCRIPTOR() {};

	STRING description;
	DINT value;

};
struct DUS {
	DUS(double identifier = 0.0, const char name[] = "", DIMENSION dimension = {}, COLOR color = { 45, 180, 150 }, DESCRIPTOR desc = {}) {
		DINT p = 0;
		this->original._set(color);
		for (DINT w = 0; w < dimension.width; w++) {
			for (DINT h = 0; h < dimension.height; h++) {
				this->pixel[p]._set(w, h, this->color);
				this->pixel[p].unique = p;
				p++;
			}
		}
		this->info = desc;
		this->name._write(name);
		this->identifier = identifier;
		this->dimension.x = dimension.x;
		this->dimension.y = dimension.y;
		this->dimension.width = dimension.width;
		this->dimension.height = dimension.height;
		this->to._set(this->dimension);
		//this->to._set(this->dimension);
		this->boundary.width = 24;
		this->boundary.height = 32;
		this->speed.value = ENGINE_DATABASE_DUS_SPEED;
		this->set = 0;
		//this->unique = this->dice._roll(0, 255);
		this->unique = 0;
		this->move = 0;
		this->temp = { 255, 255, 255 };
		this->exist = 0;
	};
	~DUS() {};
	double identifier;
	DINT exist;
	DINT set, unique, move;
	COUNTER steady;
	DIMENSION dimension, to, boundary, previous;
	PIXEL pixel[4096];
	COLOR color, temp, original;
	STRING name;
	RANDOM dice;
	ATTRIBUTE speed, offense, defense;
	DAMAGE damage;
	HEALTH health;
	EXPERIENCE experience;
	COLLISION collision;
	INVENTORY inventory;
	DESCRIPTOR info;
	void _color(COLOR color) {
		this->color = color;
	}

	void _update() {
		if(this->dimension.x + this->dimension.width > this->boundary.width){
			this->dimension.x = this->boundary.width - this->dimension.width - this->speed.value;
		}
		if (this->dimension.y + this->dimension.height > this->boundary.height) {
			this->dimension.y = this->boundary.height - this->dimension.height - this->speed.value;
		}

	}

	void _pixelize(HDC tool) {
		DINT x = 0, y = 0;
		for (DINT p = 0; p < this->dimension.width * this->dimension.height; p++) {
			x = this->dimension.x + this->pixel[p].x;
			y = this->dimension.y + this->pixel[p].y;
			switch (this->collision.current) {
			default:
				this->_color(this->original);
				break;
			case 1:
				this->_color({ 255, 0, 0 });
				break;
			}
			this->pixel[p].color._set(this->color);
			this->pixel[p]._draw(tool, x, y);
		}
	}

	void _move() {
		this->to._set(this->dimension);
		switch (this->dice._roll(0, 8)) {
		default:
			break;
		case 0:
			if(this->to.x > 0) this->to.x -= this->speed.value;
			break;
		case 1:
			if(this->to.x < this->boundary.width - this->dimension.width - this->speed.value) this->to.x += this->speed.value;
			break;
		case 2:
			if(this->to.y > 0) this->to.y -= this->speed.value;
			break;
		case 3:
			if(this->to.y < this->boundary.height - this->dimension.height - this->speed.value) this->to.y += this->speed.value;
			break;

		}
	}

	void _towards(DUS dus) {
		this->to._set(this->dimension);
		if (this->to.x + this->to.width < dus.to.x) {
			this->to.x += this->speed.value;
		}
		if (this->to.x > dus.to.x + dus.to.width) {
			this->to.x -= this->speed.value;
		}
		if (this->to.y + this->to.height < dus.to.y) {
			this->to.y += this->speed.value;
		}
		if (this->to.y > dus.to.y + dus.to.height) {
			this->to.y -= this->speed.value;
		}

	}

	void _to() {
		this->previous._set(this->dimension);
		this->dimension._set(this->to);
	}

	DINT _collision(DUS dus) {
		DINT collision = 1;
		this->move = 1;
		if (this->to.x + this->to.width >= dus.to.x &&
			this->to.x <= dus.to.x + dus.to.width &&
			this->to.y + this->to.height >= dus.to.y &&
			this->to.y <= dus.to.y + dus.to.height
			) { 
			// within dus, collision
			this->collision.current = 1;
			this->collision.collie = dus.unique;
			this->collision.amount.current += 1;
			this->collision.from.current += 1;
			this->move = 0;
			collision = 0;
		}
		return collision;
	}


	DINT _description(DIMENSION dimension) {
		if (
			dimension.x >= this->dimension.x &&
			dimension.x <= this->dimension.x + this->dimension.width &&
			dimension.y >= this->dimension.y &&
			dimension.y <= this->dimension.y + this->dimension.height
			) {
			return 1;
		}
		return 0;
	}
	

};

struct GAME {
	GAME() {
		this->set = 0;
		this->window = 0;
		this->temp = 0;
		this->building = ENGINE_DATABASE_DUS_MINE;
		
	};
	~GAME() {};
	DINT set, temp;
	COUNTER counter, elapsed, fps, lps;
	LIST <DUS> dus;
	LIST <DUS> resource;
	DUS building;
	CANVAS canvas;
	HWND window;
	RANDOM dice;
	CONTROLS controls;

	void _generate(DUS dus, DINT w = 300, DINT h = 200) {
		DINT length = this->dus._set(dus);
		this->dus.item[length].dice._set(0, 1);
		this->dus.item[length].dimension.x = this->dus.item[length].dice._roll(0, w);
		this->dus.item[length].dimension.y = this->dus.item[length].dice._roll(0, h);
		this->dus.item[length].unique = length;
		
		if (this->dus.length > 0)
		{
			DINT temp = 0;
			do {

				if (this->dus.item[length].unique != this->dus.item[temp].unique) {
					if (this->dus.item[length].unique == this->dus.item[temp].unique) {
						/*
						do {
							this->dus.item[length].unique = this->dus.item[length].dice._roll(0, length);
						} while (this->dus.item[length].unique == this->dus.item[temp].unique || this->dus.item[length].unique == 0);
						temp = 0;
						*/
					}
				}
				temp++;
			} while (temp < length);
		}
		this->dus.item[length].exist = 1;
		
	}


	SINT _unique(DINT unique) {
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].unique == unique) return (SINT)d;
		}
		return -1;
	}
	void _set() {
		this->controls._set();
		for (DINT d = 0; d < 0; d++) {
			this->_generate(ENGINE_DATABASE_DUS_SAMPLE);
		}

		this->set = 1;
	}

	void _update() {
		GetClientRect(this->window, &this->canvas.client);
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].boundary.width != this->canvas.client.right) this->dus.item[d].boundary.width = this->canvas.client.right;
			if (this->dus.item[d].boundary.height != this->canvas.client.bottom) this->dus.item[d].boundary.height = this->canvas.client.bottom;
			this->dus.item[d]._update();
			this->dus.item[d].collision._reset();
		}
	}


	void _movement() {
		for (DINT d = 0; d < this->dus.length; d++) {

			if (this->dus.item[d].steady.current > 25) {
				this->dus.item[d]._towards(this->dus.item[this->dice._roll(0, this->dus.length - 1)]);
				this->dus.item[d].steady.current = 0;
			}
			else {
				this->dus.item[d]._towards(this->building);
				this->dus.item[d].steady.current += 1;
			}

			for (DINT c = 0; c < this->dus.length; c++) {
				if (this->dus.item[d].unique != this->dus.item[c].unique) {
					this->dus.item[c].move = this->dus.item[d]._collision(this->dus.item[c]);
				}
			}
			if (this->dus.item[d].collision.current != 1) this->dus.item[d]._to();

		}
	}

	void _play() {
		this->_update();
		if (this->dus.length < ENGINE_DATABASE_DUS_APPEARANCES) {
			switch (this->dice._roll(0, (DINT)(8 + (ENGINE_DATABASE_DUS_APPEARANCE_CHANCE / (this->lps.current + 1))))) {
			default:
				break;
			case 0:
				this->_generate(ENGINE_DATABASE_DUS_SAMPLE);
				break;
			case 1:
				this->_generate(ENGINE_DATABASE_DUS_NOTHING);
				break;
			case 2:
				this->_generate(ENGINE_DATABASE_DUS_UNIQUE);
				break;
			case 3:
				this->_generate(ENGINE_DATABASE_DUS_OFFENSE);
				break;
			case 4:
				this->_generate(ENGINE_DATABASE_DUS_DEFENSE);
				break;

			}

		}

		this->_movement();
		this->_collect();
		this->_battle();
		this->_other();
	}

	void _collect() {

		for (DINT d = 0; d < this->dus.length; d++) {
			for (DINT r = 0; r < this->resource.length; r++) {


			}
		}
	}

	void _other() {
		for (DINT d = 0; d < this->dus.length; d++) {
			this->dus.item[d]._collision(this->building);
			if (this->dus.item[d].collision.current == 1) {
				this->dus.item[d].inventory._add(ENGINE_DATABASE_ITEM_CURRENCY);
			}
		}
	}

	void _battle() {
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].collision.current != 0) {
				for (DINT c = 0; c < this->dus.length; c++) {
					if (this->dus.item[c].unique != this->dus.item[d].unique) {
						if (this->dus.item[d].collision.collie == this->dus.item[c].unique) {
							if (this->dus.item[c].health.value < this->dus.item[d].damage.value) {
								this->dus.item[c].health.value = 0;
							}
							else {
								this->dus.item[c].health.value -= this->dus.item[d].damage.value;
							}
							this->dus.item[c].collision.amount.current += 1;
							this->dus.item[c].collision.to.current += 1;
						} 
						if(this->dus.item[c].health.value <= 0){
							switch (*this->dus.item[c].name.text) {
							default:
								break;
							case *"Defense":
								this->dus.item[d].defense.value += 1;
								break;
							case *"Offense":
								this->dus.item[d].offense.value += 1;
								break;
							case *"Nothing":
								this->dus.item[d].health.value += 2;
								break;
							case *"Unique":
								switch (this->dice._roll(0, 8)) {
								default:
									break;
								case 0:
									this->dus.item[d].health.value += 1;
									break;
								}
								break;
							case *"Sample":
								switch (this->dice._roll(0, 12)) {
								default:
									break;
								case 0:
									this->dus.item[d].health.value += 1;
									break;
								case 1:
									this->dus.item[d].damage.value += 1;
									break;
								}
								break;
							}
							this->dus.item[d].experience.value += 1;
							this->dus._remove(c);
							//system("pause");
							break;
						}
					}
				}
				break;
			}
		}
	}

};
