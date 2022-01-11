

struct BUTTON {
	BUTTON(DINT key = 0, DINT pushed = 0) {
		this->key = key;
		this->pushed = pushed;
	};
	~BUTTON() {};

	DINT key, pushed, down;
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


	void _down(WPARAM key, SINT state = ENGINE_DATABASE_KEY_NOT_PUSHED) {
		for (DINT b = 0; b < this->button.length; b++) {
			if (this->button.item[b].key == key) {
				this->button.item[b].down = state;
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
	DINT exist;
	SINT velocity;
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
			SINT x, y, p;
			for (DINT l = 0; l < this->limb.length; l++) {
				p = 0;
				for (SINT w = 1; w <= this->limb.item[l].dimension.width; w++) {
					p++;
					for (SINT h = 1; h <= this->limb.item[l].dimension.height; h++) {
						x = this->dimension.x + this->limb.item[l].dimension.x + w;
						y = this->dimension.y + this->limb.item[l].dimension.y + h;
						//this->limb.item[l].pixel.item[p]._set(x, y, this->limb.item[l].pixel.item[p].color.ref);
						this->limb.item[l].pixel.item[p]._draw(tool, x, y);
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

	SINT value, modifier;
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
		this->min = 0;
		this->max = 0;
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

	void _set(DINT collie) {
		this->collie = (SINT)collie;
		this->current = 1;
		this->amount.current += 1;
		this->from.current += 1;

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
	INVENTORY() {
		this->slots = 0;
	};
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
struct TARGET {
	TARGET() {
		this->identifier = 0;
		this->exist = 0;
	};
	~TARGET() {};
	DINT identifier, exist;
	DIMENSION dimension;
	STRING name;
};
struct DUS {
	DUS(double identifier = 0.0, const char name[] = "", DIMENSION dimension = {}, COLOR color = { 45, 180, 150 }, DESCRIPTOR desc = {}) {
		DINT p = 0;
		this->original._set(color);
		if (dimension.width > 0 && dimension.height > 0) {
			for (SINT w = 0; w < dimension.width; w++) {
				for (SINT h = 0; h < dimension.height; h++) {
					this->pixel[p]._set(w, h, this->original);
					this->pixel[p].unique = p;
					p++;
				}
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
		this->boundary.width = 24;
		this->boundary.height = 32;
		this->speed.value = ENGINE_DATABASE_DUS_SPEED;
		this->set = 0;
		this->unique = 0;
		this->move = 0;
		this->temp = { 255, 255, 255 };
		this->exist = 0;
	};
	~DUS() {};
	double identifier;
	DINT exist, set, unique, move;
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
	TARGET target;

	void _color(COLOR color) {
		this->color = color;
	}

	void _update() {
		this->collision._reset();
		if(this->dimension.x + this->dimension.width > this->boundary.width){
			this->dimension.x = this->boundary.width - this->dimension.width - this->speed.value;
		}
		if (this->dimension.y + this->dimension.height > this->boundary.height) {
			this->dimension.y = this->boundary.height - this->dimension.height - this->speed.value;
		}
		this->steady.current++;
	}

	void _pixelize(HDC tool) {
		if (this->dimension.width > 0 && this->dimension.height > 0) {
			for (SINT p = 0; p < this->dimension.width * this->dimension.height; p++) {
				switch (this->collision.current) {
				default:
					this->_color(this->original);
					break;
				case 1:
					this->_color({ 255, 0, 0 });
					break;
				}
				this->pixel[p].color._set(this->color);
				this->pixel[p]._draw(tool, this->dimension.x, this->dimension.y);
			}
		}
	}

	void _repixel(DIMENSION dimension) {
		this->dimension._set(dimension);
		DINT p = 0;
		for (SINT w = 0; w < this->dimension.width; w++) {
			for (SINT h = 0; h < this->dimension.height; h++) {
				this->pixel[p]._set(w, h, this->original);
				p++;
			}
		}
	}

	void _move() {
		this->to._set(this->dimension);
		switch (this->dice._roll(0, ENGINE_DATABASE_DUS_MOVEMENT_CHANCE)) {
		default:
			break;
		case 0:
			this->to.x -= this->speed.value;
			break;
		case 1:
			this->to.x += this->speed.value;
			break;
		case 2:
			this->to.y -= this->speed.value;
			break;
		case 3:
			this->to.y += this->speed.value;
			break;

		}
	}

	void _towards(DIMENSION dimension = {}) {
		this->to._set(this->dimension);
		if (this->to.x + this->to.width <= dimension.x) {
			this->to.x += this->speed.value;
		}
		if (this->to.x >= dimension.x + dimension.width) {
			this->to.x -= this->speed.value;
		}
		if (this->to.y + this->to.height <= dimension.y) {
			this->to.y += this->speed.value;
		}
		if (this->to.y >= dimension.y + dimension.height) {
			this->to.y -= this->speed.value;
		}

	}

	void _to() {
		if (
			this->to.x >= this->boundary.x + this->speed.value &&
			this->to.x <= this->boundary.width - this->speed.value - this->dimension.width &&
			this->to.y >= this->boundary.x + this->speed.value &&
			this->to.y <= this->boundary.height - this->speed.value - this->dimension.height

			) {
			this->previous._set(this->dimension);
			this->dimension._set(this->to);
			this->steady.current = 0;
		}
	}

	DINT _collive(LIST <DUS> *list) {
		DINT collision = 0;
		this->move = 1;
		for (DINT c = 0; c <= list->length; c++) {
			if (this->unique != list->item[c].unique) {
				if (this->to.x + this->to.width >= list->item[c].to.x &&
					this->to.x <= list->item[c].to.x + list->item[c].to.width &&
					this->to.y + this->to.height >= list->item[c].to.y &&
					this->to.y <= list->item[c].to.y + list->item[c].to.height
					) {
					// within dus, collision
					this->collision._set(list->item[c].unique);
					this->move = 0;
					collision = 1;
					break;
				}
			}
		}
		return collision;
	}

	DINT _collsiion(DUS dus) {
		DINT collision = 0;
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
			collision = 1;
		}
	}

	DINT _description(DIMENSION dimension = {}) {
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

	void _gather(LIST<DUS> &list) {
			for (DINT d = 0; d < list.length; d++) {
				
				if (this->target.exist == 0) {
					this->target.identifier = list.item[d].unique;
					this->target.name = list.item[d].name;
					this->target.dimension._set(list.item[d].dimension);
					this->target.exist = 1;
					break;
				}
				
			}
	}
	

};

struct GAME {
	GAME() {
		this->set = 0;
		this->window = 0;
		this->temp = 0;
		this->building = ENGINE_DATABASE_DUS_MINE;
		this->carrier._set(this->building);
		
	};
	~GAME() {};
	DINT set, temp;
	COUNTER counter, elapsed, fps, lps;
	LIST <DUS> dus;
	LIST <DUS> resource;
	LIST <DUS> carrier;
	DUS building;
	DIMENSION client;
	HWND window;
	RANDOM dice;
	CONTROLS controls;

	void _carriage() {

		// 
		this->carrier._deconstruct();

		this->carrier._carry(&this->dus);
		this->carrier._carry(&this->resource);
		this->carrier._set(this->building);
	}

	void _generate(DUS dus, DIMENSION dimension, DINT list = 0) {
		SINT u;
		//dus.dimension._set(dimension);
		do {
			u = 0; 
			dus.unique = dus.dice._roll(0, 999);

			for (DINT c = 0; c < this->carrier.length; c++) {
				if (dus.unique == this->carrier.item[c].unique) {
					u = -1;
				}
			}
		} while (u == -1);
		
		dus.dimension.x = this->dice._roll(0, this->client.width); //this->kit.canvas.measure.right - dus.speed.value - dus.dimension.width);
		dus.dimension.y = this->dice._roll(0, this->client.height);  //this->kit.canvas.measure.bottom - dus.speed.value - dus.dimension.height);
		dus.boundary._set({ 0, 0, this->client.width, this->client.height });
		switch (list) {
		default:
		case 0:
			this->dus._set(dus);
			break;
		case 1:
			this->resource._set(dus);
			break;
		}
		this->carrier._set(dus);
	}


	DUS _unique(DINT unique) {
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].unique == unique) return this->dus.item[d];
		}
		return -1;
	}
	void _set() {
		this->controls._set();
		for (DINT d = 0; d < 0; d++) {
			//this->_generate(ENGINE_DATABASE_DUS_SAMPLE);
		}

		this->set = 1;
	}

	void _update() {
		this->_carriage();
		RECT client;
		GetClientRect(this->window, &client);
		this->client.x = 0;
		this->client.y = 0;
		this->client.width = client.right;
		this->client.height = client.bottom;
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].boundary.width != this->client.width) this->dus.item[d].boundary.width = this->client.width;
			if (this->dus.item[d].boundary.height != this->client.height) this->dus.item[d].boundary.height = this->client.height;
			this->dus.item[d]._update();
		}
	}


	void _play() {
		this->_update();
		if (this->resource.length < ENGINE_DATABASE_DUS_RESOURCE_APPEARANCES) {
			switch (this->dice._roll(0, 32)) {
			default:
				break;
			case 0:
				this->_generate(ENGINE_DATABASE_DUS_CURRENCY, { -1, -1, -1, -1 }, 1);
				break;
			}
		}
		if (this->dus.length < ENGINE_DATABASE_DUS_APPEARANCES) {
			switch (this->dice._roll(0, (DINT)(8 + (ENGINE_DATABASE_DUS_APPEARANCE_CHANCE * (this->lps.current + 1))))) {
			default:
				break;
			case 0:
				this->_generate(ENGINE_DATABASE_DUS_SAMPLE, {-1, -1, 4, 4});
				break;
			case 1:
				this->_generate(ENGINE_DATABASE_DUS_NOTHING, { -1, -1, 4, 4 });
				break;
			case 2:
				this->_generate(ENGINE_DATABASE_DUS_UNIQUE, { -1, -1, 4, 4 });
				break;
			case 3:
				this->_generate(ENGINE_DATABASE_DUS_OFFENSE, { -1, -1, 4, 4 });
				break;
			case 4:
				this->_generate(ENGINE_DATABASE_DUS_DEFENSE, { -1, -1, 4, 4 });
				break;

			}
		}
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.item[d].steady.current >= 25) this->dus.item[d].steady.current = 0;
			this->dus.item[d]._gather(this->resource);			
			if(this->resource.length > 0) this->dus.item[d]._towards(this->resource.item[0].dimension);
			if (this->dus.item[d]._collive(&this->carrier) == 0) {
				this->dus.item[d]._to();
			}
			else {
				if(this->dus.item[d].steady.current == 0) this->dus.item[d]._move();
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
