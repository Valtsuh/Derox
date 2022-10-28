struct ART {

	struct NOTE {
		NOTE(const char icon[], DINT x, DINT y) {
			this->icon = GAME::library.sprite[GAME::library._search(icon)];
			this->position.x = x;
			this->position.y = y;
			this->position.h = y + this->icon.size.h * this->icon.scale + 2;
			this->position.w = this->icon.size.w * this->icon.scale;
			this->text.x = 3 + this->position.x + this->position.w;
			this->text.y = this->position.y + 5;
		};
		NOTE() {};
		POS position;
		SPRITE icon;
		TEXTUAL text;


		void _draw() {
			this->icon._draw(1, this->position.x, this->position.y);
			WRITER::_draw(this->text);
		}

		void _set(STRING text) {
			this->text._update(text.text);
		}

	};

	struct BOX {
		BOX(DINT x, DINT y) {
			this->bg = PNK;
			this->size.x = x;
			this->size.y = y;
			this->scale = 1;
			this->gender = { "note-gender", this->size.x, this->size.y };
			this->str = { "note-strength", this->size.x, this->gender.position.h };
			this->grd = { "note-guard", this->size.x, this->str.position.h };
			this->agi = { "note-agility", this->size.x, this->grd.position.h };
			this->hlt = { "note", this->size.x, this->agi.position.h };
		};
		BOX() {
			this->scale = 1;
		};

		DIMENSION size;
		COLOR bg;
		DINT scale;
		NOTE gender, str, grd, agi, hlt;
		TEXTUAL info;
		void _draw() {
			state._set(this->size.x - 2, this->size.y - 2, this->bg, this->gender.position.w + 50, this->hlt.position.h);
			this->gender._draw();
			this->str._draw();
			this->grd._draw();
			this->agi._draw();
			this->hlt._draw();
			WRITER::_draw(this->info);
		}
	};
};