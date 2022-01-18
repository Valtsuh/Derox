struct GAME {
	struct DIRECTION {
		DIRECTION() {};
		~DIRECTION() {};
		DINT value, exist, available;
	};
	struct STATISTICS{
		STATISTICS() {};
		~STATISTICS() {};
		COUNTER loop, fps;

	};
	struct COLLISION {
		COLLISION() {
			this->current = 0;
			this->collie = -1;
		};
		~COLLISION() {};
		DINT current;
		SINT collie;


		void _reset() {
			this->current = 0;
			this->collie = -1;
		}
	};
	struct TARGET {
		TARGET() {
			this->unique = -1;
			this->type = 0;
		};
		~TARGET() {};

		SINT unique, type;

		void _set(DINT unique, DINT type = 0) {
			this->unique = unique;
			this->type = type;
		}
		void _reset() {
			this->unique = -1;
			this->type = 0;
		}
	};
	struct DUS {
		DUS(double identifier = 0.0, const char text[] = "", DINT width = 3, DINT heigth = 3, COLOR color = {}, DINT x = 25, DINT y = 25) {
			this->identifier = identifier;
			this->model._set(x, y, width, heigth);
			this->model.color._set(color);
			this->model.pixel._set(0, 0, color);
			this->speed = 1;
			this->exist = 0;
			this->name._write(text);
			this->unique = 0;
		};
		~DUS() {};
		double identifier;
		MODEL model;
		DINT speed, unique, exist, direction;
		RANDOM dice;
		COLLISION collision;
		STRING name;
		COUNTER amount, directed;
		TARGET target;
		LIST <DIRECTION> directions;

		void _update() {
			this->model.to.direction = 0;
		}

		void _towards(DIMENSION to) {
			if (this->model.position.x < to.x && this->model.position.y < to.y) {
				this->model.to.x = this->model.position.x + this->speed;
				this->model.to.y = this->model.position.y + this->speed;
				this->model.to.direction = 3;
			}
			else {
				if (this->model.position.x < to.x && this->model.position.y > to.y) {
					this->model.to.x = this->model.position.x + this->speed;
					this->model.to.y = this->model.position.y - this->speed;
					this->model.to.direction = 9;
				}
				else {
					if (this->model.position.x > to.x && this->model.position.y < to.y) {

						this->model.to.x = this->model.position.x - this->speed;
						this->model.to.y = this->model.position.y + this->speed;
						this->model.to.direction = 1;
					}
					else {
						if (this->model.position.x > to.x && this->model.position.y > to.y) {

							this->model.to.x = this->model.position.x - this->speed;
							this->model.to.y = this->model.position.y - this->speed;
							this->model.to.direction = 7;
						}
						else {

							if (this->model.position.x < to.x) {
								this->model.to.x = this->model.position.x + this->speed;
								this->model.to.direction = 6;
							}
							if (this->model.position.x > to.x) {
								this->model.to.x = this->model.position.x - this->speed;
								this->model.to.direction = 4;
							}
							if (this->model.position.y < to.y) {
								this->model.to.y = this->model.position.y + this->speed;
								this->model.to.direction = 2;
							}
							if (this->model.position.y > to.y) {
								this->model.to.y = this->model.position.y - this->speed;
								this->model.to.direction = 8;
							}
						}
					}
				}
			}
		}

		void _move() {
			switch (this->dice._roll(0, 16)) {
			default:
				//this->model.to.x = this->model.position.x + this->speed;
				break;
			case 4:
				this->model.to.x = this->model.position.x - this->speed;
				this->model.to.direction = 4;
				break;
			case 5:
				this->model.to.x = this->model.position.x + this->speed;
				this->model.to.direction = 6;
				break;
			case 6:
				this->model.to.y = this->model.position.y - this->speed;
				this->model.to.direction = 8;
				break;
			case 7:
				this->model.to.y = this->model.position.y + this->speed;
				this->model.to.direction = 2;
				break;
			}
		}

		void _direct(DINT direction) {
			switch (direction) {
			case 1:
				this->model.position.x = this->model.position.x - this->speed;
				this->model.position.y = this->model.position.y + this->speed;
				break;
			case 3:
				this->model.position.x = this->model.position.x + this->speed;
				this->model.position.y = this->model.position.y + this->speed;
				break;
			case 7:
				this->model.position.x = this->model.position.x - this->speed;
				this->model.position.y = this->model.position.y - this->speed;
				break;
			case 9:
				this->model.position.x = this->model.position.x + this->speed;
				this->model.position.y = this->model.position.y - this->speed;
				break;
			case 4:
				this->model.position.x = this->model.position.x - this->speed;
				break;
			case 6:
				this->model.position.x = this->model.position.x + this->speed;
				break;
			case 8:
				this->model.position.y = this->model.position.y - this->speed;
				break;
			case 2:
				this->model.position.y = this->model.position.y + this->speed;
				break;
			}
			this->model.position.direction = direction;
		}

		void _to() {
			if (this->collision.current != 1) {
				if (this->model.to.x >= 0 + this->speed && this->model.to.x <= this->model.client.w - this->model.position.w - this->speed) {
					this->model.previous._set(this->model.position);
					this->model.position.x = this->model.to.x;
					this->model.position.direction = this->model.to.direction;
				}
				if (this->model.to.y >= this->speed && this->model.to.y <= this->model.client.h - this->model.position.h - this->speed) {
					this->model.previous._set(this->model.position);
					this->model.position.y = this->model.to.y;
					this->model.position.direction = this->model.to.direction;
				}
			}
		}

		void _draw(HDC tool) {
			switch (this->collision.current) {
			default:
				this->model.pixel.color._set(this->model.color);
				break;
			case 1:
				this->model.pixel.color._set({ 255, 0, 0, });
				break;
			}
			this->model.pixel._rect(tool, this->model.position.x, this->model.position.y, this->model.position.w, this->model.position.h);
		}

		DINT _collision(DUS dus) {
			if (
				this->model.to.x <= dus.model.position.x + dus.model.position.w &&
				this->model.to.y <= dus.model.position.y + dus.model.position.h &&
				this->model.to.x + this->model.to.w >= dus.model.position.x &&
				this->model.to.y + this->model.to.h >= dus.model.position.y
				) {
				this->collision.current = 1;
				this->collision.collie = (SINT)dus.unique;
			}
			return this->collision.current;
		}

		DINT _collive(LIST <DUS> *list) {
			this->collision.current = 0;
			DINT ll = list->length;
			for (DINT d = 0; d < ll; d++) {
				if (list->existance[d] == 1) {
					if (list->item[d].unique != this->unique) {
						this->collision.current = this->_collision(list->item[d]);
						
					}
				}
				else {
					ll++;
				}
			}
			return this->collision.current;

		}

		DINT _collect(LIST <DUS> *list) {
			DINT ll = list->length;
			for (DINT l = 0; l < ll; l++) {
				if (list->existance[l] == 1) {
					this->target._set(list->item[l].unique);
					break;
				}
				else {
					if (ll < 256) ll++;
				}
			}
			return 0;
		}

	};

	GAME() {
		this->played = 0;
		this->sleep = 0;
		this->window = 0;
	};
	~GAME() {};
	DINT played, sleep;
	RANDOM dice;
	STATISTICS statistics;
	TIME time, current;
	LIST <DUS> dus, carrier, building, resource;
	HWND window;
	DIMENSION client;

	void _carriage() {
		this->carrier._deconstruct();
		for (DINT d = 0; d < ENGINE_DUS_AMOUNT; d++) {
			if (this->dus.existance[d] == 1) this->carrier._set(this->dus.item[d]);
		}
		for (DINT b = 0; b < 256; b++) {
			if (this->building.existance[b] == 1) this->carrier._set(this->building.item[b]);
		}
		for (DINT r = 0; r < ENGINE_DUS_RESOURCE_AMOUNT; r++) {
			if (this->resource.existance[r] == 1) this->carrier._set(this->resource.item[r]);
		}

	}

	DUS _locate(DINT unique) {
		for (DINT c = 0; c < this->carrier.length; c++) {
			if (this->carrier.existance[c] == 1) {
				if (this->carrier.item[c].unique == unique) return this->carrier.item[c];
			}
		}
		DUS dummy;
		return dummy;
	}

	void _generate(DUS dus, DINT list = ENGINE_DUS_LIST_CREATURE) {
		dus.model._set(dus.dice._roll(0, this->client.w - dus.model.position.w), dus.dice._roll(0, this->client.h - dus.model.position.h), dus.model.position.w, dus.model.position.h);
		dus.model.client._set(this->client);

		SINT u;
		do {
			u = 0;
			dus.unique = dus.dice._roll(0, 999);
			for (DINT c = 0; c < this->carrier.length; c++) {
				if (this->carrier.existance[c] == 1) {
					if (dus.unique == this->carrier.item[c].unique) {
						u = -1;
					}
				}
			}
		} while (u == -1);
		this->_carriage();
		switch (list) {
		default:
			break;
		case ENGINE_DUS_LIST_CREATURE:
			this->dus._set(dus);
			break;
		case ENGINE_DUS_LIST_RESOURCE:
			this->resource._set(dus);
			break;
		case ENGINE_DUS_LIST_BUILDING:
			this->building._set(dus);
			break;
		}
	}

	void _update() {
		this->_carriage();
		this->dus.item[0]._update();
		if (this->resource.length > 0) {
			if (this->dus.item[0].target.unique == -1) {
				this->dus.item[0]._collect(&this->resource);
			}
			else {
				this->dus.item[0]._towards(this->_locate(this->dus.item[0].target.unique).model.position);
			}
				
		}
		else {
			this->dus.item[0]._move();
		}
		this->dus.item[0]._collive(&this->carrier);
		if (this->dus.item[0].collision.current == 1) {
			if (this->dus.item[0].collision.collie == this->dus.item[0].target.unique) {
				this->dus.item[0].directed.current = 0;
				DINT rl = this->resource.length;
				for (DINT r = 0; r < rl; r++) {
					if (this->resource.existance[r] == 1) {
						if (this->resource.item[r].unique == this->dus.item[0].target.unique) {
							this->resource._remove(r);
							this->dus.item[0].collision._reset();
							this->dus.item[0].target._reset();
							this->_carriage();
							break;
						}
					}
					else {
						if(rl < 256) rl--;
					}
				}
				//for(DINT c = 0; c < this->carrier.length; )
			}
			else {
				switch (this->dus.item[0].model.to.direction) {
				default:
					this->dus.item[0].collision._reset();
					break;
				case 1:
					this->dus.item[0]._direct(6);
					break;
				case 3:
				case 7:
					this->dus.item[0]._direct(2);
					break;
				case 2:
					this->dus.item[0]._direct(9);
					break;
				case 4:
					this->dus.item[0]._direct(2);
					break;
				case 9:
				case 6:
					this->dus.item[0]._direct(2);
					break;
				case 8:
					this->dus.item[0]._direct(1);
					break;
				}
				//this->dus.item[0].collision.current = 0;
				this->dus.item[0].directed.current++;
				this->dus.item[0]._collive(&this->carrier);
			}
		}
		this->dus.item[0]._to();
		//this->dus.item[0]._towards(this->_locate(this->dus.item[0].target.unique).model.position);
		for (DINT d = 1; d < this->dus.length; d++) {
			//this->dus.item[d]._towards(this->building.model.position);
			//this->_carriage();
			this->dus.item[d]._update();
			if (this->dus.item[d].collision.current == 0) {
				this->dus.item[d]._move();
			}
			else {
				this->dus.item[d].model.to._set(this->dus.item[d].model.previous);
			}
			this->dus.item[d]._collive(&this->carrier);
			this->dus.item[d]._to();
			this->dus.item[d].collision._reset();
		}
	}

	DINT _play() {
		if (this->dus.length < ENGINE_DUS_AMOUNT) {
			switch (this->dice._roll(0, 2)) {
			default:
				break;
			case 0:
				this->_generate(ENGINE_DUS_SAMPLE, ENGINE_DUS_LIST_CREATURE);
				break;
			case 1:
				this->_generate(ENGINE_DUS_DEFENSE, ENGINE_DUS_LIST_CREATURE);
				break;
			}
		}
		if (this->building.length < ENGINE_DUS_BUILDING_AMOUNT) {
			this->_generate(ENGINE_DUS_BUILDING, ENGINE_DUS_LIST_BUILDING);
		}
		if (this->resource.length < ENGINE_DUS_RESOURCE_AMOUNT) {
			switch (this->dice._roll(0, 99)) {
			default:
				break;
			case 0:
				this->_generate(ENGINE_DUS_DIRT, ENGINE_DUS_LIST_RESOURCE);
				break;
			}
		}
		this->_update();
		this->statistics.loop.current++;
		this->current._difference(this->time);
		if (this->statistics.loop.current > 0 && this->current.elapsed > 0) this->statistics.fps.current = (DINT)(this->statistics.loop.current / this->current.elapsed);
		if(ENGINE_MODE_SLEEP) Sleep(17);
		return this->played;
	}
};