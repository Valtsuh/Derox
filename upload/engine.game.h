struct GAME {
	struct DIRECTION {
		DIRECTION(DINT value = 0, DINT exist = 0, DINT available = 0) {
			this->value = value;
			this->exist = exist;
			this->available = available;
		};
		~DIRECTION() {};
		DINT value, exist, available;


		void _set(DINT number) {
			this->value = number;
			this->exist = 1;
			this->available = 0;
		}
	};
	struct STATISTICS{
		STATISTICS() {};
		~STATISTICS() {};
		COUNTER loop, fps;
		TIME time, current, tick;
		void _loop() {
			this->loop.current++;
			this->current._difference(this->time);
			if (loop.current > 0 && this->current.elapsed > 0) this->fps.current = (DINT)(loop.current / this->current.elapsed);
			this->tick._clock();
		}

	};
	struct COLLISION {
		COLLISION() {
			this->current = 0;
			this->collie = -1;
			this->collided = 0;
			this->type = 0;
		};
		~COLLISION() {};
		DINT current, collided, type;
		SINT collie;


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
		};
		~DUS() {};

		double identifier;
		STRING name;
		DINT health, amount;
	};
	struct ITEM {
		ITEM(double identifier = 0.0, const char name[] = "Undefined") {
			this->identifier = identifier;
			this->amount = 0;
			this->name._write(name);
			this->type = 0;
		};
		~ITEM() {};

		double identifier;
		DINT amount, type;
		STRING name;
	};
	struct INVENTORY {
		INVENTORY() {};
		~INVENTORY() {};

		LIST <ITEM> items;

		
		void _gather(ITEM item) {
			DINT found = 0;
			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.existance[i] == 1) {
					if (this->items.item[i].identifier == item.identifier) {
						found = 1;
						this->items.item[i].amount += item.amount;
					}
				}
			}
			if (found == 0) {
				this->items._set(item);
			}
		}

		DINT _reduce(ITEM item, DINT amount) {
			DINT found = 0;
			for (DINT i = 0; i < this->items.length; i++) {
				if (this->items.existance[i] == 1) {
					if (this->items.item[i].identifier == item.identifier) {
						found = 1;
						this->items.item[i].amount -= amount;
					}
				}
			}
			return (found == 1) ? (1) : (0);
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
	struct BASIS {
		BASIS(double identifier = 0.0, const char name[] = "Undefined", DUS dus = {}, DINT type = 0.0, SPRITE sprite = {}, ANIMATION animation = {}, DINT scale = 2, DINT width = 5, DINT height = 5, DINT speed = 5) {
			this->model.sprite = sprite;
			this->model.animation = animation;
			this->model._set(-1, -1, width, height, scale);
			this->speed = speed;
			this->name._write(name);
			this->type = type;
			this->identifier = identifier;
			this->origin = dus;
			this->unique = 0;
		};
		~BASIS() {};

		double identifier;
		STRING name;
		DINT unique, type, speed;
		MODEL model;
		RANDOM dice;
		DUS origin;


		void _base(BASIS basis) {
			this->model = basis.model;
			this->speed = basis.speed;
			this->type = basis.type;
			this->name = basis.name;
			this->origin = basis.origin;
			this->identifier = basis.identifier;
			this->unique = basis.unique;
		}

		void _update() {
			if (this->model.animation.total > 1) {
				this->model.animation.current++;
				if (this->model.animation.current == this->model.animation.total) {
					this->model.animation.current = 0;
				}
			}
		}

		COLLISION _collision(DIMENSION bp, DINT unique = 0) {
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
					collision.collie = unique;
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
					collision.collie = unique;
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
					collision.collie = unique;
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
					collision.collie = unique;
					collision.collided = 1;
				}
				break;
			}
			return collision;
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
			this->model._animate(tool);
		}
	};
	struct CREATURE : BASIS {
		CREATURE() {
			this->direction[2]._set(2);
		};
		~CREATURE() {};
		COUNTER health;
		DIRECTION direction[9];
		COLLISION collision;
		INVENTORY inventory;
		EFFECT effect;
		INDEX <DUS> mutation;

		void _use(ITEM item) {
			switch (item.type) {
			default:
				break;
			case ENGINE_TYPE_RESOURCE_BERRY:
				this->health.current += 2;
				this->inventory._reduce(item, 1);
				break;
			}
		}

		void _draw(HDC tool) {

			// Health
			DINT px = 0, py = 0;
			double temp = floor(this->health.total / this->model.position.w) + 0.50;
			PIXEL pixel = {};
			SPRITE sprite = this->model.animation.stage[this->model.animation.current];
			if (this->health.total > 0) {
				for (DINT w = 0; w < this->model.position.w; w++) {
					px = this->model.position.x + w * this->model.position.size;
					py = this->model.position.y - (1 * this->model.position.size);
					if (this->health.current == this->health.total) {
						pixel.color._set(G);
					}
					else {
						if ((1 + w) * temp <= this->health.current) {
							pixel.color._set(G);
						}
						else {
							pixel.color._set(R);
						}
					}
					pixel._scale(tool, px, py, this->model.position.size);
				}
			}

			// Sprite
			this->model._animate(tool);

			// Effect
			if (this->effect.exist == 1) {
				px = this->model.position.x + (this->effect.pixel.x - 2) * this->model.position.size;
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
			SINT has = this->_has(dus.identifier);
			if (has >= 0) {
				this->mutation.items[has].amount++;
			}
			else {
				this->mutation._add(dus);
			}
			this->health.total += dus.health;
			//switch(dus.)
		}

		SINT _has(double identifier) {
			for (DINT m = 0; m < this->mutation.length; m++) {
				if (this->mutation.exist[m] == 1) {
					if (this->mutation.items[m].identifier == identifier) return m;
				}
			}
			return -1;
		}
	};
	struct TERRAIN {
		TERRAIN() {
			this->type = 0;
			this->directed = 0;
			this->sprite = ENGINE_MAP_BACKGROUND_NONE;
		};
		~TERRAIN() {};

		SPRITE sprite, n, s, w, e;
		DIMENSION position;
		DINT type, directed;

	};
	struct MAP {
		MAP() {
		};
		~MAP() {};

		//INDEX <CREATURE> creatures;
		//INDEX <RESOURCE> resources;
		RANDOM dice;
		ITEM loot;
		DIMENSION measure, position;
		INDEX <TERRAIN> terrain;
		/*
		void _appear(BASIS b = {}, SINT x = -1, SINT y = -1, SINT speed = -1) {
			x = (x > -1)?(this->measure.x + x):(b.dice._roll(this->measure.x, this->measure.w - (b.model.position.size * b.model.position.w)));
			y = (y > -1)?(this->measure.y + y):(b.dice._roll(this->measure.y, this->measure.h - (b.model.position.size * b.model.position.h)));
			//x = (x > -1) ? (this->measure.x + (x * 8)) : (b.dice._roll(0, 16));
			//x = (y > -1) ? (this->measure.y + (y * 8)) : (b.dice._roll(0, 16));
			b.model._set(x, y, b.model.position.w, b.model.position.h, b.model.position.size);
			b.unique = b.dice._roll(1, 999);
			if (speed == 0) b.speed = 0;
			switch (b.type) {
				default: {
					break;
				}
				case ENGINE_TYPE_CREATURE: {
					CREATURE c = {};
					c._base(b);
					c.health.total = b.origin.health;
					c.health.current = c.health.total;
					this->creatures._add(c);
					break;
				}
				case ENGINE_TYPE_RESOURCE:
				case ENGINE_TYPE_RESOURCE_PLANT:
				case ENGINE_TYPE_RESOURCE_BERRY:
				case ENGINE_TYPE_RESOURCE_STONE:
				case ENGINE_TYPE_RESOURCE_CURRENCY:
				{
					RESOURCE r = {};
					r._base(b);
					r.item.name._write(r.name.text);
					r.dice._roll(1, 2);
					r.item.amount = r.dice.value;
					r.item.identifier = r.identifier;
					r.item.type = r.type;
					this->resources._add(r);
					break;
				}
			}

		}

		void _update() {
			
			if (this->creatures.length > 0) {
				for (DINT d = 0; d < this->creatures.length; d++) {
					if (this->creatures.exist[d] == 1) {
						this->creatures.items[d]._update();
					}
				}
			}
			if (this->resources.length > 0) {
				for (DINT r = 0; r < this->resources.length; r++) {
					if (this->resources.exist[r] == 1) {
						this->resources.items[r]._update();
					}
				}
			}
			
		}

		COLLISION _collive(CREATURE a) {
			COLLISION collision = {};
			collision.collided = 0;
			DIMENSION ap = a.model.position, bp;

			for (DINT c = 0; c < this->creatures.length; c++) {
				if (this->creatures.exist[c] == 1) {
					//if (distance < x){
					if (this->creatures.items[c].unique != a.unique) {
						collision = a._collision(this->creatures.items[c].model.position, this->creatures.items[c].unique);
						if (collision.collided == 1) {
							collision.type = ENGINE_TYPE_CREATURE;
							break;
						}
					}
				}
			}

			if (collision.collided == 0) {
				SINT result = 0;
				for (DINT r = 0; r < this->resources.length; r++) {
					if (this->resources.exist[r] == 1) {
						collision = a._collision(this->resources.items[r].model.position, this->resources.items[r].unique);
						if (collision.collided == 1) {
							collision.type = ENGINE_TYPE_RESOURCE;
							this->loot = this->resources.items[r].item;
							this->resources._remove(r);
							break;
						}
					}
				}
			}

			return collision;
		}		

		void _movement() {
			DINT n = 0;
			COLLISION collision = {};
			if (this->creatures.length > 0) {
				do {
					if (this->creatures.exist[n] == 1) {
						if (this->creatures.items[n].speed > 0) {
							this->creatures.items[n].dice._roll(0, 8);
							this->creatures.items[n].model.collision = 0;
							CREATURE d = this->creatures.items[n];
							switch (d.dice.value) {
							default:
								break;
							case 2:
								this->creatures.items[n].model.facing = 2;
								if (d.model.position.y < (this->measure.h + this->measure.y - (d.model.position.size * d.model.position.h)) - d.speed) {
									this->creatures.items[n].model.to.y = d.model.position.y + d.speed;
								}
								else {
									this->creatures.items[n].model.to.y = this->measure.h + this->measure.y - (d.model.position.size * d.model.position.h);
								}
								break;
							case 4:
								this->creatures.items[n].model.facing = 4;
								if (d.model.position.x >= d.speed + this->measure.x) {
									this->creatures.items[n].model.to.x = d.model.position.x - d.speed;
								}
								else {
									this->creatures.items[n].model.to.x = this->measure.x;
								}
								break;
							case 6:
								this->creatures.items[n].model.facing = 6;
								if (d.model.position.x < (this->measure.w + this->measure.x - (d.model.position.size * d.model.position.w)) - d.speed) {
									this->creatures.items[n].model.to.x = d.model.position.x + d.speed;
								}
								else {
									this->creatures.items[n].model.to.x = this->measure.w + this->measure.x - (d.model.position.size * d.model.position.w);
								}
								break;
							case 8:
								this->creatures.items[n].model.facing = 8;
								if (d.model.position.y >= d.speed + this->measure.y) {
									this->creatures.items[n].model.to.y = d.model.position.y - d.speed;
								}
								else {
									this->creatures.items[n].model.to.y = this->measure.y;
								}
								break;
							}
							collision = this->_collive(this->creatures.items[n]);
							if (collision.collided == 0) {
								this->creatures.items[n].model.position._set(this->creatures.items[n].model.to);
							}
							else {
								//this->creatures.items[n].model.to._set(this->creatures.items[n].model.position);
								this->creatures.items[n].model.collision = 1;
								this->creatures.items[n].collision = collision;
								if (collision.type == ENGINE_TYPE_RESOURCE) {
									if (this->loot.amount > 0) {
										this->creatures.items[n].inventory._gather(this->loot);
										this->loot = {};
									}
								}
							}
						}
					}
					n++;
				} while (n < this->creatures.length);
			}
		}
		*/
		void _set(DINT w, DINT h) {
			TERRAIN terrain = {}, a = {}, b = {};
			SINT u = -1, d = -1, l = -1, r = -1;
			for (DINT x = 0; x < w; x++) {
				for (DINT y = 0; y < h; y++) {
					switch (this->dice._roll(0, 6)) {
					default:
						terrain.sprite = ENGINE_MAP_BACKGROUND_DESOLATE;
						terrain.type = ENGINE_TYPE_TILE_DESOLATE;
						break;
					case 2:
						terrain.sprite = ENGINE_MAP_BACKGROUND_MEADOW;
						terrain.type = ENGINE_TYPE_TILE_MEADOW;
						break;
					case 4:
						terrain.sprite = ENGINE_MAP_BACKGROUND_SWAMP;
						terrain.n = ENGINE_MAP_BACKGROUND_SWAMP_NORTH;
						terrain.s = ENGINE_MAP_BACKGROUND_SWAMP_SOUTH;
						terrain.w = ENGINE_MAP_BACKGROUND_SWAMP_WEST;
						terrain.e = ENGINE_MAP_BACKGROUND_SWAMP_EAST;
						terrain.type = ENGINE_TYPE_TILE_SWAMP;
						break;
					}
					terrain.sprite._position(x, y);
					terrain.position.x = x;
					terrain.position.y = y;
					this->terrain._add(terrain);
				}
			}

			for (DINT t = 0; t < this->terrain.length; t++) {
				a = this->terrain.items[t];
				switch (a.type) {
				default:
					break;
				case ENGINE_TYPE_TILE_SWAMP:
					if (a.directed != 1) {
						u = this->_get(a.position.x, a.position.y, 8);
						d = this->_get(a.position.x, a.position.y, 2);
						if (u > -1 && d > -1) {

							l = this->_get(a.position.x, a.position.y, 4);
							r = this->_get(a.position.x, a.position.y, 6);
							if (l > -1) {
								this->terrain.items[l].sprite = a.w;
							}
							else {
								if (r > -1) {
									this->terrain.items[r].sprite = a.e;
								}
								else {

								}
							}

						}
						else {
							if (u > -1) {
								this->terrain.items[u].sprite = a.n;
							}
							else {
								if (d > -1) {
									this->terrain.items[d].sprite = a.s;
								}
								else {

								}
							}
						}
						this->terrain.items[t].directed = 1;
					}
					break;
				}
			}
		}

		void _draw(HDC tool) {
			DINT x, y;
			TERRAIN terrain;
			PIXEL pixel;
			for (DINT s = 0; s < this->terrain.length; s++) {
				terrain = this->terrain.items[s];
				for (DINT w = 0; w < 8; w++) {
					for (DINT h = 0; h < 8; h++) {
						pixel = terrain.sprite._get(w, h);
						x = (pixel.x * this->measure.size) + this->measure.x + (terrain.position.x * (this->measure.size * 8));
						if (x >= this->measure.w + this->measure.x) break;
						y = (pixel.y * this->measure.size) + this->measure.y + (terrain.position.y * (this->measure.size * 8));
						if (y >= this->measure.h + this->measure.y) break;

						if (y == this->measure.y || x == this->measure.x) pixel.color = B;

						pixel._scale(tool, x, y, this->measure.size);
					}
				}
			}
		}

		SINT _get(DINT x, DINT y, DINT adjacent = 0) {
			TERRAIN terrain = {};
			for (DINT t = 0; t < this->terrain.length; t++) {
				if (this->terrain.exist[t] == 1) {
					terrain = this->terrain.items[t];
					switch (adjacent) {
					default:
						if (terrain.position.x == x) {
							if (terrain.position.y == y) {
								return t;
							}
						}
						break;
					case 2:
						if (terrain.position.x == x) {
							if (terrain.position.y == y + 1) {
								return t;
							}
						}
						break;
					case 4:
						if (terrain.position.x == x - 1) {
							if (terrain.position.y == y) {
								return t;
							}
						}
						break;
					case 6:
						if (terrain.position.x == x + 1) {
							if (terrain.position.y == y) {
								return t;
							}
						}
						break;
					case 8:
						if (terrain.position.x == x) {
							if (terrain.position.y == y - 1) {
								return t;
							}
						}
						break;
					}
				}
			}
			return -1;
		}
	};
	struct ATLAS {
		ATLAS() {
			this->bg = ENGINE_COLOR_MAP_BACKGROUND;
		};
		~ATLAS() {
			this->maps.~INDEX();
			this->creatures.~INDEX();
			this->resources.~INDEX();
		};
		INDEX <MAP> maps;
		INDEX <CREATURE> creatures;
		INDEX <RESOURCE> resources;
		COLOR bg;
		DIMENSION measure;
		RANDOM dice; 
		ITEM loot;


		void _update() {

			if (this->creatures.length > 0) {
				for (DINT d = 0; d < this->creatures.length; d++) {
					if (this->creatures.exist[d] == 1) {
						this->creatures.items[d]._update();
					}
				}
			}
			if (this->resources.length > 0) {
				for (DINT r = 0; r < this->resources.length; r++) {
					if (this->resources.exist[r] == 1) {
						this->resources.items[r]._update();
					}
				}
			}

		}

		COLLISION _collive(CREATURE a) {
			COLLISION collision = {};
			collision.collided = 0;
			DIMENSION ap = a.model.position, bp;
			CREATURE b;
			for (DINT c = 0; c < this->creatures.length; c++) {
				if (this->creatures.exist[c] == 1) {
					b = this->creatures.items[c];
					//if (distance < x){
					if (b.unique != a.unique) {
						collision = a._collision(b.model.position, b.unique);
						if (collision.collided == 1) {
							collision.type = ENGINE_TYPE_CREATURE;
							break;
						}
					}
				}
			}

			if (collision.collided == 0) {
				SINT result = 0;
				RESOURCE c;
				for (DINT r = 0; r < this->resources.length; r++) {
					if (this->resources.exist[r] == 1) {
						c = this->resources.items[r];
						collision = a._collision(c.model.position, c.unique);
						if (collision.collided == 1) {
							collision.type = ENGINE_TYPE_RESOURCE;
							this->loot = c.item;
							this->resources._remove(r);
							break;
						}
					}
				}
			}

			return collision;
		}

		void _movement() {
			DINT n = 0;
			COLLISION collision = {};
			if (this->creatures.length > 0) {
				do {
					if (this->creatures.exist[n] == 1) {
						if (this->creatures.items[n].speed > 0) {
							this->creatures.items[n].dice._roll(0, 8);
							this->creatures.items[n].model.collision = 0;
							CREATURE d = this->creatures.items[n];
							switch (d.dice.value) {
							default:
								break;
							case 2:
								this->creatures.items[n].model.facing = 2;
								if (d.model.position.y < (this->measure.h + this->measure.y - (d.model.position.size * d.model.position.h)) - d.speed) {
									this->creatures.items[n].model.to.y = d.model.position.y + d.speed;
								}
								else {
									this->creatures.items[n].model.to.y = this->measure.h + this->measure.y - (d.model.position.size * d.model.position.h);
								}
								break;
							case 4:
								this->creatures.items[n].model.facing = 4;
								if (d.model.position.x >= d.speed + this->measure.x) {
									this->creatures.items[n].model.to.x = d.model.position.x - d.speed;
								}
								else {
									this->creatures.items[n].model.to.x = this->measure.x;
								}
								break;
							case 6:
								this->creatures.items[n].model.facing = 6;
								if (d.model.position.x < (this->measure.w + this->measure.x - (d.model.position.size * d.model.position.w)) - d.speed) {
									this->creatures.items[n].model.to.x = d.model.position.x + d.speed;
								}
								else {
									this->creatures.items[n].model.to.x = this->measure.w + this->measure.x - (d.model.position.size * d.model.position.w);
								}
								break;
							case 8:
								this->creatures.items[n].model.facing = 8;
								if (d.model.position.y >= d.speed + this->measure.y) {
									this->creatures.items[n].model.to.y = d.model.position.y - d.speed;
								}
								else {
									this->creatures.items[n].model.to.y = this->measure.y;
								}
								break;
							}
							collision = this->_collive(this->creatures.items[n]);
							if (collision.collided == 0) {
								this->creatures.items[n].model.position._set(this->creatures.items[n].model.to);
							}
							else {
								//this->creatures.items[n].model.to._set(this->creatures.items[n].model.position);
								this->creatures.items[n].model.collision = 1;
								this->creatures.items[n].collision = collision;
								if (collision.type == ENGINE_TYPE_RESOURCE) {
									if (this->loot.amount > 0) {
										this->creatures.items[n].inventory._gather(this->loot);
										this->loot = {};
									}
								}
							}
						}
					}
					n++;
				} while (n < this->creatures.length);
			}
		}

		void _appear(BASIS b = {}, SINT x = -1, SINT y = -1, SINT speed = -1) {
			x = (x > -1) ? (this->measure.x + x) : (b.dice._roll(this->measure.x, this->measure.w - (b.model.position.size * b.model.position.w)));
			y = (y > -1) ? (this->measure.y + y) : (b.dice._roll(this->measure.y, this->measure.h - (b.model.position.size * b.model.position.h)));
			//x = (x > -1) ? (this->measure.x + (x * 8)) : (b.dice._roll(0, 16));
			//x = (y > -1) ? (this->measure.y + (y * 8)) : (b.dice._roll(0, 16));
			b.model._set(x, y, b.model.position.w, b.model.position.h, b.model.position.size);
			b.unique = b.dice._roll(1, 999);
			if (speed == 0) b.speed = 0;
			switch (b.type) {
			default: {
				break;
			}
			case ENGINE_TYPE_CREATURE: {
				CREATURE c = {};
				c._base(b);
				c.health.total = b.origin.health;
				c.health.current = c.health.total;
				this->creatures._add(c);
				break;
			}
			case ENGINE_TYPE_RESOURCE:
			case ENGINE_TYPE_RESOURCE_PLANT:
			case ENGINE_TYPE_RESOURCE_BERRY:
			case ENGINE_TYPE_RESOURCE_STONE:
			case ENGINE_TYPE_RESOURCE_CURRENCY:
			{
				RESOURCE r = {};
				r._base(b);
				r.item.name._write(r.name.text);
				r.dice._roll(1, 2);
				r.item.amount = r.dice.value;
				r.item.identifier = r.identifier;
				r.item.type = r.type;
				this->resources._add(r);
				break;
			}
			}

		}

		void _draw(HDC tool) {
			MAP map;
			TERRAIN terrain;
			PIXEL pixel;
			DINT x = 0, y = 0;
			for (DINT m = 0; m < this->maps.length; m++) {
				map = this->maps.items[m];
				for (DINT t = 0; t < this->maps.items[m].terrain.length; t++) {
					terrain = map.terrain.items[t];
					for (DINT w = 0; w < 8; w++) {
						for (DINT h = 0; h < 8; h++) {
							pixel = terrain.sprite._get(w, h);
							//x = map.position.x * (terrain.position.x * (map.measure.))
						}
					}
				}
			}
		}
	};

	GAME() {
		this->played = 0;
		this->sleep = 0;
		this->configured = 0;
	};
	~GAME() {
		this->played = 0;
		this->sleep = 0;
		this->configured = 0;
		this->dice.~RANDOM();
		this->atlas.~ATLAS();
		this->client.~DIMENSION();

	};
	DINT played, sleep, configured;
	RANDOM dice;
	STATISTICS statistics;
	ATLAS atlas;
	DIMENSION client;
	
	void _config() {
		DINT mw = 8, mh = 8, ah = 2, aw = 2;
		MAP map = {};
		this->atlas.measure.w = 0;
		this->atlas.measure.h = 0;
		for (DINT x = 0; x < aw; x++) {
			for (DINT y = 0; y < ah; y++) {
				map = {};
				map.measure.size = 2;
				map.measure.w = (8 * map.measure.size) * mw;
				map.measure.h = (8 * map.measure.size) * mh;
				map.measure.x = this->client.w - (x + 1) * (mw * (8 * map.measure.size));
				map.measure.y = 0 + y * (mh * (8 * map.measure.size));
				map.position.x = x;
				map.position.y = y;
				map._set(mw, mh);
				this->atlas.maps._add(map);
			}
		}
		this->atlas.measure.w = map.measure.w * aw;
		this->atlas.measure.h = map.measure.h * ah;
		this->atlas.measure.x = this->client.w - this->atlas.measure.w;
		this->atlas.measure.y = 0;
	}

	DINT _play() {
		if (this->configured != 1) {
			this->_config();
			this->configured = 1;
		}
		if (this->atlas.creatures.length < 3) {
			switch (this->dice._roll(0, 8)) {
			default:
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
			}
		}
		if (this->atlas.resources.length < 8) {
			this->dice._roll(0, 8);
			switch (this->dice.value) {
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
		this->atlas._movement();
		this->atlas._update();
		this->statistics._loop();
		return this->played;
	}
};