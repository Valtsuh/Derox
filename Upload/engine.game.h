struct GAME {

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
		DINT speed, unique, exist;
		RANDOM dice;
		COLLISION collision;
		STRING name;
		
		void _towards(DIMENSION to) {
			if (this->model.position.x < to.x) this->model.to.x = this->model.position.x + this->speed;
			if (this->model.position.x > to.x) this->model.to.x = this->model.position.x - this->speed;
			if (this->model.position.y < to.y) this->model.to.y = this->model.position.y + this->speed;
			if (this->model.position.y > to.y) this->model.to.y = this->model.position.y - this->speed;
		}

		void _move() {
			switch (this->dice._roll(0, 16)) {
			default:
				//this->model.to.x = this->model.position.x + this->speed;
				break;
			case 4:
				this->model.to.x = this->model.position.x - this->speed;
				break;
			case 5:
				this->model.to.x = this->model.position.x + this->speed;
				break;
			case 6:
				this->model.to.y = this->model.position.y - this->speed;
				break;
			case 7:
				this->model.to.y = this->model.position.y + this->speed;
				break;
			}
		}

		void _to() {
			if (this->collision.current != 1) {
				if (this->model.to.x >= 0 + this->speed && this->model.to.x <= this->model.client.w - this->model.position.w - this->speed) {
					this->model.position.x = this->model.to.x;
				}
				if (this->model.to.y >= this->speed && this->model.to.y <= this->model.client.h - this->model.position.h - this->speed) {
					this->model.position.y = this->model.to.y;
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
			this->collision._reset();
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

			for (DINT d = 0; d < list->length; d++) {
				if (list->existance[d] == 1) {
					if(list->item[d].unique != this->unique) this->collision.current = this->_collision(list->item[d]);
				}
			}
			return this->collision.current;

		}

		DINT _collect(LIST <DUS> *list) {
			if (this->collision.collie == -1) {
				for (DINT l = 0; l < list->length; l++) {

				}
			}
			return 0;
		}

	};

	GAME() {
		this->played = 0;
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
		for (DINT d = 0; d < this->dus.length; d++) {
			if (this->dus.existance[d] == 1) this->carrier._set(this->dus.item[d]);
		}
		for (DINT b = 0; b < this->building.length; b++) {
			if (this->building.existance[b] == 1) this->carrier._set(this->building.item[b]);
		}
		for (DINT r = 0; r < this->resource.length; r++) {
			if (this->resource.existance[r] == 1) this->carrier._set(this->resource.item[r]);
		}

	}


	void _generate(DUS dus, DINT list = ENGINE_DUS_LIST_CREATURE) {
		dus.model._set(dus.dice._roll(0, this->client.w), dus.dice._roll(0, this->client.h), dus.model.position.w, dus.model.position.h);
		dus.model.client._set(this->client);

		SINT u;
		this->_carriage();
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
		if(this->resource.length > 0) this->dus.item[0]._collect(&this->resource);
		for (DINT d = 1; d < this->dus.length; d++) {
			//this->dus.item[d].collision._reset();
			this->dus.item[d]._move();
			//this->dus.item[d]._towards(this->building.model.position);
			this->_carriage();
			this->dus.item[d]._collive(&this->carrier);
			this->dus.item[d]._to();
		}
	}

	DINT _play() {
		if (this->dus.length < ENGINE_DUS_AMOUNT) {
			this->_generate(ENGINE_DUS_SAMPLE, ENGINE_DUS_LIST_CREATURE);
		}
		if (this->building.length < 1) {
			this->_generate(ENGINE_DUS_BUILDING, ENGINE_DUS_LIST_BUILDING);
		}
		if (this->resource.length < 2) {
			this->_generate(ENGINE_DUS_DIRT, ENGINE_DUS_LIST_RESOURCE);
		}
		this->_update();
		this->statistics.loop.current++;
		this->current._difference(this->time);
		if (this->statistics.loop.current > 0 && this->current.elapsed > 0) this->statistics.fps.current = (DINT)(this->statistics.loop.current / this->current.elapsed);
		//Sleep(16);
		return this->played;
	}
};