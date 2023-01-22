
// Modify paths accordingly
#define ENGINE_MAP_DIRECTORY_SOURCES		"../../"
#define ENGINE_MAP_DIRECTORY_SPRITE			"sprites"
#define ENGINE_MAP_DIRECTORY_POLYGON		"polygons"

#define ENGINE_VERSION_MINOR				2
#define ENGINE_VERSION_LESSER				1
#define ENGINE_VERSION_LARGE				4
#define ENGINE_VERSION_MAJOR				0


#include "../../assets/engine.wrapper.h"
#include "../Derox/upload/engine.database.h"
#include "../Derox/upload/engine.creature.h"
#include "../Derox/upload/engine.game.h"



struct ENGINE : drx::ENGINE {
	GAME game;
	void _load() override {
		// Load stuff
		STRING s = ENGINE_MAP_DIRECTORY_SOURCES;
		for (; s._strip('.', '/');) {
			std::filesystem::current_path(std::filesystem::current_path().parent_path());
		}
		if (s.length > 0) {
			std::string p = s.text;
			std::filesystem::current_path(p);
		}
		CODEX();
		this->game._config();


	}
	void _update() override {
		// Do stuff
		if (GAME::selected != -1) {
			GAME::CREATURE c = this->game.map.creature[GAME::selected];
			c._showStats(5, 5);
		}
		if (ENGINE::keyer.mouse.left.down) {

			for (DINT i = 0; i < this->game.map.creature.length; i++) {
				GAME::CREATURE c = this->game.map.creature[i];
				if (MATH::_between(drx::WINDOW::mouse.x, c.position.x, c.position.w)) {
					if (MATH::_between(drx::WINDOW::mouse.y, c.position.y, c.position.h)) {
						GAME::selected = i;
						break;
					}
				}

			}
			if (drx::WINDOW::mouseLast.x != drx::WINDOW::mouse.x) {
				this->game.camera.offset.x -= drx::WINDOW::mouseLast.x - drx::WINDOW::mouse.x;
			}
			if (drx::WINDOW::mouseLast.y != drx::WINDOW::mouse.y) {
				this->game.camera.offset.y -= drx::WINDOW::mouseLast.y - drx::WINDOW::mouse.y;
			}
		}

		if (ENGINE::keyer.mouse.right.down) GAME::selected = -1;

		if (ENGINE::keyer.mouse.up.down) {
			this->game.map.scale -= 1;
			ENGINE::keyer.mouse.up.down = false;
		}
		if (ENGINE::keyer.mouse.down.down) {
			this->game.map.scale += 1;
			ENGINE::keyer.mouse.down.down = false;
		}


		this->game._play();
		this->game.map._paint();
		WRITER::_type("Hello, world!", 25, 25);

	}

};

ENGINE engine;



int main(HINSTANCE hinst) {
	// Width, height, x, y, instance (from main function), name, console, fullscreen
	engine._config(640, 480, 25, 25, hinst, L"Engine", true, false);

	engine._run();

	return 0;
};
