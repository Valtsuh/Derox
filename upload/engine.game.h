struct GAME {
	GAME() {
		this->played = 0;
		this->debug = 0;
	};
	~GAME() {};

	struct CAMERA {
		CAMERA() {
			this->speed = 0.1;
		};
		POS center, offset, tile;
		double speed;


		void _center(SINT x, SINT y) {

		}
	};
	struct TAG {
		TAG(const char base[], PREFIX prefix, SUFFIX suffix) {
			if (prefix.name.length > 0) {
				this->prefix = prefix;
				this->name._append(prefix.name.text);
			}

			this->base = base;
			if (this->name.length > 0) {
				this->name._space(base);
			}
			else {
				this->name._append(base);
			}

			if (suffix.name.length > 0) {
				this->suffix = suffix;
				this->name._space(suffix.name.text);
			}
			this->id = -1;
		};
		TAG() {
			this->id = -1;
		};

		STRING name;
		STRING base;
		PREFIX prefix;
		SUFFIX suffix;
		SINT id;

		void _generate() {
			DICE dice;
			*this = { GAME::library.base[dice._roll(0, GAME::library.base.length - 1)].text, GAME::library.prefix[dice._roll(0, GAME::library.prefix.length)], GAME::library.suffix[dice._roll(0, GAME::library.suffix.length - 1)] };

		}
	};

	struct TILE {
		TILE() {
			this->occupee = -1;
			this->type = ENGINE_TYPE_TILE;
			this->base = ENGINE_TYPE_TILE;
			this->steps = 0;
			this->unstepped = this->dice._roll(0, (DINT)(ENGINE_DEVELOP_ROAD_DECAY / 2));
			//std::cout << "\n>Unstepped: " << this->unstepped;
			this->moisture = this->dice._droll(-0.035, 0.055, 0.0001);
			//std::cout << "\n>Moisture: " << this->moisture;
			this->raining = 0;
		};
		BIOME biome;
		SPRITE graphic;
		POS position, center, origin, id;
		DINT base, type, unstepped, raining;
		SINT occupee, steps;
		double moisture;
		DICE dice;


		void _set(DINT type) {
			this->type = type;
			switch (type) {
			default:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-block")];
				break;
			case ENGINE_TYPE_TILE_DESOLATE:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-desolate")];
				break;
			case ENGINE_TYPE_TILE_MEADOW:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-grass")];
				break;
			case ENGINE_TYPE_TILE_ROAD:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-road")];
				break;
			case ENGINE_TYPE_TILE_GROWTH:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-growth")];
				break;
			case ENGINE_TYPE_TILE_WATER:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-water")];
				break;
			}
		}

	};

	struct ABILITY {
		struct EFFECT {
			EFFECT(DINT type) {
				this->type = type;
			};
			EFFECT() {
				this->type = 0;
			};
			DINT type;
		};
		ABILITY(const char name[], const char sprite[], double cost, DINT duration, double chance, DINT effect, DINT cast) {
			this->name = name;
			this->cost = cost;
			this->duration = duration;
			this->chance = chance;
			this->effect = effect;
			this->cast = cast;
			this->chance = chance;
			this->movement.speed = 0.0;
			switch (cast) {
			default:
			case ENGINE_TYPE_CAST_INSTANT:
				this->display = 4;
				this->speed = 0.0;
				break;
			case ENGINE_TYPE_CAST_RANGE:
				this->display = -1;
				this->speed = 0.15 * GAME::MAP::scale;
				break;
			}
			this->graphic = GAME::library.animation[GAME::library._asearch(sprite)];
			this->target = -1;
		};
		ABILITY() {
			this->cost = 0;
			this->duration = 0;
			this->effect = 0;
			this->cast = 0;
			this->chance = 0.0;
			this->display = 0;
			this->speed = 0.0;
			this->target = -1;
		};
		STRING name;
		ANIMATION graphic;
		EFFECT effect;
		DINT duration, cast;
		SINT display, target;
		double chance, speed, cost;
		MOVEMENT movement;

	};

	struct CONTRACT {
		//
	};

	struct BEHAVIOUR {
		BEHAVIOUR() {
			this->discover = 0;
			this->generation = 0;
			this->target = -1;
			this->contest.current = 0;
		};

		DINT discover, generation;
		COUNTER contest;
		POS aware;
		SINT target;
		FIGURE hunger;


	};

	struct MOVE {
		MOVE() {
			this->ready = 0.0;
		};		
		double ready;

	};

	struct DUS {
		DUS(double identifier, DINT type, const char name[]) {
			this->id = identifier;
			this->type = type;
			this->name = name;
		};
		DUS() {
			this->type = 0;
			this->id = 0.0;
		};

		DINT type;
		STRING name;
		double id;

	};

	struct CREATURE {
		CREATURE(STRING name, DINT gender = -1) {
			if (name.length == 0) {
				this->tag._generate();
			}
			else {
				this->tag.name = name.text;
			}
			this->current = 0;
			this->from = 0;
			this->strength = { "Strength", "STR", this->dice._roll(2, 5) };
			this->agility = { "Agility", "AGI", this->dice._roll(2, 5) };
			this->guard = { "Guard", "GRD", this->dice._roll(2, 5) };
			this->charisma = { "Charisma", "CMA", this->dice._roll(0, 5) };
			this->sense = { "Sense", "SNS", this->dice._roll(0, 5) };
			this->energy = { "Energy", "EGY", this->dice._roll(2, 5) + this->agility.point.total };
			this->health = { "Health", "HLT", this->dice._roll(10, 20) };
			this->behaviour.contest.total = 10 + this->sense.point.total;
			switch (gender) {
			default:
				switch (this->dice._roll(0, 1)) {
				default:
					this->sex.gender = { "Unknown", "NA", 2 };
					break;
				case 0:
					this->sex.gender = { "Female", "F", 0 };
					break;
				case 1:
					this->sex.gender = { "Male", "M", 1 };
					break;

				}
				break;
			case 0:
				this->sex.gender = { "Female", "F", 0 };
				break;
			case 1:
				this->sex.gender = { "Male", "M", 1 };
				break;
			}
			this->battling = -1;
			this->casted = -1;
		}
		CREATURE() {
			this->current = 0;
			this->from = 0;
			this->battling = -1;
			this->casted = -1;
		};
		TAG tag;
		FIGURE strength, agility, guard, charisma, sense, energy, health;
		SEX sex;
		ANIMATION graphic;
		MOVEMENT movement;
		BEHAVIOUR behaviour;
		INVENTORY inventory;
		MOVE move;
		POS position;
		DINT current, from;
		SINT battling, casted;
		CHART <TILE> astar;
		DICE dice;

		SINT _clampX(SINT value) {
			SINT w = (GAME::MAP::position.x - 1) / 2;
			if (value <= -w) return -w;
			if (value >= w) return w;
			return value;
		}
		SINT _clampY(SINT value) {
			SINT h = (GAME::MAP::position.y - 1) / 2;
			if (value <= -h) return -h;
			if (value >= h) return h;
			return value;
		}

		void _die() {
			this->astar._close();
			this->movement.type._close();

		}


	};	
	struct MAP {
		MAP() {
			measure.x = 0;
			measure.y = 0;
			measure.w = 0;
			measure.h = 0;
			this->enabled = 0;
			this->discovered = 0;
		};
		
		CHART <CREATURE> creature;
		CHART <TILE> tile;
		static CHART <ABILITY> action;
		DINT enabled, discovered;
		DICE dice;
		RANDOM random;
		static DINT scale, debug, targeting;
		static DIMENSION measure;
		static POS position, tiling;
		static double speed;
		static POS init, current, max;


		void _gen(SINT w, SINT h, DINT scale = 1) {

			// TO DO: tiles < creatures
			TILE t;
			for (SINT x = -w; x <= w; x++) {
				for (SINT y = -h; y <= h; y++) {
					//std::cout << "\n " << x << ", " << y;
					if(x == 0 && y == 0) {
						t.graphic = GAME::library.sprite[GAME::library._search("tile-base-center")];
						GAME::MAP::tiling.x = t.graphic.size.w;
						GAME::MAP::tiling.y = t.graphic.size.h;
						t.origin = { GAME::MAP::position.x + (x - y - 1) * (GAME::MAP::tiling.x / 2), GAME::MAP::position.y + (x + y - 1) * (GAME::MAP::tiling.y / 2) };
						t.position = { t.origin.x * GAME::MAP::scale, t.origin.y * GAME::MAP::scale };
						t.center = { t.position.x + GAME::MAP::tiling.x / 2 * GAME::MAP::scale, t.position.y + GAME::MAP::tiling.y / 2 * GAME::MAP::scale };
						t.id = { x, y };
						this->tile << t;
					}
					else {
						this->_generateTile(x, y);
					}
				}
			}
			GAME::MAP::init = { -w, -h, w, h };
			GAME::MAP::current = { -w, -h, w, h };
		}


		void _paint() {
			SINT cx = 0, cy = 0, hx = 0, hy = 0, hw = 0, hh = 0;

			for (DINT t = 0; t < this->tile.length; t++) {
				TILE *tile = &this->tile[t];
				tile->position = { GAME::camera.offset.x * GAME::MAP::scale + state.w / 2 + (tile->id.x - tile->id.y - 1) * (GAME::MAP::tiling.x / 2) * GAME::MAP::scale, GAME::camera.offset.y * GAME::MAP::scale + state.h / 2 + (tile->id.x + tile->id.y - 1) * (GAME::MAP::tiling.y / 2) * GAME::MAP::scale };
				tile->center = { tile->position.x + GAME::MAP::tiling.x / 2 * GAME::MAP::scale, tile->position.y + GAME::MAP::tiling.y / 2 * GAME::MAP::scale };

				if (tile->center.x > 0 && tile->center.x < state.w) {
					if (tile->center.y > 0 && tile->center.y < state.h) {
						if (GAME::camera.center.x + state.w / 2 > tile->position.x && 
							GAME::camera.center.x + state.w / 2 < tile->position.x + GAME::MAP::tiling.x * GAME::MAP::scale &&
							GAME::camera.center.y + state.h / 2 > tile->position.y &&
							GAME::camera.center.y + state.h / 2 < tile->position.y + GAME::MAP::tiling.y * GAME::MAP::scale
							) {

							SPRITE g = GAME::library.sprite[GAME::library._search("tile-base-camera")];
							g._draw(GAME::MAP::scale, tile->position.x, tile->position.y);
							//GAME::camera.tile = {tile->center.x, tile->center.y};
						}
						else {


							SINT ty = 0;
							if (tile->graphic.size.h != GAME::MAP::tiling.y) {
								ty = tile->position.y - (tile->graphic.size.h - GAME::MAP::tiling.y) * GAME::MAP::scale;
							}
							else {
								ty = tile->position.y;
							}
							tile->graphic._draw(GAME::MAP::scale, tile->position.x, ty);
							if (tile->raining > 0) {
								SPRITE rain = GAME::library.sprite[GAME::library._search("tile-base-rain")];
								rain._draw(GAME::MAP::scale, tile->position.x, ty);
							}
							if (GAME::MAP::debug && tile->occupee != -1) {
								state._set(tile->center.x, tile->center.y, R, 2, 2);
							}
						}
					}
					if (GAME::MAP::debug == 2) {
						STRING steps;
						steps = WRITER::_itc(tile->steps);
						WRITER::_draw({ steps.text, tile->center.x - 5, tile->center.y - 5 }, R);
					}
					/*
					TEXTUAL text;
					STRING pos;
					pos._append(WRITER::_itc(tile->id.x));
					pos._space(".");
					pos._append(WRITER::_itc(tile->id.y));
					text = { pos.text, tile->center.x - 15, tile->center.y - 5, B, 2, 1 };
					WRITER::_draw(text, R);
					*/
				}
			}


			for (DINT b = 0; b < this->creature.length; b++) {
				CREATURE *c = &this->creature[b];
				if (GAME::MAP::debug) {
					for (DINT a = 0; a < c->astar.length - 1; a++) {
						TILE ta = this->tile[this->_getTile(c->astar[a].id.x, c->astar[a].id.y)];
						if (ta.center.x > 0 && ta.center.x < state.w) {
							if (ta.center.y > 0 && ta.center.y < state.h) {
								TILE tb = this->tile[this->_getTile(c->astar[a + 1].id.x, c->astar[a + 1].id.y)];
								SPOT aa = { (double)ta.center.x, (double)ta.center.y };
								SPOT ab = { (double)tb.center.x, (double)tb.center.y };
								LINE line = { aa, ab, 1 , Y };
								line._draw();
							}
						}
					}
				}
				SINT r = this->_getTile(c->movement.current.x, c->movement.current.y);
				if(r != -1){
					TILE tile = this->tile[r];
					if (tile.center.x > 0 && tile.center.x < state.w) {
						if (tile.center.y > 0 && tile.center.y < state.h) {
							c->movement.travelling.x = (tile.center.x + c->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed);
							c->movement.travelling.y = (tile.center.y + c->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed);
							SINT curx = (SINT)(c->movement.travelling.x - c->graphic.size.w / 2 * GAME::MAP::scale / 2), cury = (SINT)(c->movement.travelling.y - c->graphic.size.h / 2 * GAME::MAP::scale / 2);
							//std::cout << "\n> Dir: " << c->movement.direction;
							switch (c->movement.direction) {
							default:
								c->graphic._draw(GAME::MAP::scale / 2, -1, curx, cury);
								break;
							case 2:
							case 4: {
								//std::cout << "\n> " << curx << ", " << cury;
								//std::cout << " - " << c->movement.travelling.x << ", " << c->movement.travelling.y;
								c->graphic._draw(GAME::MAP::scale / 2, -1, curx, cury, 1);
								//c->movement.start = { (double)curx, (double)cury };
							} break;
							case 6:
							case 8: {
								c->graphic._draw(GAME::MAP::scale / 2, -1, curx, cury);
								//c->movement.start = { (double)curx, (double)cury };
							} break;
							}
							//state._set((SINT)c->movement.travelling.x, (SINT)c->movement.travelling.y, PNK, 3, 3);

							COLOR color = G;
							hw = c->graphic.size.w * GAME::MAP::scale / 2 + 2;
							hh = GAME::MAP::scale / 2 + 2;
							hx = c->graphic.size.w / 2 * GAME::MAP::scale / 2; // c->graphic.size.w* GAME::MAP::scale / 2;
							hy = c->graphic.size.h / 2 * GAME::MAP::scale / 2 + GAME::MAP::scale; // (c->graphic.size.h / 2)* GAME::MAP::scale; // -GAME::MAP::scale / 2;
							for (DINT x = 0; x < hw; x++) {
								for (DINT y = 0; y < hh; y++) {
									if (x == 0 || y == 0 || x == hw - 1 || y == hh - 1) {
										if (GAME::selected == b) {
											color = PNK;
										}
										else {
											color = B;
										}
									}
									else {
										if (c->health.point.current == c->health.point.total) {
											color = G;
										}
										else {

											if (((double)x + 0.1) * c->health.point.total / hw <= (double)c->health.point.current) {
												color = G;
											}
											else {
												color = R;
											}
										}
									}
									state._set((SINT)c->movement.travelling.x - hx + x, (SINT)c->movement.travelling.y - hy + y, color);
								}
							}
						}
					}
				}

			}


		}

		
		void _app(const char sprite[], const char name[], SINT gender = -1, DINT movement = ENGINE_TYPE_TILE_MEADOW) {
			CREATURE b = {name, gender};
			SINT r = -1, t = -1, id = -1, x = 0, y = 0;
			//std::cout << "\n>>" << this->tile.length;
			do {
				x = this->dice._roll(GAME::MAP::current.x, GAME::MAP::current.w); // WIDTH
				y = this->dice._roll(GAME::MAP::current.y, GAME::MAP::current.h); // HEIGHT
				r = this->_getTile(x, y);
				t = -1;
				//std::cout << "\n> " << x << ", " << y << "(" << r << ", " << this->tile[r].type<< ")";
				for (DINT c = 0; c < this->creature.size; c++) {
					CREATURE cr = this->creature[c];
					if (cr.movement.to.x == x && cr.movement.to.y == y) {
						t = 1;
						break;
					}
				}
			} while (t == 1 || r == -1 || this->tile[r].type != movement);
			do {
				id = this->dice._roll(0, 999);
				for (DINT c = 0; c < this->creature.size; c++) {
					if (this->creature._exist(c) == 1) {
						if (this->creature[c].tag.id == id) {
							id = -1;
							break;
						}
					}
				}

			} while (id == -1);
			b.tag.id = id;
			b.graphic = GAME::library.animation[GAME::library._asearch(sprite)];
			b.position = { x, y };
			b.movement.current = { this->tile[r].id.x, this->tile[r].id.y };
			b.movement.to = { this->tile[r].id.x, this->tile[r].id.y };
			b.movement.type << movement;
			if (movement == ENGINE_TYPE_TILE_MEADOW) {
				b.movement.type << ENGINE_TYPE_TILE_DESOLATE;
				b.movement.type << ENGINE_TYPE_TILE_ROAD;
			}
			this->creature << b;
			//this->creature[this->creature.last].tag.id = this->creature.last;
			this->tile[r].occupee = this->creature.last;
		}

		SINT _getTile(SINT x, SINT y) {

			for (DINT t = 0; t < this->tile.size; t++) {
				if (this->tile._exist(t) == 1) {
					if (this->tile[t].id.x == x && this->tile[t].id.y == y) return t;
				}
			}
			return -1;
		}

		void _generateTile(SINT x, SINT y) {
			TILE t;
			switch (this->dice._roll(0, 3)) {
			default:
				t._set(ENGINE_TYPE_TILE_MEADOW);
				break;
				/*
			case 1:
				t.graphic = GAME::library.sprite[GAME::library._search("tile-base-grass")];
				t.blocked = 0;
				t.type = ENGINE_TYPE_TILE_MEADOW;
				break;
				*/
			case 2:
				t._set(ENGINE_TYPE_TILE_WATER);
				break;
			case 6:
				t._set(ENGINE_TYPE_TILE_WALL);
				break;
			case 9:
				t._set(ENGINE_TYPE_TILE_TREE);
				break;
			}
			//t.raining = this->dice._roll(0, 1500);
			t.base = t.type;
			t.id = { x, y };
			t.steps = 0;
			t.unstepped = 0;
			this->tile << t;

		}

		SINT _getCreature(DINT id) {
			for (DINT c = 0; c < this->creature.size; c++) {
				if (this->creature._exist(c) == 1) {
					if (this->creature[c].tag.id == id) return c;
				}
			}
			return -1;
		}

		void _towards(CREATURE* creature, POS to) {

			POS s = this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)].id;
			CHART<NODE> positions;
			for (DINT tl = 0; tl < this->tile.length; tl++) {
				if (this->tile._exist(tl) == 1) {
					POS pst = this->tile[tl].id;
					NODE n = {};
					n.x = pst.x;
					n.y = pst.y;
					n.blocked = creature->movement._able(this->tile[tl].type);
					n.parent = nullptr;
					n.checked = 0;
					n.g = INFINITY; // this->random._roll(0, 300);
					n.l = INFINITY;
					n.f = INFINITY;
					n.h = INFINITY;
					n.index = tl;
					n.draw = { this->tile[tl].center.x, this->tile[tl].center.y };
					positions << n;
				}
			}

			for (DINT n = 0; n < positions.length; n++) {
				NODE* cur = &positions[n];
				cur->neighbour << _getNode(positions, cur->x - 1, cur->y, 4);
				cur->neighbour << _getNode(positions, cur->x, cur->y - 1, 8);
				cur->neighbour << _getNode(positions, cur->x, cur->y + 1, 2);
				cur->neighbour << _getNode(positions, cur->x + 1, cur->y, 6);
			}
			CHART <POS> result = _path(&positions, s, to);
			if (result.length > 0) {
				creature->astar._close();
				//result >> result._first();
				for (DINT ps = 0; ps < result.length; ps++) {
					if (result._exist(ps) == 1) {
						SINT res = this->_getTile(result[ps].x, result[ps].y);
						//std::cout << "\n>> " << res;
						if (res >= 0) {
							creature->astar << this->tile[res];
						}
					}
				}
			}
				for (DINT p = 0; p < positions.length; p++) {
					positions[p].neighbour._close();
				}
			positions._close();
			result._close();
		}


		SINT _randomCreature(SINT self = -1) {
			SINT c = -1;
			//do {
				c = this->dice._roll(0, this->creature.length - 1);
			//} while (c == -1);
			return c;
		}


		void _move() {
			SINT x = 0, y = 0, r = -1;
			for (DINT b = 0; b < this->creature.size; b++) {
				if (this->creature._exist(b) == 1) {
					CREATURE* creature = &this->creature[b];
					//SINT f = this->_getTile(creature->movement.current.x, creature->movement.current.y), t = this->_getTile(creature->movement.to.x, creature->movement.to.y);
					TILE* from = &this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)], * to = &this->tile[this->_getTile(creature->movement.to.x, creature->movement.to.y)];
					
					//from->occupee = b;
					//to->occupee = b;
					if (creature->battling == -1) {
						if (from->id.x == to->id.x && from->id.y == to->id.y) creature->movement.arrived = 1;
						if (creature->movement.arrived == 1) {
							if (creature->behaviour.contest > 25) {
								creature->behaviour.contest = 0;
							}
							from->occupee = -1;
							to->occupee = creature->tag.id;
							x = to->id.x;
							y = to->id.y;
							SINT px = from->id.x, py = from->id.y, tx = to->id.x, ty = to->id.y;
							DINT move = 0;
							TILE* next = nullptr;
							switch (this->dice._roll(0, 12)) {
							default:
								break;
							case 2:
								creature->movement.direction = 2;
								move = 1;
								y += 1;
								break;
							case 4:
								creature->movement.direction = 4;
								move = 1;
								x -= 1;
								break;
							case 6:
								creature->movement.direction = 6;
								move = 1;
								x += 1;
								break;
							case 8:
								creature->movement.direction = 8;
								move = 1;
								y -= 1;
								break;
							}
							r = this->_getTile(x, y);
							if (r == -1) {
								if (x <= GAME::MAP::max.w && y <= GAME::MAP::max.h) {
									if (x >= GAME::MAP::max.x && y >= GAME::MAP::max.y) {
										this->_generateTile(x, y);
										r = this->tile.last; // this->_getTile(x, y);
										from = &this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)];
										to = &this->tile[this->_getTile(creature->movement.to.x, creature->movement.to.y)];
										move = 1;
										creature->behaviour.discover = 0;
										//current = &this->tile[this->_getTile(creature->movement.to.x, creature->movement.to.y)];
										//std::cout << "\n> New tile (" << x << ", " << y << "): ";
										//std::cout << r;
									}
								}
							}
							if (move) {
								next = &this->tile[r];
								if (next->occupee == -1 || next->occupee == creature->tag.id) {
									if (creature->movement._able(next->type)) {
										if (to != next) {
											next->occupee = creature->tag.id;
											to->steps++;
											to->unstepped = 0;
											creature->movement.current = { to->id.x, to->id.y };
											creature->movement.to = { next->id.x, next->id.y };
											creature->movement.arrived = 0;
											creature->movement.travelled = { 0.0, 0.0 };
											creature->behaviour.contest++;
										}
									}
								}
								else {
									CREATURE* target = &this->creature[this->_getCreature(next->occupee)];
									if (target->battling == -1) {
										creature->battling = next->occupee;
										target->battling = creature->tag.id;
									}
								}
							}
						}
						else {
							double speed = 0.0;
							switch (from->type) {
							default:
								speed = 1.0;
								break;
							case ENGINE_TYPE_TILE_ROAD:
								speed = 1.8;
								break;
							case ENGINE_TYPE_TILE_GROWTH:
								speed = 0.65;
								break;
							}
							creature->movement._advance(speed);
							SINT fx = from->center.x, fy = from->center.y, tx = to->center.x, ty = to->center.y;

							switch (creature->movement.direction) {
							default:
								break;
							case 2:
								if (fx + creature->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed <= tx) {
									if (fy + creature->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed >= ty) {
										creature->movement.arrived = 1;
									}
								}
								break;
							case 4:
								if (fx + creature->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed <= tx) {
									if (fy + creature->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed <= ty) {
										creature->movement.arrived = 1;
									}
								}
								break;
							case 6:
								if (fx + creature->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed >= tx) {
									if (fy + creature->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed >= ty) {
										creature->movement.arrived = 1;
									}
								}
								break;
							case 8:
								if (fx + creature->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed >= tx) {
									if (fy + creature->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed <= ty) {
										creature->movement.arrived = 1;
									}
								}
								break;
							}
						}
					}
					else {
						SINT battling = this->_getCreature(creature->battling);
						if (creature->health.point.current > 0 && battling >= 0 && this->creature._exist(battling) == 1) {
							creature->move.ready += 0.025 * creature->energy.point.total;
							if (creature->move.ready >= 2.0) {
								if (this->creature._exist(battling) == 1) {
									CREATURE* target = &this->creature[battling];
									SINT damage = creature->strength.point.total - target->guard.point.current;
									//std::cout << "\n>" << b << " - " << creature->strength.point.total << " - " << target->guard.point.current << " = " << damage;
									target->health.point.current -= (damage <= 0) ? (1) : (damage);
									if (target->health.point.current <= 0) {
										TILE* tf = &this->tile[this->_getTile(target->movement.current.x, target->movement.current.y)], * tt = &this->tile[this->_getTile(target->movement.to.x, target->movement.to.y)];
										tf->occupee = -1;
										tt->occupee = -1;
										TILE* cf = &this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)], * ct = &this->tile[this->_getTile(creature->movement.to.x, creature->movement.to.y)];
										cf->occupee = creature->tag.id;
										ct->occupee = creature->tag.id;
										creature->battling = -1;
										creature->behaviour.target = -1;
										if (GAME::selected == battling) GAME::selected = -1;
										this->creature[battling]._die();
										this->creature >> battling;
									}

									creature->move.ready -= 2.0;
								}
								else {
									creature->battling = -1;
								}
							}
						}
					}
				}
			}
		}

		DINT _countTile(DINT type, DINT exist = 1) {
			DINT count = 0;
			for (DINT t = 0; t < this->tile.length; t++) {
				if (this->tile[t].type == type) {
					if (exist == 1) {
						return 1;
					}
					else {
						count++;
					}
				}
			}
			
			return count;
		}

		void _clean() {
			if (GAME::climate) {
				for (DINT t = 0; t < this->tile.length; t++) {
					TILE* tile = &this->tile[t];
					if (tile != nullptr) {
						SINT n = this->_getTile(tile->id.x, tile->id.y - 1), s = this->_getTile(tile->id.x, tile->id.y + 1), w = this->_getTile(tile->id.x - 1, tile->id.y), e = this->_getTile(tile->id.x + 1, tile->id.y);
						if (tile->raining > 0) {
							tile->raining--;
							double amount = 0.0012;
							if (n >= 0 && this->tile[n].type == ENGINE_TYPE_TILE_WATER) tile->moisture += amount;
							if (s >= 0 && this->tile[s].type == ENGINE_TYPE_TILE_WATER) tile->moisture += amount;
							if (w >= 0 && this->tile[w].type == ENGINE_TYPE_TILE_WATER) tile->moisture += amount;
							if (e >= 0 && this->tile[e].type == ENGINE_TYPE_TILE_WATER) tile->moisture += amount;
							tile->moisture += amount;
						}
						else {
							double amount = 0.0003;
							if (n >= 0 && this->tile[n].type == ENGINE_TYPE_TILE_DESOLATE) tile->moisture -= amount;
							if (s >= 0 && this->tile[s].type == ENGINE_TYPE_TILE_DESOLATE) tile->moisture -= amount;
							if (w >= 0 && this->tile[w].type == ENGINE_TYPE_TILE_DESOLATE) tile->moisture -= amount;
							if (e >= 0 && this->tile[e].type == ENGINE_TYPE_TILE_DESOLATE) tile->moisture -= amount;
							tile->moisture -= amount;
						}

						if (tile->moisture < -0.95 && tile->type != ENGINE_TYPE_TILE_DESOLATE) {
							tile->_set(ENGINE_TYPE_TILE_DESOLATE);
						}
						else {
							if (tile->moisture >= 0.1 && tile->type == ENGINE_TYPE_TILE_DESOLATE && tile->type != ENGINE_TYPE_TILE_MEADOW) {
								tile->_set(ENGINE_TYPE_TILE_MEADOW);
							}
							else {
								if (tile->moisture >= 2.75 && tile->type != ENGINE_TYPE_TILE_WATER) {
									tile->_set(ENGINE_TYPE_TILE_WATER);
								}
							}
						}

						tile->unstepped++;
						if (tile->unstepped == ENGINE_DEVELOP_ROAD_DECAY) {
							tile->steps--;
							tile->unstepped = 0;
						}
						if (tile->type != ENGINE_TYPE_TILE_WATER && tile->type != ENGINE_TYPE_TILE_WALL) {
							if (tile->type != ENGINE_TYPE_TILE_ROAD && tile->steps >= ENGINE_DEVELOP_ROAD) {
								tile->_set(ENGINE_TYPE_TILE_ROAD);
							}
						}
					}
				}
			}
		}

		void _climate() {
			switch (this->dice._roll(0, 18)) {
			default:
				break;
			case 6:
				DINT r = this->dice._roll(0, this->tile.length - 1);
				TILE* random = &this->tile[r];
				if(random != nullptr) random->raining += this->dice._roll(0, 1500);

				break;
			}
		}

	};

	MAP map;
	DINT played, debug;
	static DINT climate;
	static SINT selected, selectedTile;
	DICE dice;
	static CODEX library;
	static CAMERA camera;
	void _debug() {
		this->map.enabled = 1;
	}

	void _config() {
		//this->map.tile.debug = 1;
		DINT creatures = 2;
		DINT size = 4;
		GAME::selected = -1;
		GAME::selectedTile = -1;
		GAME::climate = 0;
		GAME::MAP::debug = 1;
		GAME::MAP::targeting = 0;
		GAME::MAP::speed = 0.12;
		GAME::MAP::scale = 2;
		GAME::camera.speed = 0.9;
		GAME::MAP::position = { state.w / 2, state.h / 2 };
		GAME::MAP::max = { -size, -size, size, size };
		this->map._gen(2, 2);

		if (1 == 0) {
			this->map._app("character-veraccus", "Veraccus", 0);
			this->map._app("character-brittany", "Brittany", 0);

		}
		std::cout << "\nConfigured: ";
		//std::cout << GAME::library.move.length << " moves, ";
		std::cout << GAME::library.animation.length << " animations, ";
		std::cout << GAME::library.sprite.length << " sprites, ";
		std::cout << GAME::library.base.length << " basenames, ";
		std::cout << GAME::library.prefix.length << " prefixes, ";
		std::cout << GAME::library.suffix.length << " suffixes";

		//GAME::library._dump();
		//GAME::library._dump();

	}

	void _play() {
		if (this->debug != 1) this->_debug();
		if (this->map.creature.length < 6) {
			switch (this->dice._roll(0, 1)) {
			default:
				if (this->map._countTile(ENGINE_TYPE_TILE_WATER, 1) > 0) {
					if(GAME::climate) this->map._app("blub", "", -1, ENGINE_TYPE_TILE_WATER);
				}
				break;
			case 1:
				if (this->map._countTile(ENGINE_TYPE_TILE_MEADOW, 1) > 0) {
					this->map._app("dummy", "");
				}
				break;
			}
		}
		this->map._clean();
		if(GAME::climate) this->map._climate();
		this->map._move();
		/*
		if (this->map.creature.length < 5) {
			//this->map._appear(GAME::library.animation[this->dice._roll(0, GAME::library.animation.length - 1)], 1);
			switch (this->dice._roll(0, 1)) {
			default:
				break;
			case 0:
				this->map._appear(GAME::library.animation[GAME::library._asearch("blub")], 1);
				break;
			case 1:
				this->map._appear(GAME::library.animation[GAME::library._asearch("spack")], 1);
				break;
			}
			//std::cout << "\n " << this->map.creature[this->map.creature.last].tag.name.text << " has appeared.";
		}
		this->map._clean();
		this->map._battle();
		//this->map._update();
		this->map._movage();
		*/

	}
};
CODEX GAME::library;
DIMENSION GAME::MAP::measure;
DINT GAME::MAP::scale;
DINT GAME::MAP::debug;
DINT GAME::MAP::targeting;
POS GAME::MAP::position;
POS GAME::MAP::tiling;
double GAME::MAP::speed;
GAME::CAMERA GAME::camera;
SINT GAME::selected;
SINT GAME::selectedTile;
DINT GAME::climate;
POS GAME::MAP::init;
POS GAME::MAP::current;
POS GAME::MAP::max;
CHART <GAME::ABILITY> GAME::MAP::action;