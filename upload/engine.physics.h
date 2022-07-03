
struct SQUARE {
	SQUARE(double x, double y, double size, double angle = 90.0, COLOR color = {}) {
		this->gravity = 1.0;
		this->weight = 2.0;
		this->angle = angle;
		this->size = size;
		if (this->lines.length > 0) {
			delete[] this->lines.item;
			delete[] this->lines.exist;
		}
		LINE line = { (DINT)x, (DINT)y, 0.0, 0.0, size, 0.0, color };
		this->lines << line;
		this->line[0] = line;
		line = { (DINT)x, (DINT)y, size, 0.0, size, size, color };
		this->lines << line;
		this->line[1] = line;
		line = { (DINT)x, (DINT)y, size, size, 0.0, size, color };
		this->lines << line;
		this->line[2] = line;
		line = { (DINT)x, (DINT)y, 0.0, size, 0.0, 0.0, color };
		this->lines << line;
		this->line[3] = line;
		this->position = { x, y, 0 };
		this->center = { x + size / 2, y + size / 2, 0 };
		this->_rotate(0.0);
	
	}
	SQUARE() {
		this->angle = 0.0;
		this->weight = 1.0;
		this->gravity = 0.5;
		this->size = 1.0;
	};
	SPOT center, position;
	POSITION rotational;
	CHART <LINE> lines;
	double angle, gravity, weight, size;
	LINE line[4];

	void _draw(HDC tool, SINT x = -1, SINT y = -1) {
		LINE line = {};
		for (DINT l = 0; l < 4; l++) {
			line = this->lines.item[l];
			line._draw(tool);
		}
	}

	void _rotate(double velocity = 0.0) {
		if (this->angle >= 360.0 || this->angle <= -360.0) {
			this->angle = 0.0;
		}

		double fx, fy, tx, ty, corner = 90.0;
		if (velocity != 0.0) {
			this->rotational.velocity.x = velocity;
			this->angle += this->rotational.velocity.x;
		}
		for (DINT l = 0; l < this->lines.length; l++) {

			/*
			fx = this->position.x + (double)(this->size / 2) * MATH::_cos((DINT)this->angle + l * 45, 0.001);
			fy = this->position.y + (double)(this->size / 2) * MATH::_sin((DINT)this->angle + l * 45, 0.001);
			*/
			if (l == 0) {
				fx = (this->size / 2.0) * MATH::_cos(this->angle + 3.0 * corner, 0.001);
				fy = (this->size / 2.0) * MATH::_sin(this->angle + 3.0 * corner, 0.001);
			}
			else {
				fx = this->lines.item[l - 1].to.x;
				fy = this->lines.item[l - 1].to.y;
			}

			tx = (this->size / 2.0) * MATH::_cos(this->angle + (double)l * corner, 0.001);
			ty = (this->size / 2.0) * MATH::_sin(this->angle + (double)l * corner, 0.001);
			//this->line[l] = { (DINT)this->center.x, (DINT)this->center.y, fx, fy, tx, ty };
			this->lines.item[l] = { (DINT)this->center.x, (DINT)this->center.y, fx, fy, tx, ty, this->lines.item[l].color};

		}

	}


	void _set(double velocity = 0.0, double angle = 0.0) {
		if (angle != 0.0) {
			this->angle = angle;
		}

		if (velocity != 0.0) {
			this->rotational.velocity.x = velocity;
		}
	}

	void _naturate(DIMENSION border) {
	}

};

struct DOLL {
	DOLL() {
		this->scale = 1.5;
		this->weight = 0.0;
		this->gravity = 0.0;
		this->exist = 0;
	}
	struct LIMB {
		LIMB(double x = 0.0, double y = 0.0, double size = 0.0, double angle = 90.0, COLOR color = {}) {
			this->part = { x, y, size, angle, color };
			this->weight = 0.0;
			this->gravity = 0.0;
			this->velocity = 0.0;
			this->resistance = 0.0;
			this->angle = 90;
			this->length = 0.0;
		}
		double angle, weight, gravity, velocity, resistance, length;
		CRCL part;

	};

	struct RAC {
		RAC() {
			this->weight = 0.0;
			this->gravity = 0.0;
			this->velocity = 0.0;
			this->resistance = 0.0;
			this->angle = 90;
			this->length = 0.0;
		}
		double angle, weight, gravity, velocity, resistance, length;
		LINE part;

	};


	struct ARM {
		ARM(DINT x = 0, DINT y = 0, double bx = 0, double by = 0, double angle = 270.0, double top = 10.0, double bottom = 7.0, double scale = 1.0) {
			this->scale = scale;
			this->top.length = top * this->scale;
			this->top.part = { x, y, bx, by, bx + this->top.length * MATH::_cos(angle, 0.001), by + this->top.length * MATH::_sin(angle, 0.001) };
			this->top.angle = angle;
			this->gravity = 1.0;
			this->weight = 0.0;
			this->weight += top * 0.25;
			this->bottom.angle = 270;
			this->bottom.length = bottom * this->scale;
			this->bottom.part = { x, y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + this->bottom.length * MATH::_cos(this->bottom.angle, 0.001), this->top.part.to.y + this->bottom.length * MATH::_sin(this->bottom.angle, 0.001) };
			this->weight += bottom * 0.15;
			this->_joint();
			this->weight += this->shoulder.part.radius * 0.25;
			this->weight += this->elbow.part.radius * 0.25;
			this->weight += this->hand.part.radius * 0.15;
			this->weight *= 0.25;


		}

		double weight, gravity, scale;
		RAC top, bottom;
		LIMB hand, elbow, shoulder;


		void _draw(HDC tool) {
			LINE top, bottom;
			top = this->top.part;
			top._draw(tool);
			this->shoulder.part._draw(tool);
			this->elbow.part._draw(tool);
			bottom = this->bottom.part;
			bottom._draw(tool);
			this->hand.part._draw(tool);
		}

		void _stretch() {
			if (this->top.angle <= 360.0) {
				if (this->top.angle <= 180.0) {
					this->top.velocity += this->top.weight * this->top.gravity;
				}
				else {
					this->top.velocity -= this->top.resistance * this->top.weight * this->top.gravity;
				}
				this->top.angle += this->top.velocity;
			}
			else {
				this->top.angle = 0.0;
			}

			//std::cout << "\nArm 1 at (" << this->top.part.position.x << ", " << this->top.part.position.y << ") " << this->top.part.from.x << ", " << this->top.part.from.y << " - ";
			//std::cout << this->top.part.to.x << ", " << this->top.part.to.y;
			this->top.part = { (DINT)this->top.part.position.x, (DINT)this->top.part.position.y, this->top.part.from.x, this->top.part.from.y, this->top.part.from.x + (double)this->top.length * MATH::_cos((SINT)this->top.angle, 0.001), this->top.part.from.y + (double)this->top.length * MATH::_sin((SINT)this->top.angle, 0.001) };
			this->bottom.part = { (DINT)this->bottom.part.position.x, (DINT)this->bottom.part.position.y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + (double)this->bottom.length * MATH::_cos((SINT)this->bottom.angle, 0.001), this->top.part.to.y + (double)this->bottom.length * MATH::_sin((SINT)this->bottom.angle, 0.001) };
			//std::cout << "\nElbow 1 at " << this->elbow.center.x << ", " << this->elbow.center.y;
			this->_joint();

		}

		void _loosen() {
			if (this->top.angle >= 360.0) this->top.angle = 0.0;
			if (this->bottom.angle >= 360.0) this->bottom.angle = 0.0;
			this->top.velocity += this->top.weight * this->top.gravity;
			if (this->top.angle != 90.0) {
				if (this->top.angle <= 270.0 && this->top.angle > 90.0) {
					this->top.angle -= this->top.velocity;
				}
				else {
					this->top.velocity = 0.0;
					this->top.angle = 90.0;
				}
				if (this->top.angle > 270.0 && this->top.angle < 90.0) {
					this->top.angle += this->top.velocity;
				}
				else {
				}
			}
			this->bottom.angle = 90.0;
			//std::cout << "\nArm 2 at (" << this->top.part.position.x << ", " << this->top.part.position.y << ") " << this->top.part.from.x << ", " << this->top.part.from.y << " - ";
			//std::cout << this->top.part.to.x << ", " << this->top.part.to.y;

			this->top.part = { (DINT)this->top.part.position.x, (DINT)this->top.part.position.y, this->top.part.from.x, this->top.part.from.y, this->top.part.from.x + (double)this->top.length * MATH::_cos((SINT)this->top.angle, 0.001), this->top.part.from.y + (double)this->top.length * MATH::_sin((SINT)this->top.angle, 0.001) };
			this->bottom.part = { (DINT)this->bottom.part.position.x, (DINT)this->bottom.part.position.y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + (double)this->bottom.length * MATH::_cos((SINT)this->bottom.angle, 0.001), this->top.part.to.y + (double)this->bottom.length * MATH::_sin((SINT)this->bottom.angle, 0.001) };
			this->_joint();
		}
		
		void _straighten(double to = 90.0, double direction = 1.0) {
			if (this->top.angle != to) {
				if(this->top.velocity == 0.0) this->top.velocity = (this->weight * this->gravity);
				if (this->top.angle < to) {
					this->top.angle += this->top.velocity;
				}
				if(this->top.angle > to) {
					this->top.angle -= this->top.velocity;
					if (this->top.angle > to && this->top.angle < to - this->top.velocity) {
						this->top.angle = to;
					}
				}

			}
			else {
				this->top.velocity = 0.0;
			}
			if (this->bottom.angle != this->top.angle) {
				if (this->bottom.angle > this->top.angle) {
					this->bottom.angle -= this->weight * this->gravity;
					if (this->bottom.angle < this->top.angle) this->bottom.angle = this->top.angle;
				}
				else {
					this->bottom.angle += this->weight * this->gravity;
					if (this->bottom.angle > this->top.angle) this->bottom.angle = this->top.angle;
				}
			}
			this->top.part = { (DINT)this->top.part.position.x, (DINT)this->top.part.position.y, this->top.part.from.x, this->top.part.from.y, this->top.part.from.x + (double)this->top.length * MATH::_cos((SINT)this->top.angle, 0.001), this->top.part.from.y + (double)this->top.length * MATH::_sin((SINT)this->top.angle, 0.001) };
			this->bottom.part = { (DINT)this->bottom.part.position.x, (DINT)this->bottom.part.position.y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + (double)this->bottom.length * MATH::_cos((SINT)this->bottom.angle, 0.001), this->top.part.to.y + (double)this->bottom.length * MATH::_sin((SINT)this->bottom.angle, 0.001) };

			this->_joint();
		}
		void _joint() {
			this->shoulder = { this->top.part.position.x + this->top.part.from.x, this->top.part.position.y + this->top.part.from.y, 1.5 * this->scale, 90.0, DGR };
			this->elbow = { this->top.part.position.x + this->top.part.to.x, this->top.part.position.y + this->top.part.to.y, 1.5 * this->scale, 90.0, R };
			this->hand = { this->bottom.part.position.x + this->bottom.part.to.x, this->bottom.part.position.y + this->bottom.part.to.y, 2.5 * this->scale, 90.0, PNK };
		}
	};

	struct LEG {
		LEG(DINT x = 0, DINT y = 0, double bx = 0, double by = 0, double angle = 90.0, double top = 10.0, double bottom = 7.0, double scale = 1.0) {

			this->scale = scale;
			this->top.length = top * this->scale;
			this->top.part = { x, y, bx, by, bx + this->top.length * MATH::_cos(angle, 0.001), by + this->top.length * MATH::_sin(angle, 0.001) };
			this->top.angle = angle;
			this->weight = 0.0;
			this->gravity = 1.0;
			this->weight += top * 0.25;
			this->bottom.angle = 90.0;
			this->bottom.length = bottom * this->scale;
			this->bottom.part = { x, y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + this->bottom.length * MATH::_cos(this->bottom.angle, 0.001), this->top.part.to.y + this->bottom.length * MATH::_sin(this->bottom.angle, 0.001) };
			this->weight += bottom * 0.15;
			this->_joint();
			this->weight += this->pelvis.part.radius * 0.25;
			this->weight += this->knee.part.radius * 0.25;
			this->weight += this->foot.part.radius * 0.15;
			this->weight *= 0.25;
			//*/

		}

		double weight, gravity, scale;
		RAC top, bottom;
		LIMB foot, knee, pelvis;

		void _draw(HDC tool) {
			LINE top, bottom;
			top = this->top.part;

			top._draw(tool);
			this->pelvis.part._draw(tool);
			this->knee.part._draw(tool);
			bottom = this->bottom.part;
			bottom._draw(tool);
			this->foot.part._draw(tool);
		}

		void _rotate() {

			if (this->top.angle >= 360.0) this->top.angle = 0.0;

			this->top.angle += 2.5;


			this->top.part = { (DINT)this->top.part.position.x, (DINT)this->top.part.position.y, this->top.part.from.x, this->top.part.from.y, this->top.part.from.x + this->top.length * MATH::_cos(this->top.angle, 0.001), this->top.part.from.y + this->top.length * MATH::_sin(this->top.angle, 0.001) };
			this->bottom.part = { (DINT)this->bottom.part.position.x, (DINT)this->bottom.part.position.y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + this->bottom.length * MATH::_cos(this->bottom.angle, 0.001), this->top.part.to.y + this->bottom.length * MATH::_sin(this->bottom.angle, 0.001) };
			this->_joint();

		}

		void _straighten(double to = 90.0) {
			if (this->top.angle >= 270.0) {
				this->top.angle += this->weight * this->gravity;
				if (this->top.angle > to) this->top.angle = to;
			}
			if (this->top.angle < 270.0) {
				this->top.angle -= this->weight * this->gravity;
				if (this->top.angle < to) this->top.angle = to;
			}
			if (this->bottom.angle > this->top.angle) {
				this->bottom.angle -= this->weight * this->gravity;
				if (this->bottom.angle < this->top.angle) this->bottom.angle = this->top.angle;
			}
			else {
				this->bottom.angle += this->weight * this->gravity;
				if (this->bottom.angle > this->top.angle) this->bottom.angle = this->top.angle;
			}
			this->top.part = { (DINT)this->top.part.position.x, (DINT)this->top.part.position.y, this->top.part.from.x, this->top.part.from.y, this->top.part.from.x + this->top.length * MATH::_cos(this->top.angle, 0.001), this->top.part.from.y + this->top.length * MATH::_sin(this->top.angle, 0.001) };
			this->bottom.part = { (DINT)this->bottom.part.position.x, (DINT)this->bottom.part.position.y, this->top.part.to.x, this->top.part.to.y, this->top.part.to.x + this->bottom.length * MATH::_cos(this->bottom.angle, 0.001), this->top.part.to.y + this->bottom.length * MATH::_sin(this->bottom.angle, 0.001) };
			this->_joint();
		}


		void _joint() {

			this->pelvis = { this->top.part.position.x + this->top.part.from.x, this->top.part.position.y + this->top.part.from.y, 1.5 * this->scale, 90.0, DGR };
			this->knee = { this->top.part.position.x + this->top.part.to.x, this->top.part.position.y + this->top.part.to.y, 1.5 * this->scale, 90.0, R };
			this->foot = { this->bottom.part.position.x + this->bottom.part.to.x, this->bottom.part.position.y + this->bottom.part.to.y, 2.5 * this->scale, 90.0, PNK };
		}


	};

	struct HEAD {
		HEAD(DINT x = 0, DINT y = 0, double bx = 0, double by = 0, double angle = 270.0, double length = 12.0, double scale = 1.0) {
			this->scale = scale;
			this->neck.length = length * this->scale;
			this->neck.part = { x, y, bx, by, bx + this->neck.length * MATH::_cos(angle, 0.001), by - this->neck.length * MATH::_sin(angle, 0.001) - 1.5 * this->scale};
			this->neck.angle = angle;
			this->_joint();
		}

		RAC neck;
		LIMB cranium, top, bottom;
		double weight, scale;


		void _draw(HDC tool) {
			LINE neck;
			neck = this->neck.part;
			neck._draw(tool);
			this->cranium.part._draw(tool);
			this->top.part._draw(tool);
			this->bottom.part._draw(tool);
		}

		void _stretch() {
			if (this->neck.angle >= 360.0) this->neck.angle = 0.0;
			this->neck.angle += 2.5;

			this->neck.part = { (DINT)this->neck.part.position.x, (DINT)this->neck.part.position.y, this->neck.part.from.x, this->neck.part.from.y, this->neck.part.from.x + this->neck.length * MATH::_cos(this->neck.angle, 0.001), this->neck.part.from.y + this->neck.length * MATH::_sin(this->neck.angle, 0.001) - 1.5 * this->scale};
			this->_joint();

		}

		void _joint() {
			this->cranium = { this->neck.part.position.x + this->neck.part.to.x, this->neck.part.position.y + this->neck.part.to.y, 5.5 * this->scale, 90.0, PNK };
			this->top = { this->neck.part.position.x + this->neck.part.to.x, this->neck.part.position.y + this->neck.part.to.y + 1.5 * this->scale, 3.0, 90.0, R };
			this->bottom = { this->neck.part.position.x + this->neck.part.from.x, this->neck.part.position.y + this->neck.part.from.y, 1.5 * this->scale, 90.0, DGR };
		}
	};

	struct TORSO {
		TORSO(double x = 0.0, double y = 0.0, double w = 0.0, double h = 0.0) {
			this->part = { x, y, w, h };
			this->weight = 0.0;
		}
		RCT part;
		double weight;
		void _draw(HDC tool) {
			this->part._draw(tool);
		}
	};
	DINT exist;
	double scale, gravity, weight;
	POSITION center, position, mutual;
	DIMENSION border;
	ARM aleft, aright;
	LEG lleft, lright;
	HEAD head;
	TORSO torso;
	COLOR color;
	DICE dice;

	void _form(DINT x, DINT y, COLOR color = R, DIMENSION border = {}) {
		this->border._set(border);
		this->color = color;
		this->position.x = (double)x;
		this->position.y = (double)y;
		this->torso = { (double)x, (double)y, (double)x + 20.0 * this->scale, (double)y + 30.0 * this->scale };
		this->weight += this->torso.weight;
		this->head = { x,y, (this->torso.part.pb.x - this->torso.part.pa.x) / 2.0, this->torso.part.pa.y - (double)y + 2.5 * this->scale, 270.0, 4.0, this->scale};
		this->weight += this->head.weight;
		this->aleft = { 0, 0, this->torso.part.pb.x, this->torso.part.pb.y, 270, 10.0, 7.0, this->scale};
		this->aright = { 0, 0, this->torso.part.pa.x, this->torso.part.pa.y, 270, 10.0, 7.0, this->scale};
		
		this->lleft = { 0, 0, this->torso.part.pc.x, this->torso.part.pc.y, 0, 14.0, 10.0, this->scale };
		this->lright = { 0, 0, this->torso.part.pd.x, this->torso.part.pd.y, 180, 14.0, 10.0, this->scale };
		this->exist = 1;
	}


	void _draw(HDC tool) {
		
		this->torso._draw(tool);
		this->aleft._draw(tool);
		this->lleft._draw(tool);
		this->aright._draw(tool);
		this->lright._draw(tool);
		this->head._draw(tool);

		RCT hb;
		CHART <SINT> *ys = new CHART<SINT>, *xs = new CHART<SINT>, *ws = new CHART<SINT>, *hs = new CHART<SINT>;
		
		*ys << (SINT)(this->head.cranium.part.center.y - this->head.cranium.part.radius);
		*ys << (SINT)(this->aleft.hand.part.center.y - this->aleft.hand.part.radius);
		*ys << (SINT)(this->aleft.elbow.part.center.y - this->aleft.elbow.part.radius);
		*ys << (SINT)(this->aright.hand.part.center.y - this->aright.hand.part.radius);
		*ys << (SINT)(this->aright.elbow.part.center.y - this->aright.elbow.part.radius);
		*ys << (SINT)(this->aright.shoulder.part.center.y - this->aright.shoulder.part.radius);
		*ys << (SINT)(this->lright.foot.part.center.y - this->lright.foot.part.radius);
		*ys << (SINT)(this->lright.knee.part.center.y - this->lright.knee.part.radius);

		*xs << (SINT)(this->aright.hand.part.center.x - this->aright.hand.part.radius);
		*xs << (SINT)(this->aright.elbow.part.center.x - this->aright.elbow.part.radius);
		*xs << (SINT)(this->lright.knee.part.center.x - this->lright.knee.part.radius);
		*xs << (SINT)(this->aright.shoulder.part.center.x - this->aright.shoulder.part.radius);

		*ws << (SINT)(this->lleft.knee.part.center.x + this->lleft.knee.part.radius);
		*ws << (SINT)(this->lleft.foot.part.center.x + this->lleft.foot.part.radius);
		*ws << (SINT)(this->aleft.elbow.part.center.x + this->aleft.elbow.part.radius);
		*ws << (SINT)(this->head.cranium.part.center.x + this->head.cranium.part.radius);
		*ws << (SINT)(this->aleft.shoulder.part.center.x + this->aleft.shoulder.part.radius);
		*ws << (SINT)(this->aleft.hand.part.center.x + this->aleft.hand.part.radius);

		*hs << (SINT)(this->lleft.pelvis.part.center.x + this->lleft.pelvis.part.radius);
		*hs << (SINT)(this->lleft.foot.part.center.y + this->lleft.foot.part.radius);
		*hs << (SINT)(this->lright.foot.part.center.y + this->lright.foot.part.radius);
		
		DINT x, y, w, h;
		x = (DINT)MATH::_cmin(*xs);
		y = (DINT)MATH::_cmin(*ys);
		w = (DINT)MATH::_cmax(*ws);
		h = (DINT)MATH::_cmax(*hs);
		delete[] xs->exist;
		delete[] xs->item;
		delete xs;
		delete[] ys->exist;
		delete[] ys->item;
		delete ys;
		delete[] ws->exist;
		delete[] ws->item;
		delete ws;
		delete[] hs->exist;
		delete[] hs->item;
		delete hs;
		hb = { (double)x, (double)y, (double)w, (double)h, LG };
		hb._draw(tool);

	}


	void _drop() {
	}

	void _animate() {
		this->aright._stretch();
		this->aleft._loosen();
		this->lleft._rotate();
		this->lright._rotate();
		this->head._stretch();
	}

	void _test() {
		this->aleft.gravity = this->dice._droll(0.75, 1.0);
		this->aleft.bottom.angle = this->dice._droll(0.0, 360.0);
		this->aleft.top.angle = this->dice._droll(0.0, 360.0);
		this->aright.gravity = this->dice._droll(0.75, 1.0);
		this->aright.bottom.angle = this->dice._droll(0.0, 360.0);
		this->aright.top.angle = this->dice._droll(0.0, 360.0); std::cout << "ARBA";
	}

	void _gravitate() {
		this->lright._straighten(100.0);
		this->lleft._straighten(80.0);
		this->aleft._straighten(0.0);
		this->aright._straighten(180.0, -1.0);
		this->head._stretch();
		//this->mutual.velocity.y += t
		//this->lright._position()
	}

};

struct YOYO {
	YOYO(double x = 0.0, double y = 0.0, double size = 10, double length = 80.0, double angle = 90.0) {
		this->position = { x, y, 0.0 };
		this->angle = angle;
		this->cord = { 0, 0, x, y, x + (double)size * MATH::_cos((DINT)angle), y + (double)size * MATH::_sin((DINT)angle), B};
		this->spinner = { this->cord.to.x, this->cord.to.y, size, 0 };
		this->length = length;
		this->slack = 0.0;
		this->weight = 0.75;
		this->gravity = 1.0;
		this->force = 0.0;
		this->velocity = 0.0;
		this->hold = 0.0;
	}

	LINE cord;
	CRCL spinner;
	SPOT position;
	double angle, length, hold, force, slack, weight, gravity, velocity;

	void _draw(HDC tool) {
		LINE cord = this->cord;
		cord._draw(tool);
		this->spinner._draw(tool);
	}


	void _spin(double force = 2.0, double hold = 3.5) {

		this->force = force;
		this->hold = hold;
		//this->cord = { 0, 0, this->cord.from.x, this->cord.from.y, this->cord.to.x, this->cord.to.y + (double)force, this->cord.color };
		//this->spinner._set((DINT)this->cord.to.x, (DINT)this->cord.to.y, this->spinner.radius, this->spinner.angle);

	}

	void _lift() {
		if (this->slack >= this->length && this->hold > 0.0) {
			this->hold -= 0.1;
		}
		else{
			if (this->slack < this->length && this->force > 0.0 || this->velocity < 0.0 && this->slack > 0.0) {
this->force -= 0.25;
this->velocity += this->force * (this->weight * this->gravity);
this->slack += this->velocity;
			}
			else {
			this->velocity = -this->velocity;
			}
		}
		if (this->slack < 0.0) {
			this->slack = 0.0;
			this->velocity = 0.0;
			this->force = 0.0;
		}
		if (this->slack < this->length || this->slack > 0.0) {
			this->cord = { 0, 0, this->cord.from.x, this->cord.from.y, this->cord.to.x, this->cord.from.y + this->slack, this->cord.color };
			this->spinner = { this->cord.to.x, this->cord.to.y, this->spinner.radius, this->spinner.angle };
		}

	}
};

struct BALL {
	BALL() {
		this->weight = 0.0;
		this->gravity = 1.0;
		this->wind = 0.0; // this->dice._droll(0.0, 2.5);
		this->friction = 0.0;
		this->momentum = 0.0;
		this->density = 0.0;
		this->identifier = this->dice._roll(1, 9999);
		this->velocity = 0.0;

	}
	BINT identifier;
	POSITION rotational, original;
	CRCL circle;
	double gravity, weight, wind, friction, momentum, density, velocity;
	DICE dice;

	void _create(double x, double y, double radius, double angle, COLOR color = {}) {

		this->circle = { x, y, radius, angle, color };
		this->original.x = this->circle.center.x;
		this->original.y = this->circle.center.y;
		this->weight = this->circle.radius * 0.25;
		this->density = this->weight;
	}


	void _angular(DIMENSION border = {}) {

		this->circle.center.x = this->rotational.velocity.x * MATH::_cos(this->circle.angle, 0.0001) + this->circle.center.x;
		this->circle.center.y = this->rotational.velocity.y * MATH::_sin(this->circle.angle, 0.0001) + this->circle.center.y;

		if (this->circle.angle >= 360.0) {
			this->circle.angle -= 360.0;
		}
		if (this->circle.angle < 0.0) {
			this->circle.angle = 360.0 - this->circle.angle;
		}
		if (this->circle.center.y > (double)border.h - this->circle.radius) {
			this->circle.center.y = (double)border.h - this->circle.radius - 1.0;
			this->circle.angle += 180.0;
			//this->rotational.velocity.y = -(this->rotational.velocity.y * this->gravity * (1.0 - this->friction));
		}
		else {
			if(this->circle.angle < 180 && this->circle.angle > 0.0){
				this->rotational.velocity.y += this->weight * this->gravity;
			}
			else {
				if (this->rotational.velocity.y > 0.0) {
					this->rotational.velocity.y -= this->weight * (this->gravity * 2.0);
					if (this->rotational.velocity.y < 0.0 || this->rotational.velocity.y == 0.0) {
						this->rotational.velocity.y = 0.0;
						this->circle.angle = 90.0;
					}
				}
			}
		}
		if (this->circle.center.y < 0.0 + this->circle.radius) {
			this->circle.center.y = 0.0 + this->circle.radius + 1.0;
			this->circle.angle += 180.0;
			//this->rotational.velocity.y = -(this->rotational.velocity.y * this->gravity * 0.9);
		}

		if (this->circle.center.x > (double)border.w - this->circle.radius) {
			this->circle.center.x = (double)border.w - this->circle.radius - 1.0;
			//this->rotational.velocity.x = -(this->rotational.velocity.x * this->gravity * 0.9);
		}
		if (this->circle.center.x < 0.0 + this->circle.radius) {
			this->circle.center.x = 0.0 + this->circle.radius + 1.0;
			//this->rotational.velocity.x = -(this->rotational.velocity.x * this->gravity * 0.9);
		}


		this->circle = { this->circle.center.x, this->circle.center.y, this->circle.radius, this->circle.angle, this->circle.color };
	}

	void _drop() {
		this->circle.center.y = 25.0 + this->circle.radius;
		this->circle.center.x = this->original.x;
		std::cout << "\n-";
		this->circle.radius = this->dice._droll(10.0, 30.0);
		this->rotational.velocity.y = 0.0;
		this->rotational.velocity.x = this->dice._droll(-10.0, 10.0);
		this->gravity = this->dice._droll(0.5, 1.0);
		this->density = 0.2;
		//this->density = this->dice._droll(0.05, 0.9);
		this->weight = 2.5;
		//this->weight = this->circle.radius * 0.025 / this->density;
		this->friction = this->dice._droll(0.1, 0.9);
		this->velocity = 0;
		//this->wind = this->dice._droll(0.0, 2.5);

	}

	void _naturate(DIMENSION border = {}) {
		if (this->circle.center.y + this->circle.radius <= (double)border.h && this->circle.center.y - this->circle.radius >= 0.0) {
			this->rotational.velocity.y += this->weight * this->gravity;
			this->circle.center.y += this->rotational.velocity.y;
			if (this->circle.center.y > (double)border.h - this->circle.radius) {
				this->circle.center.y = (double)border.h - this->circle.radius;
				this->rotational.velocity.y = -(this->rotational.velocity.y * this->gravity * (1.0 - this->friction));
			}
			if (this->circle.center.y < 0.0 + this->circle.radius) {
				this->circle.center.y = 0.0 + this->circle.radius;
				this->rotational.velocity.y = -(this->rotational.velocity.y * this->gravity * 0.9);
			}
		}
		if (this->circle.center.x >= 0.0 + this->circle.radius && this->circle.center.x <= (double)border.w - this->circle.radius) {
			this->circle.center.x += this->rotational.velocity.x;
			if (this->circle.center.x > (double)border.w - this->circle.radius) {
				this->circle.center.x = (double)border.w - this->circle.radius;
				this->rotational.velocity.x = -(this->rotational.velocity.x * this->gravity * 0.9);
			}
			if (this->circle.center.x < 0.0 + this->circle.radius) {
				this->circle.center.x = 0.0 + this->circle.radius;
				this->rotational.velocity.x = -(this->rotational.velocity.x * this->gravity * 0.9);
			}
			if (this->rotational.velocity.x != 0.0) {
				if (this->rotational.velocity.x > 0.0) {
					this->rotational.velocity.x -= this->density;
					if (this->rotational.velocity.x < 0.0) this->rotational.velocity.x = 0.0;
				}
				else {
					if (this->rotational.velocity.x < 0.0) {
						this->rotational.velocity.x += this->density;
						if (this->rotational.velocity.x > 0.0) this->rotational.velocity.x = 0.0;
					}
				}
				
			}
		}
		this->circle = { this->circle.center.x, this->circle.center.y, this->circle.radius, this->circle.angle, this->circle.color };
	}

	void _draw(HDC tool) {
		this->circle._draw(tool);
	}

	DINT _collision(BALL& ball) {
		double tr = this->circle.radius + ball.circle.radius;
		double distance = MATH::_dabs(this->_distance(ball));
		DINT value = distance <= tr + 1.0;
		if (value) {
			double overlap = tr - distance;
			if (ball.rotational.velocity.y > 0.0) {
				ball.rotational.velocity.y /= 0.2;
			}
			else {
				ball.rotational.velocity.y *= 0.2;
				//ball.rotational.velocity.y = -ball.rotational.velocity.y;
			}
			ball.rotational.velocity.x = MATH::_side(ball.circle.center.x, this->circle.center.x) * (ball.rotational.velocity.y * ball.weight * ball.gravity) - overlap;
			this->rotational.velocity.y = -(this->rotational.velocity.y * 0.2);

		}
		return value;
	}

	double _distance(BALL& ball) {
		double dx = 0.0, dy = 0.0, tr = 0.0;
		dx = MATH::_dabs(this->circle.center.x - ball.circle.center.x);
		dy = MATH::_dabs(this->circle.center.y - ball.circle.center.y);
		return MATH::_srt(dx * dx + dy * dy);
		//return (dx > dy) ? (dx) : (dy);
	}

	void _reverse() {
		this->rotational.velocity.x = -this->rotational.velocity.x;
		this->rotational.velocity.y = -this->rotational.velocity.y;
	}
};

struct FLUID {
	FLUID() {
		this->drops = 1;
	};

	~FLUID() {};

	struct DROP {
		DROP(double x = 0.0, double y = 0.0, COLOR color = {}) {
			this->gravity = 1.0;
			this->velocity = 0.0;
			this->shape = {x, y, this->dice._droll(5.0, 15.0), 180.0, color};
			this->mass = this->dice._droll(0.1, this->shape.radius / 2.0);
			this->unique = 0;
		};
		~DROP() {};
		CRCL shape;
		DICE dice;
		DINT unique;
		SPOT velocity;
		double gravity, mass;


		DINT _collision(DROP drop) {
			double tr = this->shape.radius + drop.shape.radius;
			double dx = MATH::_dabs(this->shape.center.x - drop.shape.center.x);
			double dy = MATH::_dabs(this->shape.center.y - drop.shape.center.y);
			double distance = MATH::_srt(MATH::_dabs(dx * dx - dy * dy));// this->_distance(drop); // sqrtl(dx * dx - dy * dy);
			return distance <= tr + 1.0;
		}

		double _distance(DROP drop) {
			double dx = MATH::_dabs(this->shape.center.x - drop.shape.center.x);
			double dy = MATH::_dabs(this->shape.center.y - drop.shape.center.y);
			return (dx > dy) ? (dx) : (dy);
		}
	};		
	CHART <DROP> drops;
	DIMENSION boundary;

	void _liquid() {
		DROP* l;
		DINT collision;
		for (DINT d = 0; d < drops.length; d++) {
			if (drops.exist[d]) {
				collision = 0;
				//std::cout << "\n>Dropping liquid (" << d << ")";
				l = &drops[d];
				for (DINT e = 0; e < drops.length; e++) {
					if (l->unique != drops[e].unique) {
						collision = l->_collision(drops[e]);
						if(collision) break;
					}
				}
				if (l->shape.center.y < this->boundary.h - l->shape.radius) {
					l->velocity.y += l->mass * l->gravity;
					l->shape.center.y += l->velocity.y;
					if (l->shape.center.y > this->boundary.h - l->shape.radius) l->shape.center.y = this->boundary.h - l->shape.radius;
				}
				if (l->velocity.x > 0.0) l->velocity.x -= 0.1;
				if(collision){
					l->velocity.x += (l->mass * 0.25) * l->gravity;
					l->shape.center.x += l->velocity.x;
				}
			}
		}
	};

	void operator<<(DROP drop) {
		std::cout << "\n>Pouring liquid.";
		DINT found = 0;
		DINT u = 0;
		do {
			found = 0;
			u = drop.dice._roll(1, 999);
			for (DINT d = 0; d < this->drops.length; d++) {
				if (this->drops.exist[d]) {
					if (this->drops[d].unique == u) {
						found = 1;
					}
				}
			}

		} while (found);
		drop.unique = u;
		this->drops << drop;
	};
};
