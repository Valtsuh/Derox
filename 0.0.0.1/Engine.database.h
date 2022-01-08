#define ENGINE_DATABASE_TYPOGRAPH				{1, {0.0001, 48, '0', 0, 1}, {0.0002, 49, '1', 1, 1}, {0.0003, 50, '2', 2, 1}, {0.0004, 51, '3', 3, 1}, {0.0005, 52, '4', 4, 1}, {0.0006, 53, '5', 5, 1}, {0.0007, 54, '6', 6, 1}, {0.0008, 55, '7', 7, 1}, {0.0009, 56, '8', 8, 1}, {0.001, 57, '9', 9, 1}, {0.0011, 97, 'a', 'A', 1}, {0.0012, 98, 'b', 'B', 1}, {0.0013, 99, 'c', 'C', 1}, {0.0014, 100, 'd', 'D', 1}, {0.0015, 101, 'e', 'E', 1}, {0.0016, 102, 'f', 'F', 1}, {0.0017, 103, 'g', 'G', 1}, {0.0018, 104, 'h', 'H', 1}, {0.0019, 105, 'i', 'I', 1}, {0.002, 106, 'j', 'J', 1}, {0.0021, 107, 'k', 'K', 1}, {0.0022, 108, 'l', 'L', 1}, {0.0023, 109, 'm', 'M', 1}, {0.0024, 110, 'n', 'N', 1}, {0.0025, 111, 'o', 'O', 1}, {0.0026, 112, 'p', 'P', 1}, {0.0027, 113, 'q', 'Q', 1}, {0.0028, 114, 'r', 'R', 1}, {0.0029, 115, 's', 'S', 1}, {0.003, 116, 't', 'T', 1}, {0.0031, 117, 'u', 'U', 1}, {0.0032, 118, 'v', 'V', 1}, {0.0033, 119, 'w', 'W', 1}, {0.0034, 120, 'x', 'X', 1}, {0.0035, 121, 'y', 'Y', 1}, {0.0036, 122, 'z', 'Z', 1}, {0.0037, 44, ',', ';', 1}, {0.0038, 46, '.', ':', 1 }, {0.0039, 32, ' ', ' ', 1}, {0.004, 33, '!', '!', 1}, {0.0041, 63, '?', '?', 1}, {0.0042, 1, '?', 1, 1}}


#define ENGINE_DATABASE_MAX_CHARS				128


#define ENGINE_DATABASE_KEY_UP					0x57
#define ENGINE_DATABASE_KEY_DOWN				0x53
#define ENGINE_DATABASE_KEY_LEFT				0x41
#define ENGINE_DATABASE_KEY_RIGHT				0x44
#define ENGINE_DATABASE_KEY_SELECT				0x46

#define ENGINE_DATABASE_KEY_PUSHED				1
#define ENGINE_DATABASE_KEY_NOT_PUSHED			2

#define ENGINE_DATABASE_DUS_TEST				

#ifdef ENGINE_DATABASE_DUS_TESST
#define ENGINE_DATABASE_DUS_SPEED				5
#define ENGINE_DATABASE_SLEEP					1
#define ENGINE_DATABASE_SLOW_DOWN				120
#define ENGINE_DATABASE_FPS_SMOOTHER			1
#else
#define ENGINE_DATABASE_DUS_SPEED				1
#define ENGINE_DATABASE_SLEEP					0
#define ENGINE_DATABASE_SLOW_DOWN				0
#define ENGINE_DATABASE_FPS_SMOOTHER			0
#endif

#define ENGINE_DATABASE_ARM_HEIGHT				10
#define ENGINE_DATABASE_LEG_HEIGHT				24
#define ENGINE_DATABASE_MOVEMENT_CHANCE			16
	
#define ENGINE_DATABASE_LIMB_CARCASS			{0.00000000, "Sample", {10, 0, 0}			0, 0,			0,	0,		0,	0, 1}
#define ENGINE_DATABASE_LIMB_HEAD				{0.00000001, "Head", {125, 250, 250},		8, 8,			8,  0,		12, 4, 1}
#define ENGINE_DATABASE_LIMB_CHEST				{0.00000002, "Chest", {75, 125, 125},		16, 16,			4,  10,		8, 14, 1}
#define ENGINE_DATABASE_LIMB_ARM_LEFT			{0.00000003, "Arm left", {255, 125, 125},	6, 12,			2, ENGINE_DATABASE_ARM_HEIGHT,		6, ENGINE_DATABASE_ARM_HEIGHT + 4, 1}
#define ENGINE_DATABASE_LIMB_ARM_RIGHT			{0.00000003, "Arm right", {125, 125, 255},	6, 12,			16,	ENGINE_DATABASE_ARM_HEIGHT,		20, ENGINE_DATABASE_ARM_HEIGHT + 4, 1}
#define ENGINE_DATABASE_LIMB_LEG_LEFT			{0.00000004, "Leg left", {255, 50, 50},		8, 14,			4, ENGINE_DATABASE_LEG_HEIGHT,		8, ENGINE_DATABASE_LEG_HEIGHT + 6, 1}
#define ENGINE_DATABASE_LIMB_LEG_RIGHT			{0.00000004, "Leg right", {50, 50, 255},	8, 14,			14, ENGINE_DATABASE_LEG_HEIGHT,		18, ENGINE_DATABASE_LEG_HEIGHT + 6, 1}

#define ENGINE_DATABASE_DUS_APPEARANCES			9
#define ENGINE_DATABASE_DUS_APPEARANCE_CHANCE	8192


#define ENGINE_DATABASE_DUS_SAMPLE				{0.00000101, "Sample", {0, 0, 4, 4}}
#define ENGINE_DATABASE_DUS_NOTHING				{0.00000102, "Nothing", {0, 0, 4, 4}, {25, 25, 250}, {"   Nothing"}}
#define ENGINE_DATABASE_DUS_UNIQUE				{0.00000103, "Unique", {0, 0, 4, 4}, {25, 125, 250}, {"   A unique"}}
#define ENGINE_DATABASE_DUS_OFFENSE				{0.00000104, "Offense", {0, 0, 4, 4}, {25, 50, 175}, {"   An offensive"}}
#define ENGINE_DATABASE_DUS_DEFENSE				{0.00000104, "Defense", {0, 0, 4, 4}, {175, 100, 125}, {"   A defensive"}}
#define ENGINE_DATABASE_DUS_MINE				{0.00000105, "Mine", {250, 125, 16, 16}, {225, 90, 110}, {"   A building"}}

#define ENGINE_DATABASE_INVENTORY				1
#define ENGINE_DATABASE_INVENTORY_SLOTS			4
#define ENGINE_DATABASE_ITEM					0
#define ENGINE_DATABASE_ITEM_CURRENCY			{1, "Currency"}
#define ENGINE_DATABASE_ITEM_			{0.00001001, ""}
#define ENGINE_DATABASE_COLLISION				1