struct GAME {
	struct STATISTICS{
		STATISTICS() {};
		~STATISTICS() {};
		COUNTER loop, fps;
		TIME time, current, tick;
		void _loop() {
			this->loop.current++;
			this->current._difference(this->time);
			if (this->loop.current > 0 && this->current.elapsed > 0) this->fps.current = (DINT)(this->loop.current / this->current.elapsed);
			this->tick._clock();
		}

	};
	struct CONFIG {
		CONFIG() {};
		~CONFIG() {};

		DIMENSION map, atlas;
	};
	struct COLLISION {
		COLLISION() {
			this->current = 0;
			this->collie = -1;
			this->collided = 0;
			this->type = 0;
			this->last = -1;
		};
		~COLLISION() {};
		DINT current, collided, type;
		SINT collie, last;


		void _reset() {
			this->current = 0;
			this->collie = -1;
			this->collided = 0;
			this->type = 0;
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
		DUS(double identifier = 0.0, const char name[] = "Undefined", DINT health = 0) {
			this->identifier = identifier;
			this->name._write(name);
			this->health = health;
			this->amount = 0;
			this->size = this->dice._droll(5.0, 10.0);
			this->type = this->dice._roll(0, 2);
			this->spot = { this->dice._droll(0.0, 50.0), this->dice._droll(0.0, 50.0), 0 };
			this->direction = this->dice._droll(-10.0, 10.0);
			this->dice._roll(0, 3);
			switch (this->dice.value.i) {
			default:
				this->color = B;
				break;
			case 0:
				this->color = R;
				break;
			case 1:
				this->color = G;
				break;
			case 2:
				this->color = BL;
				break;
			case 3:
				this->color = Y;
				break;
			}
			this->angle = this->dice._droll(0, 359.0);

		};
		~DUS() {
			this->identifier = 0.0;
			this->name.~STRING();
			this->health = 0;
			this->amount = 0;
		};

		double identifier, size, angle, direction;
		STRING name;
		DICE dice;
		DINT health, amount, type;
		COLOR color;
		SPOT spot;

		void _draw(HDC tool) {
			switch (this->type) {
			default:
				break;
			case 0: {
				CRCL circle = { 400.0 + this->spot.x, 150.0 + this->spot.y, this->size, this->angle, this->color };
				circle._draw(tool);
				break;
			}
			case 1: {
				LINE line = { 400.0 + this->spot.x, 150.0 + this->spot.y, this->size, this->angle, this->color, 1 };
				line._draw(tool);
				break;
			}
			case 2: {
				SQUARE square = { 400.0 + this->spot.x, 150.0 + this->spot.y, this->size * 2.0, this->angle, this->color };
				square._draw(tool);
				delete[] square.lines.item;
				delete[] square.lines.exist;
				break;
			}
			}
		}
	};
	struct ITEM {
		ITEM(double identifier = 0.0, const char name[] = "Undefined") {
			this->identifier = identifier;
			this->amount = 0;
			this->name._write(name);
			this->type = 0;
		};
		~ITEM() {
			this->identifier = 0.0;
			this->amount = 0;
			this->type = 0;
			this->name.~STRING();
		};

		double identifier;
		DINT amount, type;
		STRING name;

		void _trash() {
			this->~ITEM();
			*this = {};
		}
	};
	struct INVENTORY {
		INVENTORY() {};
		~INVENTORY() {};

		CHART <ITEM> items;

		
		void _gather(ITEM item) {
			DINT found = 0;
			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.exist[i] == 1) {
					if (this->items.item[i].type == item.type) {
						found = 1;
						this->items.item[i].amount += item.amount;
					}
				}
			}
			if (found == 0) {
				this->items << item;
			}
		}

		DINT _reduce(DINT type, DINT amount) {
			DINT found = 0;
			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.exist[i] == 1) {
					if (this->items.item[i].type == type) {
						found = 1;
						this->items.item[i].amount -= amount;
					}
				}
			}
			return (found == 1) ? (1) : (0);
		}

		DINT _available(DINT type = 0) {
			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.exist[i] == 1) {
					if (this->items.item[i].type == type) {
						if (this->items.item[i].amount > 0) return this->items.item[i].amount;
					}
				}
			}
			return 0;
		}

		void _empty() {

			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.exist[i] == 1) {
					this->items.item[i]._trash();
					this->items.exist[i] = 0;
				}
			}
			delete[] this->items.item;
			delete[] this->items.exist;
		}

	};
	struct EFFECT {
		EFFECT() {
			this->length = 0;
			this->type = 0;
			this->exist = 0;
			this->pixel.x = 0;
			this->pixel.y = 0;

		};
		~EFFECT() {
			this->length = 0;
			this->type = 0;
			this->exist = 0;
		};
		DINT length, type, exist;
		PIXEL pixel;
	};
	struct STATUS {
		STATUS() {
			this->immune = 0;
		};
		~STATUS() {};

		DINT immune;
	};
	struct LIMB {
		LIMB(double identifier = 0.0, const char name[] = "Undefined", DINT health = 0, SPRT sprite = {}) {
			this->identifier = identifier;
			this->name._write(name);
			this->health.total = health;
			this->health.current = this->health.total;
			this->exist = 0;
			this->sprite = sprite;
			this->amount = (health > 0) ? (1) : (0);
		};
		~LIMB() {
			this->identifier = 0.0;
			this->name.~STRING();
			this->health.~COUNTER();
			this->exist = 0;
			//this->sprite.~SPRITE();
			this->position.~DIMENSION();
		};
		double identifier;
		STRING name;
		COUNTER health;
		DINT exist, amount;
		SPRT sprite;
		DIMENSION position;
		STATUS status;

		void _loose() {
			this->~LIMB();
			*this = {};
		}
	};
	struct CARCASS {
		CARCASS() {};
		~CARCASS() {
		};
		COUNTER health;
		CHART <LIMB> limbs;
		DIMENSION position;
		void _dismantle() {
			for (DINT l = 0; l < this->limbs.length; l++) {
				if (this->limbs.exist[l] == 1) {
					this->limbs.item[l]._loose();
					this->limbs.exist[l] = 0;
				}
			}
			this->health.~COUNTER();
		}


		DINT _health() {
			this->health.current = 0;
			this->health.total = 0;
			for (DINT i = 0; i < this->limbs.length; i++) {
				this->health.current += this->limbs[i].health.current;
				this->health.total += this->limbs[i].health.total;
			}
			return this->health.current;
		}

		SINT _exist(double identifier) {
			for (DINT i = 0; i < this->limbs.length; i++) {
				if (this->limbs[i].identifier == identifier) return i;
			}
			return -1;
		}
	};
	struct EXPERIENCE {
		EXPERIENCE() {
			this->point = {};
			this->level = {};
		};
		~EXPERIENCE() {};
		COUNTER point, level;

		void _gain(DINT amount = 0) {
			this->point._add(amount);
			SINT up = (5 * this->level.current + 8);
			if(this->point.current >= up){
				if (this->point.current > up) {
					this->point.current -= up;
				}
				else {
					this->point.current = 0;

				}
				this->level._add(1);
			}
		} 
	};
	struct BASIS {
		BASIS(double identifier = 0.0, const char name[] = "Undefined", DUS dus = {}, DINT type = 0.0, ANM animation = {}, DINT scale = 2, DINT width = 5, DINT height = 5, DINT speed = 5) {
			this->model.animation = animation;
			this->model.position.w = width;
			this->model.position.h = height;
			this->model.position.size = scale;
			this->speed = speed;
			this->name._write(name);
			this->type = type;
			this->identifier = identifier;
			this->origin = dus;
			this->unique = 0;
			this->temp = -1;
		};
		~BASIS() {};

		double identifier;
		STRING name;
		COUNTER health, speed;
		DINT unique, type;
		SINT temp;
		MDL model;
		DIMENSION position;
		DICE dice;
		DUS origin;
		CARCASS animate;
		COUNTER loop;

		void _base(BASIS basis) {
			this->model = basis.model;
			this->speed = basis.speed;
			this->type = basis.type;
			this->name = basis.name;
			this->origin = basis.origin;
			this->identifier = basis.identifier;
			this->unique = basis.unique;
			this->dice._roll(0, 3);

			switch (this->dice.value.i) {
			default:
				break;
			case 0:
				this->_develop(ENGINE_BIONIC);
				break;
			case 1:
				this->_develop(ENGINE_CARCASS);
				break;
			case 2:
				this->_develop(ENGINE_BOTANY);
				break;
			case 3:
				this->_develop(ENGINE_MIRAGE);
				break;
			}
		}


		COLLISION _collision(DIMENSION bp) {
			DIMENSION ap = this->model.position;
			COLLISION collision = {};
			switch (this->model.facing) {
			case 2:
				// Down
				if (
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.y < bp.y &&
					ap.x < bp.x + (bp.w * bp.size) &&
					ap.x + (ap.w * ap.size) > bp.x
					) {
					collision.collided = 1;
				}
				break;
			case 4:
				// Left
				if (
					ap.x <= bp.x + (bp.w * bp.size) &&
					ap.x + (ap.w * ap.size) > bp.x &&
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.y < bp.y + (bp.h * bp.size)
					) {
					collision.collided = 1;
				}
				break;
			case 6:
				// Right
				if (
					ap.x + (ap.w * ap.size) >= bp.x &&
					ap.x < bp.x &&
					ap.y < bp.y + (bp.h * bp.size) &&
					ap.y + (ap.h * ap.size) > bp.y
					) {
					collision.collided = 1;
				}
				break;
			case 8:
				// Up
				if (
					ap.y < bp.y + (bp.h * bp.size) &&
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.x + (ap.w * ap.size) > bp.x &&
					ap.x < bp.x + (bp.w * bp.size)
					) {
					collision.collided = 1;
				}
				break;
			}
			return collision;
		}

		void _develop(LIMB limb) {
			SINT exist = this->animate._exist(limb.identifier);
			if (exist >= 0) {
				this->animate.limbs[exist].amount++;
				this->animate.limbs[exist].health.current += limb.health.total;
				this->animate.limbs[exist].health.total += limb.health.total;
			}
			else {
				this->animate.limbs << limb;
			}
			this->health.total += limb.health.total;
		}
	};
	struct RESOURCE : BASIS {
		RESOURCE() {
			this->item.amount = 0;
			this->item.identifier = this->identifier;
		};
		~RESOURCE() {
		};
		ITEM item;

		void _draw(HDC tool) {
			this->model._draw(tool);
		}

		void _decay() {
			if (this->animate.limbs.length > 0) {
				for (DINT i = 0; i < this->animate.limbs.length; i++) {
					delete[] this->animate.limbs[i].sprite.pixels.exist;
					delete[] this->animate.limbs[i].sprite.pixels.item;
				}
				delete[] this->animate.limbs.item;
				delete[] this->animate.limbs.exist;
			}
			if (this->model.animation.sprites.length > 0) {
				for (DINT i = 0; i < this->model.animation.sprites.length; i++) {
					delete[] this->model.animation.sprites[i].pixels.exist;
					delete[] this->model.animation.sprites[i].pixels.item;
				}
				delete[] this->model.animation.sprites.item;
				delete[] this->model.animation.sprites.exist;
			}
			//this->model.~MODEL();
		}
	};
	struct CREATURE : BASIS {
		CREATURE() {
		};
		~CREATURE() {

		};
		EXPERIENCE experience;
		COLLISION collision;
		INVENTORY inventory;
		EFFECT effect;
		CHART <DUS> mutation;
		TARGET target;
		TIME appearance;

		void _update() {
			this->loop.current++;
			DUS* d;
			for (DINT m = 0; m < this->mutation.length; m++) {
				if (this->mutation.exist[m]) {
					d = &this->mutation[m];
					d->angle += d->direction;
					if (d->angle >= 360.0) {
						d->angle -= 360.0;
					}
					else {
						if (d->angle <= -360.0) {
							d->angle += 360.0;
						}
					}

				}
			}
		}
		void _use(DINT type = 0) {
			switch (type) {
			default:
				break;
			case ENGINE_TYPE_RESOURCE_BERRY:
				this->_heal(2);
				this->inventory._reduce(type, 1);
				break;
			}
		}

		void _draw(HDC tool) {

			// Health
			DINT px = 0, py = 0;
			PIXEL pixel = {};
			COLOR h;
			SPRT sprite = this->model.animation.sprites[this->model.animation.stage];
			if (this->health.total > 0) {
				double temp = (double)this->health.total / (double)this->model.position.w;
				for (DINT w = 0; w < this->model.position.w; w++) {
					px = this->model.position.x + w * this->model.position.size;
					py = this->model.position.y - (1 * this->model.position.size);

					if (this->effect.exist == 1) {
						switch (this->effect.type) {
						default:
							switch (this->dice._roll(0, 2)) {
							default:
								h = G;
								break;
							case 1:
								h = DG;
								break;
							case 2:
								h = LG;
								break;
							}
							break;
						case ENGINE_TYPE_EFFECT:
							break;
						}
					}
					else {
						h = G;
					}

					if (this->health.current == this->health.total) {
						pixel.color._set(h);
					}
					else {
						if (((double)w + 0.1) * temp <= (double)this->health.current) {
							pixel.color._set(h);
						}
						else {
							pixel.color._set(R);
						}
					}
					pixel._scale(tool, px, py, this->model.position.size);
				}
			}

			// Sprite
			this->model._draw(tool);

			// Effect
			if (this->effect.exist == 1) {
				px = this->model.position.x + this->effect.pixel.x * this->model.position.size;
				py = this->model.position.y + this->effect.pixel.y * this->model.position.size;
				this->effect.pixel.color = DG;
				this->effect.pixel._scale(tool, px, py, this->model.position.size);
				this->effect.pixel.x++;
				//this->effect.pixel.y++;
				if (this->effect.pixel.x == this->model.position.w) this->effect.pixel.x = 0;
				if (this->effect.pixel.y == this->model.position.h) this->effect.pixel.y = 0;
			}
		}

		DINT _distance(BASIS basis) {

		}
		void _gain(DUS dus) {
			SINT has = this->_has(dus);
			if (has >= 0) {
				this->mutation[has].amount++;
			}
			else {
				this->mutation << dus;
			}
			this->health.total += dus.health;
			//switch(dus.)
		}

		SINT _has(DUS dus) {
			for (DINT m = 0; m < this->mutation.size; m++) {
				if (this->mutation.exist[m] == 1) {
					if (this->mutation.item[m].identifier == dus.identifier) return m;
				}
			}
			return -1;
		}

		void _vanish() {
			if (this->inventory.items.length > 0) {
				delete[] this->inventory.items.item;
				delete[] this->inventory.items.exist;
			}
			//this->inventory.items._clear();
			if (this->mutation.length > 0) {
				delete[] this->mutation.item;
				delete[] this->mutation.exist;
			}

			if (this->animate.limbs.length > 0) {
				for (DINT i = 0; i < this->animate.limbs.length; i++) {
					delete[] this->animate.limbs[i].sprite.pixels.exist;
					delete[] this->animate.limbs[i].sprite.pixels.item;
				}
				delete[] this->animate.limbs.item;
				delete[] this->animate.limbs.exist;
			}
			if (this->model.animation.sprites.length > 0) {
				for (DINT i = 0; i < this->model.animation.sprites.length; i++) {
					delete[] this->model.animation.sprites[i].pixels.exist;
					delete[] this->model.animation.sprites[i].pixels.item;
				}
				delete[] this->model.animation.sprites.item;
				delete[] this->model.animation.sprites.exist;
			}
			//this->mutation._clear();


		}
		void _heal(DINT amount) {
			if (this->health.current < this->health.total) {
				for (DINT i = 0; i < this->animate.limbs.length; i++) {
					if (this->animate.limbs.exist[i]) {
						LIMB* l = &this->animate.limbs[i];
						if (l->health.current < l->health.total) {
							l->health.current += amount;
							if (l->health.current > l->health.total) l->health.current = l->health.total;
							break;
						}
					}
				}
				this->health.current = this->animate._health();
			}
		}
		void _damage(DINT amount) {
			SINT identifier = -1;
			LIMB* limb = {};
			do {
				identifier = -1;
				this->dice._roll(0, this->animate.limbs.length);
				if (this->animate.limbs.exist[this->dice.value.i]) {
					limb = &this->animate.limbs[this->dice.value.i];
					if (limb->health.current > 0) {
						if (limb->status.immune != 1) {
							identifier = this->dice.value.i;
						}
					}
				}
				
			} while (identifier == -1);

			limb->health.current -= amount;
			//if (limb->health.current < 0) limb->health.current = 0;
			this->health.current = this->animate._health();

		}
	};
	struct TERRAIN {
		TERRAIN() {
			this->type = 0;
			this->directed = 0;
			//this->sprite = ENGINE_MAP_BACKGROUND_NONE;
			this->count = 0;
		};
		~TERRAIN() {
			this->type = 0;
			this->directed = 0;
			/*
			this->sprite.~SPRITE();
			this->n.~SPRITE();
			this->s.~SPRITE();
			this->w.~SPRITE();
			this->e.~SPRITE();
			*/
		};
		DIMENSION position, measure;
		DINT type, directed, count;
		GROUND sprt;

	};
	struct MAP {
		MAP() {
			this->count = 0;
		};
		~MAP() {};

		DICE dice;
		ITEM loot;
		DIMENSION measure, position;
		CHART <TERRAIN> terrain;
		DINT count;
		TIME timer;
		void _set() {
			TERRAIN *terrain;
			DINT count = 0;
			this->timer._clock();
			this->terrain = this->position.w * this->position.h;
			for (DINT x = 0; x < this->position.w; x++) {
				for (DINT y = 0; y < this->position.h; y++) {
					terrain = new TERRAIN;					
					switch (this->dice._roll(0, 6)) {
					default:
						terrain->type = ENGINE_TYPE_TILE_DESOLATE;
						terrain->sprt.color = LBR;
						break;
					case 2:
						terrain->type = ENGINE_TYPE_TILE_MEADOW;
						terrain->sprt.color = G;
						break;
					case 4:
						terrain->type = ENGINE_TYPE_TILE_SWAMP;
						terrain->sprt.color = BLG;
						break;
					case 5:
						terrain->type = ENGINE_TYPE_TILE_WATER;
						terrain->sprt.color = BL;
						break;
					}
					terrain->sprt._set(terrain->type, -1);
					//terrain->sprite._position(0, 0);
					terrain->measure.x = x;
					terrain->measure.y = y;
					terrain->position.x = x;
					terrain->position.y = y;
					terrain->position.w = this->measure.x + terrain->measure.x * (this->measure.size * terrain->sprt.size.w);
					terrain->position.h = this->measure.y + terrain->measure.y * (this->measure.size * terrain->sprt.size.h);
					terrain->count = count + (this->count * (this->position.w * this->position.h));
					this->terrain << *terrain;
					delete terrain;
					count++;
				}
			}
			/*
			DINT test = this->dice._roll(1, 2);
			SINT x = this->dice._roll(0, this->position.w - 1);
			SINT y = this->dice._roll(0, this->position.h - 1);
			DINT tile = 0;
			DINT type = ENGINE_TYPE_TILE_TEST;
			COLOR c = LGR;
			TERRAIN* current = this->_get(x, y);
			current->type = type;
			current->sprt._color(c);
			std::cout << "\n>" << current->position.x << ", " << current->position.y;
			std::cout << " - " << x << ", " << y;
			for(DINT tile = 0; tile < test; tile++){
				switch (this->dice._roll(1, 4)) {
				default:
					break;
				case 1:
					x = current->position.x + 1;
					y = current->position.y - 1;
					current = this->_get(x, y);
					if (current->type != -1) {
						current->type = ENGINE_TYPE_TILE_TEST;
						current->sprt._color(c);
					}
					else {
						//current->position.x = x - 1;
						//current->position.y = y + 1;
					}

					break;
				case 4:
					x = current->position.x - 1;
					y = current->position.y;
					current = this->_get(x, y);
					if (current->type != -1) {
						current->type = ENGINE_TYPE_TILE_TEST;
						current->sprt._color(c);
					}
					else {
						//current->position.x = x - 1;
					}
				}
				std::cout << "\n>" << current->position.x << ", " << current->position.y;
				std::cout << " - " << x << ", " << y;
			}
			system("pause");
			*/
			TERRAIN *tr;
			for (DINT t = 0; t < this->terrain.length; t++) {
				if (this->terrain.exist[t]) {
					tr = &this->terrain[t];
					SINT pos = -1;
					SINT w = this->_type(tr->position.x - 1, tr->position.y), e = this->_type(tr->position.x + 1, tr->position.y);
					SINT n = this->_type(tr->position.x, tr->position.y - 1), s = this->_type(tr->position.x, tr->position.y + 1);
					SINT nw = this->_type(tr->position.x - 1, tr->position.y - 1), ne = this->_type(tr->position.x + 1, tr->position.y - 1);
					SINT sw = this->_type(tr->position.x - 1, tr->position.y + 1), se = this->_type(tr->position.x + 1, tr->position.y + 1);
					
					if (n == tr->type) {
						if (s == tr->type) {
							if (e == tr->type) {
								if (w == tr->type) {
									if (nw != tr->type) {
										if (ne != tr->type) {
											if (sw != tr->type) {
												if (se != tr->type) {
													tr->sprt._set(tr->type, 501);
												}
												else {
													tr->sprt._set(tr->type, 502);
												}
											}
											else {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 503);
												}
												else {
													tr->sprt._set(tr->type, 504);
												}
											}
										}
										else {
											if (sw == tr->type) {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 505);
												}
												else {
													tr->sprt._set(tr->type, 506);
												}
											}
											else {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 507);
												}
												else {
													tr->sprt._set(tr->type, 508);
												}
											}
										}
									}
									else {
										if (ne == tr->type) {
											if (sw == tr->type) {
												if (se == tr->type) {
													//tr->sprt._set(tr->type, 509); center (5)
												}
												else {
													tr->sprt._set(tr->type, 509);
												}
											}
											else {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 510);
												}
												else {
													tr->sprt._set(tr->type, 511);
												}
											}
										}
										else {
											if (sw == tr->type) {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 512);
												}
												else {
													tr->sprt._set(tr->type, 513);
												}
											}
											else {
												if (se == tr->type) {
													tr->sprt._set(tr->type, 514);
												}
												else {
													tr->sprt._set(tr->type, 515);
												}
											}
										}
									}
								}
								else {
									if (ne == tr->type) {
										if (se == tr->type) {
											tr->sprt._set(tr->type, 4);
										}
										else {
											tr->sprt._set(tr->type, 41);
										}
									}
									else {
										if (se == tr->type) {
											tr->sprt._set(tr->type, 42);
										}
										else {
											tr->sprt._set(tr->type, 43);
										}
									}
								}
							}
							else {
								if (w == tr->type) {
									if (nw == tr->type) {
										if (sw == tr->type) {
											tr->sprt._set(tr->type, 6);
										}
										else {
											tr->sprt._set(tr->type, 61);
										}
									}
									else {
										if (sw == tr->type) {
											tr->sprt._set(tr->type, 62);
										}
										else {
											tr->sprt._set(tr->type, 63);
										}
									}
								}
								else {
									tr->sprt._set(tr->type, 101);
								}
							}
						}
						else {
							if (s != tr->type) {
								if (e != tr->type) {
									if (w != tr->type) {
										tr->sprt._set(tr->type, 12);
									}
									else {
										if (nw == tr->type) {
											tr->sprt._set(tr->type, 3);
										}
										else {
											tr->sprt._set(tr->type, 31);
										}
									}
								}
								else {
									if (w == tr->type) {
										if (nw == tr->type) {
											if (ne == tr->type) {
												tr->sprt._set(tr->type, 2);
											}
											else {
												tr->sprt._set(tr->type, 21);
											}
										}
										else {
											if (ne == tr->type) {
												tr->sprt._set(tr->type, 22);
											}
											else {
												tr->sprt._set(tr->type, 23);
											}
										}
									}
									else {
										if (ne == tr->type) {
											tr->sprt._set(tr->type, 1);
										}
										else {
											tr->sprt._set(tr->type, 11);
										}
									}
								}
							}
						}
					}
					else {
						if (s != tr->type) {
							if (e != tr->type) {
								if (w != tr->type) {
									tr->sprt._set(tr->type, 0);
								}
								else {
									tr->sprt._set(tr->type, 16);
								}
							}
							else {
								if (w != tr->type) {
									tr->sprt._set(tr->type, 14);
								}
								else {
									tr->sprt._set(tr->type, 102);
								}
							}
						}
						else {
							if (e != tr->type) {
								if (w != tr->type) {
									tr->sprt._set(tr->type, 18);
								}
								else {
									if (sw == tr->type) {
										tr->sprt._set(tr->type, 9);
									}
									else {
										tr->sprt._set(tr->type, 91);
									}
								}
							}
							else {
								if (w == tr->type) {
									if (sw == tr->type) {
										if (se == tr->type) {
											tr->sprt._set(tr->type, 8);
										}
										else {
											tr->sprt._set(tr->type, 81);
										}
									}
									else {
										if (se == tr->type) {
											tr->sprt._set(tr->type, 82);
										}
										else {
											tr->sprt._set(tr->type, 83);
										}
									}
								}
								else {
									if (se == tr->type) {
										tr->sprt._set(tr->type, 7);
									}
									else {
										tr->sprt._set(tr->type, 71);
									}
								}
							}
						}
					}

					//std::cout << "\n>" << tr->type << ": " << tr->position.x << ", " << tr->position.y;
					//std::cout << " - " << tr->sprt.color.r << ", " << tr->sprt.color.g << ", " << tr->sprt.color.b;
				}
			}
			std::cout << "\n> Terrain set. " << this->timer._difference(this->timer);
			//system("pause");
		}

		void _draw(HDC tool, DINT scale = 2, DINT outline = 1) {
			/*
			auto w = [] (HDC tool, INDEX <TERRAIN> terrains, DIMENSION measure) {
				DINT x = 0, y = 0;
				TERRAIN terrain = {};
				PIXEL pixel = {};
				for (DINT s = 0; s < terrains.length; s++) {
					if (terrains.exist[s] == 1) {
						terrain = terrains.item[s];
						if (terrain.position.x == 0 && terrain.position.y == 0) {
							terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 7);
						}
						else {
							if (terrain.position.x == 0) {
								terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 4);
							}
							else {
								if (terrain.position.y == 0) {
									terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 8);
								}
								else {
									terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size);
								}
							}
						}
					}
				}
			};

			std::thread t(w, tool, this->terrain, this->measure);
			t.join(); DINT x = 0, y = 0;
			*/
			TERRAIN terrain = {};
			PIXEL pixel = {};
			/*
			auto w = [](HDC tool, TERRAIN terrain, DIMENSION measure) {
				if (terrain.position.x == 0 && terrain.position.y == 0) {
					terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 7);
				}
				else {
					if (terrain.position.x == 0) {
						terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 4);
					}
					else {
						if (terrain.position.y == 0) {
							terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size, 0, 0, 8);
						}
						else {
							terrain.sprite._draw(tool, terrain.position.w, terrain.position.h, measure.size);
						}
					}
				}
			};
			std::thread *threads = new std::thread[this->terrain.size];
			for (DINT s = 0; s < this->terrain.size; s++) {

				if (this->terrain.exist[s] == 1) {
					terrain = this->terrain.item[s];
					threads[s] = std::thread(w, tool, terrain, this->measure);
					threads[s].join();
				}
			}
			delete[] threads;
			*/
			for (DINT s = 0; s < this->terrain.length; s++) {
				if (this->terrain.exist[s] == 1) {
					terrain = this->terrain.item[s];
					//std::cout << "\n> " << s << ": " << terrain.sprt.color.r << ", " << terrain.sprt.color.g << ", " << terrain.sprt.color.b;
					terrain.sprt._draw(tool, terrain.position.w, terrain.position.h, this->measure.size);
				}
				
			}
		}

		SINT _type(SINT x, SINT y) {
			if (x < 0 || y < 0) return -1;
			for (DINT t = 0; t < this->terrain.length; t++) {
				if (this->terrain[t].position.x == x && this->terrain[t].position.y == y) return this->terrain[t].type;
			}
			return -1;
		}

		TERRAIN* _get(DINT x, DINT y) {
			TERRAIN tr;
			tr.type = -1;
			TERRAIN* ter = &tr;
			for (DINT t = 0; t < this->terrain.length; t++) {
				if (this->terrain.exist[t]) {
					ter = &this->terrain[t];
					if (ter->position.x == x && ter->position.y == y) return ter;

				}
			}
			return ter;
		}

	};
	struct ATLAS {
		ATLAS() {
			this->bg = ENGINE_COLOR_MAP_BACKGROUND;
			this->streak = 0;
			this->loops = 0;
			this->st = 0;
			std::cout << "\nAtlas constructor called.";
		};
		~ATLAS() {
			//this->maps.~INDEX();
			//this->creatures.~INDEX();
			//this->resources.~INDEX();
		};
		CHART <MAP> maps;
		CHART <CREATURE> creatures;
		CHART <RESOURCE> resources;
		COLOR bg;
		DIMENSION measure;
		DICE dice; 
		ITEM loot;
		DINT streak;
		STRING streaker;
		LINT st;
		DINT loops;

		void _a() {

			auto w = [](ATLAS a) {
				a._movement();
				a._update();
				return a;
			};
			std::future<ATLAS> at = std::async(w, *this);
			std::thread a(w, *this);
			a.join();
			*this = at.get();


		}

		void _pre(){
			TERRAIN* ter;
			for (DINT m = 0; m < this->maps.length; m++) {
				if (this->maps.exist[m]) {
					for (DINT t = 0; t < this->maps[m].terrain.length; t++) {
						if (this->maps[m].terrain.exist[t]) {
							ter = &this->maps[m].terrain[t];
							ter->sprt.occupied = 0;
							//ter->sprt.a = ter->sprt.oa;
							//ter->sprt.b = ter->sprt.ob;

						}
					}
				}
			}

			for (DINT c = 0; c < this->creatures.size; c++) {
				if (this->creatures.exist[c]) {
					this->creatures[c].speed.current = this->creatures[c].speed.total;
				}
			}
		}

		void _update() {

			if (this->creatures.length > 0) {
				for (DINT d = 0; d < this->creatures.length; d++) {
					if (this->creatures.exist[d] == 1) {
						CREATURE* a = &this->creatures.item[d];
						SINT type = this->_tile(a);
						switch (type) {
						default:
							break;
						case ENGINE_TYPE_TILE_SWAMP:
							//a->speed.current = 
							break;
						}
						//std::cout << "\nSpeed: " << a->speed.current;
						a->_update();
						if ((double)a->health.current <= (double)a->health.total / 2.0) {
							if (a->inventory._available(ENGINE_TYPE_RESOURCE_BERRY) > 0) {
								a->_use(ENGINE_TYPE_RESOURCE_BERRY);
							}
						}
					}
				}
			}
			if (this->resources.length > 0) {
				for (DINT r = 0; r < this->resources.length; r++) {
					if (this->resources.exist[r] == 1) {
						//this->resources.item[r]._update();
					}
				}
			}
		}

		COLLISION _collive(CREATURE a = {}) {
			COLLISION collision = {};
			if (this->creatures.length > 1) {
				CREATURE *b;				
				for (DINT c = 0; c < this->creatures.size; c++) {
					if (this->creatures.exist[c] == 1) {
						b = &this->creatures.item[c];
						//if (distance < x){
						if (b->unique != a.unique) {
							collision = a._collision(b->model.position);
							if (collision.collided == 1) {
								collision.type = ENGINE_TYPE_CREATURE;
								collision.collie = b->unique;
								break;
							}
						}
					}
				}
				
			}
			if (collision.collided == 0) {
				if (this->resources.length > 0) {					
					RESOURCE *c;
					for (DINT r = 0; r < this->resources.size; r++) {
						if (this->resources.exist[r] == 1) {
							c = &this->resources.item[r];
							collision = a._collision(c->model.position);
							if (collision.collided == 1) {
								collision.type = ENGINE_TYPE_RESOURCE;
								collision.collie = c->unique;
								this->loot = c->item;
								c->_decay();
								this->resources >> r;
								break;
							}
						}
					}
					
				}
			}
			return collision;
		}

		SINT _locate(DINT unique) {
			if (this->creatures.length > 0) {
				for (DINT c = 0; c < this->creatures.size; c++) {
					if (this->creatures.exist[c] == 1) {
						if (this->creatures.item[c].unique == unique) return c;
					}
				}
			}
			return -1;
		}

		void _event() {
			if(this->creatures.length > 1){
				if (this->creatures.item[0].target.type == 0) {
					//this->creatures.item[0].target._set(this->creatures.item[1].unique, ENGINE_TYPE_CREATURE);
				}
			}
		}

		void _movement() {
			DINT n = 0;
			COLLISION collision = {};
			CREATURE* a = {}, * b = {};
			if (this->creatures.length > 0) {
				do {
					if (this->creatures.exist[n] == 1) {
						if (this->creatures.item[n].speed.current > 0) {
							//SwitchToThread();
							a = &this->creatures.item[n];
							a->dice._roll(0, 8);
							a->model.collision = 0;
							a->model.type = 0;
							if(a->collision.collie >= 0) a->collision.last = a->collision.collie;
							a->collision._reset();
							//this->creatures.item[n].model.to._set(d.model.position);
							a->model.to._set(a->model.position);
							switch (a->dice.value.i) {
							default:
								break;
							case 2:
								a->model.facing = 2;
								if (a->model.position.y < (this->measure.h + this->measure.y - (a->model.position.size * a->model.position.h)) - a->speed.current) {
									a->model.to.y = a->model.position.y + a->speed.current;
								}
								else {
									a->model.to.y = this->measure.h + this->measure.y - (a->model.position.size * a->model.position.h);
								}
								break;
							case 4:
								a->model.facing = 4;
								if (a->model.position.x >= a->speed.current + this->measure.x) {
									a->model.to.x = a->model.position.x - a->speed.current;
								}
								else {
									a->model.to.x = this->measure.x;
								}
								break;
							case 6:
								a->model.facing = 6;
								if (a->model.position.x < (this->measure.w + this->measure.x - (a->model.position.size * a->model.position.w)) - a->speed.current) {
									a->model.to.x = a->model.position.x + a->speed.current;
								}
								else {
									a->model.to.x = this->measure.w + this->measure.x - (a->model.position.size * a->model.position.w);
								}
								break;
							case 8:
								a->model.facing = 8;
								if (a->model.position.y >= a->speed.current + this->measure.y) {
									a->model.to.y = a->model.position.y - a->speed.current;
								}
								else {
									a->model.to.y = this->measure.y;
								}
								break;
							}
							collision = this->_collive(*a);
							if (collision.collided == 0) {
								a->model.position._set(a->model.to);
								a->position._set(a->model.to);
							}
							else {
								//a->model.to._set(a->model.position);
								a->model.collision = 1;
								a->model.type = collision.type;
								a->collision = collision;
								switch (collision.type) {
								default:
									break;
								case ENGINE_TYPE_RESOURCE:
									if (this->loot.amount > 0) {
										a->inventory._gather(this->loot);
										this->loot = {};
									}
									break;
								case ENGINE_TYPE_CREATURE:
									a->temp = this->_locate(collision.collie);
									if (a->temp != -1) {
										b = &this->creatures.item[a->temp];
										a->dice._roll(0, 2);
										b->_damage(a->dice.value.i);
										//b->health.current -= a->dice.value.i;
										if (b->health.current <= 0) {
											if (b->experience.point.total > (SINT)this->streak) {
												this->streak = (DINT)b->experience.point.total;
												this->streaker._write(b->name.text);
												TIME time;
												this->st = (LINT)time._difference(b->appearance);
												this->loops = b->loop.current;
												std::cout << "\n>Streak (" << this->streak <<") time: " << this->st << " (" << this->loops << ") by " << this->streaker.text;
											}
											b->_vanish();
											this->creatures >> a->temp;
											a->experience._gain(1);
										}
									}
									break;
								}
							}
							

						}
					}
					n++;
				} while (n < this->creatures.size);
			}
		}

		void _appear(BASIS b = {}, SINT x = -1, SINT y = -1, SINT speed = -1) {
			x = (x > -1) ? (this->measure.x + x) : (b.dice._roll(this->measure.x, this->measure.x + this->measure.w - (b.model.position.size * b.model.position.w)));
			y = (y > -1) ? (this->measure.y + y) : (b.dice._roll(this->measure.y, this->measure.y + this->measure.h - (b.model.position.size * b.model.position.h)));
			//x = (x > -1) ? (this->measure.x + (x * 8)) : (b.dice._roll(0, 16));
			//x = (y > -1) ? (this->measure.y + (y * 8)) : (b.dice._roll(0, 16));
			b.model._set(x, y, b.model.position.size, b.model.position.w, b.model.position.h);
			INDEX <DINT> *uniques = new INDEX<DINT>;
			DINT found = 0;
			for (DINT c = 0; c < this->creatures.size; c++) {
				uniques->_add(this->creatures.item[c].unique);
			}
			for (DINT r = 0; r < this->resources.size; r++) {
				uniques->_add(this->resources.item[r].unique);
			}
			do {
				found = 0;
				b.dice._roll(1, uniques->size + 1);
				for (DINT u = 0; u < uniques->size; u++) {
					if (uniques->item[u] == b.dice.value.i) {
						found = 1;
					}
				}
			} while (found == 1);
			b.unique = b.dice.value.i;
			if (speed == 0) b.speed = 0;
			switch (b.type) {
				default: {
					break;
				}
				case ENGINE_TYPE_CREATURE: {
					CREATURE *c = new CREATURE;
					//b.speed = 16;
					b.name._generate(b.dice._roll(2, 8));
					c->_base(b);
					//c->health.total = b.origin.health;
					for (DINT d = 0; d < 3; d++) {
						c->dice._roll(0, 16);
						switch (c->dice.value.i) {
						default:
							c->_develop(ENGINE_CARCASS_CELL);
							break;
						case 1:
							c->_develop(ENGINE_BIONIC_ARM);
							break;
						case 2:
							c->_develop(ENGINE_BIONIC_FINGER);
							break;
						case 3:
							c->_develop(ENGINE_BIONIC_HAND);
							break;
						case 4:
							c->_develop(ENGINE_BOTANY_BRANCH);
							break;
						case 5:
							c->_develop(ENGINE_BIONIC_LEG);
							break;
						case 6:
							c->_develop(ENGINE_CARCASS_TISSUE);
							break;
						case 7:
							c->_develop(ENGINE_BOTANY_BLOOM);
							break;
						case 8:
							c->_develop(ENGINE_BIONIC_FOOT);
							break;
						case 9:
							c->_develop(ENGINE_BIONIC_TOE);
							break;
						}
					}
					c->health.current = c->health.total;
					c->_gain(ENGINE_DUS_TEST);
					c->appearance._clock();
					this->creatures << *c;
					delete c;
					break;
				}
				case ENGINE_TYPE_RESOURCE:
				case ENGINE_TYPE_RESOURCE_PLANT:
				case ENGINE_TYPE_RESOURCE_BERRY:
				case ENGINE_TYPE_RESOURCE_STONE:
				case ENGINE_TYPE_RESOURCE_CURRENCY:
				{
					RESOURCE *r = new RESOURCE;
					r->_base(b);
					r->item.name._write(r->name.text);
					r->dice._roll(1, 2);
					r->item.amount = r->dice.value.i;
					r->item.identifier = r->identifier;
					r->item.type = r->type;
					this->resources << *r;
					delete r;
					break;
				}
			}
			uniques->_close();
		}

		DINT _tile(CREATURE *creature) {
			TERRAIN *ter;
			DINT x, y, w, h;
			SINT type = -1;
			for (DINT m = 0; m < this->maps.length; m++) {
				if (this->maps.exist[m]) {
					for (DINT t = 0; t < this->maps[m].terrain.length; t++) {
						if (this->maps[m].terrain.exist[t]) {
							ter = &this->maps[m].terrain[t];
							//ter->sprt.occupied = 0;
							x = creature->model.position.x + creature->model.position.w / 2;
							y = creature->model.position.y + creature->model.position.h / 2;
							w = ter->sprt.size.w * this->measure.size + ter->position.w;
							h = ter->sprt.size.h * this->measure.size + ter->position.h;
							if (x >= ter->position.w && x <= w) {
								if (y >= ter->position.h && y <= h) {
									ter->sprt.occupied = 1;
									switch (ter->type) {
									default:
										break;
									case ENGINE_TYPE_TILE_SWAMP:
										if(creature->speed.current == creature->speed.total) creature->speed.current = (DINT)(creature->speed.total / 2);
										break;
									case ENGINE_TYPE_TILE_MEADOW:
										creature->_heal(1);
										break;
									}
									type = ter->type;
								}
							}
						}
					}
				}
			}
			return type;
		}
	};

	GAME() {
		this->played = 0;
		this->sleep = 0;
		this->configured = 0;
		std::cout << "\nGame constructor called.";
	};
	~GAME() {
		this->played = 0;
		this->sleep = 0;
		this->configured = 0;
		//this->dice.~RANDOM();
		this->atlas.~ATLAS();
		this->client.~DIMENSION();

	};
	DINT played, sleep, configured;
	DICE dice;
	STATISTICS statistics;
	ATLAS atlas;
	DIMENSION client, mouse;
	CONFIG config;
	TIME timer;
	DOLL doll;
	FLUID water;
	BOX box;
	
	void _config() {
		this->config.map.w = 4;
		this->config.map.h = 4;
		this->config.atlas.w = 2;
		this->config.atlas.h = 1;
		DINT mw = this->config.map.w , mh = this->config.map.h, ah = this->config.atlas.h, aw = this->config.atlas.w, count = 0; // a > m
		MAP *map;
		this->atlas.measure.w = 0;
		this->atlas.measure.h = 0;
		this->atlas.measure.size = 3;
		std::cout << "\nSetting atlas.";
		this->timer._clock();
		//this->atlas.maps.block = this->config.atlas.w * this->config.atlas.h;
		for (DINT x = 0; x < aw; x++) {
			for (DINT y = 0; y < ah; y++) {
				map = new MAP;
				map->measure.size = this->atlas.measure.size;
				map->measure.x = this->client.w - (x + 1) * (mw * (8 * map->measure.size));
				map->measure.y = 0 + y * (mh * (8 * map->measure.size));
				map->measure.w = (8 * map->measure.size) * mw;
				map->measure.h = (8 * map->measure.size) * mh;
				map->position.x = x;
				map->position.y = y;
				map->position.w = mw;
				map->position.h = mh;
				map->count = count;
				map->_set();
				this->atlas.maps << *map;
				delete map;
				count++;
			}
		}
		std::cout << "\nAtlas set: " << this->timer._difference(this->timer);
		this->atlas.measure.w = (this->config.map.w * 8 * this->atlas.measure.size) * this->config.atlas.w;
		this->atlas.measure.h = (this->config.map.h * 8 * this->atlas.measure.size) * this->config.atlas.h;
		this->atlas.measure.x = this->client.w - this->atlas.measure.w;
		this->atlas.measure.y = 0;

	}


	DINT _play() {
		if (this->configured != 1) {
			this->_config();
			this->configured = 1;
		}
		this->atlas._pre();
		if (this->atlas.creatures.length < ENGINE_CREATURE_AMOUNT) {
			switch (this->dice._roll(0, 8)) {
			default:
				break;
			case 1:
				this->atlas._appear(ENGINE_CREATURE_REAPER);
				break;
			case 2:
				this->atlas._appear(ENGINE_D);
				break;
			case 4:
				this->atlas._appear(ENGINE_CREATURE_DEFENSE);
				break;
			case 6:
				this->atlas._appear(ENGINE_CREATURE_OFFENSE);
				break;
			case 7:
				this->atlas._appear(ENGINE_CREATURE_HALT);
				break;
			}
		}

		if (this->atlas.resources.length < ENGINE_RESOURCE_AMOUNT) {
			this->dice._roll(0, 8);
			switch (this->dice.value.i) {
			default:
				break;
			case 2:
				this->atlas._appear(ENGINE_RESOURCE_BERRY);
				break;
			case 4:
				this->atlas._appear(ENGINE_RESOURCE_PLANT);
				break;
			case 6:
				this->atlas._appear(ENGINE_RESOURCE_STONE);
				break;
			case 8:
				this->atlas._appear(ENGINE_RESOURCE_CURRENCY);
				break;
			}
		}
		this->atlas._update();
		this->atlas._movement();
		if(this->doll.exist) this->doll._gravitate();
		//this->water._liquid();
		this->statistics._loop();
		this->box.angle.x += 1.0;
		this->box.angle.y += 1.0;
		if (this->box.angle.x >= 360.0) {
			this->box.angle.x = this->box.angle.x - 360.0;
		}
		if (this->box.angle.y >= 360.0) {
			this->box.angle.y = this->box.angle.y - 360.0;
		}

		return this->played;
	}
};