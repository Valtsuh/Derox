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

	struct BIOME {
		BIOME() {
			this->moisture = 0.0;
			this->growth = 0.0;
		};
		struct RAIN {
			RAIN() {
				this->duration = 0;
				this->density = 0.0;
			};
			DINT duration;
			double density;

			void _drop() {
				this->duration--;
				if (this->duration == 0) {
					this->density = 0.0;
				}
				else {
					if(this->density < 0.0011) this->density += 0.000002;
				}
			}
		};
		double moisture, growth;
		RAIN rain;
	};
	struct TILE {
		TILE() {
			this->occupee = -1;
			this->type = ENGINE_TYPE_TILE;
			this->base = ENGINE_TYPE_TILE;
			this->state = ENGINE_TYPE_TILE;
			this->duration = -1;
			this->blocked = 0;
		};
		BIOME biome;
		SPRITE graphic;
		POS position, center, origin, id;
		DINT base, type, state, blocked;
		SINT occupee, duration;
		DICE dice;


		void _set(DINT type, DINT state = 0) {
			if (state == 1) {
				this->state = type;
			}
			else {
				this->base = type;
				this->state = type;
				this->type = type;
			}
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
			case ENGINE_TYPE_TILE_GROWTH_BUSH:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-growth-bush")];
				break;
			case ENGINE_TYPE_TILE_WATER:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-water")];
				break;
			case ENGINE_TYPE_TILE_STONE:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-stone")];
				break;
			case ENGINE_TYPE_TILE_MUD:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-mud")];
				break;
			case ENGINE_TYPE_TILE_FIRE:
				this->graphic = GAME::library.sprite[GAME::library._search("tile-base-fire")];
				break;
			}
		}

		void _update(DINT base, SINT n, SINT s, SINT w, SINT e, SINT nw, SINT ne, SINT sw, SINT se) {
			DINT direction = 0;
			switch (base) {
			default:
				break;
			case ENGINE_TYPE_TILE_WATER:
				if(w != ENGINE_TYPE_TILE_WATER && e != ENGINE_TYPE_TILE_WATER && n != ENGINE_TYPE_TILE_WATER && s == ENGINE_TYPE_TILE_WATER) this->graphic = CODEX::sprite[CODEX::_search("tile-water-top-top")];
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

	struct EXPERIENCE {
		EXPERIENCE() {
			this->level._add(1);
		};
		COUNTER level, point;

		void _gain(DINT amount) {
		}
	};

	struct AGE {
		AGE() {
			this->lasted._reset();
			this->time._reset();
			this->base._reset();
		};
		TIME base, time, lasted;
	
		void _lasted() {
			//this->time._reset();
			this->time._increment(this->time);
			DINT ms = this->time._since(1);
			this->lasted._reset();
			for (; ms > 999; ms -= 1000) this->lasted.second += 1;
			for (; this->lasted.second > 59; this->lasted.second -= 60) this->lasted.minute += 1;
			for (; this->lasted.minute > 59; this->lasted.minute -= 60) this->lasted.hour += 1;
			for (; this->lasted.hour > 23; this->lasted.hour -= 24) this->lasted.day += 1;
			this->lasted.millisecond = ms;
		}

	};

	struct ITEM {
		ITEM(double id, const char name[], const char abbr[], const char sprite[]) {
			this->id = id;
			this->name = name;
			this->abbr = abbr;
			//this->graphic = GAME::library._sprite(sprite);
			this->graphic = sprite;
			this->amount = 0;
		};
		ITEM() {
			this->amount = 0;
			this->id = 0.0;
		};

		double id;
		STRING graphic;
		STRING name, abbr;
		DINT amount;

	};

	struct INVENTORY {
		INVENTORY() {
			this->dummy = ENGINE_RESOURCE_DUMMY;
		};

		CHART <ITEM> item;
		ITEM dummy;
		void _trash() {
			this->item._close();

		}

		void _craft(ITEM item) {
			DINT found = 0;
			for (DINT i = 0; i < this->item.length; i++) {
				if (this->item[i].id == item.id) {
					this->item[i].amount++;
					found = 1;
					break;
				}
			}
			if (found == 0) {
				item.amount = 1;
				this->item << item;
			}
		}

		DINT _has(ITEM item) {
			for (DINT i = 0; i < this->item.length; i++) {
				if (this->item[i].id == item.id) return this->item[i].amount;
			}
			return 0;
		}

		void _use(ITEM item, DINT amount) {
			for (DINT i = 0; i < this->item.length; i++) {
				if (this->item[i].id == item.id) {
					this->item[i].amount -= amount;
					break;
				}
			}
		}

		ITEM _select(ITEM item) {

			for (DINT i = 0; i < this->item.length; i++) {
				if (this->item[i].id == item.id) return this->item[i];
			}
			return this->dummy;
		}

	};

	struct CONSTRUCTION {
		CONSTRUCTION(double id, const char name[], const char abbr[], const char graphic[]) {
			this->id = id;
			this->name = name;
			this->abbr = abbr;
			this->graphic = graphic;
			this->duration = -1;
		};
		CONSTRUCTION() {
			this->id = 0.0;
			this->duration = -1;
		};

		double id;
		SINT duration;
		STRING name, abbr, graphic;

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
			this->defeats = 0;
		}
		CREATURE() {
			this->current = 0;
			this->from = 0;
			this->battling = -1;
			this->casted = -1;
			this->defeats = 0;
		};
		TAG tag;
		FIGURE strength, agility, guard, charisma, sense, energy, health;
		SEX sex;
		ANIMATION graphic;
		MOVEMENT movement;
		BEHAVIOUR behaviour;
		INVENTORY inventory;
		EXPERIENCE experience;
		AGE age;
		MOVE move;
		POS position;
		DINT current, from, defeats;
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
			this->inventory._trash();
		}

		void _level(DINT exp) {
			for (DINT p = 0; p < exp; p++) {
				DINT level = this->experience.level.total;
				DINT up = (3 * this->experience.level.total) + 4;
				this->experience.point._add(1);
				if (this->experience.point.current >= up) {
					this->experience.level._add(1);
					this->experience.point.current -= up;
				}
				if (this->experience.level.current > level) {
					this->strength.point._add(this->dice._roll(0, 1));
					this->guard.point._add(this->dice._roll(0, 1));
					//this->agility.point._add(this->dice._roll(0, 1));
				}
			}
		}

		STRING _info(DINT type) {
			STRING string;
			switch (type) {
			default:
				break;
			case ENGINE_TYPE_TEXT_CHARACTER:
				string = this->tag.name.text;
				break;
			case ENGINE_TYPE_TEXT_GENDER:
				string = this->sex.gender.name.text;
				string += " (";
				string += WRITER::_itc(this->tag.id);
				string += ")";
				break;
			case ENGINE_TYPE_TEXT_STRENGTH:
				string = WRITER::_itc(this->strength.point);
				string += " (";
				string += WRITER::_itc(this->behaviour.contest);
				string += ", ";
				string += WRITER::_itc(this->battling);
				string += ", ";
				string += WRITER::_itc(this->behaviour.target);
				string += ")";
				break;
			case ENGINE_TYPE_TEXT_GUARD:
				string = WRITER::_itc(this->guard.point);
				break;
			case ENGINE_TYPE_TEXT_AGILITY:
				string = WRITER::_itc(this->agility.point);
				string += " (";
				string += WRITER::_itc(this->astar.length);
				string += ")";
				break;
			case ENGINE_TYPE_TEXT_HEALTH:
				string = WRITER::_itc(this->health.point);
				string += " / ";
				string += WRITER::_itc(this->health.point.total);
				break;	
			case ENGINE_TYPE_TEXT_EXPERIENCE:
				string = WRITER::_itc(this->experience.point.current);
				string += " / ";
				string += WRITER::_itc(this->experience.point.total);
				string += " (";
				string += WRITER::_itc(this->experience.level.total);
				string += ")";
				break;
			case ENGINE_TYPE_TEXT_TO:
				string = WRITER::_itc(this->movement.arrived);
				string += " / ";
				string += WRITER::_itc(this->movement.direction);
				string += " - ";
				string += WRITER::_itc(this->movement.current.x);
				string += ", ";
				string += WRITER::_itc(this->movement.current.y);
				string += " / ";
				string += WRITER::_itc(this->movement.to.x);
				string += ", ";
				string += WRITER::_itc(this->movement.to.y);
				break;
			case ENGINE_TYPE_TEXT_CHARISMA:
				string = WRITER::_itc(this->charisma.point);
				break;
			case ENGINE_TYPE_TEXT_SENSE:
				string = WRITER::_itc(this->sense.point);
				break;
			}
			return string;

		}

		void _gather(DINT type) {

			ITEM item;
			SINT found = -1;
			switch (type) {
			default:
				item = ENGINE_RESOURCE_DUMMY;
				break;
			case ENGINE_TYPE_TILE_GROWTH:
				item = ENGINE_RESOURCE_BOTANY_GRASS;
				break;
			case ENGINE_TYPE_TILE_GROWTH_BUSH:
				item = ENGINE_RESOURCE_BOTANY_BRANCH;
				break;
			case ENGINE_TYPE_TILE_STONE:
				switch (this->dice._roll(0, 1)) {
				default:
					break;
				case 0:
					item = ENGINE_RESOURCE_GEOLOGY_ROCK;
					break;
				case 1:
					item = ENGINE_RESOURCE_GEOLOGY_ROCK_SHARP;
					break;
				}
				break;
			}
			item.amount = 1;
			for (DINT i = 0; i < this->inventory.item.length; i++) {
				if (this->inventory.item[i].id == item.id) {
					found = i;
					break;
				}
			}
			if (found == -1) {
				this->inventory.item << item;
			}
			else {
				this->inventory.item[found].amount++;
			}

		}

		void _showStats(DINT x, DINT y) {
			struct A {
				A(SPRITE s, STRING t) {
					this->s = s;
					this->t = t;
				}
				A() {};
				SPRITE s;
				STRING t;
			};
			CHART<A> a;

			DINT padding = 5;
			DINT scale = 1;
			A strength = { CODEX::sprite[CODEX::_search("note-strength")], this->_info(ENGINE_TYPE_TEXT_STRENGTH)};
			A agility = { CODEX::sprite[CODEX::_search("note-agility")], this->_info(ENGINE_TYPE_TEXT_AGILITY) };
			A guard = { CODEX::sprite[CODEX::_search("note-guard")], this->_info(ENGINE_TYPE_TEXT_GUARD) };
			A charisma = { CODEX::sprite[CODEX::_search("note-charisma")], this->_info(ENGINE_TYPE_TEXT_CHARISMA) };
			A sense = { CODEX::sprite[CODEX::_search("note-empty")], this->_info(ENGINE_TYPE_TEXT_SENSE) };
			A health = { CODEX::sprite[CODEX::_search("note-health")], this->_info(ENGINE_TYPE_TEXT_HEALTH) };
			A experience = { CODEX::sprite[CODEX::_search("note-experience")], this->_info(ENGINE_TYPE_TEXT_EXPERIENCE) };
			A gender = { CODEX::sprite[CODEX::_search("note-gender")], this->_info(ENGINE_TYPE_TEXT_GENDER) };
			A to = { CODEX::sprite[CODEX::_search("note-to")], this->_info(ENGINE_TYPE_TEXT_TO) };
			A character = { CODEX::sprite[CODEX::_search("note-character")], this->_info(ENGINE_TYPE_TEXT_CHARACTER) };
			a << character;
			a << gender;
			a << health;
			a << experience;
			a << strength;
			a << agility;
			a << guard;
			state._set(x, y, PNK, 100, a[0].s.size.h * a.length + padding * (a.length + 1));
			for (DINT i = 0; i < a.length; i++) {
				SPRITE sprite = a[i].s;
				sprite._position(x + padding, y + padding * (i + 1) + sprite.size.h * scale * i);
				sprite._draw();
				STRING text = a[i].t;
				WRITER::_draw({ text.text, x + padding * 2 + sprite.size.w * scale, sprite.size.y + sprite.size.h / 2 - 5 * scale / 2, B, scale });

			}
			a._close();
		}

	};
	struct SCORE {
		SCORE() {
			this->defeats = 0;
			this->exp = 0;
			this->age._reset();
		};
		DINT defeats, exp;
		TIME age;
		STRING name;

		void _set(const char name[], DINT d, DINT e, TIME age) {
			//std::cout << "\n>>" << d << " , " << this->defeats;
			if (this->defeats < d) {
				this->defeats = d;
				this->exp = e;
				this->name = name;
				this->age = age;
			}

		}

		STRING _text() {
			STRING text;
			text = this->name.text;
			text += "  Defeats: ";
			text += WRITER::_itc(this->defeats);
			text += "  Exp: ";
			text += WRITER::_itc(this->exp);
			text += "  Age: ";
			if (this->age.day > 0) {
				text += WRITER::_itc(this->age.day);
				text += "d ";
				text += WRITER::_itc(this->age.hour);
				text += "h ";
				text += WRITER::_itc(this->age.minute);
				text += "m ";
				text += WRITER::_itc(this->age.second);
				text += "s ";
				text += WRITER::_itc(this->age.millisecond);
				text += "ms ";
			} 
			else {
				if (this->age.hour > 0) {
					text += WRITER::_itc(this->age.hour);
					text += "h ";
					text += WRITER::_itc(this->age.minute);
					text += "m ";
					text += WRITER::_itc(this->age.second);
					text += "s ";
					text += WRITER::_itc(this->age.millisecond);
					text += "ms ";
				}
				else {
					if (this->age.minute > 0) {
						text += WRITER::_itc(this->age.minute);
						text += "m ";
						text += WRITER::_itc(this->age.second);
						text += "s ";
						text += WRITER::_itc(this->age.millisecond);
						text += "ms ";
					}
					else {
						text += WRITER::_itc(this->age.second);
						text += "s ";
						text += WRITER::_itc(this->age.millisecond);
						text += "ms ";
					}
				}
			}



			return text;

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
		static CHART <ANIMATION> action;
		DINT enabled, discovered;
		DICE dice;
		RANDOM random;
		static DINT scale, debug, targeting, bypassSize;
		static DIMENSION measure;
		static POS position, tiling;
		static double speed;
		static POS init, current, max;
		static SCORE score, high;


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
							g.scale = { (double)GAME::MAP::scale, (double)GAME::MAP::scale };
							g._draw(tile->position.x, tile->position.y);
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
							tile->graphic.scale = { (double)GAME::MAP::scale, (double)GAME::MAP::scale };
							tile->graphic._draw(tile->position.x, ty);
							if (tile->biome.rain.duration > 0) {
								SPRITE rain = GAME::library.sprite[GAME::library._search("tile-base-rain")];
								rain.scale = {(double)GAME::MAP::scale, (double)GAME::MAP::scale};
								rain._draw(tile->position.x, ty);
							}
							if (GAME::MAP::debug && tile->occupee != -1) {
								state._set(tile->center.x, tile->center.y, R, 2, 2);
							}
						}
					}
				}
			}
			
			for (DINT b = 0; b < this->creature.size; b++) {
				if (this->creature.exist[b]) {
					CREATURE* c = &this->creature[b];
					if (GAME::MAP::debug) {
						for (DINT a = 0; a < c->astar.length - 1; a++) {
							TILE ta = this->tile[this->_getTile(c->astar[a].id.x, c->astar[a].id.y)];
							if (ta.center.x > 0 && ta.center.x < state.w) {
								if (ta.center.y > 0 && ta.center.y < state.h) {
									TILE tb = this->tile[this->_getTile(c->astar[a + 1].id.x, c->astar[a + 1].id.y)];
									SPOT aa = { (double)ta.center.x, (double)ta.center.y };
									SPOT ab = { (double)tb.center.x, (double)tb.center.y };
									LINE line = { aa, ab, 2 , {c->astar.color.r, c->astar.color.g, c->astar.color.b} };
									line._draw();
								}
							}
						}
					}
					SINT r = this->_getTile(c->movement.current.x, c->movement.current.y);
					if (r != -1) {
						TILE tile = this->tile[r];
						if (tile.center.x > 0 && tile.center.x < state.w) {
							if (tile.center.y > 0 && tile.center.y < state.h) {
								c->movement.travelling.x = (tile.center.x + c->movement.travelled.x * GAME::MAP::scale * GAME::MAP::speed);
								c->movement.travelling.y = (tile.center.y + c->movement.travelled.y * GAME::MAP::scale * GAME::MAP::speed);
								SINT curx = (SINT)(c->movement.travelling.x - c->graphic.size.w / 2 * GAME::MAP::scale / 2), cury = (SINT)(c->movement.travelling.y - c->graphic.size.h / 2 * GAME::MAP::scale / 2);
								//std::cout << "\n> Dir: " << c->movement.direction;
								DINT scale = (GAME::MAP::scale / 2 < 1) ? (1) : (GAME::MAP::scale / 2);
								DINT mirror = 0;
								switch (c->movement.direction) {
								default:
									mirror = 0;
									break;
								case 2:
								case 4: {
									//std::cout << "\n> " << curx << ", " << cury;
									//std::cout << " - " << c->movement.travelling.x << ", " << c->movement.travelling.y;
									mirror = 1;
									//c->movement.start = { (double)curx, (double)cury };
								} break;
								case 6:
								case 8: {
									mirror = 0;
									//c->movement.start = { (double)curx, (double)cury };
								} break;
								}
								for (DINT i = 0; i < c->graphic.sprite.length; i++) {
									c->graphic.sprite[i].scale = { (double)scale, (double)scale };
								}
								c->graphic._draw(curx, cury, mirror);
								c->position = { curx, cury, curx + (DINT)(c->graphic.sprite[0].size.w * c->graphic.sprite[0].scale.x), cury + (DINT)(c->graphic.sprite[0].size.h * c->graphic.sprite[0].scale.y)};
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
						
		}
		
		void _app(const char sprite[], const char name[], SINT gender = -1, DINT movement = ENGINE_TYPE_TILE_MEADOW) {
			CREATURE b = {name, gender};
			SINT r = -1, t = -1, id = -1, x = 0, y = 0;
			//std::cout << "\n>>" << this->tile.length;
			do {
				x = this->dice._roll(GAME::MAP::current.x, GAME::MAP::current.w); // WIDTH
				y = this->dice._roll(GAME::MAP::current.y, GAME::MAP::current.h); // HEIGHT
				r = this->_getTile(x, y);				
				t = this->tile[r].occupee;
				//std::cout << "\n> " << x << ", " << y << "(" << r << ", " << this->tile[r].type<< ")";
				/*
				for (DINT c = 0; c < this->creature.size; c++) {
					CREATURE cr = this->creature[c];
					if (cr.movement.to.x == x && cr.movement.to.y == y) {
						t = 1;
						break;
					}
				}
				*/
			} while (t != -1 || r == -1 || this->tile[r].base != movement);
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
			b.age.time._clock(0);
			b.age.base._clock(0);
			if (movement == ENGINE_TYPE_TILE_MEADOW) {
				b.movement.type << ENGINE_TYPE_TILE_DESOLATE;
				b.movement.type << ENGINE_TYPE_TILE_ROAD;
				//b.movement.type << ENGINE_TYPE_TILE;
			}
			this->creature << b;
			//this->creature[this->creature.last].tag.id = this->creature.last;
			this->tile[r].occupee = b.tag.id;
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
			switch (this->dice._roll(0, 8)) {
			default:
				t._set(ENGINE_TYPE_TILE_MEADOW);
				break;
			case 1:
				t._set(ENGINE_TYPE_TILE_STONE);
				t.blocked = 1;
				break;
			case 2:
				t._set(ENGINE_TYPE_TILE_WATER);
				t.blocked = 1;
				break;
			}
			//t.raining = this->dice._roll(0, 1500);			
			t.id = { x, y };
			this->tile << t; 
			/*
			for (DINT t = 0; t < this->tile.length; t++) {
				TILE* tile = &this->tile[t];
				SINT n = this->_getTile(tile->id.x, tile->id.y - 1), s = this->_getTile(tile->id.x, tile->id.y + 1), w = this->_getTile(tile->id.x - 1, tile->id.y), e = this->_getTile(tile->id.x + 1, tile->id.y);
				SINT nw = this->_getTile(tile->id.x - 1, tile->id.y - 1), ne = this->_getTile(tile->id.x + 1, tile->id.y - 1), sw = this->_getTile(tile->id.x - 1, tile->id.y + 1), se = this->_getTile(tile->id.x + 1, tile->id.y + 1);
				n = (n != -1) ? (this->tile[n].base) : (-1);
				s = (s != -1) ? (this->tile[s].base) : (-1);
				w = (w != -1) ? (this->tile[w].base) : (-1);
				e = (e != -1) ? (this->tile[e].base) : (-1);
				nw = (nw != -1) ? (this->tile[nw].base) : (-1);
				ne = (ne != -1) ? (this->tile[ne].base) : (-1);
				sw = (sw != -1) ? (this->tile[sw].base) : (-1);
				se = (sw != -1) ? (this->tile[se].base) : (-1);
				tile->_update(ENGINE_TYPE_TILE_WATER, n, s, w, e, nw, ne, sw, se);
			}
			*/
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

			//POS s = this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)].id;
			CHART<NODE> positions;
			for (DINT tl = 0; tl < this->tile.length; tl++) {
				if (this->tile._exist(tl) == 1) {
					TILE tile = this->tile[tl];
					POS pst = tile.id;
					NODE n = {};
					n.x = pst.x;
					n.y = pst.y;
					n.blocked = !creature->movement._able(tile.base);
					//std::cout << "\nBlock: " << n.blocked;
					n.parent = nullptr;
					n.checked = 0;
					n.g = INFINITY; // this->random._roll(0, 300);
					n.l = INFINITY;
					n.f = INFINITY;
					n.h = INFINITY;
					n.index = tl;
					n.draw = { tile.center.x, tile.center.y };
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
			CHART <POS> result = _path(&positions, creature->movement.current, to);
			
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
				//creature->astar >> creature->astar._first();
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

		void _construct() {

		}

		void _move() {
			SINT x = 0, y = 0, r = -1;
			for (DINT b = 0; b < this->creature.size; b++) {
				if (this->creature._exist(b) == 1) {
					CREATURE* creature = &this->creature[b];
					TILE* from = &this->tile[this->_getTile(creature->movement.current.x, creature->movement.current.y)], * to = &this->tile[this->_getTile(creature->movement.to.x, creature->movement.to.y)];
					if (creature->battling == -1) {
						if (from->id.x == to->id.x && from->id.y == to->id.y) creature->movement.arrived = 1;
						if (creature->movement.arrived == 1) {
							if (creature->behaviour.contest > 25) {
								creature->behaviour.contest = 0;
							}

							if (to->state == ENGINE_TYPE_TILE_MUD){
								if (creature->inventory._has(ENGINE_ITEM_BANDAGE) < 2) {
									if (creature->inventory._has(ENGINE_RESOURCE_BOTANY_GRASS) >= 3) {
										creature->inventory._use(ENGINE_RESOURCE_BOTANY_GRASS, 3);
										creature->inventory._craft(ENGINE_ITEM_BANDAGE);
										//std::cout << "\n>" << creature->tag.name.text << " has crafted a bandage";
									}
								}
								if (creature->inventory._has(ENGINE_ITEM_PICKAXE) == 0) {
									if (creature->inventory._has(ENGINE_RESOURCE_BOTANY_GRASS) >= 8) {
										if (creature->inventory._has(ENGINE_RESOURCE_GEOLOGY_ROCK_SHARP) >= 2) {
											if (creature->inventory._has(ENGINE_RESOURCE_GEOLOGY_ROCK) >= 1) {
												creature->inventory._use(ENGINE_RESOURCE_BOTANY_GRASS, 8);
												creature->inventory._use(ENGINE_RESOURCE_GEOLOGY_ROCK_SHARP, 2);
												creature->inventory._use(ENGINE_RESOURCE_GEOLOGY_ROCK, 1);
												creature->inventory._craft(ENGINE_ITEM_PICKAXE);
												//std::cout << "\n>" << creature->tag.name.text << " has crafted a pickaxe";
											}
										}
									}
								}
							}

							from->occupee = -1;
							to->occupee = creature->tag.id;
							x = to->id.x;
							y = to->id.y;
							SINT px = from->id.x, py = from->id.y, tx = to->id.x, ty = to->id.y;
							DINT move = 0;
							TILE* next = nullptr;
							if (creature->astar.length == 0) {
								switch (this->dice._roll(0, 12)) {
								default:
									break;
								case 2:
									move = 1;
									y += 1;
									break;
								case 4:
									move = 1;
									x -= 1;
									break;
								case 6:
									move = 1;
									x += 1;
									break;
								case 8:
									move = 1;
									y -= 1;
									break;
								case 12:
									if (ENGINE_USE_PATHING) {
										POS p;
										DINT f = 0;
										TILE tile;
										do {
											p.x = this->dice._roll(GAME::MAP::max.x, GAME::MAP::max.w);
											p.x = this->dice._roll(GAME::MAP::max.y, GAME::MAP::max.h);
											DINT t = this->dice._roll(0, this->tile.length - 1);
											tile = this->tile[t];
										} while (!creature->movement._able(tile.base) && tile.id != creature->movement.current);
										this->_towards(creature, tile.id);
										break;
									}
								}
							}

							if (creature->astar.length > 0) {
								SINT res = creature->astar._last();
								if (res >= 0) {
									TILE as = creature->astar[res];
									x = as.id.x;
									y = as.id.y;
									move = 1;
								}
							}

							if (move) {
								r = this->_getTile(x, y);

								if (r == -1) {
									if (x <= GAME::MAP::max.w && y <= GAME::MAP::max.h || GAME::MAP::bypassSize) {
										if (x >= GAME::MAP::max.x && y >= GAME::MAP::max.y || GAME::MAP::bypassSize) {
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
								next = &this->tile[r];
								if (next->occupee == -1 || next->occupee == creature->tag.id) {
									if (next->base == ENGINE_TYPE_TILE_STONE) {
										if (this->dice._percent(25)) {
											creature->_gather(ENGINE_TYPE_TILE_STONE);
										}
									}
									if (next->state == ENGINE_TYPE_TILE_GROWTH_BUSH) {
										if(creature->inventory._has(ENGINE_RESOURCE_GEOLOGY_ROCK) >= 2){
											if (creature->inventory._has(ENGINE_RESOURCE_BOTANY_BRANCH) >= 24) {
												creature->inventory._use(ENGINE_RESOURCE_BOTANY_BRANCH, 24);
												creature->inventory._use(ENGINE_RESOURCE_GEOLOGY_ROCK, 2);
												next->_set(ENGINE_TYPE_TILE_FIRE, 1);
												next->duration = 50;
											}
										}
									}
									if (creature->movement._able(next->base)) {
										//if (to != next) {
											next->occupee = creature->tag.id;
											if(to->biome.growth >= 12.5){
												creature->_gather(ENGINE_TYPE_TILE_GROWTH_BUSH);
												to->biome.growth -= 7.5;
												to->biome.moisture -= 0.175;
											}
											else {
												if (to->biome.growth >= 5.0) {
													creature->_gather(ENGINE_TYPE_TILE_GROWTH);
													to->biome.growth -= 5.0;
													to->biome.moisture -= 0.125;
												}
												else {
													to->biome.growth -= 2.75;
													to->biome.moisture -= 0.045;
												}
											}
											creature->movement.current = { to->id.x, to->id.y };
											creature->movement.to = { next->id.x, next->id.y };
											creature->movement.direction = creature->movement.current._direction(next->id);
											creature->movement.arrived = 0;
											creature->movement.travelled = { 0.0, 0.0 };
											creature->behaviour.contest.current++;
											if (creature->behaviour.contest.current >= 8) {
												if (creature->health.point.current < creature->health.point.total) {
													creature->health.point.current += 1;
												}
											}
											if (creature->astar.length > 0) creature->astar >> creature->astar._last();
										//}
									}
								}
								else {
									CREATURE* target = &this->creature[this->_getCreature(next->occupee)];
									if (target->battling == -1) {
										creature->battling = next->occupee;
										target->battling = creature->tag.id;
										creature->behaviour.contest.current = 0;
										target->behaviour.contest.current = 0;
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
						if (battling >= 0){ 
							if (this->creature._exist(battling) == 1) {
								if (creature->health.point.current > 0) {
									creature->move.ready += 0.025 * creature->energy.point.total;
									if (creature->health.point < creature->health.point.total - 5) {
										if (creature->inventory._has(ENGINE_ITEM_BANDAGE) > 0) {
											creature->inventory._use(ENGINE_ITEM_BANDAGE, 1);
											creature->health.point.current += 4;
										}
									}
									if (creature->move.ready >= 5.0) {
										CREATURE* target = &this->creature[battling];
										SINT damage = creature->strength.point.total - target->guard.point.current;
										//std::cout << "\n>" << b << " - " << creature->strength.point.total << " - " << target->guard.point.current << " = " << damage;
										target->health.point.current -= (damage <= 0) ? (1) : (damage);
										ANIMATION slash = GAME::library.animation[GAME::library._asearch("slash")];
										slash.target = target->tag.id;
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
											target->age._lasted();
											GAME::MAP::high._set(target->tag.name.text, target->defeats, target->experience.point.total, target->age.lasted);
											this->creature[battling]._die();
											this->creature >> battling;
											creature->_level(1);
											creature->defeats++;
											creature->age._lasted();
											GAME::MAP::score._set(creature->tag.name.text, creature->defeats, creature->experience.point.total, creature->age.lasted);
										}

										creature->move.ready -= 5.0;
									}
								}
							}
							else {
								creature->battling = -1;
								creature->behaviour.target = -1;
							}
						}
						else {
							creature->battling = -1;
							creature->behaviour.target = -1;
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
			for (DINT t = 0; t < this->tile.length; t++) {
				TILE* tile = &this->tile[t];
				if (tile->state == ENGINE_TYPE_TILE_GROWTH) tile->biome.moisture -= 0.00025; else {
					tile->biome.moisture -= 0.00001;
				}
				if (GAME::climate) {
					if (tile->biome.rain.duration > 0) {
						tile->biome.rain._drop();
						tile->biome.moisture += tile->biome.rain.density;
					}
					
				}
				if (tile->base == ENGINE_TYPE_TILE_WATER) {
					
					/*
					if (this->tile[s].base == ENGINE_TYPE_TILE_WATER) {
						if (this->tile[w].base == ENGINE_TYPE_TILE_WATER) {
							if (this->tile[e].base == ENGINE_TYPE_TILE_WATER) {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
							else {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
						}
						else {
							if (this->tile[e].base == ENGINE_TYPE_TILE_WATER) {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
							else {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
						}
					}
					else {
						if (this->tile[w].base == ENGINE_TYPE_TILE_WATER) {
							if (this->tile[e].base == ENGINE_TYPE_TILE_WATER) {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
							else {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 2;
								}
								else {
									d = 2;
								}
							}
						}
						else {
							if (this->tile[e].base == ENGINE_TYPE_TILE_WATER) {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 1;
								}
								else {
									d = 2;
								}
							}
							else {
								if (this->tile[n].base == ENGINE_TYPE_TILE_WATER) {
									d = 21;
								}
								else {
									d = 5;
								}
							}
						}
					}
					tile->_update(ENGINE_TYPE_TILE_WATER, d);
					*/
				}
				if (tile->base == ENGINE_TYPE_TILE_MEADOW) {
					if (tile->state != ENGINE_TYPE_TILE_FIRE) {
						tile->biome.growth += ENGINE_TILE_GROWTH;
						if (tile->biome.growth >= 12.5 && tile->state != ENGINE_TYPE_TILE_GROWTH_BUSH) {
							tile->_set(ENGINE_TYPE_TILE_GROWTH_BUSH, 1);
						}
						else {
							if (tile->biome.growth < 12.5 && tile->biome.growth >= 5.0 && tile->state != ENGINE_TYPE_TILE_GROWTH) {
								tile->_set(ENGINE_TYPE_TILE_GROWTH, 1);
								//tile->graphic = GAME::library.sprite[GAME::library._search("tile-base-growth")];
							}
							else {
								if (tile->biome.growth < 5.0 && tile->state != ENGINE_TYPE_TILE_MEADOW) {
									if (tile->biome.moisture >= 2.5 && tile->state != ENGINE_TYPE_TILE_MUD) {
										tile->_set(ENGINE_TYPE_TILE_MUD, 1);
									}
									else {
										if (tile->biome.moisture < 2.5) {
											tile->_set(ENGINE_TYPE_TILE_MEADOW, 1);
										}
									}
									//tile->graphic = GAME::library.sprite[GAME::library._search("tile-base-grass")];
								}
							}
						}
					}
					else {						
						if (tile->biome.growth >= 0) {
							tile->biome.growth -= 0.1;
							tile->duration += 1;
						}
						else {
							tile->duration -= 1;
						}
						if (tile->duration <= 0) {
							tile->_set(ENGINE_TYPE_TILE_MEADOW, 1);
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
				if(random != nullptr) random->biome.rain.duration += this->dice._roll(0, 1500);

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
	static bool paint;
	void _debug() {
		this->map.enabled = 1;
	}

	void _config() {
		//this->map.tile.debug = 1;
		DINT size = 6;
		GAME::selected = -1;
		GAME::selectedTile = -1;
		GAME::climate = 1;
		GAME::MAP::debug = 1;
		GAME::MAP::targeting = 0;
		GAME::MAP::speed = 0.12;
		GAME::MAP::scale = 5;
		GAME::camera.speed = 0.9;
		GAME::MAP::position = { state.w / 2, state.h / 2 };
		GAME::MAP::bypassSize = 0;
		GAME::MAP::max = { -size, -size, size, size };
		this->map._gen(4, 4);
		GAME::paint = false;

		if (1 == 0) {
			this->map._app("character-veraccus", "Veraccus", 0);
			this->map._app("character-brittany", "Brittany", 0);

		}
		/*
		std::cout << "\nConfigured: ";
		std::cout << GAME::library.animation.length << " animations, ";
		std::cout << GAME::library.sprite.length << " sprites, ";
		std::cout << GAME::library.base.length << " basenames, ";
		std::cout << GAME::library.prefix.length << " prefixes, ";
		std::cout << GAME::library.suffix.length << " suffixes";
		*/
		//GAME::library._dump();
		//GAME::library._dump();
		this->played = 1;

	}

	void _play() {
		if (this->debug != 1) this->_debug();
		if (this->map.creature.length < 6) {
			switch (this->dice._roll(0, 1)) {
			default:
				if (this->map._countTile(ENGINE_TYPE_TILE_WATER, 1) > 0) {
					//if(GAME::climate) this->map._app("blub", "", -1, ENGINE_TYPE_TILE_WATER);
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
DINT GAME::MAP::bypassSize;
POS GAME::MAP::position;
POS GAME::MAP::tiling;
double GAME::MAP::speed;
bool GAME::paint;
GAME::CAMERA GAME::camera;
SINT GAME::selected;
SINT GAME::selectedTile;
DINT GAME::climate;
POS GAME::MAP::init;
POS GAME::MAP::current;
POS GAME::MAP::max;
CHART <ANIMATION> GAME::MAP::action;
GAME::SCORE GAME::MAP::score;
GAME::SCORE GAME::MAP::high;