#include "engine.literary.h"

#define ENGINE_MODE_SLEEP					100

#define ENGINE_DATABASE_LIST_LENGTH_MAX		512 // approx. max length, no crashes (512)
#define ENGINE_DATABASE_INDEX_BLOCK_SIZE	8
#define ENGINE_COLOR_MAP_BACKGROUND		BRN
#define ENGINE_COLOR_FACING				BL

#define ENGINE_RESOURCE_AMOUNT				8
#define ENGINE_CREATURE_AMOUNT				5		


#define ENGINE_SPRITE_TEMPLATE			{X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}
#define ENGINE_SPRITE_TEMP_A			{R, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, DGR, X, X, X, X, 	X, X, DGR, GR, DGR, X, X, X, 	X, X, GR, LGR, GR, X, X, X,	 X, X, X, X, X, X, X, X, 	7, 7}
#define ENGINE_SPRITE_TEMP_B			{Y, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, DGR, X, X, X, X, 	X, X, DGR, GR, DGR, X, X, X, 	X, DGR, GR, LGR, GR, DGR, X, X, 	X, DGR, GR, LGR, GR, DGR, X, X, 	X, X, GR, LGR, GR, X, X, X,		X, X, X, X, X, X, X, X, 	7, 7}
#define ENGINE_SPRITE_TEMP_C			{G, X, X, DGR, X, X, X, X, 	X, X, DGR, GR, DGR, X, X, X, 	X, DGR, DGR, GR, DGR, DGR, X, X, 	DGR, DGR, GR, LGR, GR, DGR, DGR, X, 	DGR, GR, GR, LGR, GR, GR, DGR, X, 	DGR, GR, GR, LGR, GR, GR, DGR, X, 	X, DGR, GR, LGR, GR, DGR, X, X,	 X, X, X, X, X, X, X, X, 7, 7}
#define ENGINE_SPRITE_TEMP_D			{BL, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}

#define ENGINE_ANIMATION_TEST			{3, ENGINE_SPRITE_TEMP_A, ENGINE_SPRITE_TEMP_B, ENGINE_SPRITE_TEMP_C, ENGINE_SPRITE_TEMP_D}

#define ENGINE_ANM_TEST					{ENGINE_SPRITE_TEMP_A, ENGINE_SPRITE_TEMP_B, ENGINE_SPRITE_TEMP_C}

// Square
#define ENGINE_MAP_SPRITE_SQUARE_ONE	{R, B, B, B, G, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,		Y, B, B, B, BL, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}
#define ENGINE_MAP_SPRITE_SQUARE_TWO	{BL, B, B, B, R, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,		G, B, B, B, Y, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}
#define ENGINE_MAP_SPRITE_SQUARE_THREE	{Y, B, B, B, BL, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,		R, B, B, B, G, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}
#define ENGINE_MAP_SPRITE_SQUARE_FOUR	{G, B, B, B, Y, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,			B, B, B, B, B, X, X, X,		BL, B, B, B, R, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}
#define ENGINE_MAP_ANIMATION_SQUARE		{ENGINE_MAP_SPRITE_SQUARE_ONE, ENGINE_MAP_SPRITE_SQUARE_TWO, ENGINE_MAP_SPRITE_SQUARE_THREE, ENGINE_MAP_SPRITE_SQUARE_FOUR}

// Defense
#define ENGINE_MAP_SPRITE_DEFENSE		{GR, GR, GR, GR, GR, X, X, X,		GR, DGR, DGR, DGR, GR, X, X, X,	GR, DGR, B, DGR, GR, X, X, X,		X, GR, DGR, GR, X, X, X, X,		X, X, GR, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}

// Offense
#define ENGINE_MAP_SPRITE_OFFENSE_ONE	{X, X, GR, LGR, X, X, X, X,		X, GR, LGR, X, GR, X, X, X,		LGR, X, DGR, DGR, LGR, GR, X, X,	GR, LGR, DGR, DGR, X, LGR, X, X,	X, GR, X, LGR, GR, X, X, X,		X, X, LGR, GR, X, X, X, X,	X, X, X, X, X, X, X, X,		X, X, X, X, X, X, X, X}
#define ENGINE_MAP_SPRITE_OFFENSE_TWO	{X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}
#define ENGINE_MAP_ANIMATION_OFFENSE	{ENGINE_MAP_SPRITE_OFFENSE_ONE}

// Halt
#define ENGINE_MAP_SPRITE_HALT			{X, X, DR, DR, DR, DR, X, X,		X, DR, X, X, X, X, DR, X,	DR, X, R, X, X, X, X, DR,	DR, X, X, R, X, X, X, DR,	DR, X, X, X, R, X, X, DR,	DR, X, X, X, X, R, X, DR,	X, DR, X, X, X, X, DR, X,	X, X, DR, DR, DR, DR, X, X}

// Scythe
#define ENGINE_MAP_SPRITE_SCYTHE		{X, X, X, DGR, DGR, DGR, X, X,		X, DGR, DGR, LGR, LGR, DBR, X, X,		DGR, LGR, LGR, X, X, DBR, X, X,		LGR, X, X, X, DBR, X, X, X,		X, X, X, X, DBR, X, X, X,		X, X, X, DBR, X, X, X, X,	X, X, X, DBR, X, X, X, X,	X, X, X, DBR, X, X, X, X }

// Grass 
#define ENGINE_MAP_SPRITE_PLANT			{X, X, DG, X, X, X, X, X, 	DG, G, X, X, X, X, X, X, 	X, LG, X, X, X, X, X, X, 	BRN, BRN, BRN, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}
#define ENGINE_MAP_SPRITE_PLANT_WATERED	{X, X, DG, X, X, X, X, X, 	DG, G, X, X, X, X, X, X, 	X, LG, X, X, X, X, X, X, 	BRN, BRN, BRN, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}

// Berry
#define ENGINE_MAP_SPRITE_BERRY			{X, R, R, R, X, X, X, X, 	R, DR, DR, DR, R, X, X, X, 	R, DR, DR, R, R, X, X, X, 	R, DR, R, R, R, X, X, X, 	X, R, R, R, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}

// Stone
#define ENGINE_MAP_SPRITE_STONE			{DGR, GR, X, X, X, X, X, X, 	GR, DGR, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X, 	X, X, X, X, X, X, X, X}

// Currency
#define ENGINE_MAP_SPRITE_CURRENCY		{X, X, X, DGR, DGR, X, X, X, 	X, X, DGR, PNK, PNK, DGR, X, X, 	X, DGR, PNK, PNK, PNK, PNK, DGR, X, 	DGR, GR, PNK, PNK, PNK, PNK, GR, DGR, 	DGR, DPNK, GR, GR, GR, GR, DPNK, DGR, 	X, DGR, DPNK, DPNK, DPNK, DPNK, DGR, X, 	X, X, DGR, DPNK, DPNK, DGR, X, X, 	X, X, X, DGR, DGR, X, X, X}



// Mold

#define ENGINE_BIONIC					{0.0001, "Bionic", 0}
#define ENGINE_BIONIC_HEAD				{0.00011, "Head", 4}
#define ENGINE_BIONIC_EYE				{0.000111, "Eye", 2}
#define ENGINE_BIONIC_NOSE				{0.000112, "Nose", 2}
#define ENGINE_BIONIC_MOUTH				{0.000113, "Mouth", 2}
#define ENGINE_BIONIC_ARM				{0.00012, "Arm", 3}
#define ENGINE_BIONIC_HAND				{0.000121, "Hand", 2}
#define ENGINE_BIONIC_FINGER			{0.0001211, "Finger", 2}
#define ENGINE_BIONIC_LEG				{0.00013, "Leg", 3}
#define ENGINE_BIONIC_FOOT				{0.000131, "Foot", 2}
#define ENGINE_BIONIC_TOE				{0.0001311, "Toe", 2}

#define ENGINE_CARCASS					{0.0002, "Carcass", 0, ENGINE_SPRITE_TEMP_C}
#define ENGINE_CARCASS_TISSUE			{0.00021, "Tissue", 2}
#define ENGINE_CARCASS_CELL				{0.000211, "Cell", 1}

#define ENGINE_BOTANY					{0.0003, "Botany", 0}
#define ENGINE_BOTANY_SPROUT			{0.00031, "Sprout", 3}
#define ENGINE_BOTANY_BRANCH			{0.000311, "Branch", 2}
#define ENGINE_BOTANY_BLOOM				{0.0003111, "Bloom", 1}

#define ENGINE_MIRAGE					{0.0004, "Mirage", 0}
#define ENGINE_MIRAGE_WING				{0.00041, "Wing", 3}
//#define ENGINE_MIRAGE_TAIL				{0.00032, "Tail", }


// Dus

#define ENGINE_DUS_SQUARE				{0.0000001, "Square"}
#define ENGINE_DUS_DEFENSE				{0.0000002, "Defense", 2}
#define ENGINE_DUS_OFFENSE				{0.0000003, "Offense", 1}
#define ENGINE_DUS_HALT					{0.0000004, "Halt", 2}
#define ENGINE_DUS_TEST					{0.00000124, "Test", 0}
#define ENGINE_DUS_MOVE					{0.00000123, "Move", 1}


#define ENGINE_TYPE_CREATURE			1010
#define ENGINE_TYPE_RESOURCE			1020
#define ENGINE_TYPE_RESOURCE_PLANT		1021
#define ENGINE_TYPE_RESOURCE_BERRY		1022
#define ENGINE_TYPE_RESOURCE_STONE		1023
#define ENGINE_TYPE_RESOURCE_CURRENCY	1024
#define ENGINE_TYPE_TILE				1030
#define ENGINE_TYPE_TILE_DESOLATE		1031
#define ENGINE_TYPE_TILE_MEADOW			1032
#define ENGINE_TYPE_TILE_SWAMP			1033
#define ENGINE_TYPE_TILE_WATER			1034
#define ENGINE_TYPE_TILE_TEST			1039
#define ENGINE_TYPE_EFFECT				1040

#define ENGINE_D						{0.0000001, "D", ENGINE_DUS_SQUARE, ENGINE_TYPE_CREATURE, ENGINE_MAP_ANIMATION_SQUARE,			2, 5, 5}
#define ENGINE_CREATURE_DEFENSE			{0.0000002, "Defense", ENGINE_DUS_DEFENSE, ENGINE_TYPE_CREATURE, {ENGINE_MAP_SPRITE_DEFENSE},		2, 5, 5}
#define ENGINE_CREATURE_REAPER			{0.0000003, "Reap", ENGINE_DUS_OFFENSE, ENGINE_TYPE_CREATURE, {ENGINE_MAP_SPRITE_SCYTHE},		2, 6, 8}
#define ENGINE_CREATURE_OFFENSE			{0.0000004, "Offense", ENGINE_DUS_OFFENSE, ENGINE_TYPE_CREATURE, ENGINE_MAP_ANIMATION_OFFENSE,	2, 6, 6}
#define ENGINE_CREATURE_HALT			{0.0000005, "Halt", ENGINE_DUS_HALT, ENGINE_TYPE_CREATURE, {ENGINE_MAP_SPRITE_HALT},	2, 8, 8}
#define ENGINE_RESOURCE_PLANT			{0.0000101, "Plant", ENGINE_DUS_DEFENSE, ENGINE_TYPE_RESOURCE_PLANT, {ENGINE_MAP_SPRITE_PLANT},		2, 3, 4, 0}
#define ENGINE_RESOURCE_BERRY			{0.0000102, "Berry", ENGINE_DUS_OFFENSE, ENGINE_TYPE_RESOURCE_BERRY, {ENGINE_MAP_SPRITE_BERRY},		1, 5, 5, 0}
#define ENGINE_RESOURCE_STONE			{0.0000103, "Stone", ENGINE_DUS_DEFENSE, ENGINE_TYPE_RESOURCE_STONE, {ENGINE_MAP_SPRITE_STONE},		2, 2, 2, 0}
#define ENGINE_RESOURCE_CURRENCY		{0.0000, "Currency", ENGINE_DUS_DEFENSE, ENGINE_TYPE_RESOURCE_CURRENCY,{ENGINE_MAP_SPRITE_CURRENCY},		1, 8, 8, 0}
#define ENGINE_DRAW						101
#define ENGINE_SPRITEGRAPH	{}

